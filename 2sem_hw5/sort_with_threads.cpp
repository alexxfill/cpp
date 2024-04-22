//Задача: Используя многопоточное программирование, отсортировать массив
#include <iostream>
#include <vector>
#include <thread>

using namespace std;

//Используем алгоритм сортировки слиянием,
//который разбивает массив на две половины, сортирует их отдельно
//в разных потоках (рекурсивно), а затем сливает их вместе

void arr_merge(vector<int>& arr, int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    vector<int> left(n1);
    vector<int> right(n2);

    for (int i = 0; i < n1; i++)
    {
         left[i] = arr[low + i];
    }

    for (int j = 0; j < n2; j++)
    {
         right[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i = i + 1;
        }

        else
        {
            arr[k] = right[j];
            j = j + 1;
        }

        k = k + 1;
    }

    while (i < n1)
    {
        arr[k] = left[i];
        i = i + 1;
        k = k + 1;
    }

    while (j < n2)
    {
        arr[k] = right[j];
        j = j + 1;
        k = k + 1;
    }
}

void mergeSort(vector<int>& arr, int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;

        thread leftThread(mergeSort, ref(arr), low, mid);
        thread rightThread(mergeSort, ref(arr), mid + 1, high);

        //ждём пока оба потока закончат
        leftThread.join();
        rightThread.join();

        //соединяем отсортированные половины
        arr_merge(arr, low, mid, high);
    }
}

int main()
{
    vector<int> arr = {9, 7, 11, 12, 2, 14, 3, 7, 6};
    mergeSort(arr, 0, arr.size() - 1);

    for(int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}
