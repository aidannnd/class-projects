<?php

/**
 * Create an array that represents the cave
 * @returns Array
 */
function cave_array() {
    $cave = array(1 => array(5, 6, 2),
        2 => array(1, 8, 3),
        3 => array(12, 10, 4),
        4 => array(3, 12, 5),
        5 => array(4, 14, 1),
        6 => array(15, 1, 7),
        7 => array(6, 8, 16),
        8 => array(7, 2, 9),
        9 => array(8, 17, 10),
        10 => array(9, 11, 3),
        11 => array(12, 18, 10),
        12 => array(13, 11, 4),
        13 => array(14, 19, 12),
        14 => array(5, 15, 13),
        15 => array(14, 6, 20),
        16 => array(20, 7, 17),
        17 => array(16, 9, 18),
        18 => array(19, 17, 11),
        19 => array(13, 20, 18),
        20 => array(19, 15, 16));

    return $cave;
}