<?php

function parse_command(string $line):array
{
    preg_match('/rect (\d+)x(\d+)/', $line, $match);
    if ($match) {
        $rect = Closure::fromCallable('rect');
        return [$rect, [intval($match[1]), intval($match[2])]];
    }

    preg_match('/rotate row y=(\d+) by (\d+)/', $line, $match);
    if ($match) {
        $rotate_row = Closure::fromCallable('rotate_row');
        return [$rotate_row, [intval($match[1]), intval($match[2])]];
    }

    preg_match('/rotate column x=(\d+) by (\d+)/', $line, $match);
    if ($match) {
        $rotate_column = Closure::fromCallable('rotate_column');
        return [$rotate_column, [intval($match[1]), intval($match[2])]];
    }
}

function rect(array $args, array &$screen): void
{
    [$width, $height] = $args;
    for ($x=0; $x<$width; $x++) {
        for ($y=0; $y<$height; $y++) {
            $screen[$y][$x] = '#';
        }
    }
}

function rotate_row(array $args, array &$screen): void
{
    [$row, $offset] = $args;
    for ($i=0; $i<$offset; $i++) {
        $item = array_pop($screen[$row]);
        array_unshift($screen[$row], $item);
    }
}

function rotate_column(array $args, array &$screen): void
{
    [$column, $offset] = $args;
    for ($i=0; $i<$offset; $i++) {
        $prev = $screen[0][$column];
        for ($y=0; $y<count($screen); $y++) {
            $keep = $screen[($y+1)%count($screen)][$column];
            $screen[($y+1)%count($screen)][$column] = $prev;
            $prev = $keep;
        }
    }
}

function print_screen(array $screen): void
{
    foreach ($screen as $row) {
        foreach ($row as $pixel) {
            echo $pixel;
        }
        echo "\n";
    }
}

$file = "08.dat";
$fin = fopen($file, "r");
$data = fread($fin, filesize($file));
$instruction_lines = preg_split('/\n/', $data, -1, PREG_SPLIT_NO_EMPTY);

for ($row=0; $row<6; $row++) {
    for ($column=0; $column<50; $column++) {
        $screen[$row][$column] = '.';
    }
}

foreach ($instruction_lines as $line) {
    echo "Parsing line '".$line."'\n";
    [$cmd, $args] = parse_command($line);
    $cmd($args, $screen);
    print_screen($screen);
}

$total = 0;
foreach ($screen as $line) {
    foreach ($line as $pixel) {
        if ($pixel == '#') {
            $total += 1;
        }
    }
}
echo 'Pixels lit:'.$total."\n";

fclose($fin);

?>
