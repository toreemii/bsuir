#pragma once
#include <iostream>
#include <deque>
#include <string>
#include <vector>
#include <tuple>
#include <iomanip>

class RulesTable
{
private:
    std::vector<std::string> headState;
    std::vector<std::string> nextHeadState;
    std::vector<char> headValue;
    std::vector<char> nextHeadValue;
    std::vector<int> direction;

public:
    RulesTable() {}
    void AddRule(std::string headState,
                 std::string nextHeadState,
                 char headValue,
                 char nextHeadValue, int direction);
    std::tuple<std::string, char, int> FindRule(std::string headState, char headValue);

    void DeleteRule(int deleteNumber);
    void PrintTable();
};
