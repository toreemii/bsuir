#include <iostream>
#include <vector>
#include <string>

class CantorovoSet
{
private:
    std::vector<std::vector<std::string>> elements;

    void nestingCheck(std::string &tempElement, int &depth, std::string &str, int &i);

    std::vector<std::vector<std::string>> parseString(std::string &str);

public:
    CantorovoSet(std::string &str);
    void print();
    void printCantorovoSet();
    std::vector<std::vector<std::string>>
    CantrovoAlgorithm(std::vector<std::vector<std::string>> elements);
};
