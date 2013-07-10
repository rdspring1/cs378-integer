// --------------------------
// projects/integer/Integer.h
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------

#ifndef Integer_h
#define Integer_h

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
		throw std::invalid_argument("Shift Left by a negative number is undefined");

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
		throw std::invalid_argument("Shift Right by a negative number is undefined");

	// Transfer values to x
	e -= n;
	while(b != e)
	{
		*x = *b;
		++b;
		++x;
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
		throw std::invalid_argument("Inverse Shift Left by a negative number is undefined");

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
	} while(greater_than(difference.begin(), diffex, b2, e2));

	return ex;
}

template <typename II1, typename II2>
bool greater_than (II1 b1, II1 e1, II2 b2, II2 e2) 
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
		if(*e1 < *e2)
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
	* <your documentation>
	*/
	friend bool operator == (const Integer& lhs, const Integer& rhs) 
	{
		// <your code>
		return false;
	}

	// -----------
	// operator !=
	// -----------

	/**
	* <your documentation>
	*/
	friend bool operator != (const Integer& lhs, const Integer& rhs) 
	{
		return !(lhs == rhs);
	}

	// ----------
	// operator <
	// ----------

	/**
	* <your documentation>
	*/
	friend bool operator < (const Integer& lhs, const Integer& rhs) 
	{
		// <your code>
		return false;
	}

	// -----------
	// operator <=
	// -----------

	/**
	* <your documentation>
	*/
	friend bool operator <= (const Integer& lhs, const Integer& rhs) 
	{
		return !(rhs < lhs);
	}

	// ----------
	// operator >
	// ----------

	/**
	* <your documentation>
	*/
	friend bool operator > (const Integer& lhs, const Integer& rhs) 
	{
		return (rhs < lhs);
	}

	// -----------
	// operator >=
	// -----------

	/**
	* <your documentation>
	*/
	friend bool operator >= (const Integer& lhs, const Integer& rhs) 
	{
		return !(lhs < rhs);
	}

	// ----------
	// operator +
	// ----------

	/**
	* <your documentation>
	*/
	friend Integer operator + (Integer lhs, const Integer& rhs) 
	{
		return lhs += rhs;
	}

	// ----------
	// operator -
	// ----------

	/**
	* <your documentation>
	*/
	friend Integer operator - (Integer lhs, const Integer& rhs) 
	{
		return lhs -= rhs;
	}

	// ----------
	// operator *
	// ----------

	/**
	* <your documentation>
	*/
	friend Integer operator * (Integer lhs, const Integer& rhs) 
	{
		return lhs *= rhs;
	}

	// ----------
	// operator /
	// ----------

	/**
	* <your documentation>
	* @throws invalid_argument if (rhs == 0)
	*/
	friend Integer operator / (Integer lhs, const Integer& rhs) 
	{
		return lhs /= rhs;
	}

	// ----------
	// operator %
	// ----------

	/**
	* <your documentation>
	* @throws invalid_argument if (rhs <= 0)
	*/
	friend Integer operator % (Integer lhs, const Integer& rhs) 
	{
		return lhs %= rhs;
	}

	// -----------
	// operator <<
	// -----------

	/**
	* <your documentation>
	* @throws invalid_argument if (rhs < 0)
	*/
	friend Integer operator << (Integer lhs, int rhs) 
	{
		return lhs <<= rhs;
	}

	// -----------
	// operator >>
	// -----------

	/**
	* <your documentation>
	* @throws invalid_argument if (rhs < 0)
	*/
	friend Integer operator >> (Integer lhs, int rhs) 
	{
		return lhs >>= rhs;
	}

	// -----------
	// operator <<
	// -----------

	/**
	* <your documentation>
	*/
	friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) 
	{
		// <your code>
		return lhs << "0";
	}

	// ---
	// abs
	// ---

	/**
	* absolute value
	* does NOT modify the argument
	* <your documentation>
	*/
	friend Integer abs (Integer x) 
	{
		return x.abs();
	}

	// ---
	// pow
	// ---

	/**
	* power
	* does NOT modify the argument
	* <your documentation>
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
	bool sign;
	typename C container;
	int digits;

private:
	// -----
	// valid
	// -----

	bool valid () const 
	{
		if(digits < 1)
			return false;


		return true;
	}

public:
	// ------------
	// constructors
	// ------------

	/**
	* <your documentation>
	*/
	void setup_integer(int& value)
	{
		digits = 0;
		if(value > 0)
		{
			sign = false;
		}
		else if(value == 0)
		{
			sign = false;
			container.push_back(value);
		}
		else
		{
			sign = true;
		}

		while(value != 0)
		{
			container.push_back(value % 10);
			value /= 10;
			++digits;
		}
	}

	/**
	* <your documentation>
	*/
	Integer (int value) 
	{
		setup_integer(value);
		assert(valid());
	}

	/**
	* <your documentation>
	* @throws invalid_argument if value is not a valid representation of an Integer
	*/
	explicit Integer (const std::string& value)
	{
		static std::string zero = "0";
		if(value == zero)
		{
			sign = false;
			container.push_back(0);
			return;
		}

		int ival = strtol(value.c_str(), nullptr, 10);
		if (ival == 0)
			throw std::invalid_argument("Integer::Integer()");
		else
			setup_integer(ival);
	}

	// Default copy, destructor, and copy assignment.
	// Integer (const Integer&);
	// ~Integer ();
	// Integer& operator = (const Integer&);

	// ----------
	// operator -
	// ----------

	/**
	* <your documentation>
	*/
	Integer operator - () const 
	{
		// <your code>
		return Integer(0);
	}

	// -----------
	// operator ++
	// -----------

	/**
	* <your documentation>
	*/
	Integer& operator ++ () 
	{
		*this += 1;
		return *this;
	}

	/**
	* <your documentation>
	*/
	Integer operator ++ (int) 
	{
		Integer x = *this;
		++(*this);
		return x;
	}

	// -----------
	// operator --
	// -----------

	/**
	* <your documentation>
	*/
	Integer& operator -- () 
	{
		*this -= 1;
		return *this;
	}

	/**
	* <your documentation>
	*/
	Integer operator -- (int) 
	{
		Integer x = *this;
		--(*this);
		return x;
	}

	// -----------
	// operator +=
	// -----------

	/**
	* <your documentation>
	*/
	Integer& operator += (const Integer& rhs) 
	{
		// <your code>
		return *this;
	}

	// -----------
	// operator -=
	// -----------

	/**
	* <your documentation>
	*/
	Integer& operator -= (const Integer& rhs) 
	{
		// <your code>
		return *this;
	}

	// -----------
	// operator *=
	// -----------

	/**
	* <your documentation>
	*/
	Integer& operator *= (const Integer& rhs) 
	{
		// <your code>
		return *this;
	}

	// -----------
	// operator /=
	// -----------

	/**
	* <your documentation>
	* @throws invalid_argument if (rhs == 0)
	*/
	Integer& operator /= (const Integer& rhs) 
	{
		// <your code>
		return *this;
	}

	// -----------
	// operator %=
	// -----------

	/**
	* <your documentation>
	* @throws invalid_argument if (rhs <= 0)
	*/
	Integer& operator %= (const Integer& rhs) 
	{
		// <your code>
		return *this;
	}

	// ------------
	// operator <<=
	// ------------

	/**
	* <your documentation>
	*/
	Integer& operator <<= (int n) 
	{
		// <your code>
		return *this;
	}

	// ------------
	// operator >>=
	// ------------

	/**
	* <your documentation>
	*/
	Integer& operator >>= (int n) 
	{
		// <your code>
		return *this;
	}

	// ---
	// abs
	// ---

	/**
	* absolute value
	* <your documentation>
	*/
	Integer& abs () 
	{
		// <your code>
		return *this;
	}

	// ---
	// pow
	// ---

	/**
	* power
	* <your documentation>
	* @throws invalid_argument if (this == 0) && (e == 0)
	* @throws invalid_argument if (e < 0)
	*/
	Integer& pow (int e) 
	{
		// <your code>
		return *this;
	}
};

#endif // Integer_h