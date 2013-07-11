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

#include "Integer.h"

// ----
// main
// ----

int main () {
    using namespace std;  
    // Acceptance Tests
    // Subtraction
    {
        const Integer<int> n = Integer<int>(10) - 10;
        cout << "10 - 10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) - 5;
        cout << "10 - 5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) - 20;
        cout << "10 - 20 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) - -5;
        cout << "10 - -5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) - -20;
        cout << "10 - -20 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) - 5;
        cout << "-10 - 5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) - 20;
        cout << "-10 - 20 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) - -10;
        cout << "-10 - -10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) - -5;
        cout << "-10 - -5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) - -20;
        cout << "-10 - -20 = " << n << endl;
    }
    std::cout << std::endl;
    // Addition
    {
        const Integer<int> n = Integer<int>(10) + 10;
        cout << "10 + 10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) + 5;
        cout << "10 + 5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) + 20;
        cout << "10 + 20 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) + -5;
        cout << "10 + -5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) + -20;
        cout << "10 + -20 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) + 5;
        cout << "-10 + 5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) + 20;
        cout << "-10 + 20 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) + -10;
        cout << "-10 + -10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) + -5;
        cout << "-10 + -5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) + -20;
        cout << "-10 + -20 = " << n << endl;
    }
    std::cout << std::endl;
    // Multiplication
    {
        const Integer<int> n = Integer<int>(10) * 10;
        cout << "10 * 10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) * 5;
        cout << "10 * 5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) * 20;
        cout << "10 * 20 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) * -5;
        cout << "10 * -5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) * -20;
        cout << "10 * -20 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) * 5;
        cout << "-10 * 5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) * 20;
        cout << "-10 * 20 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) * -10;
        cout << "-10 * -10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) * -5;
        cout << "-10 * -5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) * -20;
        cout << "-10 * -20 = " << n << endl;
    }
    std::cout << std::endl;
    // Multiplication - Reverse
    {
        const Integer<int> n = Integer<int>(10) * 10;
        cout << "10 * 10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(5) * 10;
        cout << "5 * 10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(20) * 10;
        cout << "20 * 10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-5) * 10;
        cout << "-5 * 10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-20) * 10;
        cout << "-20 * 10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(5) * -10;
        cout << "5 * -10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(20) * -10;
        cout << "20 * -10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) * -10;
        cout << "-10 * -10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-5) * -10;
        cout << "-5 * -10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-20) * -10;
        cout << "-20 * -10 = " << n << endl;
    }
    std::cout << std::endl;    
    // Division
    {
        const Integer<int> n = Integer<int>(10) / 10;
        cout << "10 / 10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) / 5;
        cout << "10 / 5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) / 20;
        cout << "10 / 20 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) / -5;
        cout << "10 / -5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(10) / -20;
        cout << "10 / -20 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) / 5;
        cout << "-10 / 5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) / 20;
        cout << "-10 / 20 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) / -10;
        cout << "-10 / -10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) / -5;
        cout << "-10 / -5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) / -20;
        cout << "-10 / -20 = " << n << endl;
    }
    std::cout << std::endl;   
    // Division - Reverse
    {
        const Integer<int> n = Integer<int>(10) / 10;
        cout << "10 / 10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(5) / 10;
        cout << "5 / 10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(20) / 10;
        cout << "20 / 10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-5) / 10;
        cout << "-5 / 10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-20) / 10;
        cout << "-20 / 10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(5) / -10;
        cout << "5 / -10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(20) / -10;
        cout << "20 / -10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-10) / -10;
        cout << "-10 / -10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-5) / -10;
        cout << "-5 / -10 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-20) / -10;
        cout << "-20 / -10 = " << n << endl;
    }
    std::cout << std::endl;   
    // Power - One
    {
        const Integer<int> n = Integer<int>(1).pow(0);
        cout << "1 ^ 0 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(1).pow(1);
        cout << "1 ^ 1 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(1).pow(2);
        cout << "1 ^ 2 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(1).pow(3);
        cout << "1 ^ 3 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(1).pow(4);
        cout << "1 ^ 4 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(1).pow(5);
        cout << "1 ^ 5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(1).pow(6);
        cout << "1 ^ 6 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(1).pow(7);
        cout << "1 ^ 7 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(1).pow(8);
        cout << "1 ^ 8 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(1).pow(9);
        cout << "1 ^ 9 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(1).pow(10);
        cout << "1 ^ 10 = " << n << endl;
    }
    std::cout << std::endl;   
    // Power - Two
    {
        const Integer<int> n = Integer<int>(2).pow(0);
        cout << "2 ^ 0 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(2).pow(1);
        cout << "2 ^ 1 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(2).pow(2);
        cout << "2 ^ 2 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(2).pow(3);
        cout << "2 ^ 3 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(2).pow(4);
        cout << "2 ^ 4 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(2).pow(5);
        cout << "2 ^ 5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(2).pow(6);
        cout << "2 ^ 6 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(2).pow(7);
        cout << "2 ^ 7 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(2).pow(8);
        cout << "2 ^ 8 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(2).pow(9);
        cout << "2 ^ 9 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(2).pow(10);
        cout << "2 ^ 10 = " << n << endl;
    }
    std::cout << std::endl;   
    // Power - 147
    {
        const Integer<int> n = Integer<int>(147).pow(0);
        cout << "147 ^ 0 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(147).pow(1);
        cout << "147 ^ 1 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(147).pow(2);
        cout << "147 ^ 2 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(147).pow(3);
        cout << "147 ^ 3 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(147).pow(4);
        cout << "147 ^ 4 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(147).pow(5);
        cout << "147 ^ 5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(147).pow(6);
        cout << "147 ^ 6 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(147).pow(7);
        cout << "147 ^ 7 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(147).pow(8);
        cout << "147 ^ 8 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(147).pow(9);
        cout << "147 ^ 9 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(147).pow(10);
        cout << "147 ^ 10 = " << n << endl;
    }
    std::cout << std::endl;   
    // Misc
    {
        const Integer<int> n = Integer<int>(12345) << 4;
        cout << "12345 << 4 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(12345) << 0;
        cout << "12345 << 0 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(0) << 4;
        cout << "0 << 4 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(0) << 0;
        cout << "0 << 0 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(12345) >> 4;
        cout << "12345 >> 4 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(12345) >> 0;
        cout << "12345 >> 0 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(0) >> 4;
        cout << "0 >> 4 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(0) >> 0;
        cout << "0 >> 0 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-12345) << 4;
        cout << "-12345 << 4 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-12345) << 0;
        cout << "-12345 << 0 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-12345) >> 4;
        cout << "-12345 >> 4 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-12345) >> 5;
        cout << "-12345 >> 5 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-12345) >> 0;
        cout << "-12345 >> 0 = " << n << endl;
    }
    {
        const Integer<int> n = Integer<int>(12345);
        cout << "abs(12345) = " << abs(n) << endl;
    }
    {
        const Integer<int> n = Integer<int>(-12345);
        cout << "abs(-12345) = " << abs(n) << endl;
    }
    {
        const Integer<int> n = Integer<int>(0);
        cout << "abs(0) = " << abs(n) << endl;
    }
    {
        const Integer<int> n = Integer<int>(12345);
        cout << "negative(12345) = " << -n << endl;
    }
    {
        const Integer<int> n = Integer<int>(-12345);
        cout << "negative(-12345) = " << -n << endl;
    }
    {
        const Integer<int> n = Integer<int>(0);
        cout << "negative(0) = " << -n << endl;
    }
    std::cout << std::endl; 
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
    cout << "*** 30th Mersenne prime: 39,751 digits ***" << endl << endl;

    {
    	const Integer<int> n = Integer<int>(2).pow(132049) - 1;
    	cout << "2^132049 - 1 = " << n << endl << endl;
    }

    cout << "Done." << endl;

    return 0;}
