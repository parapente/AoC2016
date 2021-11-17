<?php

function letterFrequency(string $name): array
{
    $letters = [];
    foreach (str_split($name) as $letter) {
        $letters[$letter] = (isset($letters[$letter]) ? $letters[$letter] : 0) + 1;
    }
    $result = [];
    foreach ($letters as $letter => $value) {
        array_push($result, [$letter, $value]);
    }
    return $result;
}

function calc_checksum(string $name): string
{
    $letters = letterFrequency(str_replace('-', '', $name));
    usort(
        $letters, function ($a, $b) {
            if ($a[1] === $b[1]) {
                return strcmp($a[0], $b[0]);
            }
            return ($a[1] > $b[1]) ? -1 : 1;
        }
    );

    $checksum = '';
    foreach ($letters as $letter) {
        $checksum .= $letter[0];
    }

    return substr($checksum, 0, 5);
}

$file = "04.dat";
$fin = fopen($file, "r");
$data = fread($fin, filesize($file));
$instruction_lines = preg_split('/\n/', $data, -1, PREG_SPLIT_NO_EMPTY);
$total = 0;
foreach ($instruction_lines as $line) {
    if (preg_match('/(.+)-(\d+)\[(.{5})\]/', $line, $m)) {
        $room_name = $m[1];
        $sector_id = $m[2];
        $checksum = $m[3];
        if (calc_checksum($room_name) == $checksum) {
            $total += intval($sector_id);
        }
            
    } else {
        echo 'Line not matched! ('.$line.')';
    }
}
echo $total;

fclose($fin);

?>
