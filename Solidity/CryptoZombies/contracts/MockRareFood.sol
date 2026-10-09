// SPDX-License-Identifier: MIT
pragma solidity ^0.8.24;

contract MockRareFood {
  function getRareGenes(uint256 _id) external pure returns (uint256) {
    uint256 baseGenes = 987654321098765400;
    if (_id > 0) {
      baseGenes = baseGenes + _id;
    }
    return baseGenes;
  }
}