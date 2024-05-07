#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

using std::mutex;
using std::vector;
using std::lock_guard;
using std::thread;
using std::cout;

template <typename T>
class ThreadSafeContainer
{
private:
    vector<T> container;
    mutable mutex mtx;
    // mutable - чтобы можно было изменять и в константных методах

public:
    // Добавление элемента в контейнер (в конец)
    void add(const T& element)
    {
        lock_guard<mutex> lock(mtx);
        container.push_back(element);
    }

    void pop() // Удаление элемента (с конца)
    {
        lock_guard<mutex> lock(mtx);
        if (!container.empty())
        {
            container.pop_back();
        }
    }

    // Удаление элемента по индексу
    void remove(int index)
    {
        lock_guard<mutex> lock(mtx);
        container.erase(container.begin() + index);
    }

    // Получение элемента по индексу
    T get(int index) const
    {
        lock_guard<mutex> lock(mtx);
        return container.at(index); // at() выбрасывает исключение, если индекс вне диапазона
    }

     typename vector<T>::iterator begin() // Итератор к первому элементу
    {
        lock_guard<mutex> lock(mtx);
        return container.begin();
    }

    typename vector<T>::iterator end() // Итератор к последнему элементу
    {
        lock_guard<mutex> lock(mtx);
        return container.end();
    }

    // Проверка, пуст ли контейнер
    bool isEmpty() const
    {
        lock_guard<mutex> lock(mtx);
        return container.empty();
    }

    // Получение размера контейнера
    size_t size() const
    {
        lock_guard<mutex> lock(mtx);
        return container.size();
    }
};

//----------------------------------------------
// Функция для добавления элементов в контейнер
void addElements(ThreadSafeContainer<int>& container)
{
    for (int i = 0; i < 10; i++)
    {
        container.add(i);
    }
};


// Функция для печати и удаления элементов из контейнера
void printDelete(ThreadSafeContainer<int>& container)
{
    while (!container.isEmpty())
    {
        int index = container.size() - 1;
        int value = container.get(index);
        cout << value << " ";
        container.remove(index);
    }
    cout << "\nIS_EMPTY: " << container.isEmpty();
};

int main()
{
    ThreadSafeContainer<int> cont;

    // Запускаем два потока:
    // (producer) добавляет элементы в контейнер,
    // а другой (consumer) печатает и удаляет элементы из контейнера.
    // Мьютексы внутри класса ThreadSafeContainer обеспечивают безопасность,
    // так что каждая операция с контейнером будет выполнена без
    // конфликтов между потоками.

    thread producer(addElements, std::ref(cont));
    thread consumer(printDelete, std::ref(cont));

    // Ожидаем завершения работы потоков
    producer.join();
    consumer.join();

    return 0;
}
