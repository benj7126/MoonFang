#include "SubToken.h"

#include <iostream>

SubToken::SubToken(std::vector<char> &chars, std::vector<std::string> &savedValues, std::string &curSaveValue) : chars{chars}, savedValues{savedValues}, curSaveValue{curSaveValue} {};

SplitCommand SubToken::GetSplitCommand(){
    SplitCommand command{};

    command.type = chars[chars.size()-1];

    std::string CharSaver{};
    bool IsInt = true;

    for (char c : chars){
        if (c == ';' || c == command.type){
            Argument arg{};
            arg.svalue = CharSaver;
            CharSaver.clear();

            if (arg.svalue.size() == 0){
                arg.ivalue = 0;
            }
            else{
                if (IsInt)
                    arg.ivalue = stoi(arg.svalue);
            }

            IsInt = true;
            command.arguments.push_back(arg);
        } else{
            CharSaver += c;

            bool found = false;
            for (char compareChar : IntChars){
                if (c == compareChar)
                    found = true;
            }

            if (found == false)
                IsInt = false;
        }
    }

    return command;
}

std::string SubToken::GetCharsAsString() {
    std::string str{};

    for (int ccount = 0; ccount < chars.size(); ccount++) {
        str += chars.at(ccount);
    }

    return str;
}

void SubToken::InternalAddChar(char c) {
    //std::cout << "cur stage type of token: " << stage << " with a total of " << stages.size() << " stages" << std::endl;
    bool doContinue = AddChar(c);

    if (!doContinue)
        return;

    chars.push_back(c);

    if (stage >= stages.size())
        return;

    while ((stage < stages.size() && !CharBetween(c, stages[stage].start, stages[stage].end)) || (stage+1 == stages.size() && CharBetween(c, stages[stage].start, stages[stage].end))) {
        stage++;
    }
    //std::cout << "between " << (int)c << " - "<< (int)stages[stage].start << " and " << (int)stages[stage].end << std::endl;
};
