#include <iostream>

using namespace std;

int bin_find(int a[], int r, int x)
{
    int l = 0;
    int mid;
    while (l <= r)
    {
        mid = (l + r)/2;
        if (a[mid] == x)
        {
            return mid;
        }

        if (a[mid] > x)
        {
            r = mid - 1;
        }

        if (a[mid] < x)
        {
            l = mid + 1;
        }
    }
    return -1;
}

int main()
{
    int a[] = {0,1,2,3,4,5};
    int element_to_find = 3;

    int r = sizeof(a)/sizeof(int) - 1;
    cout << "index(from 0): "<< bin_find(a, r, element_to_find);
}
