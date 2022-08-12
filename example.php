<?php
/**
*   File: Functions used on the Libdogecoin
*   Description: Bind Libdogecoin to PHP using c compiled that prints in JSON format
*
*   Available Commands:
*    generatePrivPubKeypair
*    generateHDMasterPubKeypair
*    generateDerivedHDPubkey
*    verifyPrivPubKeypair
*    verifyHDMasterPubKeypair
*    verifyP2pkhAddress
*    start_transaction
*/

    function libdogecoin ($commands){
      exec('./libdogecoin-php/json-php/libdogecoin-json-php '.$commands[0].' 2>&1', $output, $retval);
      return json_decode($output[0]);
    }

    $commands[] = "generatePrivPubKeypair"; //command
    //$commands[1] = ""; // hash_doge (tx hash with doge)
    //$commands[2] = ""; // external_p2pkh_addr
    //$commands[3] = ""; // numeric doge to send ex: 5.0
    //$commands[4] = ""; // numeric fees ex: 0.00226
    //$commands[5] = ""; // numeric tx index
    //$commands[6] = ""; // mypubkey
    //$commands[7] = ""; // myscriptpubkey
    //$commands[8] = ""; // myprivkey

    // Simple exemple
    echo "This is my Private Key: ";
    echo libdogecoin($commands)->private;

    echo "<br>";

    echo "This is my Public Key";
    echo libdogecoin($commands)->public;
?>
