#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <map>

using namespace std;

class Bot;
class Output;

map<int, Bot> bot_dict;
map<int, Output> output_dict;

void parse_command(string line, bool checkQueue = true);

class Output {
    public:
        int id;
        vector<int> chips;

    Output() {}

    Output(int id) : id(id) {}

    Output(int id, vector<int> chips) : id(id), chips(chips) {}

    void giveChip(int chip)
    {
        this->chips.push_back(chip);
    }
};

class Bot
{
    public:
        int id;
        vector<int> chips;
        vector<string> commandQueue;

    Bot() {}

    Bot(int id) : id(id) {}

    void giveChip(int chip)
    {
        this->chips.push_back(chip);
        sort(this->chips.begin(), this->chips.end());
        if (this->ready() && this->chips[0] == 17 && this->chips[1] == 61) {
            cout << "Bot " << this->id << " has chips 17 and 61" << endl;
        }
        if (this->ready()) {
            string cmd = this->getNextCommand();
            if (cmd != "") {
                parse_command(cmd);
            }
        }
    }

    bool ready(void)
    {
        if (this->chips.size() == 2) {
            return true;
        }
        return false;
    }
    
    vector<int> getLowHight()
    {
        vector<int> result = this->chips;
        this->chips = vector<int>();
        return result;
    }

    void addCommandToQueue(string command)
    {
        this->commandQueue.push_back(command);
    }

    string getNextCommand()
    {
        if (this->ready() && this->commandQueue.size() > 0) {
            string cmd = this->commandQueue.back();
            this->commandQueue.pop_back();
            return cmd;
        } else {
            return "";
        }
    }
};

void parse_command(string line, bool checkQueue)
{
    smatch match;
    int id, chip;
    regex cmd_set_regex("value (\\d+) goes to bot (\\d+)");
    regex cmd_give_regex("bot (\\d+) gives low to (\\w+) (\\d+) and high to (\\w+) (\\d+)");

    if (regex_match(line, match, cmd_set_regex)) {
        chip = stoi(match[1]);
        id = stoi(match[2]);
        try {
            bot_dict.at(id).giveChip(chip);
        }
        catch (out_of_range error) {
            Bot bot(id);
            bot.giveChip(chip);
            bot_dict[id] = bot;
        }
        return;
    }
    if (regex_match(line, match, cmd_give_regex)) {
        int giver_id = stoi(match[1]);
        if (!bot_dict.contains(giver_id)) {
            Bot bot(giver_id);
            bot.addCommandToQueue(line);
            bot_dict[giver_id] = bot;
        } else if (bot_dict[giver_id].ready()) {
            if (checkQueue) {
                bot_dict[giver_id].addCommandToQueue(line);
                string cmd = bot_dict[giver_id].getNextCommand();
                parse_command(cmd, false);
            } else {
                vector<int> low_high;
                low_high = bot_dict[giver_id].getLowHight();
                if ((match[2]) == "output") {
                    id = stoi(match[3]);
                    if (!output_dict.contains(id)) {
                        output_dict[id] = Output(id);
                    }
                    output_dict[id].giveChip(low_high[0]);
                } else { // bot
                    id = stoi(match[3]);
                    if (!bot_dict.contains(id)) {
                        bot_dict[id] = Bot(id);
                    }
                    bot_dict[id].giveChip(low_high[0]);
                }
                if ((match[4]) == "output") {
                    id = stoi(match[5]);
                    if (!output_dict.contains(id)) {
                        output_dict[id] = Output(id);
                    }
                    output_dict[id].giveChip(low_high[1]);
                } else { // bot
                    id = stoi(match[5]);
                    if (!bot_dict.contains(id)) {
                        bot_dict[id] = Bot(id);
                    }
                    bot_dict[id].giveChip(low_high[1]);
                }
            }
        } else {
            bot_dict[stoi(match[1])].addCommandToQueue(line);
        }
        return;
    }
}

int main(void) {
    string line;
    ifstream fin;
    vector<vector<char>> screen;
    vector<int> args;

    for (int row=0; row<6; row++) {
        screen.push_back(vector<char> {});
        for (int column=0; column<50; column++) {
            screen[row].push_back('.');
        }
    }

    fin.open("10.dat");
    while(!fin.eof()) {
        getline(fin, line);
        if (line == "") continue;

        parse_command(line);

    }
    cout << output_dict[0].chips[0] * output_dict[1].chips[0] * output_dict[2].chips[0];

    fin.close();
}
