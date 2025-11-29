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

const string const_unarmoredName = "Unarmored";
const string const_paddedName = "Padded";
const string const_leatherName = "Leather";
const string const_hideName = "Hide";
const string const_studdedName = "Studded Leather";
const string const_scaleName = "Scale";
const string const_chainshirtName = "Chain Shirt";
const string const_chainmailName = "Chain Mail";
const string const_breastplateName = "BreastPlate";
const string const_splintName = "Splint Mail";
const string const_bandedName = "Banded Splint Mail";
const string const_halfplateName = "Half Plate Suit";
const string const_fullplateName = "Full Plate Suit";

const string const_unarmoredDesc = "None";
const string const_paddedDesc = "Padded quilted material, very low protection.";
const string const_leatherDesc = "Leather armor, made from animal skins.";
const string const_hideDesc = "Hide armor, made from lizards and tough skins.";
const string const_studdedDesc = "Studded Leather, made from animal skins and studded for added rigidity.";
const string const_scaleDesc = "Scale mail, movable and breathable hide armor.";
const string const_chainshirtDesc = "Chain Shirt, loops of metal to protect the torso.";
const string const_chainmailDesc = "Chain Mail, loops of metal to protect the torso and limbs.";
const string const_breastplateDesc = "BreastPlate, thick metal to protect the torso and arms.";
const string const_splintDesc = "Splint Mail, thin strips of metal to allow walking.";
const string const_bandedDesc = "Banded Splint Mail, thin strips of metal, held closer together with leather strips.";
const string const_halfplateDesc = "Half Plate Suit, thick solid pieces of metal to protect the torso.";
const string const_fullplateDesc = "Full Plate Suit, thick solid pieces of metal to protect the whole body.";

const sint const_unarmoredAC = 0;	// +0
const sint const_unarmoredValue = 0;	// comes equipped

const sint const_paddedAC = 1;		// +1
const sint const_paddedValue = 50;	// gp

const sint const_leatherAC = 2;		// +2
const sint const_leatherValue = 100;	// gp

const sint const_hideAC = 3;		// +3
const sint const_hideValue = 150;	// gp

const sint const_studdedAC = 3;		// +3
const sint const_studdedValue = 250;	// gp

const sint const_scaleAC = 4;		// +4
const sint const_scaleValue = 500;	// gp

const sint const_chainshirtAC = 4;	// +4
const sint const_chainshirtValue = 1000;// gp

const sint const_chainmailAC = 5;	// +5
const sint const_chainmailValue = 1500;	// gp

const sint const_breastplateAC = 5;	// +5
const sint const_breastplateValue = 2000;// gp

const sint const_splintAC = 6;		// +6
const sint const_splintValue = 2250;	// gp

const sint const_bandedAC = 6;		// +6
const sint const_bandedValue = 2500;	// gp

const sint const_halfplateAC = 7;	// +7
const sint const_halfplateValue = 4500;	// gp

const sint const_fullplateAC = 8;	// +8
const sint const_fullplateValue = 8000;	// gp



/*
=================================================
END ARMOR
=================================================
*/

class cArmor : public cItem
{
private:
	sint mArmorClass;
	bool isEquipped; // Am i wearing this?

public:
	cArmor(sint ac = 0, sint value = 0, string name = "", string desc = "", string type = "armor") ;

	virtual void clear(); // Reset all values
						  // cArmor Accesors
	sint getAC() { return mArmorClass; } bool getEquipped() { return isEquipped; }
	void setAC( sint tmp ) { mArmorClass = tmp; } 

	// cItem accessors
	string getName() { return mItemName; }	string getDesc() { return mItemDesc; }	string getType() { return mItemType; } // Armor
	void setName( string tmp ) { mItemName = tmp; } void setDesc( string tmp ) { mItemDesc = tmp; } void setType( string tmp = "armor") { mItemType = tmp; }	void setEquipped( bool in ) { isEquipped = in; }
	
	void flipEquipped() { if (isEquipped) isEquipped = false; else isEquipped = true; }
};


#endif