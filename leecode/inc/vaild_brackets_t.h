#ifndef _vaild_brackets__t_h_
#define _vaild_brackets__t_h_
#include <iostream>
#include <stack>

using namespace std;

char bracket_correspond(const char& c)
{
    switch(c){
        case '}':return '{';
        case ']':return '[';
        case ')':return '(';
        default:return '\0';break;
    }
}

bool vaild_brackets_t_fi(const string& s)
{
    cout << ">> this is vaild_bracket test\n";
    uint s_size = s.size();
    if(s_size%2) return NULL;
    if(s.size() == 0) return true;
    stack<char> stack0;
    stack0.push(s[0]);
    for(auto iter = s.begin() + 1; iter != s.end(); ++iter){
        if(stack0.size() == 0){
            stack0.push(*iter);
        }
        else if(stack0.top() == bracket_correspond(*iter)){
            stack0.pop();
        }
        else{
            stack0.push(*iter);
        }
    }
    if(stack0.size()) return  NULL;
    return true;
}

#endif