#include <iostream>
#include "myStack_s156d039.hpp"
#include <string>

class myInfixPostfix
{
    public:
        myInfixPostfix(void)
        {
        }

        ~myInfixPostfix()
        {

        }

        int prec(char c) 
        { 
            if(c == '^') 
            return 3; 
            else if(c == '*' || c == '/') 
            return 2; 
            else if(c == '+' || c == '-') 
            return 1; 
            else
            return -1; 
        }

        std::string getPostfix(std::string str)
        {
            std::string res = "";
            std::string num = "";
            int len = str.length();
            for(int i = 0; i < len; i++)
            {

                if((int)str[i] > 47 && (int)str[i] < 58)
                {
                    num+=str[i];
                }
                else if(str[i]== ' ')
                {
                    continue;
                }
                else if(str[i]== '(')
                {
                    s.push('(');
                }
                else if(str[i] == ')') 
                { 
                    if(num.length()!=0){
                        res+= "(" + num + ")";
                        num = "";
                    }
                    while(s.empty() == 0 && s.top() != '(') 
                    { 
                        res += s.pop();
                    } 
                    if(s.top() == '(') 
                    { 
                        char c = s.pop(); 
                    } 
                }
                else
                { 
                    if(num.length()!=0){
                        res+= "(" + num + ")";
                        num = "";
                    }
                    while(s.empty() == 0 && prec(str[i]) <= prec(s.top())) 
                    { 
                        res += s.pop();
                    } 
                    s.push(str[i]);
                }     
            }
            
            return res;
        }

        float PostfixCalculator(std::string exp)
        {
            myStack<float> temp;
            int len = exp.length();
            for(int i = 0; i < len; i++)
            {
                if(exp[i] == '(')
                {
                    std::string num = "";
                    i++;
                    while(exp[i] != ')'){
                        num+=exp[i];
                        i++;
                    }
                    temp.push(stoi(num));
                }
                else
                {
                    float val1 = temp.pop();  
                    float val2 = temp.pop();  
                    switch (exp[i])  
                    {  
                        case '+': temp.push(val2 + val1); break;  
                        case '-': temp.push(val2 - val1); break;  
                        case '*': temp.push(val2 * val1); break;  
                        case '/': temp.push(val2/val1); break;  
                    }
                } 
            }
            return temp.pop();
        }
        // void test(std::string test)
        // {
        //     std::string mep = getPostfix(test);
        //     std::cout << mep << std::endl;
        // }
    private:
        myStack<char> s;
        
};