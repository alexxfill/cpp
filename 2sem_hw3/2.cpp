// генеалогическое дерево
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;

    map <string, string> parents; // хранит родителя для каждого члена семьи
    map <string, int> heights; // хранит "высоту" каждого члена семьи
    vector <string> names;

    string child, parent;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> child >> parent;
        parents[child] = parent;
        names.push_back(child);
    }

    // находим родоначальника
    string root;
    for (auto pair: parents)
    {
        if (parents.find(pair.second) == parents.end())
        {
            root = pair.second;
            break;
        }
    }

    // заполняем высоты всех членов семьи
    heights[root] = 0;
    names.insert(names.begin(), root);

    for (int i = 0; i < names.size(); i++)
    {
        string name = names[i];
        for (auto pair: parents)
        {
            if (pair.second == name)
            {
                heights[pair.first] = heights[name] + 1;
            }
        }
    }

     // cортируем имена членов семьи в лексикографическом порядке
    sort(names.begin(), names.end());

    cout << endl;

    // вывод имён
    for (string name: names)
    {
        cout << name << " " << heights[name] << endl;
    }

    return 0;
}
