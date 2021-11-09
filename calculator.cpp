#include "calculator.h"
#include <cmath>
/*输入限制:
     * 0000000 Nothing acceptable
     * 1000 0000 开平方根
     * 0100 0000 accept (
     * 0010 0000 accept )
     * 0001 0000 accept +-*%/^
     * 0000 1000 accept 整数
     * 0000 0100 accept 小数点
     * 0000 0010 accept 仅小数位
     * 0000 0001 accept 负号
     * 初始值 1100 1101
     * :operator +-/*%^    :number 0-9  :. :sqrt :负号 :左括号 :右括号 :0.
*/
Calculator::Calculator():expMid(""),leftBracket(0),inputConstraints(0b11001011),nextJumpRecord("")
{
    //
    nextJumpRecord.append(1,0b11001011);
}

//判断中缀表达式是否合法 并用来初始化
void Calculator::initialize(string &expMid)
{
    //判断中缀表达式是否合法

}

//重置中缀表达式和后缀表达式
void Calculator::reset()
{
    expMid="";
    expRPN.clear();
    leftBracket=0;
    inputConstraints = 0b11001011;
    nextJumpRecord.clear();
    nextJumpRecord.append(1,inputConstraints);
}

//退格并返回删除最后一个字符后的string
string Calculator::backspace()
{
    if(!expMid.empty())
    {
        string sqt="√";
        if(expMid.size() >= sqt.size() && expMid.compare(expMid.size()-sqt.size(),sqt.size(),sqt)==0)
        {
            expMid.erase(expMid.size()-sqt.size(),sqt.size());
        }
        else{
            this->expMid.erase(expMid.end()-1);
        }
        nextJumpRecord.erase(nextJumpRecord.end()-1);
        inputConstraints = nextJumpRecord.back();
    }
    return expMid;
}

//计算后缀表达式
string Calculator::do_calculate()
{
    generateRPN();
    stack<double> opNumStack;
    double leftNum(0),rightNum(0);
    for(auto it = expRPN.begin();it != expRPN.end();++it)
    {
        string curToken=*it;
        if(curToken.front() >= '0' && curToken.front() <= '9')
        {
            opNumStack.push(stod(curToken));
        }
        else
        {
            if(opNumStack.empty())return "OpNum doesn't match Operator";
            rightNum = opNumStack.top();
            opNumStack.pop();
            if(curToken == "√")
            {
                opNumStack.push(sqrt(rightNum));
            }
            else{
                if(opNumStack.empty())return "OpNum doesn't match Operator";
                leftNum = opNumStack.top();
                opNumStack.pop();
                if(curToken == "+"){opNumStack.push(leftNum+rightNum);continue;}
                if(curToken == "-"){opNumStack.push(leftNum-rightNum);continue;}
                if(curToken == "*"){opNumStack.push(leftNum*rightNum);continue;}
                if(curToken == "%"){opNumStack.push(fmod(leftNum,rightNum));continue;}
                if(curToken == "/"){if(rightNum==0.0)return "divisor can't be 0";opNumStack.push(leftNum/rightNum);continue;}
                if(curToken == "^"){opNumStack.push(pow(leftNum,rightNum));continue;}
            }
        }
    }
    if(opNumStack.size()!=1)return "OpNum doesn't match Operator";
    return to_string(opNumStack.top());
}

