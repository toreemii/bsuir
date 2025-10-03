#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "TuringMachine.h"
#include "RulesTable.h"
#include "InputCheck.h"

// Тест для проверки итерации машины Тьюринга с одним правилом
TEST(TuringMachineTest, SingleIteration)
{
    TuringMachine tm("101", "q0");
    RulesTable rules;
    rules.AddRule("q0", "q1", '1', '0', 1); // При чтении '1' меняем на '0' и двигаемся вправо
    tm.TuringMachineIteration(rules);
    EXPECT_EQ(tm.ReadElement(), '0'); // После итерации головка на позиции 1, лента: [0,0,1]
}

// Тест для проверки нескольких итераций машины Тьюринга
TEST(TuringMachineTest, MultipleIterations)
{
    TuringMachine tm("11", "q0");
    RulesTable rules;
    rules.AddRule("q0", "q1", '1', '0', 1); // Меняем '1' на '0', двигаемся вправо
    rules.AddRule("q1", "q2", '1', '0', 1); // Меняем '1' на '0', двигаемся вправо
    tm.TuringMachineIteration(rules);       // Первая итерация: лента [0,1], head=1, state=q1
    tm.TuringMachineIteration(rules);       // Вторая итерация: лента [0,0], head=2, state=q2
    EXPECT_EQ(tm.ReadElement(), '_');       // Головка вышла за ленту, читаем '_'
}

// Тест для проверки отсутствия подходящего правила
TEST(TuringMachineTest, NoMatchingRule)
{
    TuringMachine tm("101", "q0");
    RulesTable rules;
    rules.AddRule("q0", "q1", '0', '1', 1); // Правило только для '0'
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
    tm.TuringMachineIteration(rules); // Нет правила для '1' в состоянии q0
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    EXPECT_EQ(tm.ReadElement(), '1'); // Лента не изменилась, читаем '1'
    EXPECT_NE(output.find("Подходящего правила нет."), std::string::npos);
}

// Тест для проверки добавления нескольких правил и их поиска
TEST(RulesTableTest, MultipleRules)
{
    RulesTable rules;
    rules.AddRule("q0", "q1", '1', '0', 1);
    rules.AddRule("q0", "q2", '0', '1', -1);
    auto [nextState1, nextValue1, direction1] = rules.FindRule("q0", '1');
    auto [nextState2, nextValue2, direction2] = rules.FindRule("q0", '0');
    EXPECT_EQ(nextState1, "q1");
    EXPECT_EQ(nextValue1, '0');
    EXPECT_EQ(direction1, 1);
    EXPECT_EQ(nextState2, "q2");
    EXPECT_EQ(nextValue2, '1');
    EXPECT_EQ(direction2, -1);
}


TEST(TuringMachineTest, MoveRight)
{
    TuringMachine tm("1011", "q0");
    tm.MoveRight();
    EXPECT_EQ(tm.ReadElement(), '0');
    tm.MoveLeft();
    EXPECT_EQ(tm.ReadElement(), '1');
    tm.MoveLeft();
    EXPECT_EQ(tm.ReadElement(), '_');
}

TEST(TuringMachineTest, MoveLeft)
{
    TuringMachine tm("1011", "q0");
    tm.MoveLeft();
    EXPECT_EQ(tm.ReadElement(), '_');
    tm.MoveLeft();
    EXPECT_EQ(tm.ReadElement(), '_');
    tm.MoveLeft();
    EXPECT_EQ(tm.ReadElement(), '_');
}

TEST(RulesTableTest, PrintTable)
{
    RulesTable rules;
    rules.AddRule("q0", "q1", '1', '0', 1);
    rules.AddRule("q1", "q2", '0', '1', -1);
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
    rules.PrintTable();
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    EXPECT_NE(output.find("q0"), std::string::npos);
    EXPECT_NE(output.find("q1"), std::string::npos);
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("0"), std::string::npos);
    EXPECT_NE(output.find("-1"), std::string::npos);
}

TEST(RulesTableTest, DeleteRuleEmptyTable)
{
    RulesTable rules;
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
    rules.DeleteRule(0);
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    EXPECT_EQ(output, "Таблица правил пуста\n");
}

TEST(RulesTableTest, DeleteRule)
{
    RulesTable rules;
    rules.AddRule("q0", "q1", '1', '0', 1);
    rules.DeleteRule(0);
    auto [nextState, nextValue, direction] = rules.FindRule("q0", '1');
    EXPECT_EQ(nextState, "");
}

TEST(InputCheckTest, InputIntValid) {
    InputCheck ic;
    std::stringstream input("5\n");
    std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());
    std::stringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());
    int result = ic.inputInt("Enter number: ");
    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);
    EXPECT_EQ(result, 5);
}

TEST(TuringMachineTest, ConstructorAndRead)
{
    TuringMachine tm("abc", "q0");
    EXPECT_EQ(tm.ReadElement(), 'a');
}

TEST(TuringMachineTest, AddElement)
{
    TuringMachine tm("", "q0");
    tm.AddElement('x');
    EXPECT_EQ(tm.ReadElement(), 'x');
}

TEST(RulesTableTest, AddAndFindRule)
{
    RulesTable rules;
    rules.AddRule("q0", "q1", '1', '0', 1);
    auto [nextState, nextValue, direction] = rules.FindRule("q0", '1');
    EXPECT_EQ(nextState, "q1");
    EXPECT_EQ(nextValue, '0');
    EXPECT_EQ(direction, 1);
}

TEST(TuringMachineTest, SetElementAndState) {
    TuringMachine tm("101", "q0");
    tm.SetElement('0');
    EXPECT_EQ(tm.ReadElement(), '0');
    tm.SetHeadStates("q1");
}

TEST(RulesTableTest, RuleNotFound)
{
    RulesTable rules;
    auto [nextState, nextValue, direction] = rules.FindRule("q0", '1');
    EXPECT_EQ(nextState, "");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}