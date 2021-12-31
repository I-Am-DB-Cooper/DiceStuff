// GoFirstDice.cpp : This file contains the 'main' function.
// The main point of this code is to determine if all orderings (low to high)
// for each dice roll of four dice with a user-defined numbering is equally likely. 
// The idea is that these dice can be used in with four or fewer people to determine
// the order in which they play randomly without having to reroll for ties!
// Dice of this kind are called "Go First Dice", coined by Eric Harshbarger
// Go First Dice website -> http://www.ericharshbarger.org/dice/go_first_dice.html

#include <iostream>	///std::cout
#include <iomanip>	// std::setw
#include <cmath>	// std::pow
#include <vector>	// std::vector
#include <numeric>	// std::iota
#include <algorithm>	// std::sort
#include <map>		// std::map

const int D_NUM = 4;	// Number of dice
const int D_SIZE = 12;	// Number of faces on each die

// Great function I found to sort indices quickly using lambdas
// link to original code found on internet -> http://cpp.sh/4dkzg
std::vector<int> sort_indices(const std::vector<int> &v)
{
	std::vector<int> idx(D_NUM);
	iota(idx.begin(), idx.end(), 0);

	sort(idx.begin(), idx.end(),
		[&v](int i1, int i2) { return v[i1] > v[i2]; });

	return idx;
}

int main()
{
	
	int total = 0;
	int rank = 0;

	// Originally used int array, but exceeded stack size (over 200,000 bytes)
	// Better to use K,V map for 16382 byte stack
	std::map<int, int> ranks;

	// Example of 4d12 that work!
	int d1[D_SIZE] = { 1, 8, 11, 14, 19, 22, 27, 30, 35, 38, 41, 48 };
	int d2[D_SIZE] = { 2, 7, 10, 15, 18, 23, 26, 31, 34, 39, 42, 47 };
	int d3[D_SIZE] = { 3, 6, 12, 13, 17, 24, 25, 32, 36, 37, 43, 46 };
	int d4[D_SIZE] = { 4, 5,  9, 16, 20, 21, 28, 29, 33, 40, 44, 45 };

	std::vector<int> index(D_NUM);

	std::cout << "Fairness Report (No subset check)\n";
	std::cout << "DICE COUNT: " << D_NUM << "\n";
	std::cout << "FACE COUNT: " << D_SIZE << "\n";

	// Making the output look similar to Eric Harshbarger's example
	// example link -> http://www.ericharshbarger.org/dice/4d12_fairness_report.txt
	std::cout << "D1:";
	for (int t : d1)
		std::cout << std::setw(3) << t << ",";
	std::cout << "\nD2:";
	for (int t : d2)
		std::cout << std::setw(3) << t << ",";
	std::cout << "\nD3:";
	for (int t : d3)
		std::cout << std::setw(3) << t << ",";
	std::cout << "\nD4:";
	for (int t : d4)
		std::cout << std::setw(3) << t << ",";
	std::cout << "\n===================================================\n";
	for (int const& i1 : d1)
	{
		index[0] = i1;
		for (int const& i2 : d2)
		{
			index[1] = i2;
			for (int const& i3 : d3)
			{
				index[2] = i3;
				for (int const& i4 : d4)
				{
                    rank = 0;
					auto temp = D_NUM - 1;
					index[3] = i4;
						
                    for (auto j : sort_indices(index))
                    { 
                        rank += (++j) * (int)std::pow(10.0f, temp--);
                    }
                    ranks[rank]++;
                    total++;
				}
			}
		}
	}

	for (auto const& j : ranks)
	{
		std::cout << "Ranking ";
		std::cout << j.first << " occurs ";
		std::cout << j.second << " out of " << total << " times.\n";
	}

	return 0;
}
