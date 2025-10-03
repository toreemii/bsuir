#include "RulesTable.h"

void RulesTable::AddRule(std::string headState,
                         std::string nextHeadState,
                         char headValue,
                         char nextHeadValue, int direction)
{
    this->headState.push_back(headState);
    this->nextHeadState.push_back(nextHeadState);
    this->headValue.push_back(headValue);
    this->nextHeadValue.push_back(nextHeadValue);
    this->direction.push_back(direction);
}

std::tuple<std::string, char, int> RulesTable::FindRule(std::string needState, char needValue)
{
    for (int i = 0; i < headState.size(); ++i)
    {
        if (needState == headState[i] && needValue == headValue[i])
        {
            return std::make_tuple(nextHeadState[i], nextHeadValue[i], direction[i]);
        }
    }
    std::cout << "Подходящего правила нет.\n";
    return std::make_tuple("", needValue, 0);
}

void RulesTable::DeleteRule(int deleteNumber)
{
    if (headValue.size() == 0)
    {
        std::cout << "Таблица правил пуста\n";
        return;
    }
    headValue.erase(headValue.begin() + deleteNumber);
    headState.erase(headState.begin() + deleteNumber);
    direction.erase(direction.begin() + deleteNumber);
}

void RulesTable::PrintTable()
{
    std::cout << std::left << std::setw(5) << "№"
              << std::setw(18) << "Сост.головки "
              << std::setw(25) << "След.сост.головки "
              << std::setw(18) << "Текущее значение "
              << std::setw(25) << "След.значение "
              << std::setw(12) << "Направление " << "\n";

    std::cout << std::string(78, '-') << "\n";

    for (int i = 0; i < direction.size(); i++)
    {
        std::cout << std::left << std::setw(5) << (i + 1)
                  << std::setw(18) << headState[i]
                  << std::setw(25) << nextHeadState[i]
                  << std::setw(8) << headValue[i]
                  << std::setw(12) << nextHeadValue[i]
                  << std::setw(5) << direction[i] << "\n";
    }
}
