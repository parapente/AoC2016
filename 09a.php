<?php

abstract class State
{
    const COPY = 1;
    const MARKER_START = 2;
    const MARKER_WHAT = 3;
    const MARKER_HOW_MANY = 4;
    const MARKER_END = 5;
}

class Marker
{
    public int $times;
    public int $chars;
}

function get_decompressed_length(string $buffer):int
{
    $current_state = State::COPY;
    $temp_buffer = [];
    $current_marker = new Marker();
    $decompressed_length = 0;

    foreach (str_split($buffer) as $character) {
        if ($current_state == State::COPY) {
            if ($character == '(') {
                $current_marker = new Marker();
                $current_state = State::MARKER_START;
            } else if (ctype_print($character)) {
                $decompressed_length++;
            }
        } else if ($current_state == State::MARKER_START) {
            array_push($temp_buffer, $character);
            $current_state = State::MARKER_WHAT;
        } else if ($current_state == State::MARKER_WHAT) {
            if ($character == 'x') {
                $current_marker->chars = intval(implode('', $temp_buffer));
                $temp_buffer = [];
                $current_state = State::MARKER_HOW_MANY;
            } else {
                array_push($temp_buffer, $character);
            }
        } else if ($current_state == State::MARKER_HOW_MANY) {
            if ($character == ')') {
                $current_marker->times = intval(implode('', $temp_buffer));
                $temp_buffer = [];
                $current_state = State::MARKER_END;
            } else {
                array_push($temp_buffer, $character);
            }
        } else if ($current_state == State::MARKER_END) {
            array_push($temp_buffer, $character);
            $current_marker->chars--;
            if ($current_marker->chars == 0) {
                $decompressed_length += $current_marker->times * count($temp_buffer);
                $temp_buffer = [];
                $current_state = State::COPY;
            }
        }
    }
    return $decompressed_length;
}

$file = "09.dat";
$fin = fopen($file, "r");
$data = fread($fin, filesize($file));
$instruction_lines = preg_split('/\n/', $data, -1, PREG_SPLIT_NO_EMPTY);

$total = 0;

foreach ($instruction_lines as $line) {
    $total += get_decompressed_length($line);
}

print($total);

fclose($fin);

?>
