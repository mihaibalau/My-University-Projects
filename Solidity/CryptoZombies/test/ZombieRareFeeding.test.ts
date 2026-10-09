import { expect } from "chai";
import { ethers } from "hardhat";
import { time } from "@nomicfoundation/hardhat-network-helpers";
import { ZombieOwnership, MockRareFood } from "../typechain-types";
import { HardhatEthersSigner } from "@nomicfoundation/hardhat-ethers/signers";

describe("ZombieRareFeeding", function () {
  let zombieOwnership: ZombieOwnership;
  let mockRareFood: MockRareFood;
  let owner: HardhatEthersSigner;
  let addr1: HardhatEthersSigner;

  beforeEach(async function () {
    [owner, addr1] = await ethers.getSigners();

    const ZombieOwnership = await ethers.getContractFactory("ZombieOwnership");
    zombieOwnership = await ZombieOwnership.deploy() as unknown as ZombieOwnership;

    const MockRareFoodFactory = await ethers.getContractFactory("MockRareFood");
    mockRareFood = await MockRareFoodFactory.deploy() as unknown as MockRareFood;

    await zombieOwnership.setRareFoodContractAddress(await mockRareFood.getAddress());

    await zombieOwnership.connect(owner).createRandomZombie("OwnerZombie");
    await zombieOwnership.connect(addr1).createRandomZombie("Addr1Zombie");
  });

  describe("setRareFoodContractAddress", function () {
    it("Should only allow owner to set rare food address", async function () {
      const newAddress = ethers.Wallet.createRandom().address;

      await expect(
        zombieOwnership.connect(addr1).setRareFoodContractAddress(newAddress)
      ).to.be.reverted;

      await zombieOwnership.connect(owner).setRareFoodContractAddress(newAddress);
    });
  });

  describe("feedOnRare", function () {
    it("Should not allow feeding before cooldown expires", async function () {
      await expect(
        zombieOwnership.connect(owner).feedOnRare(0, 1)
      ).to.be.reverted;
    });

    it("Should feed on rare item and create a new zombie", async function () {
      await time.increase(86400);

      const zombiesBefore = await zombieOwnership.getZombiesByOwner(owner.address);
      expect(zombiesBefore.length).to.equal(1);

      await zombieOwnership.connect(owner).feedOnRare(0, 1);

      const zombiesAfter = await zombieOwnership.getZombiesByOwner(owner.address);
      expect(zombiesAfter.length).to.equal(2);
    });

    it("Should level up the feeding zombie by 2 after rare feeding", async function () {
      await time.increase(86400);

      const zombieBefore = await zombieOwnership.zombies(0);
      const levelBefore = Number(zombieBefore.level);

      await zombieOwnership.connect(owner).feedOnRare(0, 1);

      const zombieAfter = await zombieOwnership.zombies(0);
      expect(Number(zombieAfter.level)).to.equal(levelBefore + 2);
    });

    it("Should trigger cooldown on the zombie after rare feeding", async function () {
      await time.increase(86400);

      await zombieOwnership.connect(owner).feedOnRare(0, 1);

      const zombie = await zombieOwnership.zombies(0);
      const currentTime = await time.latest();

      expect(zombie.readyTime).to.be.gt(currentTime);
    });

    it("Should create new zombie with DNA not ending in 99 (species is rare, not kitty)", async function () {
      await time.increase(86400);

      await zombieOwnership.connect(owner).feedOnRare(0, 1);

      const newZombie = await zombieOwnership.zombies(2);

      expect(Number(newZombie.dna) % 100).to.not.equal(99);
    });

    it("Should only allow owner of zombie to feed on rare", async function () {
      await time.increase(86400);


      await expect(
        zombieOwnership.connect(addr1).feedOnRare(0, 1)
      ).to.be.reverted;
    });

    it("Should not allow feeding again before cooldown after rare feeding", async function () {
      await time.increase(86400);

      await zombieOwnership.connect(owner).feedOnRare(0, 1);

      await expect(
        zombieOwnership.connect(owner).feedOnRare(0, 1)
      ).to.be.reverted;
    });
  });
});