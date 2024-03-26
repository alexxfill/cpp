// реализация простой хеш-таблицы
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// класс, представляющий элемент хэш-таблицы
class H_element
{
public:
    H_element(string key, int value): key(key), value(value), next(nullptr) {}

    string getKey()
    {
        return key; // вернуть ключ
    }

    int getValue()
    {
        return value; // вернуть значение
    }

    void setValue(int newValue)
    {
        value = newValue; // установить значение
    }

    H_element* getNext()
    {
        return next; // вернуть указатель на след. элемент
    }

    void setNext(H_element* newNext) // уст. указатель на след. элемент
    {
        next = newNext;
    }

private:
    string key;
    int value;
    H_element* next;
};

// класс, представляющий хэш-таблицу
class HashTable
{
public:
    HashTable(int Size) : tableSize(Size), table(Size, nullptr) {}

    // хэширование (методом остатка)
    int hash_func(string key)
    {
        int sum = 0;
        for (char ch: key)
        {
            sum += ch;
        }
        return sum % tableSize;
    }

    // метод вставки элемента
    void hash_insert(string key, int value)
    {
        int hashValue = hash_func(key);
        H_element* newElem = new H_element(key, value);

        // метод цепочек для разрешения коллизий
        if (table[hashValue] == nullptr)
        {
            table[hashValue] = newElem;
        }

        else
        {
            H_element* current = table[hashValue];
            while (current->getNext() != nullptr)
            {
                current = current->getNext();
            }
            current->setNext(newElem);
        }
    }

    // поиск элемента по ключу
    // (в случае обнаружения возврашает значение соотв. ключу)
    int get(string key)
    {
        int hashValue = hash_func(key);
        H_element* current = table[hashValue];
        while (current != nullptr)
        {
            if (current->getKey() == key)
            {
                return current->getValue();
            }
            current = current->getNext();
        }
        return -1; // элемент не найден
    }

private:
    int tableSize;
    vector <H_element*> table;
};

int main() 
{
    HashTable HashTable(10); //хэш-таблица размера 10

    HashTable.hash_insert("A", 5);
    HashTable.hash_insert("B", 7);
    HashTable.hash_insert("C", 3);

    // поиск элемента
    cout << "Value for key 'A': " << HashTable.get("A") << endl;
    cout << "Value for key 'B': " << HashTable.get("B") << endl;
    cout << "Value for key 'C': " << HashTable.get("C") << endl;
    cout << "Value for key 'D': " << HashTable.get("D") << endl; // элемент не найден

    return 0;
}
