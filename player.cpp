#include "player.hpp"
#include <cstddef>

cMonster::cMonster()
{
	mHealth = 0; mArmor = 0; mGold = 0; mAttack = 0;
	gNumOfMonsters += 1;
}

cMonster::cMonster(string name, sint iHealth, sint iArmor, sint iGold, sint iAttack, sint iXP)
{
	// use functions for cleaner error checking such as 0 health, 0 attack, 0 armor
	setName(name);
	setHealth(iHealth); setArmorClass(iArmor); setGold(iGold); setAttack(iAttack); setExperience(iXP);
	gNumOfMonsters += 1;
}

cMonster::~cMonster()
{
	gNumOfMonsters -= 1;
}
	
void cMonster::createEnemy(string name, string weapon, sint health, sint armor, sint gold, sint attack, sint xp)
{
	mName = name; mEquippedWeaponName = weapon;
	mHealth = health; mArmor = armor; mGold = gold; mAttack = attack; mExperience = xp;
}




cPlayer::cPlayer()
{
	mEquippedWeaponName = "Unarmed";
	mEquippedWeaponDesc = "Bashing with the use of bare knuckles!";
	mEquippedArmorName = "Unarmored";
	mEquippedArmorDesc = "Bare flesh and cloth loins";
	mClassName = "Farmer";

	mCreated = false;

	mHealth = mMaxHealth = mGold = mAttack = 0;

	mStrength = mDexterity = mConstitution = mIntelligence = mWisdom = mCharisma = 0;

	mArmor = const_baseAC; // base 10 AC
	mAttack = const_unarmedDamage; // 1d3 unarmed

	mExperience = 0;
	mLevel = 1;

}


cPlayer::~cPlayer()
{

}


void cPlayer::addWeapon(cWeapon item, int number)
{
	switch(number)
	{
		case 0:
			mWeaponInventory[0] = item;
		break;
		
		case 1:
			mWeaponInventory[1] = item;
		break;

		case 2:
			mWeaponInventory[2] = item;
		break;

		default:
			cout << "Error addWeapon number out of bounds";
			cin.get(); cin.get();
		break;
	}
}

void cPlayer::delWeapon(int number)
{
	if(number < 4 && number >= 0)
		mWeaponInventory[number] = 0;
}

void cPlayer::equipWeapon(int number)
{
		mEquippedWeaponName = mWeapon.getName();
		mEquippedWeaponDesc = mWeapon.getDesc();
		mAttack = mWeapon.getDamage();
		mWeapon.flipEquipped();
}

void cPlayer::getWeapon(cWeapon &item, int number)
{
	if(number < 4 )
		item = mWeaponInventory[number];
}


void cPlayer::addArmor(cArmor item, int number)
{
	switch(number)
	{
		case 0:
			mArmorInventory[0] = item;
		break;
		
		case 1:
			mArmorInventory[1] = item;
		break;

		case 2:
			mArmorInventory[2] = item;
		break;

		default:
			cout << "Error addArmor number out of bounds" << endl;
			cin.get(); cin.get();
		break;
	}
}

void cPlayer::delArmor(int number)
{
	switch(number)
	{
		case 0:
			mArmorInventory[0] = 0;
		break;

		case 1:
			mArmorInventory[1] = 0;
		break;

		case 2:
			mArmorInventory[2] = 0;
		break;

		default:
			cout << "Error delArmor number out of bounds" << endl;
			cin.get(); cin.get();
		break;
	}
}

void cPlayer::equipArmor(int number)
{
	if (mArmor.getEquipped())
	{
		px.text(mArmor.getName(), false);
		px.text(" is already equipped...");
		px.pause();
	}
	else if ( number < 4 )
	{
		mArmor = mArmorInventory[number];
		mEquippedArmorName = mArmor.getName();
		mEquippedArmorDesc = mArmor.getDesc();
		mArmor.flipEquipped();
	}
}

void cPlayer::getArmor(cArmor &item, int number)
{
	if(number < 4)
	item = mArmorInventory[number];
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
			mHealth += gShort;
			mMaxHealth = mHealth;
			calcHP();

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
	px.clrscr();

	px.text("==============================");
	px.text("Weapon inventory");
	px.text("==============================");



	for (int index = 0; index < sizeof(mWeaponInventory) / sizeof(mWeaponInventory[0]); index++)
	{

		px.text("Name: ", false);			// Name: Dagger		Desc: A curved menacing short blade
		px.text(mWeaponInventory[index].getName(), false);		// Damage: 2d8		Critical: 20x2
		px.text("        Desc: ", false);			// Value: 200		Type: Handheld blade
		px.text(mWeaponInventory[index].getDesc());		//
		px.text("Damage: ", false);		px.shortNumber(mWeaponInventory[index].getDice(), false);
		px.text("d", false);		px.shortNumber(mWeaponInventory[index].getDamage(), false);
		px.text("        Critical: ", false);	px.shortNumber(mWeaponInventory[index].getCritical(), false); px.text("x", false); px.shortNumber(mWeaponInventory[index].getCritMod());
		px.text("Value: ", false); px.shortNumber(mWeaponInventory[index].getValue(), false); px.text("gp    Type: ", false); px.text(mWeaponInventory[index].getType());
		
	} // end for weapon loop
	
	px.nl(4);
	px.text("=============================");
	px.text("Armor Inventory");
	px.text("=============================");

	for( int index = 0; index < sizeof(mArmorInventory) / sizeof(mArmorInventory[0]); index++)
	{
		// setup output for armor inventory
	}
}

void cPlayer::calcHP()
{

	sint hp, maxhp;
	hp = mConstitution;
	hp *= const_hpScaling;
	maxhp = hp;

	mHealth = hp; mMaxHealth = maxhp;
}
