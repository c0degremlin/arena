/*

//	Todo:

//  Bugs:


*/


#ifndef ARMOR_HPP
#define ARMOR_HPP

#include "item.hpp"


/*
=================================================
BEGIN ARMOR
=================================================
*/


const sint const_unarmoredAC = 0;	// +0
const sint const_unarmoredDex = 100;	// cant have dex bonus more than that!
const sint const_unarmoredValue = 0;	// comes equipped

const sint const_paddedAC = 1;		// +1
const sint const_paddedDex = 8;		// max +8 to dex checks
const sint const_paddedValue = 50;	// gp

const sint const_leatherAC = 2;		// +2
const sint const_leatherDex = 6;	// max +6 to dex checks
const sint const_leadtherValue = 100;	// gp

const sint const_hideAC = 3;		// +3
const sint const_hideDex = 4;		// max +4 to dex checks
const sint const_hideValue = 150;	// gp

const sint const_studdedAC = 3;		// +3
const sint const_studdedDex = 5;	// max +5 to dex checks
const sint const_studdedValue = 250;	// gp

const sint const_scaleAC = 4;		// +4
const sint const_scaleDex = 3;		// max +3 to dex checks
const sint const_scaleValue = 500;	// gp

const sint const_chainshirtAC = 4;	// +4
const sint const_chainshirtDex = 4;	// max +4 to dex checks
const sint const_chainshirtValue = 1000;// gp

const sint const_chainmailAC = 5;	// +5
const sint const_chainmailDex = 2;	// max +2 to dex checks
const sint const_chaimailValue = 1500;	// gp

const sint const_breastplateAC = 5;	// +5
const sint const_breastplateDex = 3;	// max +3 to dex checks
const sint const_breastplateValue = 2000;// gp

const sint const_splintAC = 6;		// +6
const sint const_splintDex = 0;		// no dex bonus
const sint const_splintValue = 2250;	// gp

const sint const_bandedAC = 6;		// +6
const sint const_bandedDex = 1;		// max +1 to dex checks
const sint const_bandedValue = 2500;	// gp

const sint const_halfplateAC = 7;	// +7
const sint const_halfplateDex = 0;	// no dex bonus
const sint const_halfplateValue = 4500;	// gp

const sint const_fullplateAC = 8;	// +8
const sint const_fullplateDex = 1;	// max +1 to dex checks
const sint const_fullplateValue = 8000;	// gp



/*
=================================================
END ARMOR
=================================================
*/

class cArmor : public cItem
{
private:
	sint mDexMod;
	sint mArmorClass;
	bool isEquipped; // Am i wearing this?

public:
	cArmor(sint dex = 0, sint ac = 0, sint value = 0, string name = "", string desc = "", string type = "") ;

	virtual void clear(); // Reset all values
						  // Accesors
	sint getMaxDex() { return mDexMod; } sint getAC() { return mArmorClass; } sint getValue() { return mValue; } bool getEquipped() { return isEquipped; }

	string getName() { return mItemName; }
	string getDesc() { return mItemDesc; }
	string getType() { return mItemType; } // Armor
};


#endif