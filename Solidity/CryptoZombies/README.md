# CryptoZombies

Solidity version of the CryptoZombies lessons: a small on-chain game where each zombie is a token you can feed, fight with and transfer. I kept the contract chain and the Hardhat tests. Generated Typechain bindings and `node_modules` are not included.

The contracts inherit in one line, so the last contract exposes everything above it:

`ZombieFactory` (OpenZeppelin `Ownable`) creates a zombie from a name, stores a 16-digit DNA, a level, a cooldown and win/loss counts, and maps each id to an owner.

`ZombieFeeding` can read an external CryptoKitties-style contract (`MockCryptoKitties`) and mix that DNA in. `ZombieRareFeeding` does the same with `MockRareFood`. `ZombieHelper` handles level and cooldown changes. `ZombieAttack` is the fight. `ZombieEquipment` adds gear. `ZombieOwnership` is the transfer layer in the shape of ERC-721: `balanceOf`, `ownerOf`, approvals and `transferFrom`, with a `Transfer` and an `Approval` event.

Each of those steps has a Hardhat test that deploys `ZombieOwnership` (so the whole chain is there) and checks that level: creating a zombie, feeding, attacking, equipment, ownership.

Technologies: Solidity 0.8, OpenZeppelin Ownable, Hardhat, Ethers, Chai.
