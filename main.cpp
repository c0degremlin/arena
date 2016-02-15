#include "main.hpp"

pxWindow px;
pxSStream ss;

int gNumOfMonsters = 0;

void testing()
{
	cWeapon tmp(const_unarmedDamage, const_unarmedDice, const_unarmedCritical, const_unarmedCritMod, const_unarmedValue, "Bare knuckles", "Bare knuckle bashing", "weapon");
	player.addWeapon(tmp);
	player.setName("test"); player.setStrength(15); player.setDexterity(15); player.setConstitution(15); player.setIntelligence(15);
	player.setWisdom(15); player.setCharisma(15);
	player.mCreated = true;

	gShort = player.getConstitution();
	gShort *= const_hpScaling;

	player.setHealth(gShort);	player.setMaxHealth(gShort);

	gShort = 0; gShort = player.getIntelligence();
	gShort *= const_manaScaling;

	player.setMana(gShort);	player.setMaxMana(gShort);
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
		else if (gString == "d" || gString == "D") {}
		// FIGHT!
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

		player.calcHPandMP( player );

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
	px.text("\tArmor: ", false);	//		Int: 	Wis: 	Char:
	px.text(player.getArmorName());	//	Hit points: 65 / 80
	px.text("Level: ", false);		//	Mana points: 35 / 45
	px.shortNumber(player.getLevel(), false); //	Gold: 
	px.text("\tExperience: ", false);
	px.shortNumber(player.getExperience());
	px.text("Str: ", false);
	px.shortNumber(player.getStrength(), false);
	px.text("\tDex: ", false);
	px.shortNumber(player.getDexterity(), false);
	px.text("\tCon: ", false);
	px.shortNumber(player.getConstitution());
	px.text("Int: ", false);
	px.shortNumber(player.getIntelligence(), false);
	px.text("\tWis: ", false);
	px.shortNumber(player.getWisdom(), false);
	px.text("\tChar: ", false);
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
