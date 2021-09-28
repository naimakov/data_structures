#include <iostream>
#include <assert.h>
#include <stack>
#include <string>
#include <ctime>
#include <random>

using std::cin;
using std::cout;

time_t t_start, t_end;

/**
 * Check brackets in the code
 * Implement a feature to find errors in the usage of brackets in the code.
 * Input: 
 *      string S, consisting of latin letters, digits, 
 *      punctuation marks and brackets from []{}()
 * Output: 
 *      If brackets usage is correct, then "Success"
 *      else -> 1-based index of the first unmatched closing bracket.
 *      If no closing bracket unmatching, first unmatched opening bracket.
 * Constraints: 
 *      1<=|S|<=10^5
 * Time limit: 1 sec
 * Memory limit: 512 mb
*/
void tic(int mode=0)
{ 
    if (mode==0)
        t_start = time(0);
    else
    {
        t_end = time(0);
        cout<< "Elapsed time is " << difftime(t_end,t_start) << " seconds\n";
    }
}
void toc(){ tic(1); }

struct Bracket 
{
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

std::string check_brackets(std::string text)
{
    int flag = 1;

    std::stack <Bracket> opening_brackets_stack;
    for (size_t position = 0; position < text.length(); ++position) 
    {
        char next = text[position]; 

        if (next == '(' || next == '[' || next == '{') 
        {
            opening_brackets_stack.push(Bracket(next,position+1));
        }

        if (next == ')' || next == ']' || next == '}') 
        {
            if(!opening_brackets_stack.empty() && opening_brackets_stack.top().Matchc(next))
                opening_brackets_stack.pop();
            else
            {
                opening_brackets_stack.push(Bracket(next,position+1));
                flag = 0;
                break;
            }
        }
    }
    if(opening_brackets_stack.empty())
        return "Success";
    else
    {
        if(flag)
        {
            while(opening_brackets_stack.size() > 1)
            {
                opening_brackets_stack.pop();
            }
            return std::to_string(opening_brackets_stack.top().position);
        }
        else
            return std::to_string(opening_brackets_stack.top().position);
    }
}

std::string random_string(int length)
{
    int random_index;
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,;:!?(){}[]");

    std::random_device rd;
    std::mt19937 re(rd());
    std::uniform_int_distribution<int> rand_n(0,str.size()-1);

    std::string res = "";
    for(int i = 0; i < length; i++){
        random_index = rand_n(re); //get index between 0 and str.size()-1
        res += str[random_index];
    }
    return res;
}

int main() 
{
    assert(check_brackets("[]").compare("Success") == 0);
    assert(check_brackets("{}[]").compare("Success") == 0);
    assert(check_brackets("[()]").compare("Success") == 0);
    assert(check_brackets("(())").compare("Success") == 0);
    assert(check_brackets("{[]}()").compare("Success") == 0);
    assert(check_brackets("{").compare("1") == 0);
    assert(check_brackets("{[}").compare("3") == 0);
    assert(check_brackets("foo(bar)").compare("Success") == 0);
    assert(check_brackets("foo(bar[i)").compare("10") == 0);
    assert(check_brackets("()[]({}[(])").compare("10") == 0);
    assert(check_brackets("()[]({}[()]").compare("5") == 0);
    assert(check_brackets(")") == "1");

    std::cout << "All tests passed\n";

    int n;
    std::cin >> n;
    std::string ran_str = random_string(n);
    std::cout << ran_str << "\n";
    tic();
    std::cout << check_brackets(ran_str) << "\n";
    toc();

    //std::string text;
    //getline(std::cin, text);

    //tic();
    //std::cout << check_brackets(text) << "\n";
    //toc();

    return 0;
}
