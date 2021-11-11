<?php

$keypad = [
            [-1,  -1,   1,  -1, -1],
            [-1,   2,   3,   4, -1],
            [ 5,   6,   7,   8,  9],
            [-1, 'A', 'B', 'C', -1],
            [-1,  -1, 'D',  -1, -1]
        ];

$fin = fopen("02.dat", "r");
$data = fread($fin, filesize("02.dat"));
$instruction_lines = preg_split('/\n/', $data, -1, PREG_SPLIT_NO_EMPTY);
$coord = [0, 2];
foreach ($instruction_lines as $line) {
    foreach (str_split($line) as $instruction) {
        switch($instruction) {

        case 'R':
            if ($coord[0] < (count($keypad[$coord[1]]) - 1) and $keypad[$coord[1]][$coord[0] + 1] != -1) {
                $coord[0] += 1;
            }
            break;
        case 'L':
            if ($coord[0] > 0 and $keypad[$coord[1]][$coord[0] - 1] != -1) {
                $coord[0] -= 1;
            }
            break;
        case 'U':
            if ($coord[1] > 0 and $keypad[$coord[1] - 1][$coord[0]] != -1) {
                $coord[1] -= 1;
            }
            break;
        case 'D':
            if ($coord[1] < (count($keypad) - 1) and $keypad[$coord[1] + 1][$coord[0]] != -1) {
                $coord[1] += 1;
            }
        }
    }
    echo $keypad[$coord[1]][$coord[0]];
}

fclose($fin);

?>
