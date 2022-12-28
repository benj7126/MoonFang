#include "SubToken.h"

SubToken::SubToken(std::vector<char>& chars, std::vector<int>& savedValues, std::string& curSaveValue) :
    chars{chars}, savedValues{savedValues}, curSaveValue{curSaveValue} {};
