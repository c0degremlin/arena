#include "player.hpp"

cMonster::cMonster()
{
	mHealth = 0; mArmor = 0; mGold = 0; mAttack = 0; mAP = 0;
	gNumOfMonsters += 1; monsterCanRun = false; // mostly only prey can run...
}

cMonster::cMonster(sint iHealth, sint iArmor, sint iGold, sint iAttack, sint iAP, sint iXP, bool iCanRun)
{
	// use functions for cleaner error checking such as 0 health, 0 attack, 0 armor
	setHealth(iHealth); setArmorClass(iArmor); setGold(iGold); setAttack(iAttack); setAP(iAP); setExperience(iXP);

	monsterCanRun = iCanRun; gNumOfMonsters += 1;
}

cMonster::~cMonster()
{
	gNumOfMonsters -= 1;
}

void cMonster::createEnemy(string name, string weapon, sint health, sint armor, sint gold, sint attack, sint ap, sint xp)
{
	mName = name; mEquippedWeaponName = weapon;
	mHealth = health; mArmor = armor; mGold = gold; mAttack = attack; mAP = ap; mExperience = xp;
}

sint cMonster::getMod(sint in)
{
	in -= 10;
	in /= 2;
	return in;
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
		px.pause("Can't do that. You are too tired."); return false;
	}
}

cPlayer::cPlayer()
{
	mEquippedWeaponName = "Unarmed";
	mEquippedWeaponDesc = "Bashing with the use of bare knuckles!";
	mEquippedArmorName = "Unarmored";
	mEquippedArmorDesc = "Bare flesh and cloth loins";
	mClassName = "Farmer";

	mIsDead = false;
	mCreated = false;

	mHealth = mMaxHealth = mMana = mMaxMana = mGold = mAttack = mAP = mMaxAP = 0;

	mStrength = mDexterity = mConstitution = mIntelligence = mWisdom = mCharisma = 0;

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
	if (number == 0)	// default add to top of the stack
		mWeaponInventory.push_back(item);
	else			// replace specfic item
		mWeaponInventory.at(number) = item;
}

void cPlayer::delWeapon(int number)
{
	if (number == 0)	// default remove from top of the stack
		mWeaponInventory.pop_back();
	else			// replace specfic item
		mWeaponInventory.erase(mWeaponInventory.begin(), mWeaponInventory.begin() + number);
}

void cPlayer::equipWeapon(int number)
{
	if (mWeapon.getIsEquipped())
	{
		px.text(mWeapon.getName(), false);
		px.text(" is already equipped...");
		px.pause();
	}
	else
	{
		mWeapon = mWeaponInventory.at(number);
		mEquippedWeaponName = mWeapon.getName();
		mEquippedWeaponDesc = mWeapon.getDesc();
		mAttack = mWeapon.getDamage();
		mWeapon.flipEquipped();
	}
}

void cPlayer::getWeapon(cWeapon &item, int number)
{
	item = mWeaponInventory.at(number);
}

void cPlayer::addArmor(cArmor item, int number)
{
	if (number == 0)	// default add to top of the stack
		mArmorInventory.push_back(item);
	else			// replace specfic item
		mArmorInventory.at(number) = item;
}

void cPlayer::delArmor(int number)
{
	if (number == 0)	// default remove from top of the stack
		mArmorInventory.pop_back();
	else			// replace specfic item
		mArmorInventory.erase(mArmorInventory.begin(), mArmorInventory.begin() + number);
}

void cPlayer::equipArmor(int number)
{
	if (mArmor.getEquipped())
	{
		px.text(mArmor.getName(), false);
		px.text(" is already equipped...");
		px.pause();
	}
	else
	{
		mArmor = mArmorInventory.at(number);
		mEquippedArmorName = mArmor.getName();
		mEquippedArmorDesc = mArmor.getDesc();
		mArmor.flipEquipped();
	}
}

void cPlayer::getArmor(cArmor &item, int number)
{
	item = mArmorInventory.at(number);
}

void cPlayer::level()
{
	sint prevXP, prevLevel, nextXP, nextLevel;
	vector<sint> xpChart;
	vector<sint> levelChart;

	prevXP = 0;
	prevLevel = 1;

	nextLevel = 1;
	
	xpChart.push_back(prevXP);
	levelChart.push_back(prevLevel);

	// calculate 30 levels
	for( int i = 1; i < 30; i++ )
	{
		nextXP = ( i * 1000) + prevXP;
		nextLevel++;
		prevXP = nextXP;

		xpChart.push_back(nextXP);
		levelChart.push_back(nextLevel);
	}

		if( mExperience >= xpChart.at(mLevel))
		{
			mLevel = levelChart.at(mLevel);
			px.rng(gShort, 10);
			gShort += getMod(mConstitution);
			mHealth += gShort;
			mMaxHealth = mHealth;
			calcHPandMP();

			px.text("You leveled up! You are now level ", false);
			px.shortNumber(mLevel, false);
			px.text(".");
			
			px.text("Your new hp is ", false);
			px.shortNumber(mHealth, false);
			px.text(".");

			px.pause();
		}
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
		px.text(weapon_tmp->getName(), false);		// Damage: 2d8		Critical: 20x2
		px.text("        Desc: ", false);			// Value: 200		Type: Handheld blade
		px.text(weapon_tmp->getDesc());		//
		px.text("Damage: ", false);		px.shortNumber(weapon_tmp->getDice(), false);
		px.text("d", false);		px.shortNumber(weapon_tmp->getDamage(), false);
		px.text("        Critical: ", false);	px.shortNumber(weapon_tmp->getCritical(), false); px.text("x", false); px.shortNumber(weapon_tmp->getCritMod());
		px.text("Value: ", false); px.shortNumber(weapon_tmp->getValue(), false); px.text("gp    Type: ", false); px.text(weapon_tmp->getType());
	} // end for weapon loop

}

void cPlayer::calcHPandMP()
{

	sint hp, maxhp, mana, maxmana, ap, maxap;

	hp = mConstitution;
	hp *= const_hpScaling;
	maxhp = hp;

	mana = mIntelligence;
	mana *= const_manaScaling;
	maxmana = mana;

	ap = mDexterity;
	ap *= const_apScaling;
	maxap = ap;

	mHealth = hp; mMaxHealth = maxhp;
	mMana = mana; mMaxMana = maxmana;
	mAP = ap; mMaxAP = maxap;
}
