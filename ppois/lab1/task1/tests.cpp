#include <gtest/gtest.h>
#include "CantorovoSet.h"
#include <sstream>
#include <iostream>

std::string capturePrint(CantorovoSet &s) {
    std::ostringstream oss;
    auto old = std::cout.rdbuf(oss.rdbuf());
    s.print();
    std::cout.rdbuf(old);
    return oss.str();
}

std::string capturePrintCantor(CantorovoSet &s) {
    std::ostringstream oss;
    auto old = std::cout.rdbuf(oss.rdbuf());
    s.printCantorovoSet();
    std::cout.rdbuf(old);
    return oss.str();
}

TEST(CantorovoSetTest, SimpleParse) {
    std::string in = "{1,2,3}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrint(s), "{{1},{2},{3}}\n");
}

TEST(CantorovoSetTest, WithSpaces) {
    std::string in = "{ 1 , 2 , 3 }";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrint(s), "{{1},{2},{3}}\n");
}

TEST(CantorovoSetTest, WithSpaces2) {
    std::string in = "{ 1 , 5 , 8,   ,, 7   ,13 }";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrint(s), "{{1},{5},{8},{7},{13}}\n");
}

TEST(CantorovoSetTest, NestedAndEmpty) {
    std::string in = "{1,{2,3},{}}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrint(s), "{{1},{2,3},{}}\n");
}

TEST(CantorovoSetTest, Nested) {
    std::string in = "{5,{7,b},{{{6},9,3},17},4}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrint(s), "{{5},{7,b},{{{6},9,3},17},{4}}\n");
}

TEST(CantorovoSetTest, RemoveDoubleCommas) {
    std::string in = "{1,,2,3}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrint(s), "{{1},{2},{3}}\n");
}

TEST(CantorovoSetTest, RemoveDoubleCommas2) {
    std::string in = "{7,,,4,3,,6,5,2,}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrint(s), "{{7},{4},{3},{6},{5},{2}}\n");
}

TEST(CantorovoSetTest, ComplexNested) {
    std::string in = "{1,2,{{5},4},9}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrint(s), "{{1},{2},{{5},4},{9}}\n");
}

TEST(CantorovoSetTest, CantorAlgorithm) {
    std::string in = "{1,2,3,4,5,6,7,8,9}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrintCantor(s), "{{1},{3},{7},{9}}\n");
}

TEST(CantorovoSetTest, CantorAlgorithm2) {
    std::string in = "{6,12,3,4,8,9,11,22,3}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrintCantor(s), "{{6},{3},{11},{3}}\n");
}

TEST(CantorovoSetTest, EmptySet) {
    std::string in = "{}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrint(s), "{{}}\n");
}

TEST(CantorovoSetTest, NestedAndEmpty2) {
    std::string in = "{1, {1,5,{6}},{b},{},,k,{{5},l}}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrintCantor(s), "{{1},{1,5,{6}},{k},{{5},l}}\n");
}

TEST(CantorovoSetTest, CantorAlgorithmDifferent) {
    std::string in = "{1,2,3,5,8,13}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrintCantor(s), "{{1},{2},{8},{13}}\n");
}

TEST(CantorovoSetTest, LargeSet) {
    std::string in = "{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrintCantor(s), "{{1},{5},{11},{15}}\n");
}

TEST(CantorovoSetTest, DeepNested) {
    std::string in = "{{1,2}, {3, {}}, {{4},5}, {}}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrint(s), "{{1,2},{3,{}},{{4},5},{}}\n");
}

TEST(CantorovoSetTest, DefaultConstructor) {
    CantorovoSet s;
    EXPECT_EQ(capturePrint(s), "{}\n");
}

TEST(CantorovoSetTest, CharConstructor) {
    CantorovoSet s("{1,2,3}");
    EXPECT_EQ(capturePrint(s), "{{1},{2},{3}}\n");
}

TEST(CantorovoSetTest, AddElement) {
    CantorovoSet s("{1,2}");
    s.AddElement("{3,4}");
    EXPECT_EQ(capturePrint(s), "{{1},{2},{3},{4}}\n");
}

TEST(CantorovoSetTest, DeleteElement) {
    CantorovoSet s("{1,2,3,4}");
    s.DeleteElement("{2,3}");
    EXPECT_EQ(capturePrint(s), "{{1},{4}}\n");
}

TEST(CantorovoSetTest, PowerOfSets) {
    CantorovoSet s("{1,2,3}");
    EXPECT_EQ(s.PowerOfSets(), 3);
    CantorovoSet empty("{}");
    EXPECT_EQ(empty.PowerOfSets(), 1); 
}

