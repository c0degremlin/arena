/* Making string and variable converisoin easy and the C++ way
// Goal of being cross-platform with little to no more mods than a #define
// No license, just give me credit. Find any bugs drop me a line at
// slaffond1990@gmail.com
// Creator and Founder, Shane Laffond
/////////////////////////////////////////////////////////////////////////////*/

/*
	Todo:
		Add float capability
	Bugs:
		None
*/

#ifndef PHAT_SS
#define PHAT_SS

#include <string>
#include <sstream>
#include <fstream>

using std::string;
using std::istringstream;
using std::ostringstream;

static std::ofstream errOut;

inline void error( string sOut, string sMsg = "Error:" ) 
{ 
	if( errOut.is_open() ) errOut << sMsg << " " << sOut;
	else { errOut.open("error.txt", std::ios::trunc); errOut << sMsg << " " << sOut; }
}

class pxSStream
{
private:
	string mString;
	int mInt;
	short int mSint;
	bool mBool;

	ostringstream mOutputStream;
	istringstream mInputStream;
public:
	pxSStream();
	~pxSStream();
	void numberToString(int iIn, string &sOut);
	void shortToString(short iIn, string &sOut);
	void boolToString(bool iIn, string &SOut);
	void stringToNumber(string &sIn, int&iOut);  // converts a string to an int C++ way
	void stringToShort(string &sIn, short int &iOut); // converts a string to a short c++ way
	void stringToBool(string &sIn, bool &iOut);
};

#endif
