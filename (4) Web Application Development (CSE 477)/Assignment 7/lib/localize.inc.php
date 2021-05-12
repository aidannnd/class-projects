<?php
/**
 * Function to localize our site
 * @param $site The Site object
 */
return function(Felis\Site $site) {
    // Set the time zone
    date_default_timezone_set('America/Detroit');

    $site->setEmail('delfuoc1@cse.msu.edu');
    $site->setRoot('/~delfuoc1/step7');
    $site->dbConfigure('mysql:host=mysql-user.cse.msu.edu;dbname=delfuoc1',
        'delfuoc1',       // Database user
        'bQznwG1Cv8jI2N1C',     // Database password
        '');            // Table prefix
};