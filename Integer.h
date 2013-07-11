// --------------------------
// projects/integer/Integer.h
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------

#ifndef Integer_h
#define Integer_h
#define SIZE 1500

// --------
// includes
// --------

#include <algorithm> // max
#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>    // string
#include <vector>    // vector
#include <stdlib.h>  // atoi

// -----------------
// shift_left_digits
// -----------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift left of the input sequence into the output sequence
 * ([b, e) << n) => x
 */
	template <typename II, typename OI>
OI shift_left_digits (II b, II e, int n, OI x) 
{
	if(n < 0)
		throw std::invalid_argument("The shift value cannot be a negative number.");

	// Transfer values to x
	while(b != e)
	{
		*x = *b;
		++b;
		++x;
	}

	// Shift x pointer
	for(int i = 0; i < n; ++i)
	{
		*x = 0;
		++x;
	}	
	return x;
}

// ------------------
// shift_right_digits
// ------------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift right of the input sequence into the output sequence
 * ([b, e) >> n) => x
 */
	template <typename II, typename OI>
OI shift_right_digits (II b, II e, int n, OI x) 
{
	if(n < 0)
	{
		throw std::invalid_argument("The shift value cannot be a negative number.");
	}
	else if(n == 0)
	{
		e -= n;
		while(b != e)
		{
			*x = *b;
			++b;
			++x;
		}
	}
	else
	{
		// Transfer values to x
		b += n;
		while(b != e)
		{
			--e;
			*x = *e;
			++x;
		}
	}
	return x;
}

// ------------------
// inverse_shift_left_digits
// ------------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the inverse of the shift left of the input sequence into the output sequence
 * ([b, e) >> n) => x
 */
	template <typename II, typename OI>
OI inverse_shift_left_digits (II b, II e, int n, OI x) 
{
	if(n < 0)
		throw std::invalid_argument("The shift value cannot be a negative number.");

	int numelem = e - b;
	int elem = numelem - 1;
	// Transfer values to x
	while(b != e)
	{
		--e;
		*(x + n + elem) = *e;
		--elem;
	}

	// Shift x pointer
	for(int i = 0; i < n; ++i)
	{
		*x = 0;
		++x;
	}	

	return x + numelem;
}

// -----------
// plus_digits
// -----------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the sum of the two input sequences into the output sequence
 * ([b1, e1) + [b2, e2)) => x
 */
	template <typename II1, typename II2, typename OI>
OI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) 
{
	// II1 digit and II2 digit
	int carry = 0;
	while(b1 != e1 && b2 != e2)
	{
		int value = *b1 + *b2 + carry;
		if(value >= 10)
		{
			*x = value - 10;
			carry = 1;
		}
		else
		{
			*x = value;
			carry = 0;
		}
		++x;
		++b1;
		++b2;   
	}

	// II1 digit
	while(b1 != e1)
	{
		int value = *b1 + carry;
		if(value >= 10)
		{
			*x = value - 10;
			carry = 1;
		}
		else
		{
			*x = value;
			carry = 0;
		}
		++x;
		++b1;
	}

	// II2 digit
	while(b2 != e2)
	{
		int value = *b2 + carry;
		if(value >= 10)
		{
			*x = value - 10;
			carry = 1;
		}
		else
		{
			*x = value;
			carry = 0;
		}
		++x;
		++b2;
	}

	// Carry Value
	if(carry == 1)
	{
		*x = carry;
		++x;
	}

	return x;
}

// ------------
// minus_digits
// ------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the difference of the two input sequences into the output sequence
 * ([b1, e1) - [b2, e2)) => x
 */
	template <typename II1, typename II2, typename OI>
OI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) 
{
	OI cx = x;
	// II1 digit and II2 digit
	bool borrow = false;
	while(b1 != e1 && b2 != e2)
	{
		int lhs = *b1;
		if(borrow)
		{
			if(lhs == 0)
			{
				lhs = 9;
			}
			else
			{
				lhs -= 1;
				borrow = false;
			}
		}

		if(lhs < *b2)
		{
			borrow = true;
			*x = lhs + 10 - *b2;
		}
		else
		{
			*x = lhs - *b2;
		}
		++x;
		++b1;
		++b2;   
	}

	// II1 digit only
	while(b1 != e1)
	{
		if(borrow)
		{
			if(*b1 == 0)
			{
				*x = 9;
			}
			else
			{
				*x = *b1 - 1;
				borrow = false;
			}
		}
		else
		{
			*x = *b1;
		}
		++x;
		++b1;
	}

	// Extra Zeros
	while(*(x-1) == 0 && (x - 1) != cx)
		--x;

	return x;
}

