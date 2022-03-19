#include "Expand.h"
#include <iostream>
#include <map>
#include <vector>

std::string ExpandTemplate(std::string const &tpl, Dictionary const &params)
{
    std::string result = tpl;
    std::vector<bool> wasChanged(tpl.length(), false);
    std::vector<EntryPointAndSubstring> entry;
    find_all_pos(tpl, entry);
    int delta = 0;
    for (int i = 0; i < entry.size(); i++)
    {
        std::cout << "iteration "<< std::endl;
        //делаем проверку, меняем ли мы уже изменённые символы
        int start = entry[i].first;
        bool reModification = false;
        for (int j = 0; j <= entry[i].second.length(); j++)
        {
            if ((j < wasChanged.size() - start) && (wasChanged[j + start] == true))
            {
                std::cout << "break " << std::endl;
                reModification = true;
                break;
            }
        }
        if (reModification)
        {
            break;
        }
        for (int j = 0; j <= entry[i].second.length(); j++)
        {
            if (j < wasChanged.size() - start)
            {
                wasChanged[j+start]=true;
            }
        }
        std::cout << "iteration " <<i << std::endl;
        start = entry[i].first+delta-1;
        result.erase(result.begin()+start, result.begin() + start+entry[i].second.length());
        std::cout << "entry[i].second " << entry[i].second << std::endl;
        Dictionary::const_iterator iter = params.find(entry[i].second);
        result.insert(start, iter->second);
        std::cout << "iter->second " << iter->second << std::endl;
        delta = iter->second.length() - entry[i].second.length();
        std::cout << "delta " << delta << std::endl;
        std::cout << "\n";
    }
    return result;
}
