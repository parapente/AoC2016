#!/usr/bin/python3

import re
from dataclasses import dataclass, field
from typing import Union

@dataclass
class Output:
    id: int
    chips: list[int] = field(default_factory=list)

    def giveChip(self, chip: int) -> None:
        self.chips.append(chip)

@dataclass
class Bot:
    id: int
    chips: list[int] = field(default_factory=list)
    commandQueue: list[str] = field(default_factory=list)

    def giveChip(self, chip: int) -> None:
        self.chips.append(chip)
        self.chips.sort()
        if (self.ready() and self.chips[0] == 17 and self.chips[1] == 61):
            print("Bot", self.id, "has chips 17 and 61")
        if (self.ready()):
            cmd = self.getNextCommand()
            if (cmd != None):
                parse_command(cmd)

    def ready(self) -> bool:
        return True if len(self.chips) == 2 else False
    
    def getLowHight(self) -> list[int]:
        result = self.chips
        self.chips = []
        return result

    def addCommandToQueue(self, command: str) -> None:
        self.commandQueue.append(command)

    def getNextCommand(self) -> Union[str, None]:
        if self.ready() and len(self.commandQueue) > 0:
            return self.commandQueue.pop()
        else:
            return None

def parse_command(line: str, checkQueue:bool = True) -> None:
    # print(bot_dict)
    # print(output_dict)
    match = re.match(r'value (\d+) goes to bot (\d+)', line)
    if match:
        chip = int(match.group(1))
        id = int(match.group(2))
        if (id in bot_dict):
            bot_dict[id].giveChip(chip)
        else:
            bot = Bot(id)
            bot.giveChip(chip)
            bot_dict[id] = bot
        return
    match = re.match(r'bot (\d+) gives low to (\w+) (\d+) and high to (\w+) (\d+)', line)
    if match:
        giver_id = int(match.group(1))
        if (giver_id not in bot_dict.keys()):
            bot = Bot(giver_id)
            bot.addCommandToQueue(line)
            bot_dict[giver_id] = bot
        elif (bot_dict[giver_id].ready()):
            if (checkQueue):
                bot_dict[giver_id].addCommandToQueue(line)
                cmd = bot_dict[giver_id].getNextCommand()
                parse_command(cmd, False)
            else:
                low, high = bot_dict[int(giver_id)].getLowHight()
                if (match.group(2) == 'output'):
                    id = int(match.group(3))
                    if (id not in output_dict):
                        output_dict[id] = Output(id)
                    output_dict[id].giveChip(low)
                else: # bot
                    id = int(match.group(3))
                    if (id not in bot_dict):
                        bot_dict[id] = Bot(id)
                    bot_dict[id].giveChip(low)
                if (match.group(4) == 'output'):
                    id = int(match.group(5))
                    if (id not in output_dict):
                        output_dict[id] = Output(id)
                    output_dict[id].giveChip(high)
                else: # bot
                    id = int(match.group(5))
                    if (id not in bot_dict):
                        bot_dict[id] = Bot(id)
                    bot_dict[id].giveChip(high)
        else:
            bot_dict[int(match.group(1))].addCommandToQueue(line)
        return

with open('10.dat') as f:
    data = f.read()
instruction_lines = data.split('\n')
instruction_lines.pop()
bot_dict = dict()
output_dict = dict()

for line in instruction_lines:
    parse_command(line)

print(output_dict[0].chips[0] * output_dict[1].chips[0] * output_dict[2].chips[0])