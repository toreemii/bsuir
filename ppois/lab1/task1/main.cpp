#include "CantorovoSet.h"
#include "Menu.h"
#include "InputCheck.h"

int main()
{
    std::cout << "Введите множество: \n";
    std::string str;
    std::getline(std::cin, str);
    CantorovoSet Set(str);
    CantorovoSet SecondSet;
    Set.print();
    Menu menu;
    bool runMenu = true;
    while (runMenu)
    {
        menu.PrintMenu();
        int number = InputCheck::inputInt("Введите опцию: ");
        switch (number)
        {
        case 1:
            std::cout << "Введите элемент:\n";
            std::getchar();
            std::getline(std::cin, str);
            Set.AddElement(str);
            break;
        case 2:
            std::cout << "Введите элемент, который хотите удалить:\n";
            std::getchar();
            std::getline(std::cin, str);
            Set.DeleteElement(str);
            break;
        case 3:
            std::cout << "Мощность множества:\n";
            std::cout << Set.PowerOfSets() << std::endl;
            break;
        case 4:
            std::cout << "Введите элемент для поиска:\n";
            std::getchar();
            std::getline(std::cin, str);
            if (Set[str])
            {
                std::cout << "Элемент принадлежит множеству\n";
            }
            else
            {
                std::cout << "Элемент не принадлежит множеству\n";
            }
            break;
        case 5:
            std::cout << "Введите множество:\n";
            std::getchar();
            std::getline(std::cin, str);
            SecondSet.CopySet(str);
            Set += SecondSet;
            std::cout << "Объединение множеств:\n";
            break;
        case 6:
            std::cout << "Введите множество:\n";
            std::getchar();
            std::getline(std::cin, str);
            SecondSet.CopySet(str);
            Set *= SecondSet;
            std::cout << "Пересечение множеств:\n";
            break;
        case 7:
            std::cout << "Введите множество:\n";
            std::getchar();
            std::getline(std::cin, str);
            SecondSet.CopySet(str);
            Set -= SecondSet;
            std::cout << "Разность множеств:\n";
            break;
        case 8:
            Set.printBoolean(Set.getElements());
            std::cout << "Булеан множества:\n";
            break;
        case 9:
            Set.printCantorovoSet();
            continue;
            break;
        case 10:
            runMenu = false;
            break;
        default:
            std::cout << "Неверный ввод.Введите число от 1 до 10\n";
            break;
        }
        Set.print();
    }
    return 0;
}