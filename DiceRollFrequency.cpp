#include <iomanip>  // std::setw
#include <iostream> // std::cout
#include <limits>   // std::numeric_limits
#include <map>      // std::map
#include <vector>   // std::vector

std::map<int, int> output{};

void genDieRolls(const std::vector<int>& dice, const std::vector<int>::size_type index = 0, int sum = 0)
{
    for(int i = 1; i <= dice[index]; ++i) {
        ++sum;
        if(index < dice.size() - 1)
            genDieRolls(dice, index + 1, sum);
        else
            ++output[sum];
    }
}

void genDieRolls_RemoveSmallest(const std::vector<int>& dice, const std::vector<int>::size_type index = 0, int sum = 0, const int minimum = std::numeric_limits<int>::max())
{
    for(int i = 1; i <= dice[index]; ++i) {
        int currentMinimum = std::min(minimum, i);
        ++sum;

        if(index < dice.size() - 1)
            genDieRolls_RemoveSmallest(dice, index + 1, sum, currentMinimum);
        else
            ++output[sum - currentMinimum];
    }
}

void genDieRolls_RemoveLargest(const std::vector<int>& dice, const std::vector<int>::size_type index = 0, int sum = 0)
{
    genDieRolls_RemoveSmallest(dice, index, sum, std::numeric_limits<int>::max());
    auto front = output.begin();
    auto back = --output.end();
    while(front->first < back->first) {
        std::swap(front->second,back->second);
        ++front;
        --back;
    };
}

void genDieRolls_Reroll(const std::vector<int>& dice, const int& condition = 1, const std::vector<int>::size_type index = 0, int sum = 0, const bool isReroll = false)
{
    for(int i = 1; i <= dice[index]; ++i) {
        ++sum;
        if(index < dice.size() - 1)
            genDieRolls_Reroll(dice, condition, index + 1, sum);
        else {
            if (i == condition and !isReroll)
                genDieRolls_Reroll(dice, condition, index, sum - condition, true);
            else
                ++output[sum];
        }
    }
}

void printVOutput()
{
    auto cout_n = [](auto const& v, int n) { while (--n >= 0) std::cout << v; };
    int total = 0;
    float average = 0.0f;
    
    for(const auto& p : output) {
        total += p.second;
        average += p.first * p.second;
    }

    average /= total;
       
    for(const auto& p : output) {
        std::cout << std::setw(2) << p.first << " ";
        cout_n("⋮", p.second*100/total);
        std::cout << '\n';
    }
    std::cout << "Average: " << average << "\n\n";
}

int calculateBarHeight()
{
    int highest = 0;
    for(const auto& p : output) {
        if (p.second > highest) {
            highest = p.second;
        }
    }
    return highest;
}

void printHOutput(const int& MaxHeight = 5, const int& BarWidth = 2)
{
    auto cout_n = [](auto const& v, int n) { while (--n >= 0) std::cout << v; };
    float height = (float)calculateBarHeight()/(MaxHeight);
    for (auto h{MaxHeight}; h > 0; --h) {
        cout_n(' ',1);
        for (const auto& p : output) {
            char d[] = "█";
            char c[] = "▄";
            auto q = (float)p.second/height;
            q + 0.75f < h ? cout_n(' ', BarWidth) : q + 0.25f < h ? cout_n(c,BarWidth) : cout_n(d,BarWidth);
            cout_n(' ',1);
        }
        cout_n('\n',1);
    }
    for(const auto& p :output)
        std::cout << std::setw(BarWidth + 1) << p.first;
    cout_n('\n',2);
}

int main()
{
    // AD&D (3d6, Normal Distribution, Mean = 10.5)
    std::cout << "AD&D 3d6\n";
    genDieRolls({6,6,6});
    printHOutput();
    output.clear();

    // AD&D Alt (1d4 + 1d6 + 1d8, Normal Distribution, Mean = 10.5)
    std::cout << "AD&D d4 + d6 + d8\n";
    genDieRolls({4,6,8});
    printHOutput();
    output.clear();

    // AD&D Reroll 1's (3d6, Skew Left, Mean ~ 10.7)
    std::cout << "AD&D 3d6, reroll 1's\n";
    genDieRolls_Reroll({6,6,6},1);
    printHOutput();
    output.clear();
    
    // AD&D Reroll 6's
    std::cout << "AD&D 3d6, reroll 6's\n";
    genDieRolls_Reroll({6,6,6},6);
    printHOutput();
    output.clear();

    // D&D 3.5, 4, and 5 (4d6, Skew Left, Mean ~ 12.2)
    std::cout << "D&D 4d6, remove smallest\n";
    genDieRolls_RemoveSmallest({6,6,6,6});
    printHOutput();
    output.clear();

    // D&D Hard mode (4d6, Skew Right, Mean ~ 8.8)
    std::cout << "AD&D 4d6, remove largest\n";
    genDieRolls_RemoveLargest({6,6,6,6});
    printHOutput();
    output.clear();
}
