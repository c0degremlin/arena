#include "player.hpp"

cMonster::cMonster()
{
	mHealth = 0; mArmor = 0; mGold = 0; mAttack = 0;
	mName.clear();
	mEquippedWeaponName.clear();
	mExperience = 0;
	mLevel = 1;
}

cMonster::cMonster(string name, sint iHealth, sint iArmor, sint iGold, sint iAttack, sint iXP, sint iLevel)
{
	// use functions for cleaner error checking such as 0 health, 0 attack, 0 armor
	setName(name);
	setHealth(iHealth); setArmorClass(iArmor); setGold(iGold); setAttack(iAttack); setExperience(iXP);
	setLevel(iLevel);
	mEquippedWeaponName.clear();
}

cMonster::~cMonster()
{
}
	
void cMonster::createEnemy(string name, string weapon, sint health, sint armor, sint gold, sint attack, sint xp, sint level)
{
	mName = name; mEquippedWeaponName = weapon;
	mHealth = health; mArmor = armor; mGold = gold; mAttack = attack; mExperience = xp; mLevel = level;
}




cPlayer::cPlayer()
{
	mName = "cPlayer";
	mEquippedWeaponName = "Unarmed";
	mEquippedWeaponDesc = "Bashing with the use of bare knuckles!";
	mEquippedArmorName = "Unarmored";
	mEquippedArmorDesc = "Bare flesh and cloth loins";
	mClassName = "Farmer";

	mCreated = false;

	mHealth = mMaxHealth = 20;
	mGold = mAttack = 0;


	mArmor = const_baseAC; // base 10 AC
	mAttack = const_unarmedDamage; // 1d3 unarmed

	mExperience = 0;
	mLevel = 1;

	mNumberOfArmors = 0;
	mNumberOfWeapons = 0;
	mNumberOfPotions = 0;
}


cPlayer::~cPlayer()
{

}


int cPlayer::addWeapon(cWeapon item, int number)
{
	switch(number)
	{
		case 0:
			mWeaponInventory[0] = item;
			mNumberOfWeapons++;
		break;
		
		case 1:
			mWeaponInventory[1] = item;
			mNumberOfWeapons++;
		break;

		case 2:
			mWeaponInventory[2] = item;
			mNumberOfWeapons++;
		break;


		// 	possible fix is 3 means sell another weapon to keep?
		default:
			cout << "Error addWeapon number out of bounds";
			cin.get(); cin.get();
			return 100;
		break;
	}
	return mNumberOfWeapons;
}

void cPlayer::delWeapon(int number)
{
	if(number < 4 && number >= 0)
	{
		mWeaponInventory[number] = 0;
		mNumberOfWeapons--;
	}
}

void cPlayer::equipWeapon(int number)
{
		mWeapon = mWeaponInventory[number];
		mEquippedWeaponName = mWeapon.getName();
		mEquippedWeaponDesc = mWeapon.getDesc();
		mAttack = mWeapon.getDamage() * mWeapon.getDice();
		mWeapon.flipEquipped();
}

void cPlayer::getWeapon(cWeapon &item, int number)
{
	if(number <= mNumberOfWeapons )
		item = mWeaponInventory[number];
}


int cPlayer::addArmor(cArmor item, int number)
{
	switch(number)
	{
		case 0:
			mArmorInventory[0] = item;
			mNumberOfArmors++;
		break;
		
		case 1:
			mArmorInventory[1] = item;
			mNumberOfArmors++;
		break;

		case 2:
			mArmorInventory[2] = item;
			mNumberOfArmors++;
		break;


		// possible fix, 3 means sell armor to keep new one?
		default:
			cout << "Error addArmor number out of bounds" << endl;
			cin.get(); cin.get();
			return 100;
		break;
	}
	return mNumberOfArmors;
}

void cPlayer::delArmor(int number)
{
	switch(number)
	{
		case 0:
			mArmorInventory[0] = 0;
			mNumberOfArmors--;
		break;

		case 1:
			mArmorInventory[1] = 0;
			mNumberOfArmors--;
		break;

		case 2:
			mArmorInventory[2] = 0;
			mNumberOfArmors--;
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
	if(number < mNumberOfArmors)
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
	this->showWeaponInventory();
	
	px.pause();

	this->showArmorInventory();
}

void cPlayer::showWeaponInventory()
{

	px.clrscr();
	px.text("==============================");
	px.text("Weapon inventory");
	px.text("==============================");

	for (int index = 0; index < mNumberOfWeapons; index++)
	{
		px.number(index+1, false);
		px.text(".");
		px.text("Name: ", false);			// Name: Dagger		Desc: A curved menacing short blade
		px.text(mWeaponInventory[index].getName(), false);		// Damage: 2d8		Critical: 20x2
		px.text("        Desc: ", false);			// Value: 200		Type: Handheld blade
		px.text(mWeaponInventory[index].getDesc());		//
		px.text("Damage: ", false);		px.shortNumber(mWeaponInventory[index].getDice(), false);
		px.text("d", false);		px.shortNumber(mWeaponInventory[index].getDamage(), false);
		px.text("        Critical: ", false);	px.shortNumber(mWeaponInventory[index].getCritical(), false); px.text("x", false); px.shortNumber(mWeaponInventory[index].getCritMod());
		px.text("Value: ", false); px.shortNumber(mWeaponInventory[index].getValue(), false); px.text("gp    Type: ", false); px.text(mWeaponInventory[index].getType());
		
	} // end for weapon loop
}

void cPlayer::showArmorInventory()
{
	px.clrscr();
	px.text("=============================");
	px.text("Armor Inventory");
	px.text("=============================");

	for( int index = 0; mNumberOfArmors; index++)
	{
		px.number(index+1, false);
		px.text(".");
		px.text("Name: ", false);			// Name: Leather	Desc: Leather armor
		px.text( mArmorInventory[index].getName());
		px.text("		Desc: ", false);
		px.text( mArmorInventory[index].getDesc());

	}
}
