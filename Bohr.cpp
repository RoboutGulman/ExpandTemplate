#include "Expand.h"
#include <iostream>
#include <map>
#include <vector>
struct bohr_vrtx
{
    int next_vrtx[ALPHABET_SIZE], pat_num, suff_link, auto_move[ALPHABET_SIZE], par, suff_flink;
    bool flag;
    char symb;
};

std::vector<bohr_vrtx> bohr;
std::vector<std::string> pattern;


bohr_vrtx make_bohr_vrtx(int p, char c)
{ //передаем номер отца и символ на ребре в боре
    bohr_vrtx v;
    //(255)=(2^8-1)=(все единицы в каждом байте памяти)=(-1 в дополнительном коде целого 4-байтного числа int)
    memset(v.next_vrtx, 255, sizeof(v.next_vrtx));
    memset(v.auto_move, 255, sizeof(v.auto_move));
    v.flag = false;
    v.suff_link = -1;
    v.par = p;
    v.symb = c;
    v.suff_flink = -1;
    return v;
}

void bohr_ini()
{
    //добавляем единственную вершину - корень
    bohr.clear();
    bohr.push_back(make_bohr_vrtx(0, '$'));
}
void add_string_to_bohr(const std::string &s)
{
    int num = 0; //начинаем с корня
    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i] - 'a'; //получаем номер в алфавите
        if (bohr[num].next_vrtx[ch] == -1)
        { //-1 - признак отсутствия ребра
            bohr.push_back(make_bohr_vrtx(num, ch));
            bohr[num].next_vrtx[ch] = bohr.size() - 1;
        }
        num = bohr[num].next_vrtx[ch];
    }
    bohr[num].flag = true;
    pattern.push_back(s);
    bohr[num].pat_num = pattern.size() - 1;
}
bool is_string_in_bohr(const std::string &s)
{
    int num = 0;
    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i] - 'a';
        if (bohr[num].next_vrtx[ch] == -1)
        {
            return false;
        }
        num = bohr[num].next_vrtx[ch];
    }
    return true;
}
int get_auto_move(int v, char ch);

int get_suff_link(int v)
{
    if (bohr[v].suff_link == -1)        //если еще не считали
        if (v == 0 || bohr[v].par == 0) //если v - корень или предок v - корень
            bohr[v].suff_link = 0;
        else
            bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].par), bohr[v].symb);
    return bohr[v].suff_link;
}

int get_auto_move(int v, char ch)
{
    if (bohr[v].auto_move[ch] == -1)
        if (bohr[v].next_vrtx[ch] != -1)
            bohr[v].auto_move[ch] = bohr[v].next_vrtx[ch];
        else if (v == 0)
            bohr[v].auto_move[ch] = 0;
        else
            bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
    return bohr[v].auto_move[ch];
}
int get_suff_flink(int v)
{
    if (bohr[v].suff_flink == -1)
    {
        int u = get_suff_link(v);
        if (u == 0) //либо v - корень, либо суф. ссылка v указывает на корень
        {
            bohr[v].suff_flink = 0;
        }
        else
        {
            bohr[v].suff_flink = (bohr[u].flag) ? u : get_suff_flink(u);
        }
    }
    return bohr[v].suff_flink;
}
void check(int v, int i, std::vector<EntryPointAndSubstring> &result)
{
    for (int u = v; u != 0; u = get_suff_flink(u))
    {
        if (bohr[u].flag)
        {
            if (!result.empty())
            {
                auto point = result[result.size() - 1];
                if (point.first == i - pattern[bohr[u].pat_num].length() + 1)
                {
                    result.pop_back();
                }
            }
            result.push_back(std::make_pair(i - pattern[bohr[u].pat_num].length() + 1, pattern[bohr[u].pat_num]));
        }
    }
}

void find_all_pos(const std::string &s, std::vector<EntryPointAndSubstring> &result)
{
    int u = 0;
    for (int i = 0; i < s.length(); i++)
    {
        u = get_auto_move(u, s[i] - 'a');
        check(u, i + 1, result);
    }
}
