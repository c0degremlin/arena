#include "main.hpp"

pxWindow px;
pxSStream ss;

int gNumOfMonsters = 0;

void testing()
{
	cWeapon tmp(const_greatswordDamage, const_greatswordDice, const_greatswordCritical,
	const_greatswordCritMod, const_greatswordValue, "Greatsword", "A menacing and gigantic sword dripping with blood.", "weapon");
	player.addWeapon(tmp);
	player.setName("Faldor"); player.setStrength(15); player.setDexterity(15); player.setConstitution(15); player.setIntelligence(15);
	player.setWisdom(15); player.setCharisma(15);
	player.mCreated = true;

	player.equipWeapon(tmp);

	player.calcHPandMP();

}

int main()
{
	testing();
	bool gIsGameOver = false;

	while (!gIsGameOver)
	{
		px.clrscr();
		px.text("==============================");
		px.text("Main Menu");
		px.text("==============================");
		px.text("Menu Options");
		px.text("\ta. Create Character");
		px.text("\tb. Purchase Equipment");
		px.text("\tc. View Stats");
		px.text("\td. Fight!");
		px.text("\tQ. Quit");
		px.text("==============================");

		px.getS(gString, "Choice: ");
		if (gString == "a" || gString == "A")
			createCharacter();
		else if (gString == "b" || gString == "B")
			purchase();
		else if (gString == "c" || gString == "C")
			showStats();
		else if (gString == "d" || gString == "D")
			fight();
		else if (gString == "q" || gString == "Q")
			gIsGameOver = true;
		else
			px.pause("Invalid entry! Please try again.");

	} // end while
	return 0;
}


void createCharacter()
{
	gString.clear();
	bool isCharacterMade = false;
	if (player.mCreated)
	{
		px.getS(gString, "Character already made. Would you like to make a new one? Y or N");
		if (gString == "n" || gString == "N")
			return;
	}

	while (isCharacterMade == false)
	{
		px.clrscr();
		px.text("==============================");
		px.text("Create Character");
		px.text("==============================");
		px.nl(1);
		px.text("a. Name Character");
		px.text("b. Roll for Stats");
		px.text("R. Return to previous menu");
		px.text("==============================");

		px.getS(gString, "Choice: ");
		if (gString == "a" || gString == "A")
			nameCharacter();
		else if (gString == "b" || gString == "B")
			rollStats();
		else if (gString == "r" || gString == "R")
			isCharacterMade = true;
		else
			px.pause("Invalid choice.");
	}	// end while
	player.mCreated = true;
}	// end function

void nameCharacter()
{
	string tmp;
	bool isCharacterNamed = false;

	if (player.getName() != "")
	{
		px.text("You already are called ", false);
		px.text(player.getName());
		px.text(".");
		px.getS(gString, "Would you like to rename your character? Y or N: ");
		if (gString == "n" || gString == "N")
			return;
	}
	while (isCharacterNamed == false)
	{
		px.clrscr();
		px.getS(gString, "What would you like to name your character: ");

		px.nl(1);
		px.text("You want to be callled ", false);
		px.text(gString, false);
		px.text("?");
		px.nl(1);
		px.getS(tmp, "Y or N: ");
		if (tmp == "y" || tmp == "Y")
		{
			player.setName(gString);
			isCharacterNamed = true;
		}
	}
}

