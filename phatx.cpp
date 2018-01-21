#include "phatx.hpp"

pxWindow::pxWindow()
{
	mInt = 0;
	mFloat = 0.0;
	mString.clear();
	srand( time ( 0 ) ); // seed rng
}

pxWindow::~pxWindow()
{ }

void pxWindow::rng(int &iNum, int iModifier)
{
	mInt = ( rand() % iModifier ) + 1;
	iNum = mInt;
}

void pxWindow::rng(sint &iNum, sint iModifier)
{
	if (iModifier > 0)
		mShort = (rand() % iModifier) + 1;
	else
		mShort = (rand() % 1) + 1;
	iNum = mShort;
}

void pxWindow::sleep(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

void pxWindow::text(string sOut, bool NL)
{
	if(NL)
		cout << sOut << endl;
	else
		cout << sOut;
	cout.flush();
}

void pxWindow::number(int iOut, bool NL)
{
	if(NL)
		cout << iOut << endl;
	else
		cout << iOut;
	cout.flush();
}

void pxWindow::shortNumber(sint siOut, bool NL)
{
	if(NL)
		cout << siOut << endl;
	else
		cout << siOut;
	cout.flush();
}

void pxWindow::fnumber(float fOut, bool NL)
{
	if(NL)
		cout << fOut << endl;
	else
		cout << fOut;
	cout.flush();
}

void pxWindow::btext(string sMsg, bool bOut, bool NL)
{
	if(!NL)
	{
		if(bOut)
			cout << sMsg << " is true";
		else
			cout << sMsg << "is false";
	}
	else
	{
		if(bOut)
			cout << sMsg << " is true." << endl;
		else
			cout << sMsg << " is false." << endl;
	}
	cout.flush();
}

void pxWindow::getS(string &sIn, string sMsg)
{
	if(!sMsg.empty()) cout << sMsg;
	cout.flush();
	getline(cin, sIn);
}

void pxWindow::getShort(sint &siIn, string sMsg)
{
	if(!sMsg.empty()) cout << sMsg;
	cin >> siIn;
	cin.ignore();
}

void pxWindow::getI(int &iIn, string sMsg)
{
	if(!sMsg.empty()) cout << sMsg;
	cin >> iIn;
	cin.ignore();
}

// pauses the c++ way
void pxWindow::pause(string sMsg, string sText)
{
	cout << sMsg << endl;

	if (sText.empty() == false)
		cout << sText << endl;

	cin.ignore();

}

void pxWindow::clrscr()
{
#ifdef WIN32
	system("cls");
#else
	system("clear");
#endif
}
