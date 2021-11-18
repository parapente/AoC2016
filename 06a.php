<?php

$file = "06.dat";
$fin = fopen($file, "r");
$data = fread($fin, filesize($file));
$instruction_lines = preg_split('/\n/', $data, -1, PREG_SPLIT_NO_EMPTY);
foreach ($instruction_lines as $line) {
    $i = 0;
    foreach (str_split($line) as $character) {
        $frequency[$i][$character] = ($frequency[$i][$character] ?? 0) + 1;
        $i++;
    }
}

foreach ($frequency as $column) {
    $max = 0;
    $character_max = '';
    foreach ($column as $character => $value) {
        if ($value > $max) {
            $max = $value;
            $character_max = $character;
        }
    }
    echo $character_max;
}

echo "\n";

fclose($fin);

?>