void rollStats()
{
	sint rollCount = 5; 	// max five rolls
	sint tmp = 0;
	bool isStatsRolled = false;
	bool nextStat = false;
	/*
	 int mStrength; // for attack rolls and armor/weapon checks
		int mDexterity; // for hit checks, ranged, dagger, sword and unarmed attacks, dodge...
		int mConstituion; // for health calcs and poison check
		int mIntelligence; // for spell checks and damage, mana calcs, mind control, etc checks
		int mWisdom; // for number of spells possible to learn and AP checks
		int mCharisma; // for mind control, etc checks, better bartering skills, more powerful buffs
	*/
	if (player.mCreated == true)
	{
		gString.clear();
		showStats(false);
		px.getS(gString, "Character already rolled for stats. Would you like to reroll? Y or N: ");
		if (gString == "n" || gString == "N")
			return;
	}



	while (!isStatsRolled)
	{
		while (!nextStat)
		{
			do { 	// Roll 8 or more
				px.rng(tmp);
			} while (tmp < 7 && tmp < 17);
			if (rollCount > 0)
			{
				rollCount--;
				px.clrscr();
				px.text("Rolls left: ", false);
				px.number(rollCount);
				px.text("Roll for strength: ", false);
				px.number(tmp);
				px.getS(gString, "Roll again? Y or N: ");
				if (gString == "n" || gString == "N")
				{
					px.nl(1);
					px.text("You want to have ", false);
					px.number(tmp, false);
					px.getS(gString, " for strength? Y or N: ");
					if (gString == "y" || gString == "Y")
					{
						player.setStrength(tmp);
						tmp = 0;	rollCount = 5;
						nextStat = true;
					} // set player strength if loop
				} // keep strength roll if loop
			}	// roll count if loop
			else
			{
				px.text("Final roll. Strength is ", false);
				px.number(tmp);
				player.setStrength(tmp);
				tmp = 0;	rollCount = 5;
				nextStat = true;
			}
		} // strength while

		nextStat = false;
		while (!nextStat)
		{
			do {	// Roll 8 or more
				px.rng(tmp);
			} while (tmp < 7);
			if (rollCount > 0)
			{
				rollCount--;
				px.clrscr();
				px.text("Rolls left: ", false);
				px.number(rollCount);
				px.text("Roll for dexterity: ", false);
				px.number(tmp);
				px.getS(gString, "Roll again? Y or N: ");
				if (gString == "n" || gString == "N")
				{
					px.nl(1);
					px.text("You want to have ", false);
					px.number(tmp, false);
					px.getS(gString, " for dexterity? Y or N: ");
					if (gString == "y" || gString == "Y")
					{
						player.setDexterity(tmp);
						tmp = 0;	rollCount = 5;
						nextStat = true;
					} // set player dexterity if loop
				} // keep dexterity if loop
			}	// roll count if loop
			else
			{
				px.text("Final roll. Dexterity is ", false);
				px.number(tmp);
				player.setDexterity(tmp);
				tmp = 0;	rollCount = 5;
				nextStat = true;
			}
		} // dexterity while

		nextStat = false;
		while (!nextStat)
		{
			do {     // Roll 8 or more
				px.rng(tmp);
			} while (tmp < 7);
			if (rollCount > 0)
			{
				rollCount--;
				px.clrscr();
				px.text("Rolls left: ", false);
				px.number(rollCount);
				px.text("Roll for constitution: ", false);
				px.number(tmp);
				px.getS(gString, "Roll again? Y or N: ");
				if (gString == "n" || gString == "N")
				{
					px.nl(1);
					px.text("You want to have ", false);
					px.number(tmp, false);
					px.getS(gString, " for constitution? Y or N: ");
					if (gString == "y" || gString == "Y")
					{
						player.setConstitution(tmp);
						tmp = 0;	rollCount = 5;
						nextStat = true;
					} // set player constitution if loop
				} // keep constitution if loop
			}	// roll count if loop
			else
			{
				px.text("Final roll. Constitution is ", false);
				px.number(tmp);
				player.setConstitution(tmp);
				tmp = 0;	rollCount = 5;
				nextStat = true;
			}
		} // constitution while

		nextStat = false;
		while (!nextStat)
		{
			do {     // Roll 8 or more
				px.rng(tmp);
			} while (tmp < 7);
			if (rollCount > 0)
			{
				rollCount--;
				px.clrscr();
				px.text("Rolls left: ", false);
				px.number(rollCount);
				px.text("Roll for intelligence: ", false);
				px.number(tmp);
				px.getS(gString, "Roll again? Y or N: ");
				if (gString == "n" || gString == "N")
				{
					px.nl(1);
					px.text("You want to have ", false);
					px.number(tmp, false);
					px.getS(gString, " for intelligence? Y or N: ");
					if (gString == "y" || gString == "Y")
					{
						player.setIntelligence(tmp);
						tmp = 0;	rollCount = 5;
						nextStat = true;
					} // set player intelligence if loop
				} // keep intelligence if loop
			} // roll count if loop
			else
			{
				px.text("Final roll. Intelligence is ", false);
				px.number(tmp);
				player.setIntelligence(tmp);
				tmp = 0;	rollCount = 5;
				nextStat = true;
			}
		} // intelligence while

		nextStat = false;
		while (!nextStat)
		{
			do {     // Roll 8 or more
				px.rng(tmp);
			} while (tmp < 7);
			if (rollCount > 0)
			{
				rollCount--;
				px.clrscr();
				px.text("Rolls left: ", false);
				px.number(rollCount);
				px.text("Roll for wisdom: ", false);
				px.number(tmp);
				px.getS(gString, "Roll again? Y or N: ");
				if (gString == "n" || gString == "N")
				{
					px.nl(1);
					px.text("You want to have ", false);
					px.number(tmp, false);
					px.getS(gString, " for wisdom? Y or N: ");
					if (gString == "y" || gString == "Y")
					{
						player.setWisdom(tmp);
						tmp = 0; rollCount = 5;
						nextStat = true;
					} // set player wisdom if loop
				} // keep wisdom if loop
			}	// roll count if loop
			else
			{
				px.text("Final roll. Wisdom is ", false);
				px.number(tmp);
				player.setWisdom(tmp);
				tmp = 0;	rollCount = 5;
				nextStat = true;
			}
		} // wisdom while

		nextStat = false;
		while (!nextStat)
		{
			do {     // Roll 8 or more
				px.rng(tmp);
			} while (tmp < 7);
			if (rollCount > 0)
			{
				rollCount--;
				px.clrscr();
				px.text("Rolls left: ", false);
				px.number(rollCount);
				px.text("Roll for charisma: ", false);
				px.number(tmp);
				px.getS(gString, "Roll again? Y or N: ");
				if (gString == "n" || gString == "N")
				{
					px.nl(1);
					px.text("You want to have ", false);
					px.number(tmp, false);
					px.getS(gString, " for charisma? Y or N: ");
					if (gString == "y" || gString == "Y")
					{
						player.setCharisma(tmp);
						tmp = 0;
						nextStat = true;
					} // set player charisma if loop
				} // keep charisma if loop
			}	// roll count if 
			else
			{
				px.text("Final roll. Charisma is ", false);
				px.number(tmp);
				player.setCharisma(tmp);
				tmp = 0;	rollCount = 5;
				nextStat = true;
			}
		} // charisma while

		isStatsRolled = true;

		player.calcHPandMP();

		player.mCreated = true;

	} // end while
}

