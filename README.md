# libdogecoin-php

libdogecoin bindings for PHP

Supports any OS that supports PHP

#If you want to compile a new one (its compiled alredy)
```linux
gcc ./libdogecoin-php/libdogecoin-json.c -I./include -L./lib -ldogecoin -o ./libdogecoin-php/libdogecoin-json-php
```

**Note: This is project and README is a work in progress!**

# Binding progress
- [x] Address
- [x] Transactions

# Usage

```php
<?php
/**
*   File: Exemple used on the Libdogecoin
*   Description: Bind Libdogecoin to PHP using c compiled that prints in JSON format
*
*   Available Commands:
*    $LibDogecoin->generatePrivPubKeypair();
*    $LibDogecoin->generateHDMasterPubKeypair();
*    $LibDogecoin->generateDerivedHDPubkey();
*    $LibDogecoin->verifyPrivPubKeypair($privateKey,$publicKey);
*    $LibDogecoin->verifyHDMasterPubKeypair($privateKey,$publicKey);
*    $LibDogecoin->verifyP2pkhAddress($publicKey);
*    $LibDogecoin->start_transaction($hash_doge,$external_p2pkh_addr,$doge_amount,$fees,$tx_index,$mypubkey,$myscriptpubkey,$myprivkey);
*/

    require_once 'libdogecoin-php/libdogecoin-bind.php';

    // Simple exemple for generatePrivPubKeypair
    $result = $LibDogecoin->generatePrivPubKeypair();
    echo "This is my Private Key: " . $result->private;
    echo "<br>";
    echo "This is my Public Key: ". $result->public;


?>
```
