// SPDX-License-Identifier: MIT
pragma solidity ^0.8.24;

import "./ZombieAttack.sol";

contract ZombieEquipment is ZombieAttack {

  uint256 public armorPrice = 0.01 ether;
  mapping (uint256 => uint8) public zombieArmor;

  function setArmorPrice(uint256 _price) external onlyOwner {
    armorPrice = _price;
  }

  function buyArmor(uint256 _zombieId) external payable onlyOwnerOf(_zombieId) {
    require(msg.value == armorPrice, "Incorrect ETH value");
    zombieArmor[_zombieId] += 1;
  }

  function getAttackBonus(uint256 _zombieId) public view returns (uint256) {
    uint256 bonus = uint256(zombieArmor[_zombieId]) * 5;
    if (bonus > 25) {
      bonus = 25;
    }
    return bonus;
  }

  function attackWithArmor(uint256 _zombieId, uint256 _targetId) external onlyOwnerOf(_zombieId) {
    Zombie storage myZombie = zombies[_zombieId];
    require(_isReady(myZombie), "Zombie not ready to attack");
    Zombie storage enemyZombie = zombies[_targetId];

    uint256 bonus = getAttackBonus(_zombieId);
    uint256 rand = randMod(100);

    uint256 effectiveProb = attackVictoryProbability + bonus;
    if (effectiveProb > 100) {
      effectiveProb = 100;
    }

    if (rand <= effectiveProb) {
      myZombie.winCount++;
      myZombie.level++;
      enemyZombie.lossCount++;
      feedAndMultiply(_zombieId, enemyZombie.dna, "zombie");
    } else {
      myZombie.lossCount++;
      enemyZombie.winCount++;

      if (zombieArmor[_zombieId] > 0) {
        zombieArmor[_zombieId] -= 1;
      }

      _triggerCooldown(myZombie);
    }
  }
}