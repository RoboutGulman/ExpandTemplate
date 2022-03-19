// ExpandTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include "Expand.h"

int main(int argc, char* argv[])
{
    bohr_ini();
 /*   add_string_to_bohr("abc");
    add_string_to_bohr("bcdc");
    add_string_to_bohr("cccb");
    add_string_to_bohr("bcdd");
    add_string_to_bohr("bbbc");
    auto result = find_all_pos("abcdcbcddbbbcccbbbcccbb");*/
 /*   add_string_to_bohr("a");
    add_string_to_bohr("ab");
    add_string_to_bohr("abc");
    std::string const tpl = "aabbccccabc";
    std::map<std::string, std::string> params;
    params["a"] = "b";
    params["aa"] = "xx";
    params["b"] = "w";
    params["bb"] = "yy";
    params["c"] = "d";
    params["cc"] = "pp";
    add_string_to_bohr("a");
    add_string_to_bohr("aa");
    add_string_to_bohr("b");
    add_string_to_bohr("bb");
    add_string_to_bohr("c");
    add_string_to_bohr("cc");*/
    std::string const tpl = "a";
    std::map<std::string, std::string> params;
    params["a"] = "b";
    add_string_to_bohr("a"); 
    auto result = ExpandTemplate(tpl, params);
    std::cout << result << std::endl;
/*  auto result = find_all_pos("abcde");
    for (int i = 0; i < result.size(); i++)
    {
        std::cout << result[i].first << ' ' << result[i].second << std::endl;
    }
    std::string str = "abcde";
    str.erase(1, 2);
    std::cout << str;*/  
}
