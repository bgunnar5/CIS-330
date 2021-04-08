#ifndef KCIPHER_H_
#define KCIPHER_H_
#include "cipher.h"
#include "ccipher.h"

using namespace std;

const unsigned int MAX_LENGTH = 100;

/* A class that implements a
   Running key cipher class. It 
   inherts class Cipher */

class KCipher : public Cipher {
    protected:
	// Create a new Cheshire struct to hold new class members
	struct ExtraCheshire;
	ExtraCheshire *grin;

    public:
	KCipher();
	KCipher(string page_one);
	
	// These functions are used in main so we must define them here
	void add_key(string page);
	void set_id(unsigned int id);
	
	/* Encrypt and decrypt behave a little differently than they would for
	   substitution, caesar, and rot13 so we have to overwrite those methods*/
	string encrypt(string raw);
	string decrypt(string enc);
	
	~KCipher();
};

// Helper function header
void removeSpaces(string& str);

#endif

