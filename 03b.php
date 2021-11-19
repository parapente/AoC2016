<?php

$file = "03.dat";
$fin = fopen($file, "r");
$data = fread($fin, filesize($file));
$instruction_lines = preg_split('/\n/', $data, -1, PREG_SPLIT_NO_EMPTY);
$triangles = 0;
$counter = 0;
$candidates = [[], [], []];
foreach ($instruction_lines as $line) {
    $counter++;
    $sides = explode(' ', trim(preg_replace('/\s+/', ' ', $line)));
    for ($i=0; $i<count($sides); $i++) {
        array_push($candidates[$i], $sides[$i]);
    }

    if ($counter % 3 == 0) {
        foreach ($candidates as $candidate) {
            $is_triangle = true;
            foreach ($candidate as $side) {
                $other_sides = $candidate;
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

        for ($i=0; $i<count($candidates); $i++) {
            $candidates[$i] = [];
        }
    }
}
echo $triangles;

fclose($fin);

?>
