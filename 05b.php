<?php

$file = "05.dat";
$fin = fopen($file, "r");
$data = fread($fin, filesize($file));
$password = '________';
$i = 0;
$chars_found = 0;
while ($chars_found < 8) {
    $test_string = $data.strval($i);
    $result = md5($test_string);
    if (str_starts_with($result, "00000")) {
        $position = intval($result[5], 16);
        if ($position < 8 && $password[$position] == '_') {
            $password[$position] = $result[6];
            $chars_found += 1;
        }
    }
    $i += 1;
    $fancy_password = $password;
    foreach (str_split($fancy_password) as $index => $char) {
        if ($char == '_') {
            $fancy_password[$index] = dechex(random_int(0, 15));
        }
    }
    echo 'password: '.$fancy_password."\r";
}
echo $password;

fclose($fin);

?>
