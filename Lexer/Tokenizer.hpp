#pragma once
#include "../Common/common.hpp"


static std::string seperateTokensBy = ", []():+-*/";
std::vector<std::string> tokenize(std::string string);
std::vector<std::vector<std::string> > getCode(std::fstream& stream);