//生成后缀式
void Calculator::generateRPN()
{//( > "√" > */%^ > +- > )
    string curToken="",cmpOp="";
    bool isNum(false);
    string sqt = "√";
    //constexpr char sqt0 = -95;//magic number!!!不同编码的"√"不一样
    char sqt0 = sqt[0];
    stack<string> opStack;
    unsigned int leftBracketCount = 0;
    for(auto it = expMid.begin();it != expMid.end();++it){
        char ch = *it;
        switch (ch) {
        case '+':
            if(isNum){
                expRPN.push_back(curToken);
                curToken.clear();
                isNum=false;
            }
            while(!opStack.empty())
            {
                cmpOp = opStack.top();
                if(cmpOp =="√" || cmpOp =="^" || cmpOp =="*" || cmpOp =="/" || cmpOp =="%" || cmpOp =="-" || cmpOp == "+")
                {
                    expRPN.push_back(cmpOp);
                    opStack.pop();
                }
                else break;
            }
            opStack.push("+");
            break;
        case '-':
            if(isNum){
                expRPN.push_back(curToken);
                curToken.clear();
                isNum=false;
            }
            while(!opStack.empty())
            {
                cmpOp = opStack.top();
                if(cmpOp =="√" || cmpOp =="^" || cmpOp =="*" || cmpOp =="/" || cmpOp =="%" || cmpOp =="-" || cmpOp == "+")
                {
                    expRPN.push_back(cmpOp);
                    opStack.pop();
                }
                else break;
            }
            opStack.push("-");
            break;
        case '*':
            if(isNum){
                expRPN.push_back(curToken);
                curToken.clear();
                isNum=false;
            }
            while(!opStack.empty())
            {
                cmpOp = opStack.top();
                if(cmpOp =="√" || cmpOp =="^" || cmpOp =="*" || cmpOp =="/" || cmpOp =="%")
                {
                    expRPN.push_back(cmpOp);
                    opStack.pop();
                }
                else break;
            }
            opStack.push("*");
            break;
        case '/':
            if(isNum){
                expRPN.push_back(curToken);
                curToken.clear();
                isNum=false;
            }
            while(!opStack.empty())
            {
                cmpOp = opStack.top();
                if(cmpOp =="√" || cmpOp =="^" || cmpOp =="*" || cmpOp =="/" || cmpOp =="%")
                {
                    expRPN.push_back(cmpOp);
                    opStack.pop();
                }
                else break;
            }
            opStack.push("/");
            break;
        case '%':
            if(isNum){
                expRPN.push_back(curToken);
                curToken.clear();
                isNum=false;
            }
            while(!opStack.empty())
            {
                cmpOp = opStack.top();
                if(cmpOp =="√" || cmpOp =="^" || cmpOp =="*" || cmpOp =="/" || cmpOp =="%")
                {
                    expRPN.push_back(cmpOp);
                    opStack.pop();
                }
                else break;
            }
            opStack.push("%");
            break;
        case '^':
            if(isNum){
                expRPN.push_back(curToken);
                curToken.clear();
                isNum=false;
            }
            while(!opStack.empty())
            {
                cmpOp = opStack.top();
                if(cmpOp =="√" || cmpOp =="^" || cmpOp =="*" || cmpOp =="/" || cmpOp =="%")
                {
                    expRPN.push_back(cmpOp);
                    opStack.pop();
                }
                else break;
            }
            opStack.push("^");
            break;
        case '(':
            if(isNum){
                expRPN.push_back(curToken);
                curToken.clear();
                isNum=false;
            }
            opStack.push("(");
            ++leftBracketCount;
            break;
        case ')':
            if(isNum){
                expRPN.push_back(curToken);
                curToken.clear();
                isNum=false;
            }
            while(!opStack.empty()&&leftBracketCount>0)
            {
                if(opStack.top() != "(")
                {
                    expRPN.push_back(opStack.top());
                    opStack.pop();
                }
                if(opStack.top() == "(")
                {
                    opStack.pop();
                    --leftBracketCount;
                    break;
                }
            }
            break;
        case '.':
            if(isNum)curToken.append(1,ch);
            break;
        default:
            if(ch>='0' && ch <= '9')
            {
                isNum=true;
                curToken.append(1,ch);
            }
            if(ch == sqt0){
                if(isNum){
                    expRPN.push_back(curToken);
                    curToken.clear();
                    isNum=false;
                }
                //assert(*(it+1)==-52)
                it += (sqt.size()-1);
                opStack.push("√");
                break;
            }
            break;
        }
    }
    if(!curToken.empty())expRPN.push_back(curToken);
    while(!opStack.empty())
    {
        expRPN.push_back(opStack.top());
        opStack.pop();
    }
}

