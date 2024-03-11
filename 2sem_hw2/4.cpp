#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
    string s;
    cout << "Enter bracket sequence: ";
    cin >> s;


    stack <char> brackets;
    //в этой задаче удобно использовать стек

    bool flag = true;

    for (char c : s)
    {
        if (c == '(' || c == '[' || c == '{')
        {
            brackets.push(c);
        }
        else
        {
            if (brackets.empty())
            {
                flag = false;
                break;
            }

            char top = brackets.top();
            if ((c == ')' && top == '(') || (c == ']' && top == '[') || (c == '}' && top == '{'))
            {
                brackets.pop();
            }
            else
            {
                flag = false;
                break;
            }
        }
    }

    if (flag && brackets.empty())
    {
        cout << "FINE" << endl;
    }
    else
    {
        cout << "WRONG" << endl;
    }
    return 0;
}
