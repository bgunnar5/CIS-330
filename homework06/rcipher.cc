#include <string>
#include <iostream>
#include "rcipher.h"

// -------------------------------------------------------
// ROT13 Cipher implementation
// -------------------------------------------------------

// Reference the Cheshire struct defined in Cipher
struct Cipher::CipherCheshire {
    string cipher_alpha;
};

// Use CCipher's constructor with a shift of 13
RCipher::RCipher() : CCipher(13) {
}

// Destructor handled in cipher.cc
RCipher::~RCipher() {
}
