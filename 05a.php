<?php

$file = "05.dat";
$fin = fopen($file, "r");
$data = fread($fin, filesize($file));
$password = '';
$i = 0;
while (strlen($password) < 8) {
    $test_string = $data.strval($i);
    $result = md5($test_string);
    if (str_starts_with($result, "00000")) {
        $password .= $result[5];
    }
    $i += 1;
    echo 'password: '.$password.' i:'.$i."\r";
}
echo $password;

fclose($fin);

?>
