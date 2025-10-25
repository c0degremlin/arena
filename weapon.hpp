/*

//	Todo:

//  Bugs:


*/
#ifndef WEAPON_HPP
#define WEAPON_HPP
#include "item.hpp"
/*
=================================================
BEGIN WEAPONS
=================================================
*/

// 		Close ranged weapons

const string const_unarmedName = "Unarmed";
const string const_daggerName = "Dagger";
const string const_maceName = "Mace";
const string const_handaxeName = "Hand Axe";
const string const_scimitarName = "Scimitar";
const string const_shortswordName = "Short Sword";
const string const_morningstarName = "Morningstar";
const string const_spearName = "Spear";
const string const_longswordName = "Longsword";
const string const_greatclubName = "Greatclub";
const string const_halberdName = "Halberd";
const string const_bastardswordName = "Bastard Sword";
const string const_greataxeName = "Great Axe";
const string const_greatswordName = "Great Sword";

const string const_unarmedDesc = "";
const string const_daggerDesc = "A sharp curved blade that fits perfect in a belt";
const string const_maceDesc = "A club with a metal ball at the end";
const string const_handaxeDesc = "A handheld axe, very fast";
const string const_scimitarDesc = "A viciously curved blade, very fast";
const string const_morningstarDesc = "A club with several spikes at the end";
const string const_spearDesc = "A long pole weapon with a sharp point";
const string const_longswordDesc = "A straight, double-edged sword";
const string const_greatclubDesc = "A large, heavy, two-handed weapon with spikes";
const string const_halberdDesc = "A polearm weapon that combines an axe blade and a spear point";
const string const_bastardswordDesc = "A hand-and-a-half sword";
const string const_greataxeDesc = "A large, powerful axe with a double-edged head";
const string const_greatswordDesc = "A large two-handed sword almost as tall as a person";

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
const sint const_shortswordCritMod = 2;	// x2 critical
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
const sint const_greatclubCritical = 20;		// Roll a 20 for a critical hit
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

class cWeapon : public cItem
{
protected:
	sint mDamage;
	sint mDice;
	sint mCritical;
	sint mCritMod;

	bool isEquipped; // Do i have this readied	
public:
	cWeapon(sint dmg = 0, sint dice = 0, sint crit = 0, sint critmod = 0, sint value = 0, string name = "", string desc = "", string type = "weapon");

	virtual void clear(); // Reset all values
						  // Accesors for cWeapon
	sint getDamage() { return mDamage; }	sint getDice() { return mDice; }	sint getCritical() { return mCritical; }	sint getCritMod() { return mCritMod; }	bool getIsEquipped() { return isEquipped; }
	void setDamage(sint num) { mDamage = num; }	void setDice(sint num) { mDice = num; }	void setCritical(sint num) { mCritical = num; }	void setCritMod(sint num) { mCritMod = num; } void setEquipped( bool in ) { isEquipped = in; }
	
	// cItem accessors
	string getName() { return mItemName; }	string getDesc() { return mItemDesc; }	string getType() { return mItemType; } // weapon
	void setName(string tmp) { mItemName = tmp; }	void setDesc( string tmp) {	mItemDesc = tmp; } void setType( string tmp = "weapon") { mItemType = tmp; }

	void flipEquipped() { if (isEquipped) isEquipped = false; else isEquipped = true; }
};

#endif