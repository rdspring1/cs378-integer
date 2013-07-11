// -------------------------------
// projects/integer/RunInteger.c++
// Copyright (C) 2013
// Glenn P. Downing
// -------------------------------

/*
To run the program:
	% g++ -pedantic -std=c++0x -Wall Integer.c++ RunInteger.c++ -o RunInteger
	% valgrind RunInteger > RunInteger.out

To configure Doxygen:
	% doxygen -g
That creates the file "Doxyfile".
Make the following edits:
	EXTRACT_ALL            = YES
	EXTRACT_PRIVATE        = YES
	EXTRACT_STATIC         = YES
	GENERATE_LATEX         = NO

To document the program:
	% doxygen Doxyfile
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <deque>    // deque
#include <ctime>	// clock

#include "Integer.h"

#define TIMER_MODE true
#define BONUS_MODE true

// ----
// main
// ----

int main () {
	using namespace std;

	if (BONUS_MODE) {

		clock_t currentStart;
		double TIME = 0;

		cout << "RunInteger.c++ (Bonus mode)" << endl << endl;
		cout << "*** 30th Mersenne prime: 39,751 digits ***" << endl << endl;
		// less than 4 min without valgrind
		// don't run with valgrind

		{
		currentStart = clock();
		const Integer<int> n = Integer<int>(2).pow(132049) - 1;
		TIME = ((clock() - currentStart) / (double) CLOCKS_PER_SEC);

		cout << "2^132049 - 1 = " << n << endl << endl;
		}

		std::cout << "Bonus Time (sec): " << TIME << std::endl;
		std::cout << "Bonus Time (ms): " << 1000*TIME << std::endl << std::endl;

	}

	if (TIMER_MODE) {
		clock_t currentStart;
		double currentIterationTime = 0;
		double totalTime = 0;
		int numIterations = 0;

		cout << "RunInteger.c++ (Timer mode)" << endl << endl;
		cout << "*** 20th Mersenne prime: 1,332 digits ***" << endl << endl;
		// less than 300 ms without valgrind
		// less than  15  s with    valgrind

		for (int i = 0; i < 10; ++i) {

			currentStart = clock();
			const Integer<int> n = Integer<int>(2).pow(4423) - 1;
			currentIterationTime = ((clock() - currentStart) / (double) CLOCKS_PER_SEC);

			std::cout << "numIterations: " << numIterations << std::endl;
			std::cout << "currentIterationTime (sec): " << currentIterationTime << std::endl;
			std::cout << "currentIterationTime (ms): " << 1000*currentIterationTime << std::endl << std::endl;

			++numIterations;
			totalTime += currentIterationTime;
		}

		std::cout << "total iterations: " << numIterations << std::endl;
		std::cout << "total iteration time (s): " << totalTime << std::endl;
		std::cout << "total iteration time (ms): " << 1000*totalTime << std::endl;
		std::cout << "avg iteration time (s): " << totalTime / (numIterations) << std::endl;
		std::cout << "avg iteration time (ms): " << 1000*totalTime / (numIterations) << std::endl << std::endl;

		{

		currentIterationTime = 0;
		totalTime = 0;
		numIterations = 0;

		for (int i = 0; i < 10; ++i) {

			currentStart = clock();
			const Integer< int, std::deque<int> > n = Integer< int, std::deque<int> >(2).pow(4423) - 1;
			currentIterationTime = ((clock() - currentStart) / (double) CLOCKS_PER_SEC);

			std::cout << "numIterations: " << numIterations << std::endl;
			std::cout << "currentIterationTime (sec): " << currentIterationTime << std::endl;
			std::cout << "currentIterationTime (ms): " << 1000*currentIterationTime << std::endl << std::endl;

			++numIterations;
			totalTime += currentIterationTime;
		}

		std::cout << "total iterations: " << numIterations << std::endl;
		std::cout << "total iteration time (s): " << totalTime << std::endl;
		std::cout << "total iteration time (ms): " << 1000*totalTime << std::endl;
		std::cout << "avg iteration time (s): " << totalTime / (numIterations) << std::endl;
		std::cout << "avg iteration time (ms): " << 1000*totalTime / (numIterations) << std::endl << std::endl;
		}
	}
	else {
		cout << "RunInteger.c++" << endl << endl;

		// less than 300 ms without valgrind
		// less than  15  s with    valgrind
		cout << "*** 20th Mersenne prime: 1,332 digits ***" << endl << endl;

		{
		const Integer<int> n = Integer<int>(2).pow(4423) - 1;
		cout << "2^4423 - 1 = " << n << endl << endl;
		}

		{
		const Integer< int, std::deque<int> > n = Integer< int, std::deque<int> >(2).pow(4423) - 1;
		cout << "2^4423 - 1 = " << n << endl << endl;
		}

		// --------------------------
		// extra credit (5 bonus pts)
		// --------------------------

		// less than 4 min without valgrind
		// don't run with valgrind
		// cout << "*** 30th Mersenne prime: 39,751 digits ***" << endl << endl;

		{
		const Integer<int> n = Integer<int>(2).pow(132049) - 1;
		cout << "2^132049 - 1 = " << n << endl << endl;
		}
	}

	cout << "Done." << endl;
	return 0;
}
