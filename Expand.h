#pragma once
#include <iostream>
#include <vector>
#include <map>

const int ALPHABET_SIZE = 26;
typedef std::pair<int, std::string> EntryPointAndSubstring;
typedef std::map<std::string, std::string> Dictionary;




void add_string_to_bohr(const std::string& s);
void find_all_pos(const std::string& s, std::vector<EntryPointAndSubstring>& result);
void bohr_ini();
std::string ExpandTemplate(std::string const& tpl, Dictionary const& params);