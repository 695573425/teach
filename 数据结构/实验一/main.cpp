#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stack>
#include <math.h>

using namespace std;

void transfor(string str,string* suffix)  //中缀变后缀
{
    string operators = ")+-*/%(";
    string p[str.length()];
    int i,j,k,m;
    j = k = m = 0;
    for(i=0; i<str.length(); i++)  //去掉输入的中缀表达式的空格
    {
        if (str[i]==' ')
            str.erase(i,1);
    }
    for(i=0; i<str.length(); i++)   //将去空格的中缀表达式字符串数字及运算符分开储存为字符串数组
    {
        if (str[i]==' ');
        else if (operators.find(str[i])==string::npos)
            j++;
        else if((str[i] == '-')&&(i==0||operators.find(str[i-1])!=string::npos))    //对负数的处理：将负数处理为（0-正数）
        {
            p[k++] = "0";
            p[k++] = str.substr(i,1);
            m=i+1;
        }
        else
        {
            if (i != m)
                p[k++] = str.substr(m,j);
            p[k++] = str.substr(i,1);
            m = i+1;
            j = 0;
        }
    }
    if(j!=0)
        p[k++] = str.substr(m,j);
    stack<string> s ;
    j = 0;
    for(i=0; i<k; i++)              //将中缀字符串数组转化为后缀字符串数组
    {
        if(operators.find(p[i])==string::npos)
                suffix[j++] = p[i];
        else if(p[i]!=")"&&
                (s.empty() || operators.find(s.top())<2 || operators.find(p[i])>=3||(operators.find(s.top())==2&& operators.find(p[i])>=3)|| s.top()=="("))
            s.push(p[i]);
        else if(p[i]==")")
        {
            while(s.top()!="(")
            {
                suffix[j++] = s.top();
                s.pop();
            }
            s.pop();
        }
        else
        {
            do{
                suffix[j++] = s.top();
                s.pop();
           }while(!s.empty() && s.top()!="(" && operators.find(s.top())>=2 && operators.find(p[i])<3
                 );

            s.push(p[i]);
        }

    }
    while(!s.empty())
    {
        suffix[j++] = s.top();
        s.pop();
    }
    suffix[j] = "";

}

double  postfix_calculate(string* str)    //计算后缀表达式结果
{
    string operators = "+-* /%";
    stack<double> s;
    double result,num_1,num_2;
    int i=0;
    while(str[i]!="")
    {
        if(operators.find(str[i])==string::npos)          //遇到数字时，将字符串转换为double型并压栈
           s.push(atof(str[i].c_str())) ;
        else if(str[i]=="+")                              //遇到运算符时，出栈两次，将得到的两数按运算符运算
        {
            num_2 = s.top();
            s.pop();
            num_1 = s.top();
            s.pop();
            result = num_1 + num_2;
            s.push(result);
        }
        else if(str[i]=="-")
        {
            num_2 = s.top();
            s.pop();
            num_1 = s.top();
            s.pop();
            result = num_1 - num_2;
            s.push(result);
        }
        else if(str[i]=="*")
        {
            num_2 = s.top();
            s.pop();
            num_1 = s.top();
            s.pop();
            result =num_1*num_2;
            s.push(result);
        }
        else if(str[i]=="/")
        {
            num_2 = s.top();
            s.pop();
            num_1 = s.top();
            s.pop();
            result =num_1/num_2;
            s.push(result);
        }
        else
        {
            num_2 = s.top();
            s.pop();
            num_1 = s.top();
            s.pop();
            result = fmod(num_1,num_2);
            s.push(result);
        }
        i++;
    }
    return result;
}
int main()
{

    string str ;
    string* str1 = new string[100];
    int i=0;
    cout<<"请输入一串中缀表达式："<<endl;
    getline(cin,str);
    transfor(str,str1);
    cout<<"转化后的后缀表达式为："<<endl;
    while(str1[i]!="")
        cout<<str1[i++]<<" ";
    cout<<endl;
    cout<<"运算结果为："<<postfix_calculate(str1)<<endl;
    return 0;
}
