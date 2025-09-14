#include "CantorovoSet.h"


int main()
{
    std::string str;
    std::getline(std::cin, str);
    CantorovoSet A(str);
    A.print();
    A.printCantorovoSet();
    return 0;
}
