#include "Expand.h"
#include <iostream>
#include <map>
#include <vector>

std::string ExpandTemplate(std::string const &tpl, Dictionary const &params)
{
    std::string result = tpl;
    std::vector<bool> wasChanged(tpl.length(), false);
    std::vector<EntryPointAndSubstring> entry;
    FindAllPos(tpl, entry);
    int delta = 0;
    for (int i = 0; i < entry.size(); i++)
    {
        //делаем проверку, меняем ли мы уже изменённые символы
        int start = entry[i].first-1;
        bool reModification = false;
        for (int j = 0; j <= entry[i].second.length(); j++)
        {
            if ((j < wasChanged.size() - start) && (wasChanged[j + start] == true))
            {
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
        start = entry[i].first+delta-1;
        result.erase(result.begin()+start, result.begin() + start+entry[i].second.length());
        Dictionary::const_iterator iter = params.find(entry[i].second);
        if (iter != params.end()) {
            result.insert(start, iter->second);
            delta = iter->second.length() - entry[i].second.length();
        }
    }
    return result;
}
