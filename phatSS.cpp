#include "phatSS.hpp"

pxSStream::pxSStream()
{
	mInt = 0;
	mSint = 0;
	mBool = false;
	mString.clear();

	mOutputStream.clear();
	mInputStream.clear();
}

pxSStream::~pxSStream()
{
}

// Converts an int to string C++ way
void pxSStream::numberToString(int iIn, string &sOut)
{
	mInputStream.clear(); // just to be sure
	mOutputStream.str(""); // empty string

	mOutputStream << iIn;

	sOut = mOutputStream.str();
}

// Converts a short to string C++ way
void pxSStream::shortToString(short iIn, string &sOut)
{
	mInputStream.clear(); // just to be sure
	mOutputStream.str("");// empty string

	mOutputStream << iIn;

	sOut = mOutputStream.str();
}

// Converts a bool to string C++ way
void pxSStream::boolToString(bool iIn, string &sOut)
{
	mInputStream.clear(); // just to be sure
	mOutputStream.str("");// empty string

	mOutputStream << iIn;

	sOut = mOutputStream.str();
}

// converts a string to an int C++ way
void pxSStream::stringToNumber(string &sIn, int &iOut)
{
	mInputStream.clear(); // just to be sure
	mInputStream.str(sIn);

	if ( ! ( mInputStream >> iOut ) ) // if string is invalid i.e. not numbers
		iOut = 0;
}

// converts a string to a short c++ way
void pxSStream::stringToShort(string &sIn, short int &iOut)
{
	mInputStream.clear(); // just to be sure
	mInputStream.str(sIn);

	if ( ! ( mInputStream >> iOut ) ) // if string is invalid i.e. not numbers
		iOut = 0;
}

// converts a string to a bool c++ way
void pxSStream::stringToBool(string &sIn, bool &iOut)
{
	mInputStream.clear(); // just to be sure
	mInputStream.str(sIn);

	if(sIn=="0")
		iOut = false;
	else if( sIn=="1")
		iOut = true;
	else
		iOut = false;

	if ( ! ( mInputStream >> iOut ) ) // if string is invalid i.e. not numbers
		error("stringToBool error. string contents: "+sIn);
}
