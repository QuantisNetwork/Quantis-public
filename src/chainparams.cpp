// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xF2;
        pchMessageStart[1] = 0xEB;
        pchMessageStart[2] = 0xA2;
        pchMessageStart[3] = 0xC9;
        vAlertPubKey = ParseHex("0413eaacfe9137bb6593efaec62cf84d8d27282dcaef87cfc45d2207f34229434c3522f94da38d8dd326b2b6084575ffc1911fcdbe637fcfe7be46d0b9456d2a0d");        
        nDefaultPort = 5050;
        nRPCPort = 5051;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "George Soros Makes U-turn, Set to Trade Cryptocurrency";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1524632400, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1524632400;
        genesis.nBits    = 0x1e0ffff0; 
        genesis.nNonce   = 1120641;

		
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000202a7ef367ae64829dd6204888e6d898acfaf8a3645d485f8aafd8c5290"));
        assert(genesis.hashMerkleRoot == uint256("0x4f323fcfc48ac144c35da86c1adbb946eef1905896eb2bd31532529131fe0873"));

        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,58);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,120);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,10);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,10);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("nodes.docrypto.com","quan.nodes.docrypto.com"));
        vSeeds.push_back(CDNSSeedData("quantis-coin.io","quantis-coin.io"));
        vSeeds.push_back(CDNSSeedData("quantis.syshost.io","quantis.syshost.io"));
        vSeeds.push_back(CDNSSeedData("backup.syshost.io","backup.syshost.io"));

        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        //strSporkKey = "04815fc918ae312c96ea426062e38fb9fb8b6b979b4fb2cd18e1ee7be2ff46b7fd0230e958205acb76ae7b84acc25ec3f61621baf6a23e048568195525f43dedd6";
        //strMasternodePaymentsPubKey = "04815fc918ae312c96ea426062e38fb9fb8b6b979b4fb2cd18e1ee7be2ff46b7fd0230e958205acb76ae7b84acc25ec3f61621baf6a23e048568195525f43dedd6";
        strDarksendPoolDummyAddress = "QMYeJZvXekNbohxjLL9GGLF9eSLuRzEg77";
        nLastPOWBlock = 2147483647;
        nPOSStartBlock = 100;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xF2;
        pchMessageStart[1] = 0xEB;
        pchMessageStart[2] = 0xA2;
        pchMessageStart[3] = 0xCA;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0495c1153a4b833bc309fd145955e851b73d424967065d547b1a051d7de0e30cc5d3866270a79b839ce0221b8ef1eff3873e83499ee6336725b1abe8be1e4c6af0");
        nDefaultPort = 5150;
        nRPCPort = 5151;
        strDataDir = "testnet";

        const char* pszTimestamp = "George Soros Makes U-turn, Set to Trade Cryptocurrency";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1524646801, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1524646801;
        genesis.nBits    = 0x1e0ffff0; 
        genesis.nNonce   = 3106845;
        // Modify the testnet genesis block so the timestamp is valid for a later start.
		
		//hashGenesisBlock = uint256("0x01");
        if (false && (genesis.GetHash() != hashGenesisBlock))
        {
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "testnet.genesis : \n" << genesis.ToString() << endl;
            cout << "testnet.genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "testnet.genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "testnet.genesis.nTime: " << genesis.nTime << endl;
            cout << "testnet.genesis.nNonce: " << genesis.nNonce << endl;
            printf("testnet.genesis : %s\n", genesis.ToString().c_str());
            printf("testnet.genesis.GetHash(): %s\n", genesis.GetHash().ToString().c_str());
            printf("testnet.genesis.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
            printf("testnet.genesis.nTime: %u\n", genesis.nTime);
            printf("testnet.genesis.nNonce: %u\n", genesis.nNonce);
        }

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x000009edfc36c39b4c30c3948db2940a991d00655f19887ce9b546cda804a847"));
        assert(genesis.hashMerkleRoot == uint256("0x1de747b91e4038095aadecaf25ffbbd69b4550b8de124850b3f7e9f2294e3d04"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,60);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,122);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,13);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,13);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
