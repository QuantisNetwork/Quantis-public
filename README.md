# QLegacy development tree

TO build use

Build with:  make -j4 -f makefile.unix RELEASE=1

QLegacy is a hybrid PoW/PoS-based cryptocurrency with masternodes.

## PoW
* Algorithm: Scrypt
* PoW Supply: unlimited
* PoW Spacing: 30 Seconds
* PoW Interval: 5 blocks 
* PoW Reward:
    * &le; block 50: 5 QXAN
    * &le; block 555: 1055 QXAN
    * &le; block 1555: 55 QXAN
    * forever:  5 QXAN

## PoS
* PoS Reward:
    * 3 QXAN to masternodes
    * 2 QXAN to staking
* PoS Minimum Age: 24 hours
* PoS Maximum Age: none

## Masternodes
* Masternode Collateral: 5000 QXAN
* Masternode Enable:  block #1000, approximately

## Ports
* P2P Port: 5050
* RPC Port: 5051