// --------------------------------
// projects/integer/TestInteger.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
   To test the program:
   % ls /usr/include/cppunit/
   ...
   TestFixture.h
   ...
   % locate libcppunit.a
   /usr/lib/libcppunit.a
   % g++ -pedantic -std=c++0x -Wall Integer.c++ TestInteger.c++ -o TestInteger -lcppunit -ldl
   % valgrind TestInteger > TestInteger.out
 */

#define private public
#define protected public

// --------
// includes
// --------

#include <iostream>  // cout
#include <algorithm> // equal
#include <cstring>   // strcmp
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Integer.h"

// -----------
// TestInteger
// -----------

struct TestInteger : CppUnit::TestFixture {

	// -----------------
	// shift_left_digits
	// -----------------

	void test_shift_left_digits () 
	{
		const int a[] = {2, 3, 4};
		const int b[] = {2, 3, 4, 0, 0};
		int x[10];
		const int* p = shift_left_digits(a, a + 3, 2, x);
		CPPUNIT_ASSERT((p - x) == 5);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
	}

	void test_shift_left_digits_none ()
	{
		const int a[] = {2, 3, 4};
		const int b[] = {2, 3, 4};
		int x[10];
		const int* p = shift_left_digits(a, a + 3, 0, x);
		CPPUNIT_ASSERT((p - x) == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
	}

	void test_shift_left_digits_negative ()
	{
		const int a[] = {2, 3, 4};
		int x[10];
		try {
			shift_left_digits(a, a + 3, -2, x);
			CPPUNIT_ASSERT(false);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(strcmp(e.what(), "The shift value cannot be a negative number.") == 0);
		}
	}

	// -----------------
	// inverse_shift_left_digits
	// -----------------

	void test_inverse_shift_left_digits () 
	{
		const int a[] = {4, 1};
		const int b[] = {0, 4, 1};
		int x[10];
		const int* p = inverse_shift_left_digits(a, a + 2, 1, x);
		CPPUNIT_ASSERT((p - x) == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
	}

	void test_inverse_shift_left_digits_none ()
	{
		const int a[] = {2, 3, 4};
		const int b[] = {2, 3, 4};
		int x[10];
		const int* p = inverse_shift_left_digits(a, a + 3, 0, x);
		CPPUNIT_ASSERT((p - x) == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
	}

	void test_inverse_shift_left_digits_negative ()
	{
		const int a[] = {2, 3, 4};
		int x[10];
		try {
			inverse_shift_left_digits(a, a + 3, -2, x);
			CPPUNIT_ASSERT(false);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(strcmp(e.what(), "The shift value cannot be a negative number.") == 0);
		}
	}

	// -----------------
	// shift_left_operator
	// -----------------

	void test_shift_left_operator ()
	{
		Integer<int> a = Integer<int>(234);
		Integer<int> b = Integer<int>(23400);
		Integer<int>& p = a <<= 2;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == b);
	}

	void test_shift_left_operator_none ()
	{
		Integer<int> a = Integer<int>(234);
		Integer<int> b = Integer<int>(234);
		Integer<int>& p = a <<= 0;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == b);
	}

	void test_shift_left_operator_negative ()
	{
		Integer<int> a = Integer<int>(234);
		try
		{
			a <<= -2;
			CPPUNIT_ASSERT(false);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(strcmp(e.what(), "The shift value cannot be a negative number.") == 0);
		}
	}

	// ------------------
	// shift_right_digits
	// ------------------

	void test_shift_right_digits () 
	{
		const int a[] = {2, 3, 4};
		const int b[] = {4};
		int x[10];
		const int* p = shift_right_digits(a, a + 3, 2, x);
		CPPUNIT_ASSERT((p - x) == 1);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
	}

	void test_shift_right_digits_none () 
	{
		const int a[] = {2, 3, 4};
		const int b[] = {2, 3, 4};
		int x[10];
		const int* p = shift_right_digits(a, a + 3, 0, x);
		CPPUNIT_ASSERT((p - x) == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
	}

	void test_shift_right_digits_negative () 
	{
		const int a[] = {2, 3, 4};
		int x[10];
		try
		{
			shift_right_digits(a, a + 3, -2, x);
			CPPUNIT_ASSERT(false);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(strcmp(e.what(), "The shift value cannot be a negative number.") == 0);
		}
	}

	// -----------------
	// shift_right_operator
	// -----------------

	void test_shift_right_operator ()
	{
		Integer<int> a = Integer<int>(234);
		Integer<int> b = Integer<int>(2);
		Integer<int>& p = a >>= 2;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == b);
	}

	void test_shift_right_operator_none ()
	{
		Integer<int> a = Integer<int>(234);
		Integer<int> b = Integer<int>(234);
		Integer<int>& p = a >>= 0;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == b);
	}