TEST(CantorovoSetTest, OperatorAssignment) {
    CantorovoSet s1("{1,2,3}");
    CantorovoSet s2;
    s2 = s1;
    EXPECT_EQ(capturePrint(s2), "{{1},{2},{3}}\n");
}

TEST(CantorovoSetTest, OperatorPlus) {
    CantorovoSet s1("{1,2}");
    CantorovoSet s2("{2,3}");
    CantorovoSet result = s1 + s2;
    EXPECT_EQ(capturePrint(result), "{{1},{2},{3}}\n");
}

TEST(CantorovoSetTest, OperatorPlusEqual) {
    CantorovoSet s1("{1,2}");
    CantorovoSet s2("{2,3}");
    s1 += s2;
    EXPECT_EQ(capturePrint(s1), "{{1},{2},{3}}\n");
}

TEST(CantorovoSetTest, OperatorMultiply) {
    CantorovoSet s1("{1,2,3}");
    CantorovoSet s2("{2,3,4}");
    CantorovoSet result = s1 * s2;
    EXPECT_EQ(capturePrint(result), "{{2},{3}}\n");
}

TEST(CantorovoSetTest, OperatorMultiplyEqual) {
    CantorovoSet s1("{1,2,3}");
    CantorovoSet s2("{2,3,4}");
    s1 *= s2;
    EXPECT_EQ(capturePrint(s1), "{{2},{3}}\n");
}

TEST(CantorovoSetTest, OperatorMinus) {
    CantorovoSet s1("{1,2,3}");
    CantorovoSet s2("{2,3}");
    CantorovoSet result = s1 - s2;
    EXPECT_EQ(capturePrint(result), "{{1}}\n");
}

TEST(CantorovoSetTest, OperatorMinusEqual) {
    CantorovoSet s1("{1,2,3}");
    CantorovoSet s2("{2,3}");
    s1 -= s2;
    EXPECT_EQ(capturePrint(s1), "{{1}}\n");
}

TEST(CantorovoSetTest, OperatorIndex) {
    CantorovoSet s("{1,2,3}");
    EXPECT_TRUE(s["1"]);
    EXPECT_TRUE(s["2"]);
    EXPECT_FALSE(s["4"]);
}

TEST(CantorovoSetTest, InvalidBrackets) {
    std::string in = "{1,2,{3";
    CantorovoSet s(in);
    std::string output = capturePrint(s);
    EXPECT_TRUE(output == "{{}}\n" || output.find("{1},{2}") != std::string::npos);
}

TEST(CantorovoSetTest, VeryDeepNested) {
    std::string in = "{{{{1},{2}},{{3}}},{{4,5}}}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrint(s), "{{{{1},{2}},{{3}}},{{4,5}}}\n");
}

TEST(CantorovoSetTest, CantorSingleElement) {
    std::string in = "{42}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrintCantor(s), "{{42}}\n");
}

TEST(CantorovoSetTest, CantorEmptySet) {
    std::string in = "{}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrintCantor(s), "{{}}\n");
}

TEST(CantorovoSetTest, StressTestLarge) {
    std::string in = "{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}";
    CantorovoSet s(in);
    std::string output = capturePrintCantor(s);
    EXPECT_TRUE(output.find("{1}") != std::string::npos);
    EXPECT_TRUE(output.find("{20}") != std::string::npos);
}

TEST(CantorovoSetTest, NestedEmptySets) {
    std::string in = "{{},{},{},{}}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrint(s), "{{},{},{},{}}\n");
}

TEST(CantorovoSetTest, DuplicateElements) {
    std::string in = "{1,1,2,2,3}";
    CantorovoSet s(in);
    EXPECT_EQ(capturePrint(s), "{{1},{1},{2},{2},{3}}\n");
}

TEST(CantorovoSetTest, CopySet) {
    CantorovoSet s;
    s.CopySet("{1,2,3}");
    EXPECT_EQ(capturePrint(s), "{{1},{2},{3}}\n");
}

std::string capturePrintBoolean(CantorovoSet &s) {
    std::ostringstream oss;
    auto old = std::cout.rdbuf(oss.rdbuf());
    s.printBoolean(s.getElements());
    std::cout.rdbuf(old);
    return oss.str();
}

TEST(CantorovoSetTest, PrintBoolean) {
    CantorovoSet s("{1,2}");
    std::string output = capturePrintBoolean(s);
    EXPECT_TRUE(output.find("{}") != std::string::npos); 
    EXPECT_TRUE(output.find("{{1}}") != std::string::npos); 
    EXPECT_TRUE(output.find("{{2}}") != std::string::npos); 
    EXPECT_TRUE(output.find("{{1}{2}}") != std::string::npos); 
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}