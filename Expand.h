#pragma once
#include <iostream>
#include <vector>
#include <map>


typedef std::pair<int, std::string> EntryPointAndSubstring;
typedef std::map<std::string, std::string> Dictionary;

void AddStringToBohr(const std::string& s);
void FindAllPos(const std::string& s, std::vector<EntryPointAndSubstring>& result);
void InitBohr();
std::string ExpandTemplate(std::string const& tpl, Dictionary const& params);