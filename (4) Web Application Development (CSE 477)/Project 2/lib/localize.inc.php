<?php
/**
 * Function to localize our site
 * @param $site The Site object
 */
return function(Game\Site $site) {
    // Set the time zone
    date_default_timezone_set('America/Detroit');


    $site->dbConfigure('mysql:host=mysql-user.cse.msu.edu;dbname=delfuoc1',
        'delfuoc1',       // Database user
        'bQznwG1Cv8jI2N1C',     // Database password
        'proj2_');            // Table prefix
};