/*

// Todo:
// finish cPlayer
// polish cMonster
// add inventory
// Make sure cPlayer all variables are initialized
// Also make sure we trim away unneccesary variables and such

//   Bugs:


*/

#ifndef PLAYER
#define PLAYER

#include "phatx.hpp"
#include "phatSS.hpp"
#include "weapon.hpp"
#include "armor.hpp"
#include "potion.hpp"

#include <vector>
using std::vector;

extern pxWindow px;
extern pxSStream ss;


const float const_hpScaling = 1.2f;	// Constitution bonus
const float const_manaScaling = 1.5f;	// Intelligence bonus
const float const_apScaling = 1.8f;	// Number of action points every five seconds
const sint const_baseAC = 10;		// Without armor

// Combat is to be based of an Action point system, for which this formula is still to
// be determined
// Experience is based on player level, along with random spawns, 5 classes of enemies, minotuar is seperate and hardest class
// See Plan.txt for more details

// Basics of a player
class cMonster
{
private:

protected:
	string mName;
	string mEquippedWeaponName;
	sint mHealth;
	sint mArmor; // AC
	sint mGold;
	sint mAttack; // damage
	sint mExperience; // basics of xp
	
	int mLevel;

public:
	cMonster();
	cMonster(string name, sint iHealth, sint iArmor, sint iGold, sint iAttack, sint iXP, sint iLevel);
	~cMonster();

	void createEnemy(string name, string weapon, sint health, sint armor, sint gold, sint attack, sint xp, sint level); // make a monster with these stats
	//accessors
	const string getName() { return mName; }
	const string getWeaponName() { return mEquippedWeaponName; }
	const sint getHealth() { return mHealth; }
	const  sint getArmorClass() { return mArmor; }
	const sint getGold() { return mGold; }
	const sint getAttack() { return mAttack; }
	const int getExperience() { return mExperience; }

	const int getLevel() { return mLevel; } 


	// zeros are for debugging purposes
	void setName(string tmp) { mName = tmp; }
	void setWeaponName(string tmp) { mEquippedWeaponName = tmp; }
	void setHealth(sint iNum = 0) { if (iNum >= 0) mHealth = iNum; }
	void setArmorClass(sint iNum = 0) { if (iNum >= 0) mArmor = iNum; }
	void setGold(sint iNum = 0) { if (iNum >= 0) mGold = iNum; }
	void setAttack(sint iNum = 0) { if (iNum >= 0) mAttack = iNum; }
	void setExperience(int tmp) { if (tmp >= 0) mExperience = tmp; }
	
	void setLevel(int tmp) { if (tmp > 1) mLevel = tmp; } 
};

class cPlayer : public cMonster
{
private:
	// Add inventory capabilities.. prob cItem vectors

	cWeapon mWeaponInventory[3];	
	cArmor mArmorInventory[3];
	cPotion mPotionInventory[10];
	

	cWeapon mWeapon; // This is the equipped stuff
	cArmor mArmor;

	string mEquippedWeaponDesc;
	
	string mEquippedArmorName;
	string mEquippedArmorDesc;

	string mClassName; // Certain class use certain weapons

	int mMaxHealth;

	int mNumberOfWeapons;
	int mNumberOfArmors;
	int mNumberOfPotions;

public:
	bool mCreated;
	cPlayer();
	~cPlayer();

	void level(); // level based on calculated tables

	//heal();

	int addWeapon(cWeapon item, int number = 0); // returns 100 when inventory is full
	void delWeapon(int number = 0);
	void equipWeapon(int number = 0);
	void getWeapon(cWeapon &item, int number = 0);
	int getWeaponCount() { return mNumberOfWeapons; } // returns weapon inventory count
	
	int addArmor(cArmor item, int number = 0);
	void delArmor(int number = 0);
	void equipArmor(int number = 0);
	void getArmor(cArmor &item, int number = 0);
	int getArmorCount() { return mNumberOfArmors; }	// returns armor inventory count

	void addPotion(cPotion item, int number = 0);
	void delPotion(int number = 0);
	void getPotion(cPotion &item, int number = 0);
	int getPotionCount() { return mNumberOfPotions; } // returns potion inventory count

	void showInventory();		// Show weapon and armor
	void showWeaponInventory();
	void showArmorInventory();

	// Accessors
	const string getWeaponDesc() { return mEquippedWeaponDesc; } const string getArmorName() { return mEquippedArmorName; }
	const string getArmorDesc() { return mEquippedArmorDesc; } const string getClass() { return mClassName; }
	const int getMaxHealth() { return mMaxHealth; }

	void setWeaponDesc(string tmp) { mEquippedWeaponDesc = tmp; }
	void setArmorName(string tmp) { mEquippedArmorName = tmp; } void setArmorDesc(string tmp) { mEquippedArmorDesc = tmp; }
	void setClass(string tmp) { mClassName = tmp; } void setMaxHealth(int tmp) { if (tmp > 0 && tmp >= mHealth) mMaxHealth = tmp; }

	
};

#endif

