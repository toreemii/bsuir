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
    std::vector<std::vector<std::string>>& getElements();
    CantorovoSet(std::string &str);
    CantorovoSet();
    CantorovoSet(const char* cstr);
    void print();
    void printCantorovoSet();
    std::vector<std::vector<std::string>>
    CantrovoAlgorithm(std::vector<std::vector<std::string>> elements);
    void CopySet(std::string str);
    void AddElement(std::string strElement);
    void DeleteElement(std::string strElement);
    int PowerOfSets();
    bool operator[](std::string str);
    CantorovoSet& operator = (const CantorovoSet& SecondSet);
    CantorovoSet operator + (const CantorovoSet& SecondSet);
    CantorovoSet& operator += (const CantorovoSet& SecondSet);
    CantorovoSet operator * (const CantorovoSet& SecondSet);
    CantorovoSet& operator *= (const CantorovoSet& SecondSet);
    CantorovoSet operator - (const CantorovoSet& SecondSet);
    CantorovoSet& operator -= (const CantorovoSet& SecondSet);
    void Boolean(int idx,
    const std::vector<std::vector<std::string>>& set,
    std::vector<std::vector<std::string>>& current,
    std::vector<std::vector<std::vector<std::string>>>& result);
    void printBoolean(const std::vector<std::vector<std::string>>& elements);
};