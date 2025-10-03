#include "InputCheck.h"
int InputCheck::inputInt(const std::string &message)
{
    int number;
    while (true)
    {
        std::cout << message;
        std::cin >> number;
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            std::cout<<"Ошибка. Введено не число.\n";
            continue;
        }

            if (number >= 1 && number <= 7)
            {
                std::cin.ignore(1000, '\n');
                return number;
            }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Введите целое число от 1 до 7.\n";
    }
}

