#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

// Генерация случайных чисел в заданном диапазоне
int randomInt(int a, int b)
{
    return a + rand() % (b - a + 1);
}

// Функция для заполнения контейнера случайными числами
void fill_cont(vector<int>& container)
{
    srand(time(0));
    for (int i = 0; i < 10000; i++)
    {
        container.push_back(randomInt(1, 10000));
    }
}

// Сортировка пузырьком
void bubbleSort(vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Быстрая сортировка
void quickSort(vector<int>& arr, int low, int high)
{
    if (low < high)
    {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++)
        {
            if (arr[j] < pivot)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int part = i + 1;
        quickSort(arr, low, part - 1);
        quickSort(arr, part + 1, high);
    }
}

int main() {
    vector<int> A, B;

    fill_cont(A);

    B = A;

    // Измеряем время выполнения сортировки пузырьком
    clock_t start_time = clock();
    bubbleSort(A);
    clock_t end_time = clock();
    double time_bubbleSort = double(end_time - start_time) / CLOCKS_PER_SEC;

    // Измеряем время выполнения быстрой сортировки
    start_time = clock();
    quickSort(B, 0, B.size() - 1);
    end_time = clock();
    double time_quickSort = double(end_time - start_time) / CLOCKS_PER_SEC;

    // Результаты
    cout << "Bubble sort time: " << time_bubbleSort << " seconds" << endl;
    cout << "Quick sort time: " << time_quickSort << " seconds" << endl;

    if (time_bubbleSort < time_quickSort)
    {
        cout << "Bubble sort is faster" << endl;
    }
    else
    {
        cout << "Quick sort is faster" << endl;
    }
    return 0;
}
