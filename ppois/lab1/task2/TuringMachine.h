#pragma once
#include <iostream>
#include <deque>
#include <string>
#include "RulesTable.h"
#include <vector>


class TuringMachine
{
private:
    std::deque<char> tape;
    int head;
    std::string state;

public:
    TuringMachine(const char *initArray, std::string initStates);
    void MoveLeft();
    void MoveRight();
    char ReadElement();
    void SetElement(char value);
    void SetHeadStates(std::string state);
    void TuringMachineIteration(RulesTable rules);
    void print();
    void AddElement(char value);
};