// -----------------
// multiplies_digits
// -----------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the product of the two input sequences into the output sequence
 * ([b1, e1) * [b2, e2)) => x
 */
	template <typename II1, typename II2, typename OI>
OI multiplies_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) 
{
	bool first = true;
	int max_digit = 0;
	int carry = 0;

	// II1 digit and II2 digit
	while(b2 != e2)
	{
		--e2;
		OI ex = x;
		// Multiply Digit against Value1
		for(II1 cb1 = b1; cb1 != e1; ++cb1)
		{
			// Uninitialized Structures are not initialized to zero
			if(first)
				*ex = *cb1 * *e2 + carry;
			else
				*ex += *cb1 * *e2 + carry;

			carry = *ex / 10;
			*ex %= 10;
			++ex;
		}

		while(carry != 0)
		{
			if(first)
				*ex = carry;
			else
				*ex += carry;

			carry = *ex / 10;
			*ex %= 10;
			++ex;
		}

		int diff = ex - x;
		max_digit = std::max(max_digit, diff); 

		if(b2 != e2)
		{
			inverse_shift_left_digits(x, x + max_digit, 1, x);
			++max_digit;
		}
		first = false;
	}

	// Extra Zeros
	OI cx = x + max_digit;
	while((cx - 1) != x && *(cx-1) == 0)
		--cx;
	return cx;
}

// --------------
// divides_digits
// --------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the division of the two input sequences into the output sequence
 * ([b1, e1) / [b2, e2)) => x
 */
	template <typename II1, typename II2, typename OI>
OI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) 
{
	bool first = true;
	int size = e1 - b1;
	std::vector<typename std::iterator_traits<II1>::value_type> difference (size);
	std::vector<typename std::iterator_traits<OI>::value_type> atom (1, 1);
	OI ex = x;
	auto diffex = difference.end();

	bool nonzero = false;
	for(II2 cb2 = b2; cb2 != e2; ++cb2)
	{
		if(*cb2 != 0)
			nonzero = true;
	}

	if(!nonzero)
		throw std::invalid_argument("Division by zero is undefined");

	do
	{
		// Increment ouput sequence
		if(first)
		{
			minus_digits(b1, e1, b2, e2, difference.begin());
		}
		else
		{
			diffex = minus_digits(difference.begin(), diffex, b2, e2, difference.begin());
		}
		ex = plus_digits(x, ex, atom.begin(), atom.end(), x);
		first = false;
	} while(greater_than_equal(difference.begin(), diffex, b2, e2));

	return ex;
}

// --------------------
// greater_than_equal
// --------------------

/**
 * @param b  an iterator to the beginning of the lhs input  sequence
 * @param e  an iterator to the end       of the lhs input  sequence
 * @param b2 an iterator to the beginning of the rhs input  sequence
 * @param e2 an iterator to the end       of the rhs input  sequence
 * @return  whether the lhs sequence is greater than or equal to the rhs sequence
 */
	template <typename II1, typename II2>
bool greater_than_equal (II1 b1, II1 e1, II2 b2, II2 e2) 
{
	int digits1 = e1 - b1;
	int digits2 = e2 - b2;

	if(digits1 > digits2)
	{
		return true;
	}
	else if(digits1 < digits2)
	{
		return false;
	}

	while(b1 != e1 && b2 != e2)
	{
		--e1;
		--e2;
		if(*e1 > *e2)
			return true;
		else if(*e1 < *e2)
			return false;
	}
	return true;
}

// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer {
	// -----------
	// operator ==
	// -----------

	/**
	 * @param lhs - the left hand side Integer
	 * @param rhs - the right hand side Integer
	 * @return true if the lhs Integer is equal to the rhs Integer
	 * equal operator
	 */
	friend bool operator == (const Integer& lhs, const Integer& rhs) 
	{
		if(lhs.negative != rhs.negative)
			return false;

		if(lhs.digits != rhs.digits)
			return false;

		auto lb = lhs.container.begin();
		auto le = lhs.container.begin() + lhs.digits;
		auto rb = rhs.container.begin();
		auto re = rhs.container.begin() + rhs.digits;
		while(lb != le && rb != re)
		{
			if(*lb != *rb)
				return false;
			++lb;
			++rb;
		}
		return true;
	}

	// -----------
	// operator !=
	// -----------

	/**
	 * @param lhs - the left hand side Integer
	 * @param rhs - the right hand side Integer
	 * @return true if the lhs Integer is not equal to the rhs Integer
	 * not equal operator
	 */
	friend bool operator != (const Integer& lhs, const Integer& rhs) 
	{
		return !(lhs == rhs);
	}

	// ----------
	// operator <
	// ----------

	/**
	 * @param lhs - the left hand side Integer
	 * @param rhs - the right hand side Integer
	 * @return true if the lhs Integer is less than the rhs Integer
	 * less than operator
	 */
	friend bool operator < (const Integer& lhs, const Integer& rhs) 
	{
		if(lhs.negative && !rhs.negative)
			return true;

		if(!lhs.negative && rhs.negative)
			return false;

		return !greater_than_equal(lhs.container.begin(), lhs.container.begin() + lhs.digits, rhs.container.begin(), rhs.container.begin() + rhs.digits);
	}

	// -----------
	// operator <=
	// -----------

	/**
	 * @param lhs - the left hand side Integer
	 * @param rhs - the right hand side Integer
	 * @return true if the lhs Integer is less than or equal to the rhs Integer
	 * less than or equal to operator
	 */
	friend bool operator <= (const Integer& lhs, const Integer& rhs) 
	{
		return !(rhs < lhs);
	}

	// ----------
	// operator >
	// ----------

	/**
	 * @param lhs - the left hand side Integer
	 * @param rhs - the right hand side Integer
	 * @return true if the lhs Integer is greater than the rhs Integer
	 * greater than operator
	 */
	friend bool operator > (const Integer& lhs, const Integer& rhs) 
	{
		return (rhs < lhs);
	}

	// -----------
	// operator >=
	// -----------

	/**
	 * @param lhs - the left hand side Integer
	 * @param rhs - the right hand side Integer
	 * @return true if the lhs Integer is greater than or equal to the rhs Integer
	 * greater than or equal to operator
	 */
	friend bool operator >= (const Integer& lhs, const Integer& rhs) 
	{
		return !(lhs < rhs);
	}

	// ----------
	// operator +
	// ----------

	/**
	 * @param lhs - the left hand side Integer
	 * @param rhs - the right hand side Integer
	 * @return an Integer that is the sum of the lhs Integer and rhs Integer
	 * addition operator
	 */
	friend Integer operator + (Integer lhs, const Integer& rhs) 
	{
		return lhs += rhs;
	}

	// ----------
	// operator -
	// ----------

	/**
	 * @param lhs - the left hand side Integer
	 * @param rhs - the right hand side Integer
	 * @return an Integer that is the difference of the lhs Integer and rhs Integer
	 * subtraction operator
	 */
	friend Integer operator - (Integer lhs, const Integer& rhs) 
	{
		return lhs -= rhs;
	}

	// ----------
	// operator *
	// ----------

	/**
	 * @param lhs - the left hand side Integer
	 * @param rhs - the right hand side Integer
	 * @return an Integer that is the product of the lhs Integer and rhs Integer
	 * multiplication operator
	 */
	friend Integer operator * (Integer lhs, const Integer& rhs) 
	{
		return lhs *= rhs;
	}

	// ----------
	// operator /
	// ----------

	/**
	 * @param lhs - the left hand side Integer
	 * @param rhs - the right hand side Integer
	 * @return an Integer that is the quotient of the lhs Integer and rhs Integer
	 * @throws invalid_argument if (rhs == 0)
	 * division operator
	 */
	friend Integer operator / (Integer lhs, const Integer& rhs) 
	{
		return lhs /= rhs;
	}

	// ----------
	// operator %
	// ----------

	/**
	 * @param lhs - the left hand side Integer
	 * @param rhs - the right hand side Integer
	 * @return an Integer that is the modulo of the lhs Integer and rhs Integer
	 * @throws invalid_argument if (rhs <= 0)
	 * modulus operator
	 */
	friend Integer operator % (Integer lhs, const Integer& rhs) 
	{
		return lhs %= rhs;
	}

	// -----------
	// operator <<
	// -----------

	/**
	 * @param lhs - the left hand side Integer
	 * @param n - the number of positions to shift the Integer
	 * @return an Integer that is shifted n positions to the left
	 * @throws invalid_argument if (rhs < 0)
	 * shift left operator
	 */
	friend Integer operator << (Integer lhs, int rhs) 
	{
		return lhs <<= rhs;
	}

	// -----------
	// operator >>
	// -----------

	/**
	 * @param lhs - the left hand side Integer
	 * @param n - the number of positions to shift the Integer
	 * @return an Integer that is shifted n positions to the right
	 * @throws invalid_argument if (rhs < 0)
	 * shift right operator
 */
	friend Integer operator >> (Integer lhs, int rhs) 
	{
		return lhs >>= rhs;
	}

	// -----------
	// operator <<
	// -----------

	/**
	 * @param lhs - an output stream
	 * @param rhs - the right hand side Integer
	 * @return an output stream that contains the string representation of the Integer
	 */
	friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) 
	{
		static std::string negative_str = "-";
		if(rhs.negative)
			lhs << negative_str;

		for(auto rb = rhs.container.begin() + rhs.digits - 1; rb != rhs.container.begin(); --rb)
			lhs << *rb;
		lhs << *rhs.container.begin();
		return lhs;
	}

	// ---
	// abs
	// ---

	/**
	 * @param x - an Integer - copy by value
	 * @return an Integer that is the absolute value of the Integer parameter
	 * absolute value operation
	 * does NOT modify the argument
	 */
	friend Integer abs (Integer x) 
	{
		return x.abs();
	}

	// ---
	// pow
	// ---

	/**
	 * @param x - an Integer that is the base number for the power function - copy by value
	 * @param e - the exponent of the power function
	 * @return an Integer that is the power of the numbers x and e
	 * power operation
	 * does NOT modify the argument
	 * @throws invalid_argument if (x == 0) && (e == 0)
	 * @throws invalid_argument if (e < 0)
	 */
	friend Integer pow (Integer x, int e) 
	{
		return x.pow(e);
	}

	private:
	// ----
	// data
	// ----
	int digits;
	bool negative;
	C container;

	private:
	// -----
	// valid
	// -----

	/**
	 * @return true if the Integer object is in a valid state
	 */
	bool valid () const 
	{
		if(digits < 1)
			return false;

		if(digits == 1 && container[0] == 0 && negative)
			return false;

		return true;
	}

	/**
	 * @param value - an int value which is used to initialize the Integer
	 * Initialize the Integer using specified value
	 */
	void setup_integer(int& value)
	{
		digits = 0;
		if(value > 0)
		{
			negative = false;
		}
		else if(value < 0)
		{
			negative = true;
			value *= -1;
		}
		else
		{
			set_single_digit(0);
		}

		while(value != 0)
		{
			container.push_back(value % 10);
			value /= 10;
			++digits;
		}
		container.resize(SIZE);
	}

	/**
	 * @param value - an rvalue reference which is used to initialize the single digit
	 * Set the Integer to a single digit positive value 
	 */
	void set_single_digit(int&& value)
	{
		assert(value >= 0 && value < 10);
		negative = false;
		container.clear();
		container.push_back(value);
		container.resize(SIZE);
		digits = 1;
	}

	/**
	 * @param e - an iterator to the Most Significant Digit(MSD) in the Integer
	 * Determine the number of digits in the Integer
	 */
	void set_digits(typename C::iterator e)
	{
		// Set digits
		digits = e - container.begin();
	}

	/**
	 * @param size - the expected size of the container implementing Integer
	 * Resize the container implementing Integer to the appropriate size
	 */
	void resize(typename C::size_type size)
	{	
		// Resize the container
		if(container.size() < 2 * size)
			container.resize(2 * size);
	}

	public:
	// ------------
	// constructors
	// ------------

	/**
	 * @param - value - an int value which is used to initialize the Integer 
	 * Construct an Integer using an int argument
	 */
	Integer (int value)
	{
		setup_integer(value);
		assert(valid());
	}

	/**
	 * @param - value - a std::string value which is used to initialize the Integer
	 * @throws invalid_argument if value is not a valid representation of an Integer
	 * Construct an Integer using a std:string argument
	 */
	explicit Integer (const std::string& value)
	{
		static std::string zero = "0";
		if(value == zero)
		{
			negative = false;
			container.push_back(0);
			return;
		}

		int ival = strtol(value.c_str(), nullptr, 10);
		if (ival == 0)
			throw std::invalid_argument("The string Value must represent a number.");
		else
			setup_integer(ival);
		assert(valid());
	}

	// Default copy, destructor, and copy asnegativement.
	// Integer (const Integer&);
	// ~Integer ();
	// Integer& operator = (const Integer&);

	// ----------
	// operator -
	// ----------

	/**
	 * @return an Integer with the opposite value of this Integer
	 * negation operator
	 */
	Integer operator - () const 
	{
		Integer x(*this);
		if(x != 0)
			x.negative = !negative;
		assert(valid());
		return x;
	}

	// -----------
	// operator ++
	// -----------

	/**
	 * @return a Integer reference incremented by 1
	 * Pre-increment Operator
	 */
	Integer& operator ++ () 
	{
		*this += 1;
		assert(valid());
		return *this;
	}

	/**
	 * @return an Integer incremented by 1
	 * Does not effect the Integer argument
	 * Post-Increment Operator
	 */
	Integer operator ++ (int) 
	{
		Integer x = *this;
		++(*this);
		assert(valid());
		return x;
	}

	// -----------
	// operator --
	// -----------

	/**
	 * @return a Integer reference decremented by 1
	 * Pre-decrement Operator
	 */
	Integer& operator -- () 
	{
		*this -= 1;
		assert(valid());
		return *this;
	}

	/**
	 * @return an Integer decremented by 1
	 * Does not effect the Integer argument
	 * Post-Decrement Operator
	 */
	Integer operator -- (int) 
	{
		Integer x = *this;
		--(*this);
		assert(valid());
		return x;
	}

	// -----------
	// operator +=
	// -----------

	/**
	 * @param rhs - the right hand side Integer
	 * @return a Integer reference that is the sum of this Integer and the rhs
	 * Addition Assignent Operator
	 */
	Integer& operator += (const Integer& rhs) 
	{
		resize(digits + rhs.digits);
		if(!negative && !rhs.negative)
		{
			set_digits(plus_digits(container.begin(), container.begin() + digits, rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin()));
		}
		else if(negative && !rhs.negative)
		{
			if(-(*this) < rhs)
			{
				negative = false;
				set_digits(minus_digits(rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin(), container.begin() + digits, container.begin()));
			}
			else if(-(*this) == rhs)
			{
				set_single_digit(0);
			}
			else
			{
				set_digits(minus_digits(container.begin(), container.begin() + digits, rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin()));
				set_digits(minus_digits(container.begin(), container.begin() + digits, rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin()));
			}
		}
		else if(!negative && rhs.negative)
		{
			if(*this < -rhs)
			{
				negative = true;
				set_digits(minus_digits(rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin(), container.begin() + digits, container.begin()));
			}
			else if(*this == -rhs)
			{
				set_single_digit(0);
			}
			else
			{
				set_digits(minus_digits(container.begin(), container.begin() + digits, rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin()));
			}
		}
		else // negative && rhs.negative
		{
			set_digits(plus_digits(container.begin(), container.begin() + digits, rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin()));
		}
		assert(valid());
		return *this;
	}

	// -----------
	// operator -=
	// -----------

	/**
	 * @param rhs - the right hand side Integer
	 * @return a Integer reference that is the difference of this Integer and the rhs
	 * Subtraction Assignent Operator
	 */
	Integer& operator -= (const Integer& rhs) 
	{
		resize(digits + rhs.digits);
		if(!negative && !rhs.negative)
		{
			if(*this < rhs)
			{
				negative = true;
				set_digits(minus_digits(rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin(), container.begin() + digits, container.begin()));
			}
			else if(*this == rhs)
			{
				set_single_digit(0);
			}
			else
			{
				set_digits(minus_digits(container.begin(), container.begin() + digits, rhs.container.begin(), rhs.container.begin() + rhs.digits , container.begin()));
			}
		}
		else if((negative && !rhs.negative) || (!negative && rhs.negative))
		{
			set_digits(plus_digits(container.begin(), container.begin() + digits, rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin()));
		}
		else // negative && rhs.negative
		{
			if(-(*this) < -rhs)
			{
				negative = false;
				set_digits(minus_digits(rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin(), container.begin() + digits, container.begin()));
			}
			else if(-(*this) == -rhs)
			{
				set_single_digit(0);
			}
			else
			{
				set_digits(minus_digits(container.begin(), container.begin() + digits, rhs.container.begin(), rhs.container.begin() + rhs.digits , container.begin()));
			}
		}
		assert(valid());
		return *this;
	}

	// -----------
	// operator *=
	// -----------

	/**
	 * @param rhs - the right hand side Integer
	 * @return a Integer reference that is the product of this Integer and the rhs
	 * Multiplication Assignent Operator
	 */
	Integer& operator *= (const Integer& rhs) 
	{
		Integer c = *this;
		resize(digits + rhs.digits);
		if(negative && rhs.negative)
		{
			negative = false;
			set_digits(multiplies_digits(c.container.begin(), c.container.begin() + digits, rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin()));
		}
		else if(!negative && rhs.negative)
		{
			negative = true;
			set_digits(multiplies_digits(c.container.begin(), c.container.begin() + digits, rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin()));
		}
		else // !negative && !!rhs.negative + negative && !rhs.negative
		{
			set_digits(multiplies_digits(c.container.begin(), c.container.begin() + digits, rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin()));
		}
		assert(valid());
		return *this;
	}

	// -----------
	// operator /=
	// -----------

	/**
	 * @param rhs - the right hand side Integer
	 * @return a Integer reference that is the quotient of this Integer and the rhs
	 * @throws invalid_argument if (rhs == 0)
	 * Division Assignent Operator
	 */
	Integer& operator /= (const Integer& rhs) 
	{
		Integer ct = *this;
		Integer cr = rhs;
		ct.abs();
		cr.abs();

		resize(digits + rhs.digits);
		if(cr <= ct)
		{
			if(negative && rhs.negative)
			{
				negative = false;
				set_digits(divides_digits(container.begin(), container.begin() + digits, rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin()));
			}
			else if(!negative && rhs.negative)
			{
				negative = true;
				set_digits(divides_digits(container.begin(), container.begin() + digits, rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin()));
			}
			else // negative && rhs.negative
			{
				set_digits(divides_digits(container.begin(), container.begin() + digits, rhs.container.begin(), rhs.container.begin() + rhs.digits, container.begin()));
			}
		}
		else
		{
			set_single_digit(0);
		}
		assert(valid());
		return *this;
	}

	// -----------
	// operator %=
	// -----------

	/**
	 * @param rhs - the right hand side Integer
	 * @return a Integer reference that is the modulo of this Integer and the rhs
	 * @throws invalid_argument if (rhs <= 0)
	 * Modulo Assignment Operator
	 */
	Integer& operator %= (const Integer& rhs) 
	{
		// check rhs > 0
		if(rhs <= 0)
			throw std::invalid_argument("Divisor cannot be less than or equal to zero");

		Integer copy(*this);
		copy /= rhs;
		copy *= rhs;
		*this -= copy;
		assert(valid());
		return *this;
	}

	// ------------
	// operator <<=
	// ------------

	/**
	 * @param n - the number of positions to shift the Integer
	 * @return an Integer Reference that is shifted n positions to the left
	 * @throws invalid_argument if (rhs < 0)
	 * shift left assignement operator
	 */
	Integer& operator <<= (int n) 
	{
		resize(digits + n);
		inverse_shift_left_digits(container.begin(), container.begin() + digits, n, container.begin());
		digits += n;
		assert(valid());
		return *this;
	}

	// ------------
	// operator >>=
	// ------------

	/**
	 * @param n - the number of positions to shift the Integer
	 * @return an Integer Reference that is shifted n positions to the right
	 * @throws invalid_argument if (rhs < 0)
	 * shift right assignement operator
	 */
	Integer& operator >>= (int n) 
	{
		resize(digits + n);
		shift_right_digits(container.begin(), container.begin() + digits, n, container.begin());
		digits -= n;
		assert(valid());
		return *this;
	}

	// ---
	// abs
	// ---

	/**
	 * @return an Integer Reference that is the absolute value of this Integer 
	 * absolute value operation
	 */
	Integer& abs () 
	{
		negative = false;
		assert(valid());
		return *this;
	}

	// ---
	// pow
	// ---

	/**
	 * @param e - the exponent of the power function
	 * @return an Integer Reference that is the power of this Integer and e
	 * power operation
	 * @throws invalid_argument if (this == 0) && (e == 0)
	 * @throws invalid_argument if (e < 0)
	 */
	Integer& pow (int e) 
	{
		// check base and exponent
		if(e < 0)
			throw std::invalid_argument("Exponent cannot be less than zero");

		if(*this == 0 && e == 0)
			throw std::invalid_argument("Exponent and Base cannot be zero");

		if(e == 0)
			set_single_digit(1);

		Integer b(*this);
		for(int i = 1; i < e; ++i)
		{
			*this *= b;
		}
		assert(valid());
		return *this;
	}
};

#endif // Integer_h
