//Задача: Разобраться, что делает код https://pastebin.com/NuG8QWYL﻿
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <string>

// Условные переменные для синхронизации между менеджером и охранником
std::condition_variable g_Bell;
std::condition_variable_any g_Door;

// Класс Manager представляет собой менеджера, который приходит на работу
class Manager
{
public:
    void ComeToWork()
    {
        // Менеджер просит охранника открыть дверь
        std::cout << "Hey security, please open the door!\n";
        // Менеджер использует звонок, чтобы привлечь внимание охранника
        g_Bell.notify_one();
        std::mutex mutex;
        mutex.lock();
        // Менеджер ждёт пока ему откроют
        g_Door.wait(mutex);
        mutex.unlock();
    }
};

// Класс Security представляет собой охранника, который открывает дверь для менеджера и уведомляет программистов
class Security
{
    static bool m_SectorClear; // флаг, показывающий, чист ли сектор
    static std::mutex m_SectorMutex; // мьютекс для синхронизации доступа к флагу m_SectorClear
public:
    // Функция для проверки, чист ли сектор
    static bool SectorClear()
    {
        std::lock_guard<std::mutex> lock(m_SectorMutex);
        return m_SectorClear;
    }
    // Функция для уведомления коллег о приходе менеджера
    void NotifyFellows()
    {
        std::lock_guard<std::mutex> lock(m_SectorMutex);
        m_SectorClear = false; // в зоне видимости есть менеджер
    }
    // Функция, в которой охранник работает и открывает дверь для менеджера
    void WorkHard()
    {
        m_SectorClear = true;
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        while(true)
        {
            if(g_Bell.wait_for(lock, std::chrono::seconds(5)) == std::cv_status::timeout) // охранник ждёт звонка 5 секунд
                std::this_thread::sleep_for(std::chrono::seconds(10)); // если прошло 5 секунд, охранник спит 10 секунд
            else
            {
                // Если менеджер позвонил, охранник уведомляет коллег и открывает дверь
                NotifyFellows();
                g_Door.notify_one();
                std::cout << "Hello Great Manager, your slaves are ready to serve you!\n" << std::endl;
            }
        }
    }
};

// Инициализация флага и мьютекса
bool Security::m_SectorClear;
std::mutex Security::m_SectorMutex;

// Класс Programmer представляет собой программиста,
// который работает или играет в Starcraft
// (в зависимости от того, пришел ли менеджер)
class Programmer
{
public:
    // Функция, в которой программист работает
    void WorkHard()
    {
        std::cout << "Let's write some govnokod!\n" << std::endl;
        int i = 0;
        while(true)
        {
            i++;
            i--;
        }
    }
    // Функция, в которой программист играет в Starcraft, если менеджер еще не пришел, иначе работает
    void PlayStarcraft()
    {
        while(Security::SectorClear()) // если сектор чист
            ; //играем! :)
        WorkHard();// работаем :(
    }
};

int main()
{
    Manager manager;
    Programmer programmer;
    Security security;

    // Лямбда-функции для запуска в потоках
    // (вызывают соответствующие методы менеджера, охранника и программиста)
    auto managerCall = [&manager]()
        {
            manager.ComeToWork();
        };
    auto programmerCall = [&programmer]()
        {
            programmer.PlayStarcraft();
        };
    auto securityCall = [&security]()
        {
            security.WorkHard();
        };

    // Создание потоков для каждого из объектов
    std::thread securityThread(securityCall);     
    std::thread programmerThread(programmerCall);
    std::this_thread::sleep_for(std::chrono::minutes(1));
    std::thread managerThread(managerCall);

    // Ожидание завершения всех потоков
    managerThread.join();
    programmerThread.join();
    securityThread.join();

    return 0;
}
