#include <iostream>
#include <vector>
#include <string>

using namespace std;

int fact(int x)
{
    int res = 1;
    for (int i = 1; i <= x; i++)
    {
        res *= i;
    }
    return res;
}

int main()
{
    string S;
    // искомое представление в факториальной с.с.

    int N, N1;
    cout << "Enter a number: ";
    cin >> N;
    N1 = N;

    int i = 1;
    bool flag = true;
    int digits_num = 0; // итоговое кол-во разрядов

    vector <int> A ;

    while (flag)
    {
      A.push_back(fact(i));
      if (fact(i) >= N)
      {
        digits_num = i;
        flag = false;
      }
      i++;

    }

    for (int k = digits_num; k >= 1; k--)
    {
        S += to_string(N / A[k - 1]);
        S += "|";
        N = N % A[k - 1];
    }

    if (S[0] == '0')
    {
        S.erase(0,2);
    }

    S.erase(S.length() - 1,1);

    cout << "Number " << N1 << " in factorial notation: " << S;
}
