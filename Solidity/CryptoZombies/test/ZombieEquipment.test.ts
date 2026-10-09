import { expect } from "chai";
import { ethers } from "hardhat";
import { time } from "@nomicfoundation/hardhat-network-helpers";
import { ZombieOwnership } from "../typechain-types";
import { HardhatEthersSigner } from "@nomicfoundation/hardhat-ethers/signers";

describe("ZombieEquipment", function () {
  let zombieOwnership: ZombieOwnership;
  let owner: HardhatEthersSigner;
  let addr1: HardhatEthersSigner;
  let armorPrice: bigint;

  beforeEach(async function () {
    [owner, addr1] = await ethers.getSigners();

    const ZombieOwnership = await ethers.getContractFactory("ZombieOwnership");
    zombieOwnership = await ZombieOwnership.deploy() as unknown as ZombieOwnership;

    armorPrice = await zombieOwnership.armorPrice();

    await zombieOwnership.connect(owner).createRandomZombie("OwnerZombie");
    await zombieOwnership.connect(addr1).createRandomZombie("Addr1Zombie");
  });

  describe("setArmorPrice", function () {
    it("Should only allow owner to set armor price", async function () {
      await expect(
        zombieOwnership.connect(addr1).setArmorPrice(ethers.parseEther("0.02"))
      ).to.be.reverted;
    });

    it("Should allow owner to update armor price", async function () {
      const newPrice = ethers.parseEther("0.05");
      await zombieOwnership.connect(owner).setArmorPrice(newPrice);

      const updatedPrice = await zombieOwnership.armorPrice();
      expect(updatedPrice).to.equal(newPrice);
    });
  });

  describe("buyArmor", function () {
    it("Should revert if wrong ETH value is sent", async function () {
      await expect(
        zombieOwnership.connect(owner).buyArmor(0, { value: armorPrice - 1n })
      ).to.be.revertedWith("Incorrect ETH value");
    });

    it("Should revert if too much ETH is sent", async function () {
      await expect(
        zombieOwnership.connect(owner).buyArmor(0, { value: armorPrice + 1n })
      ).to.be.revertedWith("Incorrect ETH value");
    });

    it("Should only allow owner of zombie to buy armor", async function () {

      await expect(
        zombieOwnership.connect(addr1).buyArmor(0, { value: armorPrice })
      ).to.be.reverted;
    });

    it("Should increment armor count when buying armor", async function () {
      await zombieOwnership.connect(owner).buyArmor(0, { value: armorPrice });

      const armor = await zombieOwnership.zombieArmor(0);
      expect(armor).to.equal(1);
    });

    it("Should allow buying multiple armors for the same zombie", async function () {
      await zombieOwnership.connect(owner).buyArmor(0, { value: armorPrice });
      await zombieOwnership.connect(owner).buyArmor(0, { value: armorPrice });
      await zombieOwnership.connect(owner).buyArmor(0, { value: armorPrice });

      const armor = await zombieOwnership.zombieArmor(0);
      expect(armor).to.equal(3);
    });

    it("Should accumulate ETH in the contract when buying armor", async function () {
      await zombieOwnership.connect(owner).buyArmor(0, { value: armorPrice });

      const contractBalance = await ethers.provider.getBalance(
        await zombieOwnership.getAddress()
      );
      expect(contractBalance).to.equal(armorPrice);
    });
  });

  describe("getAttackBonus", function () {
    it("Should return 0 bonus when zombie has no armor", async function () {
      const bonus = await zombieOwnership.getAttackBonus(0);
      expect(bonus).to.equal(0);
    });

    it("Should return 5% bonus per armor piece", async function () {
      await zombieOwnership.connect(owner).buyArmor(0, { value: armorPrice });
      expect(await zombieOwnership.getAttackBonus(0)).to.equal(5);

      await zombieOwnership.connect(owner).buyArmor(0, { value: armorPrice });
      expect(await zombieOwnership.getAttackBonus(0)).to.equal(10);

      await zombieOwnership.connect(owner).buyArmor(0, { value: armorPrice });
      expect(await zombieOwnership.getAttackBonus(0)).to.equal(15);
    });

    it("Should cap bonus at 25% regardless of armor count", async function () {
      for (let i = 0; i < 10; i++) {
        await zombieOwnership.connect(owner).buyArmor(0, { value: armorPrice });
      }

      const bonus = await zombieOwnership.getAttackBonus(0);
      expect(bonus).to.equal(25);
    });

    it("Should hit the cap at exactly 5 armor pieces", async function () {
      for (let i = 0; i < 5; i++) {
        await zombieOwnership.connect(owner).buyArmor(0, { value: armorPrice });
      }

      const bonus = await zombieOwnership.getAttackBonus(0);
      expect(bonus).to.equal(25);
    });
  });

  describe("attackWithArmor", function () {
    it("Should revert if zombie is not ready", async function () {

      await expect(
        zombieOwnership.connect(owner).attackWithArmor(0, 1)
      ).to.be.revertedWith("Zombie not ready to attack");
    });

    it("Should only allow owner of zombie to attack", async function () {
      await time.increase(86400);

      await expect(
        zombieOwnership.connect(addr1).attackWithArmor(0, 1)
      ).to.be.reverted;
    });

    it("Should update win+loss count after attack (result is random)", async function () {
      await time.increase(86400);

      const zombieBefore = await zombieOwnership.zombies(0);
      const totalBefore = Number(zombieBefore.winCount) + Number(zombieBefore.lossCount);

      await zombieOwnership.connect(owner).attackWithArmor(0, 1);

      const zombieAfter = await zombieOwnership.zombies(0);
      const totalAfter = Number(zombieAfter.winCount) + Number(zombieAfter.lossCount);

      expect(totalAfter).to.equal(totalBefore + 1);
    });

    it("Should consume one armor piece on loss", async function () {

      await zombieOwnership.connect(owner).buyArmor(0, { value: armorPrice });
      const armorBefore = Number(await zombieOwnership.zombieArmor(0));
      expect(armorBefore).to.equal(1);

      await time.increase(86400);

      await zombieOwnership.connect(owner).attackWithArmor(0, 1);

      const zombieAfter = await zombieOwnership.zombies(0);
      const armorAfter = Number(await zombieOwnership.zombieArmor(0));

      const totalCount = Number(zombieAfter.winCount) + Number(zombieAfter.lossCount);
      expect(totalCount).to.equal(1);

      if (Number(zombieAfter.lossCount) > 0) {
        expect(armorAfter).to.equal(armorBefore - 1);
      } else {
        expect(armorAfter).to.equal(armorBefore);
      }
    });

    it("Should not go below 0 armor when losing without armor", async function () {
      await time.increase(86400);

      await zombieOwnership.connect(owner).attackWithArmor(0, 1);

      const armor = await zombieOwnership.zombieArmor(0);

      expect(armor).to.be.gte(0);
    });
  });

  describe("withdraw (armor fees)", function () {
    it("Should allow owner to withdraw accumulated armor fees", async function () {
      await zombieOwnership.connect(owner).buyArmor(0, { value: armorPrice });

      const ownerBalanceBefore = await ethers.provider.getBalance(owner.address);
      const tx = await zombieOwnership.connect(owner).withdraw();
      const receipt = await tx.wait();
      const gasUsed = receipt!.gasUsed * receipt!.gasPrice;
      const ownerBalanceAfter = await ethers.provider.getBalance(owner.address);


      expect(ownerBalanceAfter).to.be.gt(ownerBalanceBefore - gasUsed);
    });
  });
});