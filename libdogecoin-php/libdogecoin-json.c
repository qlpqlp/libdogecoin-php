// LibDogecoin 0.1.2
#include "libdogecoin.h"
#include <stdio.h>
#include <string.h>

//#define PRIVKEYWIFLEN 51 //WIF length for uncompressed keys is 51 and should start with Q. This can be 52 also for compressed keys. 53 internally to lib (+stringterm)
#define PRIVKEYWIFLEN 53 //Function takes 53 but needs to be fixed to take 51.

//#define MASTERKEYLEN 111 //should be chaincode + privkey; starts with dgpv51eADS3spNJh8 or dgpv51eADS3spNJh9 (112 internally including stringterm? often 128. check this.)
#define MASTERKEYLEN 128 // Function expects 128 but needs to be fixed to take 111.

//#define PUBKEYLEN 34 //our mainnet addresses are 34 chars if p2pkh and start with D.  Internally this is cited as 35 for strings that represent it because +stringterm.
#define PUBKEYLEN 35 // Function expects 35, but needs to be fixed to take 34.

// Example of how to use libdogecoin API functions:
// gcc ./libdogecoin-php/libdogecoin-json.c -I./include -L./lib -ldogecoin -o ./libdogecoin-php/libdogecoin-json-php

int main(int argc, char *argv[]) {
	dogecoin_ecc_start();

	char wif_privkey[PRIVKEYWIFLEN];
	char p2pkh_pubkey[PUBKEYLEN];
	char wif_master_privkey[MASTERKEYLEN];
	char p2pkh_master_pubkey[PUBKEYLEN];
	char p2pkh_child_pubkey[PUBKEYLEN];
	
	// JSON keypair generation
   if (strcmp(argv[1], "generatePrivPubKeypair") == 0){
		if (generatePrivPubKeypair(wif_privkey, p2pkh_pubkey, 0)) {
			printf("{\"private\":\"%s\",\"public\":\" %s\"}", wif_privkey, p2pkh_pubkey);
		} else {
			printf("{\"error\":\"1\"}");
			return -1;
		}
    };


    if (strcmp(argv[1], "generateHDMasterPubKeypair") == 0){
    	if (generateHDMasterPubKeypair(wif_master_privkey, p2pkh_master_pubkey, 0)) {
    		printf("{\"private\":\"%s\",\"public\":\" %s\"}", wif_master_privkey, p2pkh_master_pubkey);
		} else {
			printf("{\"error\":\"1\"}");
			return -1;
		}		
    }


    if (strcmp(argv[1], "generateDerivedHDPubkey") == 0){
    	if (generateDerivedHDPubkey((const char*)wif_master_privkey, (char*)p2pkh_child_pubkey)) {
    		printf("{\"private\":\"%s\",\"public\":\" %s\"}", wif_master_privkey, p2pkh_child_pubkey);
		} else {
			printf("{\"error\":\"1\"}");
			return -1;
		}		
    }


  // keypair verification

      //argv[1] = command
      //argv[2] = privat key
      //argv[3] = public key

    if (strcmp(argv[1], "verifyPrivPubKeypair") == 0){
    	if (verifyPrivPubKeypair(argv[2], argv[3], 0)) {
            printf("{\"valid\":\"true\"}");
    	}
    	else {
            printf("{\"valid\":\"false\"}");
			return -1;
    	}
    }

    if (strcmp(argv[1], "verifyHDMasterPubKeypair") == 0){
    	if (verifyHDMasterPubKeypair(argv[2], argv[3], 0)) {
            printf("{\"valid\":\"true\"}");
    	}
    	else {
            printf("{\"valid\":\"false\"}");
			return -1;			
    	}
    }

  	// address verification

    //argv[1] = command
    //argv[2] = dp2pkh public key

    if (strcmp(argv[1], "verifyP2pkhAddress") == 0){
    	if (verifyP2pkhAddress(argv[2], strlen(argv[2]))) {
            printf("{\"valid\":\"true\"}");
    	}
    	else {
            printf("{\"valid\":\"false\"}");
			return -1;			
    	}
    }

	//To Do
	// verifyP2pkhAddress(p2pkh_master_pubkey, strlen(p2pkh_master_pubkey) //printf("Address %s is valid for mainnet 8.\n\n", p2pkh_master_pubkey);	

	// printf("\n\nBEGIN HD ADDRESS DERIVATION EXAMPLE:\n\n");
	// size_t extoutsize = 112;
	// char* extout = dogecoin_char_vla(extoutsize);
	// char* masterkey_main_ext = "dgpv51eADS3spNJh8h13wso3DdDAw3EJRqWvftZyjTNCFEG7gqV6zsZmucmJR6xZfvgfmzUthVC6LNicBeNNDQdLiqjQJjPeZnxG8uW3Q3gCA3e";	
	// getDerivedHDAddress(masterkey_main_ext, 0, false, 0, extout, true)
	// printf("Derived HD Addresses:\n%s\n%s\n\n", extout, "dgpv5BeiZXttUioRMzXUhD3s2uE9F23EhAwFu9meZeY9G99YS6hJCsQ9u6PRsAG3qfVwB1T7aQTVGLsmpxMiczV1dRDgzpbUxR7utpTRmN41iV7");

	// getDerivedHDAddressByPath(masterkey_main_ext, "m/44'/3'/0'/0/0", extout, true)
	// printf("Derived HD Addresses:\n%s\n%s\n", extout, "dgpv5BeiZXttUioRMzXUhD3s2uE9F23EhAwFu9meZeY9G99YS6hJCsQ9u6PRsAG3qfVwB1T7aQTVGLsmpxMiczV1dRDgzpbUxR7utpTRmN41iV7");
	// dogecoin_free(extout);

	// build transaction

    //argv[1] = command
    //argv[2] = hash_doge (tx hash with doge)
    //argv[3] = external_p2pkh_addr
    //argv[4] = 5.0 (doge to send)
    //argv[5] = 0.00226 (fees)
    //argv[6] = 12 (tx index)
    //argv[7] = mypubkey
    //argv[8] = myscriptpubkey
    //argv[9] = myprivkey

    if (strcmp(argv[1], "start_transaction") == 0){

    	int idx = start_transaction();
        add_utxo(idx, argv[2], 1);
        add_output(idx, argv[3], argv[4]);
        finalize_transaction(idx, argv[3], argv[5], argv[6], argv[7]);
		// To Do
		// save the finalized unsigned transaction to a new index in the hash table
		// int idx2 = store_raw_transaction(finalize_transaction(idx, external_p2pkh_addr, "0.00226", "12", mypubkey));		
        sign_transaction(idx, argv[8], argv[9]);
        printf("{\"rawtx\":\"%s\"}", get_raw_transaction(idx));
		remove_all();
    }

	// Get the moon
	if (strcmp(argv[1], "moon") == 0){
		printf("{\"moon\":\"%s\"}", moon());
	}

	// To do
	// BASIC MESSAGE SIGNING EXAMPLE
	/*
	printf("\n\nBEGIN BASIC MESSAGE SIGNING:\n\n");
	char* msg = "This is just a test message";
    char* privkey = "QUtnMFjt3JFk1NfeMe6Dj5u4p25DHZA54FsvEFAiQxcNP4bZkPu2";
    char* address = "D6a52RGbfvKDzKTh8carkGd1vNdAurHmaS";
    char* sig = sign_message(privkey, msg);
	if (verify_message(sig, msg, address)) {
		printf("Addresses match!\n");
	} else {
		printf("Addresses do not match!\n");
		return -1;
	}

    // testcase 2:
    // assert modified msg will cause verification failure:
    msg = "This is a new test message";
	if (!verify_message(sig, msg, address)) {
		printf("Addresses do not match!\n");
	} else {
		printf("Addresses match!\n");
		return -1;
	}

	// testcase 3:
    msg = "This is just a test message";
	if (verify_message(sig, msg, address)) {
		printf("Addresses match!\n");
	} else {
		printf("Addresses do not match!\n");
		return -1;
	}
    dogecoin_free(sig);
	// END ===========================================


	// ADVANCED MESSAGE SIGNING EXAMPLE
	printf("\n\nBEGIN ADVANCED MESSAGE SIGNING:\n\n");
    for (int i = 0; i < 10; i++) {
        // key 1:
        int key_id = start_key(false);
        eckey* key = find_eckey(key_id);
        char* msg = "This is a test message";
        char* sig = sign_message(key->private_key_wif, msg);
        if (verify_message(sig, msg, key->address)) {
			printf("Addresses match!\n");
		} else {
			printf("Message verification failed!\n");
			return -1;
		}
        remove_eckey(key);
        dogecoin_free(sig);

        // key 2:
        int key_id2 = start_key(true);
        eckey* key2 = find_eckey(key_id2);
        char* msg2 = "This is a test message";
        char* sig2 = sign_message(key2->private_key_wif, msg2);
        if (verify_message(sig2, msg2, key2->address)) {
			printf("Addresses match!\n");
		} else {
			printf("Message verification failed!\n");
			return -1;
		}

        // test message signature verification failure:
        msg2 = "This is an altered test message";
        if (!verify_message(sig2, msg2, key2->address)) {
			printf("Addresses do not match!\n");
		} else {
			printf("Message verification failed!\n");
			return -1;
		}
        remove_eckey(key2);
        dogecoin_free(sig2);
    }

	*/
	dogecoin_ecc_stop();
}
