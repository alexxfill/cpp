#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

const int num_philosophers = 5; // кол-во философов и, соответственно, вилок

using std::mutex;
using std::thread;
using std::cout;
using std::vector;

// Возможное решение задачи - добавление официанта возле стола.
// Философы должны дожидаться разрешения официанта перед тем, как взять вилку.
// Поскольку официант знает, сколько вилок используется в данный момент, он
// может принимать решения относительно распределения вилок и
// тем самым предотвратить взаимную блокировку философов (deadlock).
// т.е. это семафор

mutex forks[num_philosophers];
mutex waiter;

void lunch(int philosopher_number)
{
    while (true)
    {
        cout << "Philosopher " << philosopher_number << " thinking.\n";\
        std::this_thread::sleep_for(std::chrono::milliseconds(4000));

        // Спросить у официанта разрешение на еду
        waiter.lock();
        forks[philosopher_number].lock(); // правая вилка
        forks[(philosopher_number + 1) % num_philosophers].lock(); // левая вилка
        waiter.unlock();

        cout << "Philosopher " << philosopher_number << " eat.\n";

        // Философ кладет вилки на место
        forks[philosopher_number].unlock();
        forks[(philosopher_number + 1) % num_philosophers].unlock();

        cout << "\n";
    }
}

int main()
{
    vector<thread> philosophers;

    for (int i = 0; i < num_philosophers; i++)
    {
        philosophers.push_back(thread(lunch, i));
    }

    for (auto& ph : philosophers)
    {
        ph.join();
    }

    return 0;
}
