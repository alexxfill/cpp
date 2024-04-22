//Задача: Используя многопоточное программирование, найти
// сумму 3 самых больших элементов массива, заполненного случайными числами
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <iostream>

using namespace std;

mutex mtx;
priority_queue<int> pq;
//Каждый поток обработает свою часть массива и добавит
//три наибольших числа в приоритетную очередь

//После завершения всех потоков из приоритетной очереди
//извлекаются три наибольших числа и суммируются

//P.S. priority_queue
// 1) приоритетная очередь автоматически сортирует элементы
// 2) pq объявляем как глобальную переменную


//функция для вычисления суммы трех наибольших элементов в массиве
void SumTop3(vector<int>& arr, int arr_start, int arr_end)
{
    for (int i = arr_start; i < arr_end; i++)
    {
        //безопасность потока
        mtx.lock();

        if (pq.size() < 3)
        {
            pq.push(arr[i]);
        }

        else if (arr[i] > pq.top())
        {
            pq.pop();
            pq.push(arr[i]);
        }

        mtx.unlock();
    }
}

int main()
{
    srand(time(0));

    vector<int> arr(1000);

    for (int i = 0; i < 1000; ++i)
    {
        arr[i] = rand() % 1000;
    }

    //воспользуемся рекомендацией: кол-во потоков <= кол-во ядер
    int numThreads = 4;

    vector<thread> threads(numThreads);

    //размер подмассива для каждого потока
    int partSize = arr.size() / numThreads;

    for (int i = 0; i < numThreads; i++)
    {
        threads[i] = thread(SumTop3, ref(arr), i * partSize, (i + 1) * partSize);
    }

    for (thread& th : threads)
    {
        th.join();
    }

    int sum = 0;
    while (pq.empty() == false)
    {
        sum += pq.top();
        pq.pop();
    }

    cout << "Sum of three largest numbers: " << sum << endl;

    return 0;
}

