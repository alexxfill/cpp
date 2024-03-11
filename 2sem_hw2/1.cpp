#include <iostream>
#include <string>
#include <vector>

template <typename cont>
void print(const cont& A, std::string sep)
{
    for(int i = 0; i < A.size(); i++)
    {
        std::cout << A[i];
        if (i != A.size() - 1)
        {
            std::cout << sep;
        }
    }
    std::cout << "\n";
}

int main() {
    std::vector <int> numbers = {1, 2, 3, 4, 5};
    print(numbers, ", ");

    std::vector <std::string> words = {"hello", "world", "from", "C++"};
    print(words, "-");

    return 0;
}
