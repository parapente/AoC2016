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
$visited_coords = [[0, 0]];
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
    $newcoord = add_matrix($coord, mul_matrix($headings[$heading], $steps));
    if ($coord[0] === $newcoord[0]) {
        for ($i=1; $i < abs($newcoord[1] - $coord[1]); $i++) {
            $temp_coord = [$coord[0], $coord[1] + $i * $headings[$heading][1]];
            if (in_array($temp_coord, $visited_coords)) {
                $newcoord = $temp_coord;
                break;
            }
            array_push($visited_coords, $temp_coord);
        }
    }
    if ($coord[1] === $newcoord[1]) {
        for ($i=1; $i < abs($newcoord[0] - $coord[0]); $i++) {
            $temp_coord = [$coord[0] + $i * $headings[$heading][0], $coord[1]];
            if (in_array($temp_coord, $visited_coords)) {
                $newcoord = $temp_coord;
                break;
            }
            array_push($visited_coords, $temp_coord);
        }
    }
    $coord = $newcoord;
    if (in_array($coord, $visited_coords)) {
        break;
    }
    array_push($visited_coords, $coord);
}
echo($coord[0]+$coord[1]);
fclose($fin);

?>
