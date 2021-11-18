<?php

function is_abba(string $ip_part): bool
{
    $i = 0;
    $result = false;
    while ($i < (strlen($ip_part) - 3)) {
        if ($ip_part[$i] == $ip_part[$i+3]
            && $ip_part[$i+1] == $ip_part[$i+2]
            && $ip_part[$i] != $ip_part[$i+1]
        ) {
            $result = true;
        }
        $i += 1;
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
    $results = [];
    $results_brackets = [];
    
    foreach (explode("[", str_replace("]", "[", $line)) as $part) {
        if (($i % 2) === 0) {
            array_push($results, is_abba($part));
        } else {
            array_push($results_brackets, is_abba($part));
        }
        $i += 1;
    }

    $valid = (new \Ds\Vector($results))->reduce(
        function ($carry, $value) {
            return $carry || $value;
        }
    ) 
    && !(new \Ds\Vector($results_brackets))->reduce(
        function ($carry, $value) {
            return $carry || $value;
        }
    );
    if ($valid) {
        $total += 1;
    }
}

echo "$total\n";

fclose($fin);

?>
