#include "TuringMachine.h"

TuringMachine::TuringMachine(const char *initArray, std::string initStates)
{
    state = initStates;
    head = 0;
    for (int i = 0; initArray[i] != '\0'; i++)
    {
        tape.push_back(initArray[i]);
    }
}

void TuringMachine::MoveRight()
{
    head++;
    if (head >= tape.size())
    {
        tape.push_back('_');
    }
}

void TuringMachine::MoveLeft()
{
    head--;
    if (head < 0)
    {
        tape.push_front('_');
        head = 0;
        return;
    }
}

char TuringMachine::ReadElement()
{
    return tape[head];
}

void TuringMachine::SetElement(char value)
{
    tape[head] = value;
}

void TuringMachine::SetHeadStates(std::string state)
{
    this->state = state;
}

void TuringMachine::TuringMachineIteration(RulesTable rules)
{
    int tempHead = head;
    auto [ruleState, ruleValue, ruleDirection] = rules.FindRule(state, tape[head]);
    state = ruleState;
    tape[head] = ruleValue;
    switch (ruleDirection)
    {
    case -1:
        MoveLeft();
        break;
    case 0:
        break;
    case 1:
        MoveRight();
        break;
    default:
        break;
    }
}

void TuringMachine::print()
{
    for (int i = 0; i < tape.size(); ++i)
    {
        if (i == head)
        {
            std::cout << "[" << tape[i] << "]";
        }
        else
        {
            std::cout << tape[i];
        }
    }
    std::cout << std::endl;
}

void TuringMachine::AddElement(char value)
{
    tape.push_back(value);
}
