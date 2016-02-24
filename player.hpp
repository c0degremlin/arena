/*

// Todo:
// finish cPlayer
// polish cMonster
// add combat
// add inventory
//
//   Bugs:


*/

#ifndef PLAYER
#define PLAYER

#include "phatx.hpp"
#include "phatSS.hpp"
#include "item.hpp"

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
// Experience is based on player level, along with random spawns, 5 classes, minotuar is seperate and hardest class
// See Plan.txt for more details

// Basics of a player
class cMonster
{
private:
	bool monsterCanRun; // Only some monsters can be run from. Mostly prey.

protected:
	bool mIsDead;
	string mName;
	string mEquippedWeaponName;
	sint mHealth;
	sint mArmor; // AC
	sint mGold;
	sint mAttack; // damage
	sint mAP; // action points
	sint mExperience; // basics of xp
public:
	cMonster();
	cMonster(sint iHealth, sint iArmor, sint iGold, sint iAttack, sint iAP, sint iXP, bool iCanRun);
	~cMonster();

	void createEnemy(string name, string weapon, sint health, sint armor, sint gold, sint attack, sint ap, sint xp); // make a monster with these stats
	sint getMod(sint in);

	//accessors
	const bool canMonsterRun() { return monsterCanRun; }
	const bool isDead() { return mIsDead; }
	const string getName() { return mName; }
	const string getWeaponName() { return mEquippedWeaponName; }
	const sint getHealth() { return mHealth; }
	const  sint getArmor() { return mArmor; }
	const sint getGold() { return mGold; }
	const sint getAttack() { return mAttack; }
	const sint getAP() { return mAP; }
	const int getExperience() { return mExperience; }

	// zeros are for debugging purposes
	void setRun(bool tmp) { monsterCanRun = tmp; }
	void setDead(bool tmp) { mIsDead = tmp; }
	void setName(string tmp) { mName = tmp; }
	void setWeaponName(string tmp) { mEquippedWeaponName = tmp; }
	void setHealth(sint iNum = 0) { if (iNum >= 0) mHealth = iNum; }
	void setArmor(sint iNum = 0) { if (iNum >= 0) mArmor = iNum; }
	void setGold(sint iNum = 0) { if (iNum >= 0) mGold = iNum; }
	void setAttack(sint iNum = 0) { if (iNum >= 0) mAttack = iNum; }
	void setAP(sint iNum = 0) { if (iNum >= 0) mAP = iNum; }
	void setExperience(int tmp) { if (tmp > 0) mExperience = tmp; }

	// add and delete action points
	void addAP(sint num = 1) { mAP += num; }
	bool delAP(sint num = 1); // true if you have enough AP.
};

class cPlayer : public cMonster
{
private:
	// Add inventory capabilities.. prob cItem vectors

	vector<cWeapon> mWeaponInventory;
	vector<cArmor> mArmorInventory;

	string mEquippedWeaponDesc;
	string mEquippedArmorName;
	string mEquipedArmorDesc;

	string mClassName; // Certain class use certain weapons

	int mMaxHealth;
	int mMana;
	int mMaxMana;
	int mMaxAP;

	int mStrength; // for attack rolls and armor/weapon checks
	int mDexterity; // for hit checks, ranged, dagger, sword and unarmed attacks, dodge...
	int mConstitution; // for health calcs and poison check
	int mIntelligence; // for spell checks and damage, mana calcs, mind control, etc checks
	int mWisdom; // for number of spells possible to learn and AP checks
	int mCharisma; // for mind control, etc checks, better bartering skills, more powerful buffs

	int mPotions; // can only have as many potions as level	
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
	void delWeapon(cWeapon item, int number = 0);
	void equipWeapon(cWeapon weapon, int number = 0);
	void getWeapon(cWeapon &item, int number = 0);


	void showInventory();
	void calcHPandMP();

	// Accessors
	const string getWeaponDesc() { return mEquippedWeaponDesc; } const string getArmorName() { return mEquippedArmorName; }
	const string getArmorDesc() { return mEquipedArmorDesc; } const string getClass() { return mClassName; }
	const int getMaxHealth() { return mMaxHealth; } const int getMana() { return mMana; } const int getMaxMana() { return mMaxMana; }
	const int getMaxAP() { return mMaxAP; }	 const int getStrength() { return mStrength; } const int getDexterity() { return mDexterity; }
	const int getConstitution() { return mConstitution; } const int getIntelligence() { return mIntelligence; } const int getWisdom() { return mWisdom; }
	const int getCharisma() { return mCharisma; } const int getPotions() { return mPotions; }
	const int getLevel() { return mLevel; } 

	void setWeaponDesc(string tmp) { mEquippedWeaponDesc = tmp; }
	void setArmorName(string tmp) { mEquippedArmorName = tmp; } void setArmorDesc(string tmp) { mEquipedArmorDesc = tmp; }
	void setClass(string tmp) { mClassName = tmp; } void setMaxHealth(int tmp) { if (tmp > 0 && tmp >= mHealth) mMaxHealth = tmp; }
	void setMana(int tmp) { if (tmp > 0) mMana = tmp; } void setMaxMana(int tmp) { if (tmp > 0 && tmp >= mMana) mMaxMana = tmp; }
	void setMaxAP(int tmp) { if (tmp > 0 && tmp >= mAP) mMaxAP = tmp; } void setStrength(int tmp) { if (tmp > 7) mStrength = tmp; }
	void setDexterity(int tmp) { if (tmp > 7) mDexterity = tmp; } void setConstitution(int tmp) { if (tmp > 7) mConstitution = tmp; }
	void setIntelligence(int tmp) { if (tmp > 7) mIntelligence = tmp; }
	void setWisdom(int tmp) { if (tmp > 7) mWisdom = tmp; } void setCharisma(int tmp) { if (tmp > 7) mCharisma = tmp; }
	void setPotions(int tmp) { if (tmp > 0) mPotions = tmp; }
	void setLevel(int tmp) { if (tmp > 1) mLevel = tmp; } 
	void fullAP() { mAP = mMaxAP; }
	void addAP(sint tmp = 1); // do check with maxAP
	void delAP(sint tmp = 1);
};

#endif

