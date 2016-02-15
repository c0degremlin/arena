#ifndef ITEM_HPP
#define ITEM_HPP

#include "phatx.hpp"
#include "phatSS.hpp"

/*
=================================================
BEGIN WEAPONS
=================================================
*/

// 		Close ranged weapons

const sint const_unarmedDamage = 3;	// damage total
const sint const_unarmedDice = 1;	// 1d
const sint const_unarmedCritical = 20;	// Roll a 20 for critical hit
const sint const_unarmedCritMod = 2; 	// x2 critical
const sint const_unarmedValue = 0;	// free

const sint const_daggerDamage = 4; 	// damage total
const sint const_daggerDice = 1;	// 1d
const sint const_daggerCritical = 19; 	// Roll a 19 for critcal hit
const sint const_daggerCritMod = 2;	// x2 critical
const sint const_daggerValue = 200;	// 200 gp

const sint const_maceDamage = 6;	// damage total
const sint const_maceDice = 1;		// 1d
const sint const_maceCritical = 20;	// Roll a 20 for critical hit
const sint const_maceCritMod = 2;	// x2 critical
const sint const_maceValue = 500;	// 500 gp

const sint const_handaxeDamage = 6;	// damage total
const sint const_handaxeDice = 1;	// 1d
const sint const_handaxeCritical = 20;	// Roll a 20 for critical hit
const sint const_handaxeCritMod = 3;	// x3 critcal
const sint const_handaxeValue = 600;	// 600

const sint const_shortswordDamage = 6;	// damage total
const sint const_shortswordDice = 1;	// 1d
const sint const_shortswordCritical = 19; // Roll a 19 for a critical hit
const sint ocnst_shortswordCritMod = 2;	// x2 critical
const sint const_shortswordValue = 650;	// 700 gp

const sint const_scimitarDamage = 6;	// damage total
const sint const_scimitarDice = 1;	// 1d
const sint const_scimitarCritical = 18;	// Roll a 18 for a critical hit
const sint const_scimitarCritMod = 2;	// x2 critical
const sint const_scimitarValue = 700;	// 700 gp

const sint const_morningstarDamage = 8; // damage total
const sint const_morningstarDice = 1;	// 1d
const sint const_morningstarCritical = 20; // Roll a 20 for a critical hit
const sint const_morningstarCritMod = 2;// x2 critical
const sint const_morningstarValue = 800;// 800 gp

const sint const_spearDamage = 8;	// damage total
const sint const_spearDice = 1;		// 1d
const sint const_spearCritical = 20;	// Roll a 20 for a critical
const sint const_spearCritMod = 3;	// x3 critical
const sint const_spearValue = 900;	// 900 gp

const sint const_longswordDamage = 8;	// damage total
const sint const_longswordDice = 1;	// 1d
const sint const_longswordCritical = 19;// Roll a 19 for a critical
const sint const_longswordCritMod = 2;	// x2 critical
const sint const_longswordValue = 950;	// 950 gp

const sint const_greatclubDamage = 10;	// damage total
const sint const_greatclubDice = 1;	// 1d
const sint const_greatclubCritcal = 20;		// Roll a 20 for a critical hit
const sint const_greatclubCritMod = 2;	// x2 critical
const sint const_greatclubValue = 1100; // 1100 gp

const sint const_halberdDamage = 10;	// damage total
const sint const_halberdDice = 1;	// 1d
const sint const_halberdCritical = 20;	// Roll a 20 for a critical
const sint const_halberdCritMod = 3;	// x3 critical
const sint const_halberdValue = 1200;	// 1200 gp

const sint const_bastardswordDamage = 10;// damage total
const sint const_bastardswordDice = 1;	// 1d
const sint const_bastardswordCritical = 19; // crit check
const sint const_bastardswordCritMod = 2; // double critical damage
const sint const_bastardswordValue = 1250; // gp

const sint const_greataxeDamage = 12;	// d12
const sint const_greataxeDice = 1;	// 1d
const sint const_greataxeCritical = 20;	// crit check
const sint const_greataxeCritMod = 3;	// x3 critical
const sint const_greataxeValue = 1600;	// gp

const sint const_greatswordDamage = 6;	// d6
const sint const_greatswordDice = 2;	// 2d
const sint const_greatswordCritical = 20; // crit check
const sint const_greatswordCritMod = 3;	// x3 critical
const sint const_greatswordValue = 2000;// gp


//		End close ranged weapons

/*
=================================================
END WEAPONS
=================================================
*/

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

// The basic template for all wearable items for offenes and defense
class cItem
{
protected:
	string mItemName; // Basic name for display
	string mItemDesc; // When asked for details this is the output
	string mItemType; // Weapon, Armor, Potion

	sint mValue; // How much gold is this worth
public:
	cItem();
};

class cWeapon : public cItem
{
protected:
	sint mDamage;
	sint mDice;
	sint mCritical;
	sint mCritMod;

	bool isEquipped; // Do i have this readied	

	string mTypeDetail; // sword, axe, bow, dagger, polearm
public:
	cWeapon(sint dmg = 0, sint dice = 0, sint crit = 0, sint critmod = 0, sint value = 0, string name = "", string desc = "", string type = "");

	// Accesors
	sint getDamage() { return mDamage; }
	sint getDice() { return mDice; }
	sint getCritical() { return mCritical; }
	sint getCritMod() { return mCritMod; }
	sint getIsEquipped() { return isEquipped; }
	sint getValue() { return mValue; }

	string getName() { return mItemName; }
	string getDesc() { return mItemDesc; }
	string getType() { return mItemType; } // Weapon

};

class cArmor : public cItem
{
private:
	sint mDexMod;
	sint mArmorClass;
	bool isEquipped; // Am i wearing this?

	string mTypeDetail; // leather, hide, place, scale, chain, amethst, mithril
public:
	cArmor(sint dex = 0, sint ac = 0, sint value = 0, string name = "", string desc = "", string type = "");

	// Accesors
	sint getMaxDex() { return mDexMod; } sint getAC() { return mArmorClass; } sint getValue() { return mValue; } bool getEquipped() { return isEquipped; }
	string getName();
	string getDesc();
	string getType(); // metal, leather or hide
};

class cPotion : public cItem
{

};





#endif
