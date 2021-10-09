#include <iomanip>  // std::setw
#include <iostream> // std::cout
#include <map>      // std::map
#include <vector>   // std::vector

std::map<int, int> output{};

void generateDieRolls(const std::vector<int>& dice, const std::vector<int>::size_type index = 0, int sum = 0)
{
    for(int i = 1; i <= dice[index]; ++i)
    {
        ++sum;
        if(index < dice.size() - 1)
            generateDieRolls(dice, index + 1, sum);
        else
            ++output[sum];
    }
}

void printOutput()
{
    for(const auto p : output)
        std::cout << std::setw(3) << p.first << ": " << std::string(p.second, '+') << '\n';
    std::cout << '\n';
}

int main()
{
    // 3d6
    generateDieRolls({6,6,6});
    printOutput();
}
