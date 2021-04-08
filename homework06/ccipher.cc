#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"


// -------------------------------------------------------
// Caesar Cipher implementation

// Reference the struct defined in Cipher
struct Cipher::CipherCheshire {
   string cipher_alpha; 
};

CCipher::CCipher() {
    // Start with the alphabet in order
    string cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
    
    // Rotate by 0 for the default
    rotate_string(cipher_alpha, 0);
    
    // Assign the cipher alphabet to cipher_alpha in the Cheshire
    smile->cipher_alpha = cipher_alpha;
}

CCipher::CCipher(int shift) {
    // Check to make sure shift is positive
    if (shift < 0) {
    	cout << "Error: Caesar cipher is less than 0" << endl;
	exit(EXIT_FAILURE);
    }
    
    // Start with the alphabet in order
    string cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
    
    // Rotate by the shift parameter
    rotate_string(cipher_alpha, shift);
    
    // Assign the cipher alphabet to cipher_alpha in the Cheshire
    smile->cipher_alpha = cipher_alpha;
}

// Destructor handled in cipher.cc
CCipher::~CCipher() {
}

// -------------------------------------------------------


// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{
    // Shift rot number of times
    while (rot) {
	// Move the head of the in_str to the end
    	in_str[ALPHABET_SIZE] = in_str[0];
	
	// Loop through and shift the in_str down one
	for (unsigned int i = 0; i < ALPHABET_SIZE; i++) {
	    in_str[i] = in_str[i + 1];
	}
	
	// Decrement rot
	rot--;
    }
}