// Shows player stats
void showStats(bool clrscr)
{
	if (clrscr)
		px.clrscr();

	if (player.mCreated == false)
	{
		px.pause("No character found... ");
		return;
	}

	px.text("Name: ", false);	//		Name: 
	px.text(player.getName());	//		Weapon:		Armor:
	px.text("Weapon: ", false);	//		Level: 		Experience:
	px.text(player.getWeaponName(), false); //	Str: 	Dex:	Con:
	px.text("    Armor: ", false);	//		Int: 	Wis: 	Char:
	px.text(player.getArmorName());	//	Hit points: 65 / 80
	px.text("Level: ", false);		//	Mana points: 35 / 45
	px.shortNumber(player.getLevel(), false); //	Gold: 
	px.text("    Experience: ", false);
	px.shortNumber(player.getExperience());
	px.text("Str: ", false);
	px.shortNumber(player.getStrength(), false);
	px.text("    Dex: ", false);
	px.shortNumber(player.getDexterity(), false);
	px.text("    Con: ", false);
	px.shortNumber(player.getConstitution());
	px.text("Int: ", false);
	px.shortNumber(player.getIntelligence(), false);
	px.text("    Wis: ", false);
	px.shortNumber(player.getWisdom(), false);
	px.text("    Char: ", false);
	px.shortNumber(player.getCharisma());
	px.text("Hit points: ", false);		// Hit points: curr / max
	px.shortNumber(player.getHealth(), false);
	px.text(" / ", false);
	px.shortNumber(player.getMaxHealth());
	px.text("Mana points: ", false);		// Mana points: curr / max
	px.shortNumber(player.getMana(), false);
	px.text(" / ", false);
	px.shortNumber(player.getMaxMana());
	px.text("Gold: ", false);
	px.shortNumber(player.getGold());

	px.pause();
	player.showInventory();
	px.pause();
}

// purchase weapons and armor
void purchase()
{

}

