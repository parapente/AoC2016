<?php

class Output {
    public int $id;
    public array $chips;

    function __construct($id, $chips = array()) {
        $this->id = $id;
        $this->chips = $chips;
    }

    function giveChip(int $chip): void
    {
        array_push($this->chips, $chip);
    }
}

class Bot
{
    public int $id;
    public array $chips;
    public array $commandQueue;

    function __construct($id, $chips = array(), $commandQueue = array())
    {
        $this->id = $id;
        $this->chips = $chips;
        $this->commandQueue = $commandQueue;
    }

    function giveChip(int $chip): void
    {
        array_push($this->chips, $chip);
        sort($this->chips);
        if ($this->ready() && $this->chips[0] == 17 && $this->chips[1] == 61) {
            echo "Bot ".$this->id." has chips 17 and 61\n";
        }
        if ($this->ready()) {
            $cmd = $this->getNextCommand();
            if ($cmd !== null) {
                parse_command($cmd);
            }
        }
    }

    function ready(): bool
    {
        if (count($this->chips) == 2) {
            return true;
        }
        return false;
    }
    
    function getLowHight(): array
    {
        $result = $this->chips;
        $this->chips = [];
        return $result;
    }

    function addCommandToQueue(string $command): void
    {
        array_push($this->commandQueue, $command);
    }

    function getNextCommand(): string | null
    {
        if ($this->ready() && count($this->commandQueue) > 0) {
            return array_pop($this->commandQueue);
        } else {
            return null;
        }
    }
}

function parse_command(string $line, bool $checkQueue = true): void
{
    global $bot_dict;
    global $output_dict;

    preg_match('/value (\d+) goes to bot (\d+)/', $line, $match);
    if ($match) {
        $chip = intval($match[1]);
        $id = intval($match[2]);
        if (in_array($id, array_keys($bot_dict))) {
            $bot_dict[$id]->giveChip($chip);
        } else {
            $bot = new Bot($id);
            $bot->giveChip($chip);
            $bot_dict[$id] = $bot;
        }
        return;
    }
    preg_match('/bot (\d+) gives low to (\w+) (\d+) and high to (\w+) (\d+)/', $line, $match);
    if ($match) {
        $giver_id = intval($match[1]);
        if (!in_array($giver_id, array_keys($bot_dict))) {
            $bot = new Bot($giver_id);
            $bot->addCommandToQueue($line);
            $bot_dict[$giver_id] = $bot;
        } else if ($bot_dict[$giver_id]->ready()) {
            if ($checkQueue) {
                $bot_dict[$giver_id]->addCommandToQueue($line);
                $cmd = $bot_dict[$giver_id]->getNextCommand();
                parse_command($cmd, false);
            } else {
                [$low, $high] = $bot_dict[$giver_id]->getLowHight();
                if (($match[2]) == 'output') {
                    $id = intval($match[3]);
                    if (!in_array($id, array_keys($output_dict))) {
                        $output_dict[$id] = new Output($id);
                    }
                    $output_dict[$id]->giveChip($low);
                } else { // bot
                    $id = intval($match[3]);
                    if (!in_array($id, array_keys($bot_dict))) {
                        $bot_dict[$id] = new Bot($id);
                    }
                    $bot_dict[$id]->giveChip($low);
                }
                if (($match[4]) == 'output') {
                    $id = intval($match[5]);
                    if (!in_array($id, array_keys($output_dict))) {
                        $output_dict[$id] = new Output($id);
                    }
                    $output_dict[$id]->giveChip($high);
                } else { // bot
                    $id = intval($match[5]);
                    if (!in_array($id, array_keys($bot_dict))) {
                        $bot_dict[$id] = new Bot($id);
                    }
                    $bot_dict[$id]->giveChip($high);
                }
            }
        } else {
            $bot_dict[intval($match[1])]->addCommandToQueue($line);
        }
        return;
    }
}

$file = "10.dat";
$fin = fopen($file, "r");
$data = fread($fin, filesize($file));
$instruction_lines = preg_split('/\n/', $data, -1, PREG_SPLIT_NO_EMPTY);

$bot_dict = array();
$output_dict = array();

foreach ($instruction_lines as $line) {
    parse_command($line);
}

echo $output_dict[0]->chips[0] * $output_dict[1]->chips[0] * $output_dict[2]->chips[0];

fclose($fin);

?>
