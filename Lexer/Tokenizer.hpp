#pragma once
#include <string>
#include <vector>

static std::string seperateTokensBy = ", []()";
std::vector<std::string> tokenize(std::string string);