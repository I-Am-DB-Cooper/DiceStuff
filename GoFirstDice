// GoFirstDice.cpp : This file contains the 'main' function.
// The main point of this code is to determine if all orderings (low to high)
// for each dice roll of five dice with a user-defined numbering is equally likely. 
// The idea is that these dice can be used in with five or fewer people to determine
// the order in which they play randomly without having to reroll for ties!
// Dice of this kind are called "Go First Dice", coined by Eric Harshbarger
// Go First Dice website -> http://www.ericharshbarger.org/dice/go_first_dice.html
//
// As of this writing, the quickest this code runs on my machine is under 140 seconds

#include <iostream>
#include <ctime>		// clock()
#include <iomanip>		// std::setw, std::setfill
#include <cmath>		// std::pow
#include <string>
#include <fstream>
#include <vector>
#include <numeric>		// std::iota
#include <algorithm>	// std::sort
#include <map>			// std::map

using namespace std;
typedef unsigned int usint;

const usint D_NUM = 5;		// Number of dice
const usint D_SIZE = 30;	// Number of faces on each die

// Great function I found to sort indices quickly using lambdas
// link to original code found on internet -> http://cpp.sh/4dkzg
vector<usint> sort_indices(const vector<usint> &v)
{
	vector<usint> idx(D_NUM);
	iota(idx.begin(), idx.end(), 0);

	sort(idx.begin(), idx.end(),
		[&v](usint i1, usint i2) { return v[i1] > v[i2]; });

	return idx;
}

int main()
{
	
	int total = 0;
	int rank = 0;
	// Originally used int array, but exceeded stack size (over 200,000 bytes)
	// Better to use K,V map for 16382 byte stack
	std::map<usint, int> ranks;

	// Example of 4d12 that work!
	//usint d1[D_SIZE] = { 1, 8, 11, 14, 19, 22, 27, 30, 35, 38, 41, 48 };
	//usint d2[D_SIZE] = { 2, 7, 10, 15, 18, 23, 26, 31, 34, 39, 42, 47 };
	//usint d3[D_SIZE] = { 3, 6, 12, 13, 17, 24, 25, 32, 36, 37, 43, 46 };
	//usint d4[D_SIZE] = { 4, 5,  9, 16, 20, 21, 28, 29, 33, 40, 44, 45 };

	// This particular numbering of 5d30 does not work, but is somewhat close
	usint d1[D_SIZE] = { 1, 10, 12, 19, 22, 29, 33, 38, 43, 48, 53, 58, 63, 68, 72, 79, 83, 88, 93,  98, 103, 108, 113, 118, 122, 129, 132, 139, 141, 150 };
	usint d2[D_SIZE] = { 2,  9, 14, 17, 24, 27, 32, 39, 42, 49, 55, 56, 65, 66, 71, 80, 85, 86, 95,  96, 102, 109, 112, 119, 124, 127, 134, 137, 142, 149 };
	usint d3[D_SIZE] = { 3,  8, 15, 16, 21, 30, 34, 37, 44, 47, 52, 59, 62, 69, 73, 78, 82, 89, 92,  99, 104, 107, 114, 117, 121, 130, 135, 136, 143, 148 };
	usint d4[D_SIZE] = { 4,  7, 13, 18, 23, 28, 31, 40, 45, 46, 54, 60, 61, 67, 75, 76, 81, 87, 94, 100, 105, 106, 111, 120, 123, 128, 133, 138, 144, 147 };
	usint d5[D_SIZE] = { 5,  6, 11, 20, 25, 26, 35, 36, 41, 50, 51, 57, 64, 70, 74, 77, 84, 90, 91,  97, 101, 110, 115, 116, 125, 126, 131, 140, 145, 146 };

	usint i1, i2, i3, i4, i5, temp;
	vector<usint> index(D_NUM);

	ofstream myfile;
	myfile.open("fivedice.txt");
	myfile << "Fairness Report (No subset check)" << endl;
	myfile << "DICE COUNT: " << D_NUM << endl;
	myfile << "FACE COUNT: " << D_SIZE << endl;

	// Making the output text file look like Eric Harshbarger's example
	// example link -> http://www.ericharshbarger.org/dice/4d12_fairness_report.txt
	// Note: this textfile is VERY LARGE. The output here will not list every possible roll,
	// only just the setup information and the ranking results at the end.
	myfile << "D1: ";
	for (usint t : d1)
		myfile << t << ",";
	myfile << "\nD2: ";
	for (usint t : d2)
		myfile << t << ",";
	myfile << "\nD3: ";
	for (usint t : d3)
		myfile << t << ",";
	myfile << "\nD4: ";
	for (usint t : d4)
		myfile << t << ",";
	myfile << "\nD5: ";
	for (usint t : d5)
		myfile << t << ",";
	myfile << endl;
	myfile << "===================================================" << endl;
	const clock_t begin_time = clock();
	for (i1 = 0; i1 < D_SIZE; i1++)
	{
		std::cout << i1 + 1 << " ";
		index[0] = d1[i1];
		for (i2 = 0; i2 < D_SIZE; i2++)
		{
			index[1] = d2[i2];
			for (i3 = 0; i3 < D_SIZE; i3++)
			{
				index[2] = d3[i3];
				for (i4 = 0; i4 < D_SIZE; i4++)
				{
					index[3] = d4[i4];
					for (i5 = 0; i5 < D_SIZE; i5++)
					{
						rank = 0;
						temp = D_NUM - 1;
						index[4] = d5[i5];
						for (auto j : sort_indices(index))
						{
							
							rank += (++j) * (usint)std::pow(10.0f, temp--);
						}
						ranks[rank]++;
						total++;
					}
				}
			}
		}
	}
	std::cout << endl;
	std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds.";

	for (auto const& j : ranks)
	{
		myfile << "Ranking ";
		myfile << j.first << " occurs ";
		myfile << j.second << " out of " << total << " times." << endl;
	}

	myfile.close();

	return 0;
}
