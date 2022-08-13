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
