<?php

$fin = fopen("03.dat", "r");
$data = fread($fin, filesize("03.dat"));
$instruction_lines = preg_split('/\n/', $data, -1, PREG_SPLIT_NO_EMPTY);
$triangles = 0;
foreach ($instruction_lines as $line) {
    $sides = explode(' ', trim(preg_replace('/\s+/', ' ', $line)));
    $is_triangle = true;
    foreach ($sides as $side) {
        $other_sides = $sides;
        array_splice($other_sides, array_search($side, $other_sides), 1);
        $side_sum = array_reduce($other_sides, fn($sum, $other_side) => intval($sum) + intval($other_side));
        if ($side_sum <= intval($side)) {
            $is_triangle = false;
            break;
        }
    }
    if ($is_triangle) {
        $triangles += 1;
    }
}
echo $triangles;

fclose($fin);

?>
