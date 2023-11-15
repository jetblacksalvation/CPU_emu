#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdint>
static std::string seperateTokensBy = ", []():+-*/";
std::vector<std::string> tokenize(std::string string);
std::vector<std::vector<std::string> > getCode(std::fstream& stream);