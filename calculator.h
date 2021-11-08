#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
using namespace std;
class Calculator
{
private:
    vector<string> expRPN;//后缀表达式
    string expMid;//中缀表达式
    unsigned int leftBracket;//左括号计数 避免左右括号不匹配
    unsigned char inputConstraints;
    string nextJumpRecord;
    /*输入限制:
         * 0000000 Nothing acceptable
         * 1000000 开平方根
         * 0100000 accept (
         * 0010000 accept +-*%/^开平方根
         * 0001000 accept 整数
         * 0000100 accept 小数点
         * 0000010 accept 小数位
         * 0000001 accept 负号
    */
    void generateRPN();
public:
    Calculator();
    void initialize(string &expMid);
    string do_calculate();
    string getExpMid();
    bool check_push_exp(const char&);
    bool check_push_exp(const string&);
    void reset();
    string backspace();
};

#endif // CALCULATOR_H
