#include "player.hpp"

cMonster::cMonster()
{
	mHealth = 0; mArmor = 0; mGold = 0; mAttack = 0; mAP = 0;
	gNumOfMonsters += 1; monsterCanRun = false; // mostly only prey can run...
}

cMonster::cMonster(sint iHealth, sint iArmor, sint iGold, sint iAttack, sint iAP, bool iCanRun)
{
	// use functions for cleaner error checking such as 0 health, 0 attack, 0 armor
	setHealth(iHealth); setArmor(iArmor); setGold(iGold); setAttack(iAttack); setAP(iAP);

	monsterCanRun = iCanRun; gNumOfMonsters += 1;
}

cMonster::~cMonster()
{
	gNumOfMonsters -= 1;
}

bool cMonster::delAP(sint num)
{
	gShort = (mAP -= num);
	if (gShort >= 0)
	{
		mAP = gShort; return true;
	}
	else
	{
		px.pause("Can't do that. You are too tired.\nPress enter to continue..."); return false;
	}
}

cPlayer::cPlayer()
{
	mEquippedWeaponName = "Unarmed";
	mEquippedWeaponDesc = "Bashing with the use of bare knuckles!";
	mEquippedArmorName = "Unarmored";
	mEquipedArmorDesc = "Bare flesh and cloth loins";
	mClassName = "Farmer";

	mIsDead = false;
	mCreated = false;

	mHealth = mMaxHealth = mMana = mMaxMana = mGold = mAttack = mAP = mMaxAP = 0;

	mStrength = mDexterity = mConstituion = mIntelligence = mWisdom = mCharisma = 0;

	mArmor = const_baseAC; // base 10 AC
	mAttack = const_unarmedDamage; // 1d3 unarmed

	mPotions = 0;
	mExperience = 0;
	mLevel = 1;

}


cPlayer::~cPlayer()
{

}


void cPlayer::addAP(sint num)
{
	gShort = mAP + num;
	if (gShort <= mMaxAP)
		mAP = gShort;
	else
	{
		cout << __LINE__ << endl;
		px.pause("Error: Can't add action points");
	}
}

void cPlayer::addWeapon(cWeapon item, int number)
{
	string type = item.getType();

	if (number == 0)	// default add to top of the stack
		mWeaponInventory.push_back(item);
	else			// replace specfic item
		mWeaponInventory.at(number) = item;
}

void cPlayer::delWeapon(cWeapon item, int number)
{

}

void cPlayer::showInventory()
{
	cArmor armor_tmp;
	px.clrscr();

	px.text("==============================");
	px.text("Weapon inventory:");
	px.text("==============================");

	for (auto weapon_tmp = mWeaponInventory.begin(); weapon_tmp != mWeaponInventory.end(); ++weapon_tmp)
	{

		px.text("Name: ", false);			// Name: Dagger		Desc: A curved menacing short blade
		px.text(weapon_tmp->getName(), false);		// Damage: 2d8		Critical: 20 x2
		px.text("\t\tDesc: ", false);			// Value: 200		Type: Handheld blade
		px.text(weapon_tmp->getDesc());		//
		px.text("Damage: ", false);		px.shortNumber(weapon_tmp->getDice(), false);
		px.text("d", false);		px.shortNumber(weapon_tmp->getDamage(), false);
		px.text("\t\tCritical: ", false);	px.shortNumber(weapon_tmp->getCritical(), false); px.text(" x", false); px.shortNumber(weapon_tmp->getCritMod());
		px.text("Value: ", false); px.shortNumber(weapon_tmp->getValue(), false); px.text("gp\tType: ", false); px.text(weapon_tmp->getType());
	} // end for weapon loop

}

void cPlayer::calcHPandMP( cPlayer &player )
{

	sint hp, maxhp, mana, maxmana;

	hp = player.getConstitution();
	hp *= const_hpScaling;
	maxhp = hp;

	mana = player.getIntelligence();
	mana *= const_manaScaling;
	maxmana = mana;

	player.setHealth(hp); player.setMaxHealth(maxhp);
	player.setMana(mana); player.setMaxMana(maxmana);

}