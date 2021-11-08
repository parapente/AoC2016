<?php

$headings = [[0, 1], [1, 0], [0, -1], [-1, 0]];

function add_matrix($m1, $m2) {
    return [$m1[0] + $m2[0], $m1[1] + $m2[1]];
}
    
function mul_matrix($m1, $num) {
    return [$m1[0] * $num, $m1[1] * $num];
}

$fin = fopen("01.dat", "r");
$data = fread($fin, filesize("01.dat"));
$instructions = preg_split("/, /", $data);
$coord = [0, 0];
$heading = 0;
foreach ($instructions as $instruction) {
    $command = $instruction[0];
    $steps = intval(substr($instruction, 1));
    if ($command === 'R') {
        $heading += 1;
        if ($heading >= count($headings)) {
            $heading = 0;
        }
    } else {
        $heading -= 1;
        if ($heading < 0) {
            $heading = count($headings) - 1;
        }
    }
    $coord = add_matrix($coord, mul_matrix($headings[$heading], $steps));
}
echo($coord[0]+$coord[1]);
fclose($fin);

?>
