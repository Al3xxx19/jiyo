// Copyright (c) 2009-2009 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2018 The Jiyo developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x000000122db5880bbf4895ef6d368c86122f3b223957992651657fd60dfa1c26"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1551288600, // * UNIX timestamp of last checkpoint block
    0,      // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    1400        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x01"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1551288600,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256("0x01"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1551288600,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xe1;
        pchMessageStart[1] = 0xf3;
        pchMessageStart[2] = 0xc4;
        pchMessageStart[3] = 0xb5;
        vAlertPubKey = ParseHex("04bfa968a07c80fac1b2d3e7cadc66f11cbd56d05e9daf6a928ad310ad0266d99adc026b8e8023361b78106b748c8cf972c0743c9d3ea6656a3fdf3582507fa9d2");
        nDefaultPort = 35107;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // JIYO starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // JIYO: 1 day
        nTargetSpacing = 1 * 60;  // JIYO: 1 minute
        nMaturity = 9; //99
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 25000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 1;
        nZerocoinStartTime = 1569578400;		/* Fri September 27 10:00:00 UTC 2019 */
        nBlockFirstGoodChecksum = 285600;		/* First block with valid Zerocoin checksums */
        nBlockEnforceSerialRange = 245000;		/* Enforce serial range starting this block */
        nBlockZerocoinV2 = 245000;			/* First mint at block 247434 */
        nEnforceNewSporkKey = 1527822208;		/* Fri Jun  1 05:03:28 CEST 2018: sporks signed after must use the new spork key */
        nRejectOldSporkKey = 1528427008;		/* Fri Jun  8 05:03:28 CEST 2018: after that reject old spork key */

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "Jiyo Coin ReStart Wed, 27 February 2018";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04f57696dc98f0694a8d85fa125be8950b2b780747618eb0d91ead4ba8c694fb813a33e96e2385aa3d65a5e0393dcfae5213097fa93943335a6aadb945dce928bc") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1551288600;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 500537;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000000122db5880bbf4895ef6d368c86122f3b223957992651657fd60dfa1c26"));
        assert(genesis.hashMerkleRoot == uint256("0x0a4543d455cc9931ba4b86519794b21be93f2ffceb4683104571b65adeb38547"));

        //vSeeds.push_back(CDNSSeedData("79.115.42.16", "79.115.42.16")); //fixed ip
        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 43);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 20);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x21)(0x69)(0x3E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x21)(0xAE)(0xF1).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0422a02c1aab67fc545441b24b147fe894192e1efcac33f35b7192618c2e26f43f061268cfc393dcfb82dfbecf41ef1b1cf09b47561b60246268f62e03c038a412";
        strSporkKeyOld = "0422a02c1aab67fc545441b24b147fe894192e1efcac33f35b7192618c2e26f43f061268cfc393dcfb82dfbecf41ef1b1cf09b47561b60246268f62e03c038a412";
        strObfuscationPoolDummyAddress = "JZtNU63X1ct8bJULwCPZrh4oF8AE62CVJ1";
        nStartMasternodePayments = 1525192183; // Tue May  1 18:29:43 CEST 2018
        nRequiredMasternodeCollateral = 5000 * COIN; // Masternode collateral amount

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; // high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; // the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; // full security level for accumulators
        nZerocoinHeaderVersion = 4; // block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 240; //The required confirmations for a zjiyo to be stakable

        nBudget_Fee_Confirmations = 6; // number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0x64;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x65;
        vAlertPubKey = ParseHex("04af11a9a9b7294f4b33c3c2218bc4c8a07ad1ca6730694231fc8272d2dcbf91b0bee2504930845481ae9e48dc68fb3f988f9c1b4edc349576cba0045fc697f45f");
        nDefaultPort = 56123;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // JIYO: 1 day
        nTargetSpacing = 1 * 60;  // JIYO: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197;
        nMaxMoneyOut = 25000000 * COIN;
        nZerocoinStartTime = 1541797200;		/* Fri Nov  9 21:00:00 UTC 2018 */
        nBlockFirstGoodChecksum = 27000;		/* First block with valid Zerocoin checksums */
        nBlockEnforceSerialRange = 250;			/* Enforce serial range starting this block */
        nBlockZerocoinV2 = 250;				/* First mint at block 314 */
        nEnforceNewSporkKey = 1540760400;		/* Sun Oct 28 21:00:00 UTC 2018: sporks signed after must use the new spork key */
        nRejectOldSporkKey = 1541325600;		/* Sun Nov  4 21:00:00 UTC 2018: after that reject old spork key */

        /* Testnet genesis block. */
        genesis.nTime = 1551288600;			/* Testnet started: Fri Oct 26 21:00:00 UTC 2018 */
        genesis.nNonce = 1745260;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000000122db5880bbf4895ef6d368c86122f3b223957992651657fd60dfa1c26"));

        vFixedSeeds.clear();
        vSeeds.clear();

        //vSeeds.push_back(CDNSSeedData("seed1.testnet.jiyo.site", "seed1.testnet.jiyo.site"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23);  // Testnet jiyo addresses start with 'a'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);  // Testnet jiyo script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet Jiyo BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet Jiyo BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet Jiyo BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "0422a02c1aab67fc545441b24b147fe894192e1efcac33f35b7192618c2e26f43f061268cfc393dcfb82dfbecf41ef1b1cf09b47561b60246268f62e03c038a412";
        strSporkKeyOld = "0422a02c1aab67fc545441b24b147fe894192e1efcac33f35b7192618c2e26f43f061268cfc393dcfb82dfbecf41ef1b1cf09b47561b60246268f62e03c038a412";
        strObfuscationPoolDummyAddress = "acW3shX2oxMLykakdi9zvjvaX6NBCyVLTw";
        nStartMasternodePayments = 1540587600; // Fri Oct 26 21:00:00 UTC 2018
        nRequiredMasternodeCollateral = 5000 * COIN; // Masternode collateral amount
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x65;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x65;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // JIYO: 1 day
        nTargetSpacing = 1 * 60;        // JIYO: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1551288600;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 500537;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 57123;
        assert(hashGenesisBlock == uint256("0x000000122db5880bbf4895ef6d368c86122f3b223957992651657fd60dfa1c26"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 58123;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
