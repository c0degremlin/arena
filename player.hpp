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

#include <cstddef>
#include <vector>
using std::vector;

extern pxWindow px;
extern pxSStream ss;

extern int gNumOfMonsters;

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
public:
	cMonster();
	cMonster(string name, sint iHealth, sint iArmor, sint iGold, sint iAttack, sint iXP);
	~cMonster();

	void createEnemy(string name, string weapon, sint health, sint armor, sint gold, sint attack, sint xp); // make a monster with these stats
	//accessors
	const string getName() { return mName; }
	const string getWeaponName() { return mEquippedWeaponName; }
	const sint getHealth() { return mHealth; }
	const  sint getArmorClass() { return mArmor; }
	const sint getGold() { return mGold; }
	const sint getAttack() { return mAttack; }
	const int getExperience() { return mExperience; }

	// zeros are for debugging purposes
	void setName(string tmp) { mName = tmp; }
	void setWeaponName(string tmp) { mEquippedWeaponName = tmp; }
	void setHealth(sint iNum = 0) { if (iNum >= 0) mHealth = iNum; }
	void setArmorClass(sint iNum = 0) { if (iNum >= 0) mArmor = iNum; }
	void setGold(sint iNum = 0) { if (iNum >= 0) mGold = iNum; }
	void setAttack(sint iNum = 0) { if (iNum >= 0) mAttack = iNum; }
	void setExperience(int tmp) { if (tmp >= 0) mExperience = tmp; }
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

	int mStrength; // for attack rolls and armor/weapon checks
	int mDexterity; // for hit checks, ranged, dagger, sword and unarmed attacks, dodge...
	int mConstitution; // for health calcs and poison check
	int mIntelligence; // for spell checks and damage, mana calcs, mind control, etc checks
	int mWisdom; // for number of spells possible to learn and AP checks
	int mCharisma; // for mind control, etc checks, better bartering skills, more powerful buffs

	int mLevel;

public:
	bool mCreated;
	cPlayer();
	~cPlayer();

	void level(); // level based on calculated tables

	// addItem()
	// delItem()
	// heal()

	void addWeapon(cWeapon item, int number = 0);
	void delWeapon(int number = 0);
	void equipWeapon(int number = 0);
	void getWeapon(cWeapon &item, int number = 0);
	
	void addArmor(cArmor item, int number = 0);
	void delArmor(int number = 0);
	void equipArmor(int number = 0);
	void getArmor(cArmor &item, int number = 0);
	size_t  getArmorCount();	// returns armor inventory count


	void showInventory();
	void calcHP();

	// Accessors
	const string getWeaponDesc() { return mEquippedWeaponDesc; } const string getArmorName() { return mEquippedArmorName; }
	const string getArmorDesc() { return mEquippedArmorDesc; } const string getClass() { return mClassName; }
	const int getMaxHealth() { return mMaxHealth; }
	const int getStrength() { return mStrength; } const int getDexterity() { return mDexterity; }
	const int getConstitution() { return mConstitution; } const int getIntelligence() { return mIntelligence; } const int getWisdom() { return mWisdom; }
	const int getCharisma() { return mCharisma; }
	const int getLevel() { return mLevel; } 

	void setWeaponDesc(string tmp) { mEquippedWeaponDesc = tmp; }
	void setArmorName(string tmp) { mEquippedArmorName = tmp; } void setArmorDesc(string tmp) { mEquippedArmorDesc = tmp; }
	void setClass(string tmp) { mClassName = tmp; } void setMaxHealth(int tmp) { if (tmp > 0 && tmp >= mHealth) mMaxHealth = tmp; }
	void setStrength(int tmp) { if (tmp > 7) mStrength = tmp; }
	void setDexterity(int tmp) { if (tmp > 7) mDexterity = tmp; } void setConstitution(int tmp) { if (tmp > 7) mConstitution = tmp; }
	void setIntelligence(int tmp) { if (tmp > 7) mIntelligence = tmp; }
	void setWisdom(int tmp) { if (tmp > 7) mWisdom = tmp; } void setCharisma(int tmp) { if (tmp > 7) mCharisma = tmp; }

	void setLevel(int tmp) { if (tmp > 1) mLevel = tmp; } 
	
};

#endif