// fight enemies your level or lower
void fight()
{
	cMonster enemy;
	cWeapon cweapon;

	int tmp;

	sint iInitiative, eInitiative;
	sint iAttackRoll, eAttackRoll;
	sint iDamageRoll, eDamageRoll;
	sint iArmorClass, eArmorClass;

	sint roundCount = 1;

	sint eHP, eAC, eAP, eGold, eXP;
	sint eDexMod, iDexMod, eStrMod, iStrMod;

	bool bFightOver = false;

	string eName, eWeaponName;

	px.rng(iInitiative);
	px.rng(eInitiative);

	px.rng(iAttackRoll);
	px.rng(eAttackRoll);

	px.rng(iDamageRoll);
	px.rng(eDamageRoll);

	player.getWeapon(cweapon);

	if (player.mCreated == false) // no player
	{
		px.pause("No character found.");
		return;
	}

	while (bFightOver == false)
	{
		player.level();
		player.setHealth(player.getMaxHealth());
		px.clrscr();
		for (gInt = 1; gInt <= player.getLevel(); gInt++)
		{
			px.number(gInt, false);
			px.text(". Fight level ", false);
			px.number(gInt);
		}

		px.number(gInt,false);
		px.text(". Leave arena");

		px.getS(gString, "Please make a choice: ");

		ss.stringToNumber(gString, tmp);
		
		if(tmp>0)
		tmp = 0;

		// check for a quit selection
		if (tmp == gInt)
		{
			// quit
			px.getS(gString, "Are you sure you want to leave the arena? Y or N ");

			if (gString == "y" || gString == "Y")
				bFightOver = true;
		}

		if (tmp > player.getLevel())
		{
			px.pause("Invalid choice.");
			return;
		}
		
		gInt = tmp;

		if( gInt == player.getLevel() )
			gInt = 300;
		else if( gInt == ( player.getLevel() - 1))
			gInt = 150;
		else if( gInt == ( player.getLevel() -2))
			gInt = 100;
		else if( gInt == ( player.getLevel() - 3))
			gInt = 50;
		else if( gInt == ( player.getLevel() - 4))
			gInt = 25;
		else
			gInt = 5;

		switch (tmp)
		{
		case 1:
			enemy.createEnemy("Orc", "Longsword", 20, 12, 50, 3, 12, gInt);
			break;
		case 2:
			enemy.createEnemy("Orc", "Falchion", 35, 13, 150, 5, 15, gInt);
			break;
		case 3:
			enemy.createEnemy("Orc", "Scimitar", 60, 14, 250, 7, 18, gInt);
			break;
		case 4:
			enemy.createEnemy("Orc", "Broadsword", 85, 15, 350, 9, 21, gInt);
			break;
		case 5:
			enemy.createEnemy("Orc", "Waraxe", 100, 16, 450, 11, 24, gInt);
			break;
		default:
			px.pause("Invalid choice.");
			break;
		}

		eHP = enemy.getHealth();
		eAC = enemy.getArmor();
		eAP = enemy.getAP();
		eGold = enemy.getGold();
		eXP = enemy.getExperience();

		eName = enemy.getName();
		eWeaponName = enemy.getWeaponName();

		gShort = player.getMod(player.getDexterity());
		iInitiative += gShort;

		// attack roll
		iStrMod = (player.getLevel() + player.getMod(player.getStrength()));
		eStrMod = tmp;

		iDexMod = (player.getLevel() + player.getMod(player.getDexterity()));
		eDexMod = tmp;

		iAttackRoll += iStrMod;
		eAttackRoll += eStrMod;

		gShort = eAC;
		gShort += eDexMod;

		eArmorClass = gShort;

		gShort = player.getArmor();
		gShort += iDexMod;

		iArmorClass = gShort;

		rollDamage(iDamageRoll, cweapon, iStrMod);
		px.rng(eDamageRoll, enemy.getAttack());

		px.text("Round ", false);
		px.number(roundCount, false);
		px.text(" (", false);
		px.text(player.getName(), false);
		px.text(" vs. ", false);
		px.text(eName, false);
		px.text(")");

		px.number(player.getHealth(), false);
		px.text("hp remaining");

		// Initiative hit
		// player first
		if (iInitiative >= eInitiative)
		{
			// hit
			if (iAttackRoll >= eArmorClass)
			{
				px.text("> ", false);
				px.text(player.getName(), false);
				px.text(" swings his ", false);
				px.text(player.getWeaponName(), false);
				px.text(" at his opponent ", false);
				px.text(eName, false); if (iAttackRoll >= cweapon.getCritical()) // crit hit
				{
					rollDamage(iDamageRoll, cweapon, iStrMod, false);
					px.text(" and critically hits for ", false);
					px.number(iDamageRoll, false);
					px.text(" damage!");
				}
				else
				{
					px.text(" and hits for ", false);
					px.number(iDamageRoll, false);
					px.text(" damage.");
				}
				eHP -= iDamageRoll;
			}
			// miss
			else
			{
				px.text("> ", false);
				px.text(player.getName(), false);
				px.text(" swings his ", false);
				px.text(player.getWeaponName(), false);
				px.text(" at his opponent ", false);
				px.text(eName, false);
				px.text(" and misses.");
			}
			px.pause();
		}

		// enemy first
		else
		{
			// enemy hit
			if (eAttackRoll >= iArmorClass)
			{
				px.text("> ", false);
				px.text(eName, false);
				px.text(" swings his ", false);
				px.text(eWeaponName, false);
				px.text(" at ", false);
				px.text(player.getName(), false);
				px.text(" and hits for ", false);
				px.number(eDamageRoll, false);
				px.text(" damage.");

				gShort = player.getHealth();
				gShort -= eDamageRoll;
				player.setHealth(gShort);
			}
			// enemy miss
			else
			{
				px.text("> ", false);
				px.text(eName, false);
				px.text(" swings his ", false);
				px.text(eWeaponName, false);
				px.text(" at ", false);
				px.text(player.getName(), false);
				px.text(" and misses.");
			}
			px.pause();
		}


		while (eHP > 0)
		{
			px.clrscr();
			roundCount++;

			px.rng(iAttackRoll);
			px.rng(eAttackRoll);

			iAttackRoll += iStrMod;
			eAttackRoll += eStrMod;

			rollDamage(iDamageRoll, cweapon, iStrMod);
			px.rng(eDamageRoll, enemy.getAttack());

			// Round # (Player vs. enemy)
			// hp remaining: #
			// > Player swings his Weapon at enemy and misses
			// > Enemy swings his eWeapon at player for # damage

			px.text("Round ", false);
			px.number(roundCount, false);
			px.text(" ",false);
			px.text(player.getName(), false);
			px.text(" vs. ", false);
			px.text(eName, false);
			px.text(")");

			px.number(player.getHealth(), false);
			px.text("hp remaining");

			// player hit
			if (iAttackRoll >= eArmorClass)
			{
				px.text("> ", false);
				px.text(player.getName(), false);
				px.text(" swings his ", false);
				px.text(player.getWeaponName(), false);
				px.text(" at his opponent ", false);
				px.text(eName, false);
				if (iAttackRoll >= cweapon.getCritical()) // crit hit
				{
					rollDamage(iDamageRoll, cweapon, iStrMod,false);
					px.text(" and critically hits for ", false);
					px.number(iDamageRoll, false);
					px.text(" damage!");
				}
				else
				{
					px.text(" and hits for ", false);
					px.number(iDamageRoll, false);
					px.text(" damage.");
				}
				eHP -= iDamageRoll;
			}
			// player miss
			else
			{
				px.text("> ", false);
				px.text(player.getName(), false);
				px.text(" swings his ", false);
				px.text(player.getWeaponName(), false);
				px.text(" at his opponent ", false);
				px.text(eName, false);
				px.text(" and misses.");
			}

			// enemy hit
			if (eAttackRoll >= iArmorClass)
			{
				px.text("> ", false);
				px.text(eName, false);
				px.text(" swings his ", false);
				px.text(eWeaponName, false);
				px.text(" at ", false);
				px.text(player.getName(), false);
				px.text(" and hits for ", false);
				px.number(eDamageRoll, false);
				px.text(" damage.");

				gShort = player.getHealth();
				gShort -= eDamageRoll;
				player.setHealth(gShort);
			}
			// enemy miss
			else
			{
				px.text("> ", false);
				px.text(eName, false);
				px.text(" swings his ", false);
				px.text(eWeaponName, false);
				px.text(" at ", false);
				px.text(player.getName(), false);
				px.text(" and misses.");
			}

			px.pause();
		}

		gShort = player.getGold();
		gShort += eGold;
		player.setGold(gShort);
		
		gShort = player.getExperience();
		gShort += eXP;
		player.setExperience(gShort);

		bFightOver = true;
	} // fight over while loop
}

void rollDamage(sint &in, cWeapon weapon, sint strmod, bool erase)
{
	if(erase)
		in = 0;

	for (int i = 0; i < weapon.getDice(); i++)
	{
		px.rng(gInt, weapon.getDamage());
		in += gInt;
	}
	in += strmod;
}
