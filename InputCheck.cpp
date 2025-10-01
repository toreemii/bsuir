#include "InputCheck.h"

int InputCheck::inputInt(const std::string &message)
{
    int number;
    while (true)
    {
        std::cout << message;
        std::cin >> number;
        if (!std::cin.fail())
        {
            return number;
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Введите целое число от 1 до 10.\n";
    }
}