#include "Expand.h"
#include <iostream>
#include <map>
#include <vector>

const int ALPHABET_SIZE = 95;//26

const char START_ALPHABET_SYMBOL = ' '; //'a'

struct bohr_vrtx
{
    int next_vrtx[ALPHABET_SIZE], pat_num, suff_link, auto_move[ALPHABET_SIZE], par, suff_flink;
    bool flag;
    char symb;
};

std::vector<bohr_vrtx> bohr;
std::vector<std::string> pattern;

bohr_vrtx MakeBohrVertex(int p, char c)
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

void InitBohr()
{
    //добавляем единственную вершину - корень
    bohr.clear();
    bohr.push_back(MakeBohrVertex(0, '$'));
}
void AddStringToBohr(const std::string &s)
{
    int num = 0; //начинаем с корня
    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i] - START_ALPHABET_SYMBOL; //получаем номер в алфавите
        if (bohr[num].next_vrtx[ch] == -1)
        { //-1 - признак отсутствия ребра
            bohr.push_back(MakeBohrVertex(num, ch));
            bohr[num].next_vrtx[ch] = bohr.size() - 1;
        }
        num = bohr[num].next_vrtx[ch];
    }
    bohr[num].flag = true;
    pattern.push_back(s);
    bohr[num].pat_num = pattern.size() - 1;
}
bool IsStringInBohr(const std::string &s)
{
    int num = 0;
    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i] - START_ALPHABET_SYMBOL;
        if (bohr[num].next_vrtx[ch] == -1)
        {
            return false;
        }
        num = bohr[num].next_vrtx[ch];
    }
    return true;
}
int GetAutoMove(int v, char ch);

int GetSuffLink(int v)
{
    if (bohr[v].suff_link == -1)        //если еще не считали
        if (v == 0 || bohr[v].par == 0) //если v - корень или предок v - корень
            bohr[v].suff_link = 0;
        else
            bohr[v].suff_link = GetAutoMove(GetSuffLink(bohr[v].par), bohr[v].symb);
    return bohr[v].suff_link;
}

int GetAutoMove(int v, char ch)
{
    if (bohr[v].auto_move[ch] == -1)
        if (bohr[v].next_vrtx[ch] != -1)
            bohr[v].auto_move[ch] = bohr[v].next_vrtx[ch];
        else if (v == 0)
            bohr[v].auto_move[ch] = 0;
        else
            bohr[v].auto_move[ch] = GetAutoMove(GetSuffLink(v), ch);
    return bohr[v].auto_move[ch];
}
int GetSuffFlink(int v)
{
    if (bohr[v].suff_flink == -1)
    {
        int u = GetSuffLink(v);
        if (u == 0) //либо v - корень, либо суф. ссылка v указывает на корень
        {
            bohr[v].suff_flink = 0;
        }
        else
        {
            bohr[v].suff_flink = (bohr[u].flag) ? u : GetSuffFlink(u);
        }
    }
    return bohr[v].suff_flink;
}
void Check(int v, int i, std::vector<EntryPointAndSubstring> &result)
{
    for (int u = v; u != 0; u = GetSuffFlink(u))
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

void FindAllPos(const std::string &s, std::vector<EntryPointAndSubstring> &result)
{
    int u = 0;
    for (int i = 0; i < s.length(); i++)
    {
        u = GetAutoMove(u, s[i] - START_ALPHABET_SYMBOL);
        Check(u, i + 1, result);
    }
}
