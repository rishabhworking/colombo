// Copyright (c)  The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The Rito Core developers
// Copyright (c) 2019 The Colombo Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CLM_CLMCONSENSUS_H
#define CLM_CLMCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_CLM_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/colombo-config.h"
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBCLMCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define CLMCONSENSUS_API_VER 1

typedef enum colomboconsensus_error_t
{
    colomboconsensus_ERR_OK = 0,
    colomboconsensus_ERR_TX_INDEX,
    colomboconsensus_ERR_TX_SIZE_MISMATCH,
    colomboconsensus_ERR_TX_DESERIALIZE,
    colomboconsensus_ERR_AMOUNT_REQUIRED,
    colomboconsensus_ERR_INVALID_FLAGS,
} colomboconsensus_error;

/** Script verification flags */
enum
{
    colomboconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    colomboconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    colomboconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    colomboconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    colomboconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    colomboconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    colomboconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    colomboconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = colomboconsensus_SCRIPT_FLAGS_VERIFY_P2SH | colomboconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               colomboconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | colomboconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               colomboconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | colomboconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int colomboconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, colomboconsensus_error* err);

EXPORT_SYMBOL int colomboconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, colomboconsensus_error* err);

EXPORT_SYMBOL unsigned int colomboconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // CLM_CLMCONSENSUS_H
