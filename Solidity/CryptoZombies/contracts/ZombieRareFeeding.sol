// SPDX-License-Identifier: MIT
pragma solidity ^0.8.24;

import "./ZombieFeeding.sol";

interface RareFoodInterface {
  function getRareGenes(uint256 _id) external view returns (uint256);
}

contract ZombieRareFeeding is ZombieFeeding {

  RareFoodInterface public rareFoodContract;

  function setRareFoodContractAddress(address _address) external onlyOwner {
    rareFoodContract = RareFoodInterface(_address);
  }

  function feedOnRare(uint256 _zombieId, uint256 _itemId) external onlyOwnerOf(_zombieId) {
    Zombie storage myZombie = zombies[_zombieId];
    require(_isReady(myZombie), "Zombie not ready to feed");

    uint256 rareDna = rareFoodContract.getRareGenes(_itemId);
    feedAndMultiply(_zombieId, rareDna, "rare");

    myZombie.level += 2;
  }
}