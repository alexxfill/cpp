#include <iostream>
#include <vector>

using namespace std;

template <typename cont> //из прошлой задачи
void print(const cont& A, string sep)
{
    for(int i = 0; i < A.size(); i++)
    {
        cout << A[i];
        if (i != A.size() - 1)
        {
            cout << sep;
        }
    }
    cout << "\n";
}

int main()
{
    vector <int> A = {9,7,-4,-7,-3,5,-4,2,-1,1,0};
    vector <int> pos, neg;

    //чтобы не было перевыделений памяти
    pos.reserve(A.size());
    neg.reserve(A.size());

    //0 не войдёт ни в positive, ни в negative
    int it1 = -1;//итератор для pos
    int it2 = -1;//итератор для neg

    for(int i = 0; i < A.size(); i++)
    {
        if(A[i] > 0)
        {
            pos.push_back(A[i]);
            it1 = pos.size() - 1;
            while(pos[it1] < pos[it1 - 1] && it1 > 0)
            {
                swap(pos[it1], pos[it1 - 1]);
                it1--;
            }

        }

        if(A[i] < 0)
        {
            neg.push_back(A[i]);
            it2 = neg.size() - 1;
            while(neg[it2] < neg[it2 - 1] && it2 > 0)
            {
                swap(neg[it2], neg[it2 - 1]);
                it2--;
            }

        }

    }
    print(A," ");

    cout << "Positive: ";
    print(pos," ");

    cout << "Negative: ";
    print(neg," ");

    return 0;
}