string Calculator::getExpMid()
{
    return this->expMid;
}

//判断能否往中缀表达式里添加
bool Calculator::check_push_exp(const char& ch)
{/*输入限制:
     * 0000000 Nothing acceptable
     * 1000 0000 开平方根
     * 0100 0000 accept (
     * 0010 0000 accept )
     * 0001 0000 accept +-*%/^
     * 0000 1000 accept 整数
     * 0000 0100 accept 小数点
     * 0000 0010 accept 仅小数位
     * 0000 0001 accept 负号
     * 初始值 1100 1101
*/
    bool syntax_right(false);
    switch (ch) {
    case '+':
        if((0b00010000&inputConstraints) != 0)
        {
            syntax_right = true;
            inputConstraints = 0b11001010;
        }
        break;
    case '*':
        if((0b00010000&inputConstraints) != 0)
        {
            syntax_right = true;
            inputConstraints = 0b11001010;
        }
        break;
    case '%':
        if((0b00010000&inputConstraints) != 0)
        {
            syntax_right = true;
            inputConstraints = 0b11001010;
        }
        break;
    case '/':
        if((0b00010000&inputConstraints) != 0)
        {
            syntax_right = true;
            inputConstraints = 0b11001010;
        }
        break;
    case '^':
        if((0b00010000&inputConstraints) != 0)
        {
            syntax_right = true;
            inputConstraints = 0b11001010;
        }
        break;
    case '-':
        if((0b00010000&inputConstraints) != 0)
        {   //当-是作为运算符输入时
            syntax_right = true;
            inputConstraints = 0b11001010;
        }
        else if((0b00000001&inputConstraints) != 0)
        {
             //当-是作为负号输入时
            syntax_right = true;
            expMid.append(1,'0');
            nextJumpRecord.append(1,0b11111100);
            inputConstraints = 0b11001010;
        }
        break;
    case '.':
        if((0b00000100&inputConstraints) != 0)
        {
            syntax_right = true;
            inputConstraints = 0b00001000;
        }
        else if((0b00000010&inputConstraints) != 0)
        {
            syntax_right = true;
            expMid.append(1,'0');
            nextJumpRecord.append(1,0b11111100);
            inputConstraints = 0b00001000;
        }
        break;
    case '(':
        if((0b01000000&inputConstraints) != 0)
        {
            syntax_right = true;
            if(!expMid.empty() && expMid.back()>='0' && expMid.back()<='9' ){
                expMid.append(1,'*');
                nextJumpRecord.append(1,0b11001010);
            }
            ++leftBracket;
            inputConstraints = 0b11101011;
        }
        break;
    case ')':
        if(leftBracket>0 && (0b00100000&inputConstraints) != 0)
        {
            syntax_right = true;
            --leftBracket;
            inputConstraints = 0b11110000;
        }
        break;
    default:
        if(ch >= '0' && ch <= '9')
        {
            //if((nextJumpRecord.size()==1 && ch == '0'))return true;
            if((0b00001000&inputConstraints) != 0)
            {
                syntax_right = true;
                inputConstraints = (inputConstraints&0b00000110)==0 ? 0b11111000 : 0b11111100;
            }
        }
        break;
    }
    if(syntax_right){
        expMid.append(1,ch);
        nextJumpRecord.append(1,inputConstraints);
    }
    return syntax_right;
}
//处理像sqrt这种字符
bool Calculator::check_push_exp(const string& s)
{
    bool syntax_right(false);
    if(s == "√" && (0b10000000&inputConstraints) != 0)
    {
        syntax_right = true;
        if(!expMid.empty() && expMid.back()>='0' && expMid.back()<='9' || expMid.back()==')'){
            expMid.append(1,'*');
            nextJumpRecord.append(1,0b11001100);
        }
        expMid.append("√");
        inputConstraints = 0b11001100;
        nextJumpRecord.append(1,inputConstraints);
    }
    return syntax_right;
}



