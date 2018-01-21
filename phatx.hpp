/* Making console text more readable and extensive the c++ way
// Goal of being cross-platform with little to no more mods than a #define
// No license, just give me credit. Find any bugs drop me a line at
// slaffond1990@gmail.com
// Suggested titles:
// Phat eXploding Window - Founder, Shane Laffond
/////////////////////////////////////////////////////////////////////////////*/

/*

//	Todo:

//  Bugs:

If you try to pass non intergers it crashes use sstreams to make it proper and avoid crashes like a proper programmer.
Assume user is your grandma and "She didn't know what happened it was there and now its not" :D

*/

#ifndef _PHAT_SS_H
#define _PHAT_SS_H


#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::getline; // for getline( string, count )
using std::fstream; // file stream
using std::ofstream; // in file stream
using std::ifstream; // out file stream

using std::ios;
using std::ios_base;
using std::ws; // whitespace

typedef short int sint;

static int gInt;
static string gString;
static sint gShort;
static bool gBool;


/*/////////////////////////////////////////////////////////////////////////////
// To-do:
//          Add color
//			Win32 and nCurses
/////////////////////////////////////////////////////////////////////////////*/

class pxWindow
{
private:
	string mString;

	bool mBool;
	int mInt;
	float mFloat;
	sint mShort;
public:
	pxWindow();
	~pxWindow();

	///////////////////////////////////////////////////////////////////////////
	// random junk here
	///////////////////////////////////////////////////////////////////////////

	// default to d20
	void rng(int &iNum, int iModifier = 20);
	void rng(sint &iNum, sint iModifier = 20);

	// local accessors
	void flipBool() { if(mBool)mBool = false; else mBool = true; }
	void flipBool(bool &bFlip) { if (bFlip)bFlip = false; else bFlip = true; }

	void sleep(unsigned int mseconds);
	///////////////////////////////////////////////////////////////////////////
	// End Junk
	///////////////////////////////////////////////////////////////////////////

	// cout
	void text(string sOut, bool NL = true);
	void number(int iOut, bool NL = true);
	void fnumber(float fOut, bool NL = true);
	void shortNumber(sint siOut, bool NL = true);
	void btext(string sMsg, bool bOut, bool NL = true);
	void nl(int iLines = 2){ for( int i = 0; i < iLines; ++i ) cout << endl; }
	void clrscr();

	// cin
	void getS(string &sIn, string sMsg = "");
	void getShort(sint &siIn, string sMsg = "");
	void getI(int &iIn, string sMsg = "");
	void pause(string sMsg = "", string sText = "Press enter to contiune...");
};

#endif