	void test_shift_right_operator_negative ()
	{
		Integer<int> a = Integer<int>(234);
		try
		{
			a >>= -2;
			CPPUNIT_ASSERT(false);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(strcmp(e.what(), "The shift value cannot be a negative number.") == 0);
		}
	}

	// -----------
	// plus_digits
	// -----------

	void test_plus_digits () 
	{
		const int a[] = {1, 7};
		const int b[] = {0, 4, 8};
		const int c[] = {1, 1, 9};
		int x[10];
		const int* p = plus_digits(a, a + 2, b, b + 3, x);
		CPPUNIT_ASSERT(p - x == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	void test_plus_digits_large () 
	{
		const int a[] = {3, 8, 0, 7, 7};
		const int b[] = {5, 0, 7, 8, 7};
		const int c[] = {8, 8, 7, 5, 5, 1};
		int x[10];
		const int* p = plus_digits(a, a + 5, b, b + 5, x);
		CPPUNIT_ASSERT(p - x == 6);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	void test_plus_digits_zero () 
	{
		const int a[] = {5, 3, 0, 4};
		const int b[] = {0};
		const int c[] = {5, 3, 0, 4};
		int x[10];
		const int* p = plus_digits(a, a + 4, b, b + 1, x);
		CPPUNIT_ASSERT(p - x == 4);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	// ------------
	// plus_operator
	// ------------

	void test_plus_equal_operator ()
	{
		Integer<int> a = Integer<int>(-10);
		Integer<int> b = Integer<int>(5);
		Integer<int> c = Integer<int>(-5);
		Integer<int>& p = a += b;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == c);
	}

	void test_plus_equal_operator_zero ()
	{
		Integer<int> a = Integer<int>(2013);
		Integer<int> b = Integer<int>(0);
		Integer<int> c = Integer<int>(2013);
		Integer<int>& p = a += b;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == c);
	}

	void test_plus_equal_operator_negative ()
	{
		Integer<int> a = Integer<int>(12345);
		Integer<int> b = Integer<int>(-54325);
		Integer<int> c = Integer<int>(-41980);
		Integer<int>& p = a += b;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == c);
	}

	// ------------
	// minus_digits
	// ------------

	void test_minus_digits () 
	{
		const int a[] = {5, 0, 0, 1};
		const int b[] = {9};
		const int c[] = {6, 9, 9};
		int x[10];
		const int* p = minus_digits(a, a + 4, b, b + 1, x);
		CPPUNIT_ASSERT(p - x == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	void test_minus_digits_large () 
	{
		const int a[] = {0, 3, 4, 1, 8, 4};
		const int b[] = {8, 6, 2, 3, 1};
		const int c[] = {2, 6, 1, 8, 6, 4};
		int x[10];
		const int* p = minus_digits(a, a + 6, b, b + 5, x);
		CPPUNIT_ASSERT(p - x == 6);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	void test_minus_digits_zero () 
	{
		const int a[] = {2, 5, 8, 1};
		const int b[] = {0};
		const int c[] = {2, 5, 8, 1};
		int x[10];
		const int* p = minus_digits(a, a + 4, b, b + 1, x);
		CPPUNIT_ASSERT(p - x == 4);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	// ------------
	// minus_operator
	// ------------

	void test_minus_equal_operator ()
	{
		Integer<int> a = Integer<int>(801);
		Integer<int> b = Integer<int>(567);
		Integer<int> c = Integer<int>(234);
		Integer<int>& p = a -= b;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == c);
	}

	void test_minus_equal_operator_zero ()
	{
		Integer<int> a = Integer<int>(1852);
		Integer<int> b = Integer<int>(0);
		Integer<int> c = Integer<int>(1852);
		Integer<int>& p = a -= b;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == c);
	}

	void test_minus_equal_operator_negative ()
	{
		Integer<int> a = Integer<int>(481430);
		Integer<int> b = Integer<int>(-13268);
		Integer<int> c = Integer<int>(494698);
		Integer<int>& p = a -= b;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == c);
	}

	// -----------------
	// multiplies_digits
	// -----------------

	void test_multiplies_digits () 
	{
		const int a[] = {4, 1};
		const int b[] = {4, 1};
		const int c[] = {6, 9, 1};
		int x[10];
		const int* p = multiplies_digits(a, a + 2, b, b + 2, x);
		CPPUNIT_ASSERT(p - x == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	void test_multiplies_digits_one () 
	{
		const int a[] = {1};
		const int b[] = {5, 4, 3, 2, 1};
		const int c[] = {5, 4, 3, 2, 1};
		int x[10];
		const int* p = multiplies_digits(a, a + 1, b, b + 5, x);
		CPPUNIT_ASSERT(p - x == 5);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	void test_multiplies_digits_zero () 
	{
		const int a[] = {5, 4, 3, 2, 1};
		const int b[] = {0};
		const int c[] = {0};
		int x[10];
		const int* p = multiplies_digits(a, a + 5, b, b + 1, x);
		CPPUNIT_ASSERT(p - x == 1);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	// -----------------
	// multipy_operator
	// -----------------

	void test_multiply_equal_operator ()
	{
		Integer<int> a = Integer<int>(234);
		Integer<int> b = Integer<int>(567);
		Integer<int> c = Integer<int>(132678);
		Integer<int>& p = a *= b;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == c);
	}

	void test_multiply_equal_operator_one ()
	{
		Integer<int> a = Integer<int>(1);
		Integer<int> b = Integer<int>(12345);
		Integer<int> c = Integer<int>(12345);
		Integer<int>& p = a *= b;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == c);
	}

	void test_multiply_equal_operator_zero ()
	{
		Integer<int> a = Integer<int>(12345);
		Integer<int> b = Integer<int>(0);
		Integer<int> c = Integer<int>(0);
		Integer<int>& p = a *= b;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == c);
	}

	// --------------
	// divides_digits
	// --------------

	void test_divides_digits () 
	{
		const int a[] = {8, 7, 6, 2, 3, 1};
		const int b[] = {7, 6, 5};
		const int c[] = {4, 3, 2};
		int x[10];
		const int* p = divides_digits(a, a + 6, b, b + 3, x);
		CPPUNIT_ASSERT(p - x == 3);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	void test_divides_digits_one () 
	{
		const int a[] = {9, 4, 8, 7};
		const int b[] = {1};
		const int c[] = {9, 4, 8, 7};
		int x[10];
		const int* p = divides_digits(a, a + 4, b, b + 1, x);
		CPPUNIT_ASSERT(p - x == 4);
		CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
	}

	void test_divides_digits_zero () 
	{
		const int a[] = {9, 4, 8, 7};
		const int b[] = {0};
		int x[10];
		try
		{
			divides_digits(a, a + 4, b, b + 1, x);
			CPPUNIT_ASSERT(false);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(strcmp(e.what(), "Division by zero is undefined") == 0);
		}
	}

	// --------------
	// divides_operator
	// --------------

	void test_divides_operator ()
	{
		Integer<int> a = Integer<int>(144);
		Integer<int> b = Integer<int>(12);
		Integer<int> c = Integer<int>(12);
		Integer<int>& p = a /= b;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == c);
	}

	void test_divides_operator_one ()
	{
		Integer<int> a = Integer<int>(12345);
		Integer<int> b = Integer<int>(1);
		Integer<int> c = Integer<int>(12345);
		Integer<int>& p = a /= b;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == c);
	}

	void test_divides_operator_zero ()
	{
		Integer<int> a = Integer<int>(12345);
		Integer<int> b = Integer<int>(0);
		try
		{
			a /= b;
			CPPUNIT_ASSERT(false);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(strcmp(e.what(), "Division by zero is undefined") == 0);
		}
	}

	// -----------
	// constructor
	// -----------

	void test_constructor_invalid_string () 
	{
		try 
		{
			const Integer<int> x("abc");
			CPPUNIT_ASSERT(false);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(strcmp(e.what(), "The string Value must represent a number.") == 0);
		}
	}

	void test_constructor_string_num ()
	{
		try
		{
			const Integer<int> x("2");
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	void test_constructor_int () 
	{
		try 
		{
			const Integer<int> x(2);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	// ---
	// abs
	// ---

	void test_abs_1 () 
	{
		try 
		{
			Integer<int>  x = -98765;
			Integer<int>& y = x.abs();
			CPPUNIT_ASSERT( x == 98765);
			CPPUNIT_ASSERT(&x == &y);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	void test_abs_2 () 
	{
		try 
		{
			const Integer<int> x = -60582216;
			const Integer<int> y = abs(x);
			CPPUNIT_ASSERT(x == -60582216);
			CPPUNIT_ASSERT(y ==  60582216);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	void test_abs_zero () 
	{
		try 
		{
			const Integer<int> x = 0;
			const Integer<int> y = abs(x);
			CPPUNIT_ASSERT(x == 0);
			CPPUNIT_ASSERT(y == 0);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	// --------
	// equal_to
	// --------

	void test_equal_to () 
	{
		try 
		{
			const Integer<int> x = 98765;
			const Integer<int> y = 98765;
			CPPUNIT_ASSERT(      x == y);
			CPPUNIT_ASSERT(      x == 98765);
			CPPUNIT_ASSERT(  98765 == x);
			CPPUNIT_ASSERT(    !(x != y));
			CPPUNIT_ASSERT(    !(x != 98765));
			CPPUNIT_ASSERT(!(98765 != y));
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	void test_equal_to_one () 
	{
		try 
		{
			const Integer<int> x = 1;
			const Integer<int> y = 1;
			CPPUNIT_ASSERT(      x == y);
			CPPUNIT_ASSERT(      x == 1);
			CPPUNIT_ASSERT(  1 == x);
			CPPUNIT_ASSERT(    !(x != y));
			CPPUNIT_ASSERT(    !(x != 1));
			CPPUNIT_ASSERT(!(1 != y));
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	void test_equal_to_zero () 
	{
		try 
		{
			const Integer<int> x = 0;
			const Integer<int> y = 0;
			CPPUNIT_ASSERT(      x == y);
			CPPUNIT_ASSERT(      x == 0);
			CPPUNIT_ASSERT(  0 == x);
			CPPUNIT_ASSERT(    !(x != y));
			CPPUNIT_ASSERT(    !(x != 0));
			CPPUNIT_ASSERT(!(0 != y));
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}
	// --------
	// negation
	// --------

	void test_negation () 
	{
		try 
		{
			const Integer<int> x = 98765;
			const Integer<int> y = -x;
			CPPUNIT_ASSERT(y == -98765);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	void test_negation_negative () 
	{
		try 
		{
			const Integer<int> x = -98765;
			const Integer<int> y = -x;
			CPPUNIT_ASSERT(y == 98765);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	void test_negation_zero () 
	{
		try 
		{
			const Integer<int> x = 0;
			const Integer<int> y = -x;
			CPPUNIT_ASSERT(y == 0);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	// ------
	// output
	// ------
	void test_output () 
	{
		try 
		{
			const Integer<int> x = 98765;
			std::ostringstream out;
			out << x;
			CPPUNIT_ASSERT(out.str() == "98765");
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	void test_output_negative () 
	{
		try 
		{
			const Integer<int> x = -98765;
			std::ostringstream out;
			out << x;
			CPPUNIT_ASSERT(out.str() == "-98765");
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	void test_output_large () 
	{
		try 
		{
			const Integer<int> x = 1234567890;
			std::ostringstream out;
			out << x;
			CPPUNIT_ASSERT(out.str() == "1234567890");
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	// ---
	// pow
	// ---

	void test_pow_method () 
	{
		try 
		{
			Integer<int>       x = 2;
			const int          e =  10;
			Integer<int>&      y = x.pow(e);
			CPPUNIT_ASSERT( e == 10);
			CPPUNIT_ASSERT( x == 1024);
			CPPUNIT_ASSERT(&x ==   &y);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	void test_pow_function () 
	{
		try 
		{
			const Integer<int> x = 10;
			const int          e =  5;
			const Integer<int> y = pow(x, e);
			CPPUNIT_ASSERT(x == 10);
			CPPUNIT_ASSERT(e ==  5);
			CPPUNIT_ASSERT(y == 100000);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	void test_pow_e_b_zero () 
	{
		try 
		{
			Integer<int>       x = 0;
			const int          e = 0;
			x.pow(e);
			CPPUNIT_ASSERT(false);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(strcmp(e.what(), "Exponent and Base cannot be zero") == 0);
		}
	}

	void test_pow_negative () 
	{
		try 
		{
			Integer<int>       x = 2;
			const int          e = -1;
			x.pow(e);
			CPPUNIT_ASSERT(false);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(strcmp(e.what(), "Exponent cannot be less than zero") == 0);
		}
	}

	void test_pow_zero () 
	{
		try 
		{
			Integer<int>       x = 2;
			const int          e =  0;
			Integer<int>&      y = x.pow(e);
			CPPUNIT_ASSERT( e == 0);
			CPPUNIT_ASSERT( x == 1);
			CPPUNIT_ASSERT(&x ==   &y);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	void test_pow_one () 
	{
		try 
		{
			Integer<int>       x = 2;
			const int          e =  1;
			Integer<int>&      y = x.pow(e);
			CPPUNIT_ASSERT( e == 1);
			CPPUNIT_ASSERT( x == 2);
			CPPUNIT_ASSERT(&x ==   &y);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(false);
		}
	}

	// ---
	// less_than
	// ---

	void test_less_than ()
	{
		Integer<int> a = Integer<int>(12);
		Integer<int> b = Integer<int>(144);
		CPPUNIT_ASSERT(a < b);
	}

	void test_less_than_zero ()
	{
		Integer<int> a = Integer<int>(12);
		Integer<int> b = Integer<int>(0);
		CPPUNIT_ASSERT(!(a < b));
	}

	void test_less_than_negative ()
	{
		Integer<int> a = Integer<int>(12);
		Integer<int> b = Integer<int>(-12);
		CPPUNIT_ASSERT(!(a < b));
	}

	// ---
	// mod_equal
	// ---

	void test_mod_equal ()
	{
		Integer<int> a = Integer<int>(12);
		Integer<int> b = Integer<int>(5);
		Integer<int> c = Integer<int>(2);
		Integer<int>& p = a %= b;
		CPPUNIT_ASSERT(a == p);
		CPPUNIT_ASSERT(a == c);
	}

	void test_mod_zero ()
	{
		Integer<int> a = Integer<int>(12);
		Integer<int> b = Integer<int>(0);
		try
		{
			a %= b;
			CPPUNIT_ASSERT(false);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(strcmp(e.what(), "Divisor cannot be less than or equal to zero") == 0);
		}
	}

	void test_mod_negative ()
	{
		Integer<int> a = Integer<int>(12);
		Integer<int> b = Integer<int>(-1);
		try
		{
			a %= b;
			CPPUNIT_ASSERT(false);
		}
		catch (std::invalid_argument& e) 
		{
			CPPUNIT_ASSERT(strcmp(e.what(), "Divisor cannot be less than or equal to zero") == 0);
		}
	}

	void test_greater_than_equal_greater ()
	{
		const int a[] = {0, 0, 1};
		const int b[] = {0, 1};
		CPPUNIT_ASSERT(greater_than_equal(a, a + 3, b, b + 2));
	}

	void test_greater_than_equal_equal ()
	{
		const int a[] = {0, 1};
		const int b[] = {0, 1};
		CPPUNIT_ASSERT(greater_than_equal(a, a + 2, b, b + 2));
	}

	void test_greater_than_equal_less ()
	{
		const int a[] = {1};
		const int b[] = {0, 1};
		CPPUNIT_ASSERT(!greater_than_equal(a, a + 1, b, b + 2));
	}

	void test_valid ()
	{
		Integer<int> x(12345);
		CPPUNIT_ASSERT(x.valid());
	}

	void test_valid_zero ()
	{
		Integer<int> x(0);
		CPPUNIT_ASSERT(x.valid());
	}

	void test_valid_division_zero ()
	{
		Integer<int> numerator(5);
		Integer<int> denominator(10);
		Integer<int> result(0);
		numerator /= denominator;
		CPPUNIT_ASSERT(numerator == result);
		CPPUNIT_ASSERT(numerator.valid());
	}

	void test_setup_integer ()
	{
		Integer<int> x(12345);
		CPPUNIT_ASSERT(!x.negative);
		CPPUNIT_ASSERT(x.digits == 5);
		CPPUNIT_ASSERT(x.container[0] == 5);
		CPPUNIT_ASSERT(x.container[1] == 4);
		CPPUNIT_ASSERT(x.container[2] == 3);
		CPPUNIT_ASSERT(x.container[3] == 2);
		CPPUNIT_ASSERT(x.container[4] == 1);
	}

	void test_setup_integer_zero ()
	{
		Integer<int> x(0);
		CPPUNIT_ASSERT(!x.negative);
		CPPUNIT_ASSERT(x.digits == 1);
		CPPUNIT_ASSERT(x.container[0] == 0);
	}

	void test_setup_integer_negative ()
	{
		Integer<int> x(-12345);
		CPPUNIT_ASSERT(x.negative);
		CPPUNIT_ASSERT(x.digits == 5);
		CPPUNIT_ASSERT(x.container[0] == 5);
		CPPUNIT_ASSERT(x.container[1] == 4);
		CPPUNIT_ASSERT(x.container[2] == 3);
		CPPUNIT_ASSERT(x.container[3] == 2);
		CPPUNIT_ASSERT(x.container[4] == 1);
	}

	void test_setup_integer_negative_str ()
	{
		Integer<int> x("-12345");
		CPPUNIT_ASSERT(x.negative);
		CPPUNIT_ASSERT(x.digits == 5);
		CPPUNIT_ASSERT(x.container[0] == 5);
		CPPUNIT_ASSERT(x.container[1] == 4);
		CPPUNIT_ASSERT(x.container[2] == 3);
		CPPUNIT_ASSERT(x.container[3] == 2);
		CPPUNIT_ASSERT(x.container[4] == 1);
	}

	void test_set_single_digit ()
	{
		Integer<int> x(12345);
		CPPUNIT_ASSERT(!x.negative);
		CPPUNIT_ASSERT(x.digits == 5);
		CPPUNIT_ASSERT(x.container[0] == 5);
		CPPUNIT_ASSERT(x.container[1] == 4);
		CPPUNIT_ASSERT(x.container[2] == 3);
		CPPUNIT_ASSERT(x.container[3] == 2);
		CPPUNIT_ASSERT(x.container[4] == 1);
		x.set_single_digit(5);
		CPPUNIT_ASSERT(!x.negative);
		CPPUNIT_ASSERT(x.digits == 1);
		CPPUNIT_ASSERT(x.container[0] == 5);
	}

	void test_set_single_digit_zero ()
	{
		Integer<int> x(12345);
		CPPUNIT_ASSERT(!x.negative);
		CPPUNIT_ASSERT(x.digits == 5);
		CPPUNIT_ASSERT(x.container[0] == 5);
		CPPUNIT_ASSERT(x.container[1] == 4);
		CPPUNIT_ASSERT(x.container[2] == 3);
		CPPUNIT_ASSERT(x.container[3] == 2);
		CPPUNIT_ASSERT(x.container[4] == 1);
		x.set_single_digit(0);
		CPPUNIT_ASSERT(!x.negative);
		CPPUNIT_ASSERT(x.digits == 1);
		CPPUNIT_ASSERT(x.container[0] == 0);
	}

	void test_set_single_digit_one ()
	{
		Integer<int> x(12345);
		CPPUNIT_ASSERT(!x.negative);
		CPPUNIT_ASSERT(x.digits == 5);
		CPPUNIT_ASSERT(x.container[0] == 5);
		CPPUNIT_ASSERT(x.container[1] == 4);
		CPPUNIT_ASSERT(x.container[2] == 3);
		CPPUNIT_ASSERT(x.container[3] == 2);
		CPPUNIT_ASSERT(x.container[4] == 1);
		x.set_single_digit(1);
		CPPUNIT_ASSERT(!x.negative);
		CPPUNIT_ASSERT(x.digits == 1);
		CPPUNIT_ASSERT(x.container[0] == 1);
	}

	void test_set_digit_count_add ()
	{
		Integer<int> x(99);
		Integer<int> y(1);
		auto p = plus_digits(x.container.begin(), x.container.begin() + 2, y.container.begin(), y.container.begin() + 1, x.container.begin());
		CPPUNIT_ASSERT(x.container[0] == 0);
		CPPUNIT_ASSERT(x.container[1] == 0);
		CPPUNIT_ASSERT(x.container[2] == 1);
		x.set_digit_count(p);
		CPPUNIT_ASSERT(x.digits == 3);
	}

	void test_set_digit_count_subtract ()
	{
		Integer<int> x(100);
		Integer<int> y(1);
		auto p = minus_digits(x.container.begin(), x.container.begin() + 2, y.container.begin(), y.container.begin() + 1, x.container.begin());
		CPPUNIT_ASSERT(x.container[0] == 9);
		CPPUNIT_ASSERT(x.container[1] == 9);
		x.set_digit_count(p);
		CPPUNIT_ASSERT(x.digits == 2);
	}

	void test_set_digit_count_multiply ()
	{
		Integer<int> x(100);
		Integer<int> y(2);
		Integer<int> z(0);
		auto p = multiplies_digits(x.container.begin(), x.container.begin() + 3, y.container.begin(), y.container.begin() + 1, z.container.begin());
		z.set_digit_count(p);
		CPPUNIT_ASSERT(z.digits == 3);
		CPPUNIT_ASSERT(z.container[0] == 0);
		CPPUNIT_ASSERT(z.container[1] == 0);
		CPPUNIT_ASSERT(z.container[2] == 2);
	}

	void test_set_digit_count_divide ()
	{
		Integer<int> x(100);
		Integer<int> y(1);
		Integer<int> z(0);
		auto p = divides_digits(x.container.begin(), x.container.begin() + 2, y.container.begin(), y.container.begin() + 1, z.container.begin());
		CPPUNIT_ASSERT(z.container[0] == 0);
		CPPUNIT_ASSERT(z.container[1] == 0);
		CPPUNIT_ASSERT(z.container[2] == 1);
		z.set_digit_count(p);
		CPPUNIT_ASSERT(z.digits == 3);
	}

	void test_resize ()
	{
		Integer<int> x(0);
		CPPUNIT_ASSERT(x.container.size() == SIZE);
		x.resize(2000);
		CPPUNIT_ASSERT(x.container.size() == 4000);
	}

	void test_resize_less ()
	{
		Integer<int> x(0);
		CPPUNIT_ASSERT(x.container.size() == SIZE);
		x.resize(500);
		CPPUNIT_ASSERT(x.container.size() == SIZE);
	}

	void test_resize_zero ()
	{
		Integer<int> x(0);
		CPPUNIT_ASSERT(x.container.size() == SIZE);
		x.resize(0);
		CPPUNIT_ASSERT(x.container.size() == SIZE);
	}

	// -----
	// suite
	// -----

	CPPUNIT_TEST_SUITE(TestInteger);
	CPPUNIT_TEST(test_shift_left_digits);
	CPPUNIT_TEST(test_shift_left_digits_none);
	CPPUNIT_TEST(test_shift_left_digits_negative);
	CPPUNIT_TEST(test_inverse_shift_left_digits);
	CPPUNIT_TEST(test_inverse_shift_left_digits_none);
	CPPUNIT_TEST(test_inverse_shift_left_digits_negative);
	CPPUNIT_TEST(test_shift_left_operator);
	CPPUNIT_TEST(test_shift_left_operator_none);
	CPPUNIT_TEST(test_shift_left_operator_negative);
	CPPUNIT_TEST(test_shift_right_digits);
	CPPUNIT_TEST(test_shift_right_digits_none);
	CPPUNIT_TEST(test_shift_right_digits_negative);
	CPPUNIT_TEST(test_shift_right_operator);
	CPPUNIT_TEST(test_shift_right_operator_none);
	CPPUNIT_TEST(test_shift_right_operator_negative);
	CPPUNIT_TEST(test_plus_digits);
	CPPUNIT_TEST(test_plus_digits_large);
	CPPUNIT_TEST(test_plus_digits_zero);
	CPPUNIT_TEST(test_plus_equal_operator);
	CPPUNIT_TEST(test_plus_equal_operator_negative);
	CPPUNIT_TEST(test_plus_equal_operator_zero);
	CPPUNIT_TEST(test_minus_digits);
	CPPUNIT_TEST(test_minus_digits_large);
	CPPUNIT_TEST(test_minus_digits_zero);
	CPPUNIT_TEST(test_minus_equal_operator);
	CPPUNIT_TEST(test_minus_equal_operator_negative);
	CPPUNIT_TEST(test_minus_equal_operator_zero);
	CPPUNIT_TEST(test_multiplies_digits);
	CPPUNIT_TEST(test_multiplies_digits_one);
	CPPUNIT_TEST(test_multiplies_digits_zero);
	CPPUNIT_TEST(test_multiply_equal_operator);
	CPPUNIT_TEST(test_multiply_equal_operator_one);
	CPPUNIT_TEST(test_multiply_equal_operator_zero);
	CPPUNIT_TEST(test_divides_digits);
	CPPUNIT_TEST(test_divides_digits_one);
	CPPUNIT_TEST(test_divides_digits_zero);
	CPPUNIT_TEST(test_divides_operator);
	CPPUNIT_TEST(test_divides_operator_one);
	CPPUNIT_TEST(test_divides_operator_zero);
	CPPUNIT_TEST(test_constructor_invalid_string);
	CPPUNIT_TEST(test_constructor_string_num);
	CPPUNIT_TEST(test_constructor_int);
	CPPUNIT_TEST(test_abs_1);
	CPPUNIT_TEST(test_abs_2);
	CPPUNIT_TEST(test_abs_zero);
	CPPUNIT_TEST(test_equal_to);
	CPPUNIT_TEST(test_equal_to_one);
	CPPUNIT_TEST(test_equal_to_zero);
	CPPUNIT_TEST(test_negation);
	CPPUNIT_TEST(test_negation_negative);
	CPPUNIT_TEST(test_negation_zero);
	CPPUNIT_TEST(test_greater_than_equal_greater);
	CPPUNIT_TEST(test_greater_than_equal_equal);
	CPPUNIT_TEST(test_greater_than_equal_less);
	CPPUNIT_TEST(test_valid);
	CPPUNIT_TEST(test_valid_zero);
	CPPUNIT_TEST(test_valid_division_zero);
	CPPUNIT_TEST(test_setup_integer);
	CPPUNIT_TEST(test_setup_integer_zero);
	CPPUNIT_TEST(test_setup_integer_negative);
	CPPUNIT_TEST(test_setup_integer_negative_str);
	CPPUNIT_TEST(test_set_single_digit);
	CPPUNIT_TEST(test_set_single_digit_zero);
	CPPUNIT_TEST(test_set_single_digit_one);
	CPPUNIT_TEST(test_set_digit_count_add);
	CPPUNIT_TEST(test_set_digit_count_subtract);
	CPPUNIT_TEST(test_set_digit_count_multiply);
	CPPUNIT_TEST(test_set_digit_count_divide);
	CPPUNIT_TEST(test_resize);
	CPPUNIT_TEST(test_resize_less);
	CPPUNIT_TEST(test_resize_zero);
	CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
	using namespace std;
	cout << "TestInteger.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestInteger::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;}
