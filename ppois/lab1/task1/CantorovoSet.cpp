#include "CantorovoSet.h"

CantorovoSet::CantorovoSet(std::string &str) : elements(parseString(str)) {}
CantorovoSet::CantorovoSet() {}
CantorovoSet::CantorovoSet(const char* cstr)
{
    std::string tempString(cstr);
    elements = parseString(tempString);
}


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

void CantorovoSet::CopySet(std::string str)
{
    std::vector<std::vector<std::string>> elementsToCopy = parseString(str);
    elements = elementsToCopy;
}

void CantorovoSet::AddElement(std::string strElement)
{
    std::vector<std::vector<std::string>> elementsToAdd = parseString(strElement);
    for (std::vector<std::string> element : elementsToAdd)
    {
        elements.push_back(element);
    }
}

void CantorovoSet::DeleteElement(std::string strElement)
{
    std::vector<std::vector<std::string>> elementsToDelete = parseString(strElement);
    for (std::vector<std::string> element : elementsToDelete)
    {
        for (int i = 0; i < elements.size(); i++)
        {
            if (elements[i] == element)
            {
                elements.erase(elements.begin() + i);
            }
        }
    }
}

int CantorovoSet::PowerOfSets()
{
    return elements.size();
}

CantorovoSet &CantorovoSet::operator=(const CantorovoSet &SecondSet)
{
    elements.clear();
    elements = SecondSet.elements;
    return *this;
}

CantorovoSet CantorovoSet::operator+(const CantorovoSet &SecondSet)
{
    CantorovoSet result = *this;
    bool isEqual = false;
    for (std::vector<std::string> secondElement : SecondSet.elements)
    {
        for (std::vector<std::string> element : result.elements)
        {
            if (element == secondElement)
            {
                isEqual = true;
            }
        }
        if (!isEqual)
        {
            result.elements.push_back(secondElement);
        }
        isEqual = false;
    }
    return result;
}

CantorovoSet& CantorovoSet::operator+=(const CantorovoSet &SecondSet)
{
    bool isEqual = false;
    for (std::vector<std::string> secondElement : SecondSet.elements)
    {
        for (std::vector<std::string> element : elements)
        {
            if (element == secondElement)
            {
                isEqual = true;
            }
        }
        if (!isEqual)
        {
            elements.push_back(secondElement);
        }
        isEqual = false;
    }
    return *this;
}

CantorovoSet CantorovoSet::operator*(const CantorovoSet &SecondSet)
{
    CantorovoSet result = *this;
    bool isEqual = false;
    CantorovoSet tempSet;
    for (int i = 0; i < SecondSet.elements.size(); i++)
    {
        for (int j = 0; j < result.elements.size(); j++)
        {
            if (result.elements[j] == SecondSet.elements[i])
            {
                isEqual = true;
            }
        }
        if (isEqual)
        {
            tempSet.elements.push_back(SecondSet.elements[i]);
        }
        isEqual = false;
    }
    result.elements = tempSet.elements;
    return result;
}

CantorovoSet& CantorovoSet::operator*=(const CantorovoSet &SecondSet)
{
    bool isEqual = false;
    CantorovoSet tempSet;
    for (int i = 0; i < SecondSet.elements.size(); i++)
    {
        for (int j = 0; j < elements.size(); j++)
        {
            if (elements[j] == SecondSet.elements[i])
            {
                isEqual = true;
            }
        }
        if (isEqual)
        {
            tempSet.elements.push_back(SecondSet.elements[i]);
        }
        isEqual = false;
    }
    elements = tempSet.elements;
    return *this;
}

CantorovoSet& CantorovoSet::operator-=(const CantorovoSet &SecondSet)
{
    bool isEqual = false;
    CantorovoSet tempSet;
    for (int i = 0; i < elements.size(); i++)
    {
        for (int j = 0; j < SecondSet.elements.size(); j++)
        {
            if (elements[i] == SecondSet.elements[j])
            {
                isEqual = true;
            }
        }
        if (!isEqual)
        {
            tempSet.elements.push_back(elements[i]);
        }
        isEqual = false;
    }
    elements = tempSet.elements;
    return *this;
}

CantorovoSet CantorovoSet::operator-(const CantorovoSet &SecondSet)
{
    CantorovoSet result = *this;
    bool isEqual = false;
    CantorovoSet tempSet;
    for (int i = 0; i < result.elements.size(); i++)
    {
        for (int j = 0; j < SecondSet.elements.size(); j++)
        {
            if (result.elements[i] == SecondSet.elements[j])
            {
                isEqual = true;
            }
        }
        if (!isEqual)
        {
            tempSet.elements.push_back(elements[i]);
        }
        isEqual = false;
    }
    result.elements = tempSet.elements;
    return result;
}

void CantorovoSet::Boolean(
    int idx,
    const std::vector<std::vector<std::string>>& set,
    std::vector<std::vector<std::string>>& current,
    std::vector<std::vector<std::vector<std::string>>>& result
)
{
    if (idx == static_cast<int>(set.size())) {
        result.push_back(current);
        return;
    }

    Boolean(idx + 1, set, current, result);

    current.push_back(set[idx]);
    Boolean(idx + 1, set, current, result);
    current.pop_back(); 
}

void CantorovoSet::printBoolean(const std::vector<std::vector<std::string>> &elements)
{
    std::vector<std::vector<std::vector<std::string>>> powerSet;
    std::vector<std::vector<std::string>> current;
    Boolean(0, elements, current, powerSet);

    std::cout << "Булеан множества (всего " << powerSet.size() << " подмножеств):\n";
    for (const auto &subset : powerSet)
    {
        std::cout << "{";
        for (const auto &elem : subset)
        {
            std::cout << "{";
            for (const auto &s : elem)
                std::cout << s;
            std::cout << "}";
        }
        std::cout << "}\n";
    }
}

std::vector<std::vector<std::string>>& CantorovoSet::getElements(){
    return elements;
}

bool CantorovoSet::operator[](std::string str){
    std::vector<std::string> elementToFind;
    elementToFind.push_back(str);
    for(std::vector<std::string> element:elements){
        if(elementToFind==element){
            return true;
        }
    }
    return false;
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
