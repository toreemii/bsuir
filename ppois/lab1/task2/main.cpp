#include "RulesTable.h"
#include "TuringMachine.h"
#include "Menu.h"
#include "InputCheck.h"

int main()
{
    RulesTable rules;
    std::string strTape;
    std::string headState;
    std::cout << "Заполните ленту:\n";
    std::getline(std::cin, strTape);
    std::cout << "Введите значения состояния головки:\n";
    std::getline(std::cin, headState);
    TuringMachine tape(strTape.c_str(), headState);
    Menu menu;
    bool runCicle = true;
    while (runCicle)
    {
        int option, direction, choice;
        std::string nextState, currentState;
        char nextValue, currentValue;
        menu.printMenu();
        option=InputCheck::inputInt("Выберите действие: ");
        switch (option)
        {
        case 1:
            std::cout << "Введите направление(-1 - влево, 0 - остаться на месте, 1 - вправо)\n";
            std::cin >> direction;
            std::cout << "Введите текущее состояние:\n";
            std::getchar();
            std::getline(std::cin, currentState);
            std::cout << "Введите следующее состояние:\n";
            std::getline(std::cin, nextState);
            std::cout << "Введите тeкущее значение:\n";
            std::cin >> currentValue;
            std::cout << "Введите следующее значение:\n";
            std::cin >> nextValue;
            rules.AddRule(currentState, nextState, currentValue, nextValue, direction);
            break;
        case 2:
            rules.PrintTable();
            std::cin >> choice;
            rules.DeleteRule(choice - 1);
            break;
        case 3:
            rules.PrintTable();
            break;
        case 4:
            std::cout << "Задайте значение в конец ленты:\n";
            std::cin >> nextValue;
            tape.AddElement(nextValue);
            break;
        case 5:
            std::cout << "Измените значение на ленте:\n";
            std::cin >> nextValue;
            tape.SetElement(nextValue);
            break;
        case 6:
            tape.TuringMachineIteration(rules);
            break;
        case 7:
            runCicle = false;
            break;
        default:
            std::cout << "Выберите опцию от 1 до 7.\n";
            break;
        }
        tape.print();
    }
    return 0;
}