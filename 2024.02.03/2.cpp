#include <iostream>
#include <vector>

using namespace std;

//получение суммы квадратов цифр числа
int procedure(int x)
{
    int res = 0;
    while (x != 0)
    {
        res += (x % 10)*(x % 10);
        x = x / 10;
    }
    return res;
}

int main()
{
    int N;
    cout << "Enter a number to check: ";
    cin >> N;

    vector <int> A;
    A.push_back(N);

    int i = 0;
    bool flag = true;
    while (flag)
    {
        A.push_back(procedure(A[i]));
        cout << A[i] << " ";
        if (A[i] == 1)
        {
            cout << "\n" << N << " is a lucky number" << endl;
            break;
        }
        for (int j = i - 1; j >= 0; j--)
        {
            if (A[j] == A[i])
            {
                cout << "\n" << N << " is not a lucky number" << endl;
                flag = false;
                break;
            }
        }
        i++;
    }
}


