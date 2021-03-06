// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Tezos/Address.h"
#include "HDWallet.h"
#include "HexCoding.h"
#include "PrivateKey.h"
#include "Tezos/BinaryCoding.h"

#include <TrustWalletCore/TWCoinType.h>

#include <gtest/gtest.h>
#include <string>
#include <array>

using namespace TW;
using namespace TW::Tezos;

TEST(TezosAddress, ForgeBoolTrue) {
    auto expected = "ff";

    auto output = forgeBool(true);

    ASSERT_EQ(output, expected);
}

TEST(TezosAddress, ForgeBoolFalse) {
    auto expected = "00";

    auto output = forgeBool(false);

    ASSERT_EQ(output, expected);
}

TEST(TezosAddress, forge_tz1) {
    auto input = Address("tz1eZwq8b5cvE2bPKokatLkVMzkxz24z3Don");
    auto expected = "0000cfa4aae60f5d9389752d41e320da224d43287fe2";

    ASSERT_EQ(input.forge(), expected);
}

TEST(TezosAddress, forge_tz2) {
    auto input = Address("tz2Rh3NYeLxrqTuvaZJmaMiVMqCajeXMWtYo");
    auto expected = "0001be99dd914e38388ec80432818b517759e3524f16";

    ASSERT_EQ(input.forge(), expected);
}

TEST(TezosAddress, forge_tz3) {
    auto input = Address("tz3RDC3Jdn4j15J7bBHZd29EUee9gVB1CxD9");
    auto expected = "0002358cbffa97149631cfb999fa47f0035fb1ea8636";

    ASSERT_EQ(input.forge(), expected);
}

TEST(TezosAddress, forge_KT1) {
    auto input = Address("KT1HiGcq47Yek7dcre7So2yfWTLU83FTBaf1");
    auto expected = "0164244bbdc7790d7896b6a52ac49802cfe4eafc4b00";

    ASSERT_EQ(input.forge(), expected);
}

TEST(TezosAddress, isInvalid) {
    std::array<std::string, 3> invalidAddresses {
      "NmH7tmeJUmHcncBDvpr7aJNEBk7rp5zYsB1qt", // Invalid prefix, valid checksum
      "tz1eZwq8b5cvE2bPKokatLkVMzkxz24z3AAAA", // Valid prefix, invalid checksum
      "1tzeZwq8b5cvE2bPKokatLkVMzkxz24zAAAAA"  // Invalid prefix, invalid checksum
    };

    for (std::string address : invalidAddresses) {
        ASSERT_FALSE(Address::isValid(address));
    }
}

TEST(TezosAddress, isValid) {
    auto address = "tz1d1qQL3mYVuiH4JPFvuikEpFwaDm85oabM";
    ASSERT_TRUE(Address::isValid(address));
}

TEST(TezosAddress, string) {
    auto addressString = "tz1d1qQL3mYVuiH4JPFvuikEpFwaDm85oabM";
    auto address = Address(addressString);
    ASSERT_EQ(address.string(), addressString);
}

TEST(TezosAddress, PublicKeyInit) {
    std::array<uint8_t, 33> bytes {1, 254, 21, 124, 200, 1, 23, 39, 147, 108, 89, 47, 133, 108, 144, 113, 211, 156, 244, 172, 218, 223, 166, 215, 100, 53, 228, 97, 156, 157, 197, 111, 99,};
    const auto publicKey = PublicKey(bytes);
    auto address = Address(publicKey);

    auto expected = "tz1cG2jx3W4bZFeVGBjsTxUAG8tdpTXtE8PT";
    ASSERT_EQ(address.string(), expected);
}
