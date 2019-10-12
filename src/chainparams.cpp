// Copyright (c) 2013-2019 The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The Rito Core developers
// Copyright (c) 2019 The Colombo Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "arith_uint256.h"

#include <assert.h>

#include "chainparamsseeds.h"

//TODO: Take these out
extern double algoHashTotal[16];
extern int algoHashHits[16];


static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << CScriptNum(0) << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Colombo, the cryptocurrency of the Colombian people, for the Colombian people";
    const CScript genesisOutputScript = CScript() << ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

void CChainParams::TurnOffSegwit() {
	consensus.nSegwitEnabled = false;
}

void CChainParams::TurnOffCSV() {
	consensus.nCSVEnabled = false;
}

void CChainParams::TurnOffBIP34() {
	consensus.nBIP34Enabled = false;
}

void CChainParams::TurnOffBIP65() {
	consensus.nBIP65Enabled = false;
}

void CChainParams::TurnOffBIP66() {
	consensus.nBIP66Enabled = false;
}

bool CChainParams::BIP34() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::BIP65() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::BIP66() {
	return consensus.nBIP34Enabled;
}

bool CChainParams::CSVEnabled() const{
	return consensus.nCSVEnabled;
}


/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 2100000;  //~ 4 yrs at 1 min block time
        consensus.nBIP34Enabled = false; // Enable later.
        consensus.nBIP65Enabled = true; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60;
		consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1814; // Approx 90% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;  //Assets (RIP2)
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1540944000; // Oct 31, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1572480000; // Oct 31, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].bit = 7;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].nStartTime = 1568641754; // Oct 16, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].nTimeout = 1600624800; // Oct 20, 2020
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].nOverrideMinerConfirmationWindow = 2016; // ~1.4 days
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].nOverrideRuleChangeActivationThreshold = 1612; // ~80%

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x000000930ec8e61b2a619fd547745339644df0ad7a1e00850d7365701d25d1b8");

        pchMessageStart[0] = 0x43; // C
        pchMessageStart[1] = 0x4f; // O
        pchMessageStart[2] = 0x4c; // L
        pchMessageStart[3] = 0x4d; // M
        nDefaultPort = 1997;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1570472272, 10018565, 0x1e00ffff, 2, 50 * COIN);
        
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("000000930ec8e61b2a619fd547745339644df0ad7a1e00850d7365701d25d1b8"));
        assert(genesis.hashMerkleRoot == uint256S("266523f8c97b42e93ab9e409333a6dadb5f0bd269e7ecd9c01f350c6ac553795"));

        vSeeds.emplace_back("157.245.106.183", false);
        vSeeds.emplace_back("206.81.25.31", false);
        vSeeds.emplace_back("162.243.173.105", false);

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,28);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,105);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,149);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x05, 0x34, 0xE7, 0xCA};
        base58Prefixes[EXT_SECRET_KEY] = {0x05, 0x34, 0x7E, 0xAC};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fMiningRequiresPeers = true;

        // When adding a checkpoint. Update the default assume valid hash above to speed up sync times
        checkpointData = (CCheckpointData) {
            {
                    { 0, uint256S("000000930ec8e61b2a619fd547745339644df0ad7a1e00850d7365701d25d1b8") },
            }
        };

        chainTxData = ChainTxData{
            // Update as we know more about the contents of the Colombo chain
            1570472272, // * UNIX timestamp of last known number of transactions
            1,          // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            3.1         // * estimated number of transactions per second after that timestamp
        };

        /** CLM Start **/
        // Burn Amounts
        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;

        // Burn Addresses
        strIssueAssetBurnAddress = "CLMissueMainAssetxxxxxxxxxxxYN1zhs";
        strReissueAssetBurnAddress = "CLMreissueMainAssetxxxxxxxxxWBxP73";
        strIssueSubAssetBurnAddress = "CLMissueSubAssetxxxxxxxxxxxxaQLyFA";
        strIssueUniqueAssetBurnAddress = "CLMissueUniqueAssetxxxxxxxxxT58BaD";

        //Global Burn Address
        strGlobalBurnAddress = "CLMburnTheCoinsAddressxxxxxxXnPYsx";

        // DGW Activation
        nDGWActivationBlock = 1;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours
        
    }
};

