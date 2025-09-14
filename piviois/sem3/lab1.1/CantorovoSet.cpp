#include "CantorovoSet.h"

CantorovoSet::CantorovoSet(std::string &str) : elements(parseString(str)){}

void CantorovoSet::nestingCheck(std::string &tempElement, int &depth, std::string &str, int &i)
{
    if (str[i] == '{')
    {
        depth++;
        ++i;
        while (!(str[i] == '}' && depth <= 2))
        {
            if (str[i] == '{')  
            {
                depth++;
            }
            else if (str[i] == '}')
            {
                depth--;
            }
            tempElement += str[i];
            i++;
        }
        depth--;
    }
    else
    {
        tempElement += str[i];
    }
}

std::vector<std::vector<std::string>> CantorovoSet::parseString(std::string &str)
{
    std::vector<std::vector<std::string>> result;
    int position = 0;
    int depth = 1;
    std::string tempElement;
    for (int i = 0; i < str.length(); ++i)
    {
        if (str[i] == ' ')
        {
            str.erase(i, 1);
            i--;
        }
    }
    for (int i = 1; i < str.length(); ++i)
    {
        if (str[i] == ',' && str[i - 1] == ',' || str[i] == ',' && str[i - 1] == '{')
        {
            str.erase(i, 1);
            --i;
        }
    }

    for (int i = 1; i < str.length(); i++)
    {
        if (str[i] == ',' || str[i] == '}' && depth == 1)
        {
            std::vector<std::string> element;
            element.push_back(tempElement);
            result.push_back(element);
            tempElement = "";
            ++i;
        }
        nestingCheck(tempElement, depth, str, i);
    }
    return result;
}

void CantorovoSet::print()
{
    std::cout << "{";
    for (int i = 0; i < elements.size(); i++)
    {
        std::cout << "{";
        for (int j = 0; j < elements[i].size(); j++)
        {
            std::cout << elements[i][j];
            if (j < elements[i].size() - 1)
                std::cout << ",";
        }
        std::cout << "}";
        if (i < elements.size() - 1)
            std::cout << ",";
    }
    std::cout << "}" << std::endl;
}

void CantorovoSet::printCantorovoSet()
{
    elements = CantrovoAlgorithm(elements);
    print();
}

std::vector<std::vector<std::string>>
CantorovoSet::CantrovoAlgorithm(std::vector<std::vector<std::string>> elements)
{
    if (elements.size() <= 2)
    {
        return elements;
    }
    int count = elements.size() / 3;
    std::vector<std::vector<std::string>> leftThird;
    std::vector<std::vector<std::string>> rightThird;
    for (int i = 0; i < count; i++)
    {
        leftThird.push_back(elements[i]);
    }
    for (int i = elements.size() - count; i < elements.size(); i++)
    {
        rightThird.push_back(elements[i]);
    }
    auto leftResult = CantrovoAlgorithm(leftThird);
    auto rightResult = CantrovoAlgorithm(rightThird);

    std::vector<std::vector<std::string>> result;
    result.insert(result.end(), leftResult.begin(), leftResult.end());
    result.insert(result.end(), rightResult.begin(), rightResult.end());
    return result;
}
