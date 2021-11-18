<?php

function get_aba_bab(string $ip_part): array
{
    $i = 0;
    $result = [];
    while ($i < (strlen($ip_part) - 2)) {
        if ($ip_part[$i] == $ip_part[$i+2] && $ip_part[$i] != $ip_part[$i+1]) {
            array_push($result, substr($ip_part, $i, 3));
        }
        $i += 1;
    }
    return $result;
}

function check_ssl(array $supernet, array $hypernet): bool
{
    $result = false;
    foreach ($supernet as $aba) {
        $bab = $aba[1].$aba[0].$aba[1];
        if (in_array($bab, $hypernet)) {
            $result = true;
        }
    }
    return $result;
}

$file = "07.dat";
$fin = fopen($file, "r");
$data = fread($fin, filesize($file));
$instruction_lines = preg_split('/\n/', $data, -1, PREG_SPLIT_NO_EMPTY);
$total = 0;
foreach ($instruction_lines as $line) {
    $i = 0;
    $supernet = [];
    $hypernet = [];
    
    foreach (explode("[", str_replace("]", "[", $line)) as $part) {
        if (($i % 2) === 0) {
            $supernet = array_merge($supernet, get_aba_bab($part));
        } else {
            $hypernet = array_merge($hypernet, get_aba_bab($part));
        }
        $i += 1;
    }

    $valid = check_ssl($supernet, $hypernet);
    if ($valid) {
        $total += 1;
    }
}

echo "$total\n";

fclose($fin);

?>
