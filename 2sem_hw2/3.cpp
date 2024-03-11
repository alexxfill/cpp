#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    string text;
    getline(cin, text);

    map <string, int> word_freq;
    // частоту встречаемости слов удобно хранить в словаре


    // разбиваем строку на слова
    size_t pos = 0;
    string word;
    while ((pos = text.find(' ')) != text.npos)
    {
        word = text.substr(0, pos); // извлекаем слово из текста
        word_freq[word]++; // увеличиваем счётчик слова
        text.erase(0, pos + 1); // Удаляем слово из текста
    }

    if (!text.empty()) //обработка последнего слова
    {
        word_freq[text]++;
    }

    string most_frequent_word;
    int max_frequency = 0;
    //(в инете встретил интересную структуру pair)
    for (auto pair : word_freq)
    {
        if (pair.second > max_frequency)
        {
            max_frequency = pair.second;
            most_frequent_word = pair.first;
        }

        else if (pair.second == max_frequency && pair.first < most_frequent_word)
        {
            most_frequent_word = pair.first;
        }
    }

    cout << most_frequent_word << endl;

    return 0;
}
