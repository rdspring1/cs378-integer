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

// --------
// includes
// --------

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
        const int b[] = {2};
              int x[10];
        const int* p = shift_left_digits(a, a + 3, -2, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
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
	Integer<int> b = Integer<int>(2);
        Integer<int>& p = a <<= -2;
	CPPUNIT_ASSERT(a == p);
	CPPUNIT_ASSERT(a == b);
    }

    // ------------------
    // shift_right_digits
    // ------------------

    void test_shift_right_digits () 
    {
        const int a[] = {2, 3, 4};
        const int b[] = {2};
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
        const int b[] = {2, 3, 4, 0, 0};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, -2, x);
        CPPUNIT_ASSERT((p - x) == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
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
	Integer<int> b = Integer<int>(23400);
        Integer<int>& p = a >>= -2;
	CPPUNIT_ASSERT(a == p);
	CPPUNIT_ASSERT(a == b);
    }

    // -----------
    // plus_digits
    // -----------

    void test_plus_digits () 
    {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {8, 0, 1};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_plus_digits_medium () 
    {
        const int a[] = {4, 0, 3, 5};
        const int b[] = {2, 1, 6};
        const int c[] = {4, 2, 5, 1};
              int x[10];
        const int* p = plus_digits(a, a + 4, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_plus_digits_large () 
    {
        const int a[] = {7, 7, 0, 8, 3};
        const int b[] = {7, 8, 7, 0, 5};
        const int c[] = {1, 5, 5, 7, 8, 8};
              int x[10];
        const int* p = plus_digits(a, a + 5, b, b + 5, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    // ------------
    // plus_operator
    // ------------

    void test_plus_equal_operator ()
    {
	Integer<int> a = Integer<int>(567);
	Integer<int> b = Integer<int>(243);
	Integer<int> c = Integer<int>(801);
	Integer<int>& p = a += b;
	CPPUNIT_ASSERT(a == p);
	CPPUNIT_ASSERT(a == c);
    }

    void test_plus_equal_operator_medium ()
    {
	Integer<int> a = Integer<int>(2013);
	Integer<int> b = Integer<int>(2014);
	Integer<int> c = Integer<int>(4027);
	Integer<int>& p = a += b;
	CPPUNIT_ASSERT(a == p);
	CPPUNIT_ASSERT(a == c);
    }

    void test_plus_equal_operator_large ()
    {
	Integer<int> a = Integer<int>(12345);
	Integer<int> b = Integer<int>(54321);
	Integer<int> c = Integer<int>(66666);
	Integer<int>& p = a += b;
	CPPUNIT_ASSERT(a == p);
	CPPUNIT_ASSERT(a == c);
    }

    // ------------
    // minus_digits
    // ------------

    void test_minus_digits () {
        const int a[] = {8, 0, 1};
        const int b[] = {5, 6, 7};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    // -----------------
    // multiplies_digits
    // -----------------

    void test_multiplies_digits () {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {1, 3, 2, 6, 7, 8};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    // --------------
    // divides_digits
    // --------------

    void test_divides_digits () {
        const int a[] = {1, 3, 2, 6, 7, 8};
        const int b[] = {5, 6, 7};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    // -----------
    // constructor
    // -----------

    void test_constructor_1 () {
        try {
            const Integer<int> x("abc");
            CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));}}

    void test_constructor_2 () {
        try {
            const Integer<int> x("2");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_constructor_3 () {
        try {
            const Integer<int> x(2);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // abs
    // ---

    void test_abs_1 () {
        try {
            Integer<int>  x = -98765;
            Integer<int>& y = x.abs();
            CPPUNIT_ASSERT( x == 98765);
            CPPUNIT_ASSERT(&x == &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs_2 () {
        try {
            const Integer<int> x = -98765;
            const Integer<int> y = abs(x);
            CPPUNIT_ASSERT(x == -98765);
            CPPUNIT_ASSERT(y ==  98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --------
    // equal_to
    // --------

    void test_equal_to () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = 98765;
            CPPUNIT_ASSERT(      x == y);
            CPPUNIT_ASSERT(      x == 98765);
            CPPUNIT_ASSERT(  98765 == x);
            CPPUNIT_ASSERT(    !(x != y));
            CPPUNIT_ASSERT(    !(x != 98765));
            CPPUNIT_ASSERT(!(98765 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --------
    // negation
    // --------

    void test_negation () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == -98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ------
    // output
    // ------

    void test_output () {
        try {
            const Integer<int> x = 98765;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // pow
    // ---

    void test_pow_1 () {
        try {
            Integer<int>       x = 98765;
            const int          e =  9867;
            Integer<int>&      y = x.pow(e);
            CPPUNIT_ASSERT( e == 9867);
            CPPUNIT_ASSERT( x ==    0);
            CPPUNIT_ASSERT(&x ==   &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_2 () {
        try {
            const Integer<int> x = 98765;
            const int          e =  9867;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x == 98765);
            CPPUNIT_ASSERT(e ==  9867);
            CPPUNIT_ASSERT(y ==     0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestInteger);
    CPPUNIT_TEST(test_shift_left_digits);
    CPPUNIT_TEST(test_shift_left_digits_none);
    CPPUNIT_TEST(test_shift_left_digits_negative);
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
    CPPUNIT_TEST(test_plus_digits_medium);
    CPPUNIT_TEST(test_plus_digits_large);
    CPPUNIT_TEST(test_plus_equal_operator);
    CPPUNIT_TEST(test_plus_equal_operator_medium);
    CPPUNIT_TEST(test_plus_equal_operator_large);
    CPPUNIT_TEST(test_minus_digits);
    CPPUNIT_TEST(test_multiplies_digits);
    CPPUNIT_TEST(test_divides_digits);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_abs_1);
    CPPUNIT_TEST(test_abs_2);
    CPPUNIT_TEST(test_negation);
    CPPUNIT_TEST(test_output);
    CPPUNIT_TEST(test_pow_1);
    CPPUNIT_TEST(test_pow_2);
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