class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 2100000;  //~ 4 yrs at 1 min block time
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;

        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1310; // Approx 65% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 5;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1533924000; // GMT: Friday, August 10, 2018 6:00:00 PM
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1538351999; // GMT: Sunday, September 30, 2018 11:59:59 PM
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].bit = 7;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].nStartTime = 1568641754; // Oct 16, 2019
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].nTimeout = 1600624800; // Oct 20, 2020
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].nOverrideMinerConfirmationWindow = 2016; // ~1.4 days
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].nOverrideRuleChangeActivationThreshold = 1612; // ~80%

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x63; // c
        pchMessageStart[1] = 0x6f; // o
        pchMessageStart[2] = 0x6c; // l
        pchMessageStart[3] = 0x6d; // m
        nDefaultPort = 1998;
        nPruneAfterHeight = 1000;

        uint32_t nGenesisTime = 1570472618;
        genesis = CreateGenesisBlock(nGenesisTime, 10396180, 0x1e00ffff, 2, 50 * COIN);        

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000000647f4666d492637566072cfe6f9c56744cb34197c88a7febb00b587bd"));
        assert(genesis.hashMerkleRoot == uint256S("266523f8c97b42e93ab9e409333a6dadb5f0bd269e7ecd9c01f350c6ac553795"));

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.emplace_back("157.245.106.183", false);
        

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,87);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCD};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x91};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fMiningRequiresPeers = true;

        checkpointData = (CCheckpointData) {
            {
            }
        };

        chainTxData = ChainTxData{
            // Update as we know more about the contents of the Colombo chain
            1570472618, // * UNIX timestamp of last known number of transactions
            1,          // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            3.1         // * estimated number of transactions per second after that timestamp
        };

        /** CLM Start **/
        // Burn Amounts
        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;

        // Burn Addresses
        strIssueAssetBurnAddress = "c1issueAssetXXXXXXXXXXXXXXXXWPtVdM";
        strReissueAssetBurnAddress = "c1ReissueAssetXXXXXXXXXXXXXXXCiLpn";
        strIssueSubAssetBurnAddress = "c1issueSubAssetXXXXXXXXXXXXXX4aFwE";
        strIssueUniqueAssetBurnAddress = "c1issueUniqueAssetXXXXXXXXXXWhDHmm";

        // Global Burn Address
        strGlobalBurnAddress = "c1burnTheCoinsAddressXXXXXXXcFn2iq";

        // DGW Activation
        nDGWActivationBlock = 200;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours 

    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].bit = 7;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].nOverrideMinerConfirmationWindow = 0; // ~1.4 days
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSET_FIX].nOverrideRuleChangeActivationThreshold = 0; // ~80%

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x72; // r
        pchMessageStart[1] = 0x65; // e
        pchMessageStart[2] = 0x67; // g
        pchMessageStart[3] = 0x74; // t
        nDefaultPort = 1999;
        nPruneAfterHeight = 1000;

        uint32_t nGenesisTime = 1570472635;
        genesis = CreateGenesisBlock(nGenesisTime, 4948104, 0x1e00ffff, 2, 50 * COIN);

        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x000000f34e01d0efd8a95abcf5c1a9a2a121c0f3569de46b3bb2b26872565241"));
        assert(genesis.hashMerkleRoot == uint256S("266523f8c97b42e93ab9e409333a6dadb5f0bd269e7ecd9c01f350c6ac553795"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData) {
            {
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,60);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,197);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,240);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x85, 0xCD};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x33, 0x92};


        /** CLM Start **/
        // Burn Amounts
        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;

        // Burn Addresses
        strIssueAssetBurnAddress = "REGissueMainAssetXXXXXXXXXXXWofRh8";
        strReissueAssetBurnAddress = "REGreissueAssetXXXXXXXXXXXXXSiPbvR";
        strIssueSubAssetBurnAddress = "REGissueSubAssetXXXXXXXXXXXXUjLDkC";
        strIssueUniqueAssetBurnAddress = "REGissueUniqueAssetXXXXXXXXXbruBNC";

        // Global Burn Address
        strGlobalBurnAddress = "REGburnTheCoinsAddressXXXXXXZL2EDP";

        // DGW Activation
        nDGWActivationBlock = 200;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours
        /** CLM End **/
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}

void TurnOffSegwit(){
	globalChainParams->TurnOffSegwit();
}

void TurnOffCSV() {
	globalChainParams->TurnOffCSV();
}

void TurnOffBIP34() {
	globalChainParams->TurnOffBIP34();
}

void TurnOffBIP65() {
	globalChainParams->TurnOffBIP65();
}

void TurnOffBIP66() {
	globalChainParams->TurnOffBIP66();
}
