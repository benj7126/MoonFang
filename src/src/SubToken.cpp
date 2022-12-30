#include "SubToken.h"

SubToken::SubToken(std::vector<char>& chars, std::vector<std::string>& savedValues, std::string& curSaveValue) :
    chars{chars}, savedValues{savedValues}, curSaveValue{curSaveValue} {};
