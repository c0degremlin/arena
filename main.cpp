#include "main.hpp"

pxWindow px;
pxSStream ss;

int gNumOfMonsters = 0;

void testing()
{
	// Make a player, set him up with a dagger for a mock inventory
	cWeapon tmp(const_daggerDamage, const_daggerDice, const_daggerCritical,
		const_daggerCritMod, const_daggerValue, const_daggerName, const_daggerDesc, "weapon");
	player.addWeapon(tmp);
	player.setName("Faldor"); player.setStrength(15); player.setDexterity(15); player.setConstitution(15); player.setIntelligence(15);
	player.setWisdom(15); player.setCharisma(15);
	player.mCreated = true; player.setLevel(2);

	player.calcHPandMP();

	// messing around with the inventory functions to make sure that they work properly.

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
		px.text("\te. Equip Items");
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
		else if (gString == "e" || gString == "E")
			equip();
		else if (gString == "q" || gString == "Q")
			gIsGameOver = true;
		else
			px.pause("Invalid choice.");

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
		else if (gString == "r" || gString == "R") // maybe do a double check here in the final version
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

	if (player.mCreated)
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


/*
//  Bugs:
		

int mStrength; // for attack rolls and armor/weapon checks
int mDexterity; // for hit checks, ranged, dagger, sword and unarmed attacks, dodge...
int mConstituion; // for health calcs and poison check
int mIntelligence; // for spell checks and damage, mana calcs, mind control, etc checks
int mWisdom; // for number of spells possible to learn and AP checks
int mCharisma; // for mind control, etc checks, better bartering skills, more powerful buffs
*/
void rollStats()
{
	sint rollCount = 5; 	// max five rolls
	sint tmp = 0;
	bool isStatsRolled = false;
	bool nextStat = false;
	
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
			// Roll 8-17
			px.rng(tmp, 8, 17);
			
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
				px.pause();
			}
		} // strength while

		nextStat = false;
		while (!nextStat)
		{
			// Roll 8-17
			px.rng(tmp, 8, 17);
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
				px.pause();
			}
		} // dexterity while

		nextStat = false;
		while (!nextStat)
		{
			// Roll 8-17
			px.rng(tmp, 8, 17);
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
				px.pause();
			}
		} // constitution while

		nextStat = false;
		while (!nextStat)
		{
			// Roll 8-17
			px.rng(tmp, 8, 17);
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
				px.pause();
			}
		} // intelligence while

		nextStat = false;
		while (!nextStat)
		{
			// Roll 8-17
			px.rng(tmp, 8, 17);
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
				px.pause();
			}
		} // wisdom while

		nextStat = false;
		while (!nextStat)
		{
			// Roll 8-17
			px.rng(tmp, 8, 17);
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
				px.pause();
			}
		} // charisma while

		isStatsRolled = true;

		player.calcHPandMP();

		player.mCreated = true;

	} // end while
}

// Shows player stats
/*

//	Todo:
//			Adjust formatting	
//  Bugs:


*/
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
/*
//	Todo:
					Finish the armor area of the switch statement
//  Bugs:
			

*/
void purchase()
{
	bool bPurchaseDone = false;
	bool bWeaponDone = false;
	bool bArmorDone = false;

	cWeapon cweapon;
	cArmor carmor;

	int iCount = 1;
	sint iValue = 0;

	while (!bPurchaseDone)
	{
		px.clrscr();
		px.text("==============================");
		px.text("Purchase Equipment");
		px.text("==============================");
		px.text("Menu Options");
		px.text("a. Purchase armor");
		px.text("b. Purchase weapon");
		px.text("r. Return to previous menu");
		px.text("==============================");

		px.getS(gString, "Choice: ");

		if (gString == "a" || gString == "A")	// Armor
		{
			while(!bArmorDone)
			{
				iCount = 1;
				
				// Display the armor choices
				px.clrscr();
				px.text("Name | AC | Dex Mod | Value");
				px.nl();
				/*
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
				*/
				showArmor(const_paddedName, const_paddedAC, const_paddedDex, const_paddedValue, iCount);
				showArmor(const_leatherName, const_leatherAC, const_leatherDex, const_leatherValue, iCount);
				showArmor(const_hideName, const_hideAC, const_hideDex, const_hideValue, iCount);
				showArmor(const_studdedName, const_studdedAC, const_studdedDex, const_studdedValue, iCount);
				showArmor(const_scaleName, const_scaleAC, const_scaleDex, const_scaleValue, iCount);
				showArmor(const_chainshirtName, const_chainshirtAC, const_chainshirtDex, const_chainshirtValue, iCount);
				showArmor(const_chainmailName, const_chainmailAC, const_chainmailDex, const_chainmailValue, iCount);
				showArmor(const_breastplateName, const_breastplateAC, const_breastplateDex, const_breastplateValue, iCount);
				showArmor(const_splintName, const_splintAC, const_splintDex, const_splintValue, iCount);
				showArmor(const_bandedName, const_bandedAC, const_bandedDex, const_bandedValue, iCount);
				showArmor(const_halfplateName, const_halfplateAC, const_halfplateDex, const_halfplateValue, iCount);
				showArmor(const_fullplateName, const_fullplateAC, const_fullplateDex, const_fullplateValue, iCount);
				
				// end Armor choices
				px.number(iCount, false);
				px.text(". Return to previous menu");

				px.getS(gString, "Choice: ");
				px.clrscr();
				ss.stringToNumber(gString, gInt);
				
				// Done
				if (gInt == iCount) // return to purchase weapon menu
				{
					bArmorDone = true;
					break;
				}
				
			}
		}
		else if (gString == "b" || gString == "B")	// Weapon
		{
			while (!bWeaponDone)
			{
				iCount = 1;

				// Display the weapon choices

				px.clrscr();
				
				px.text("Name | Damage | Critical | Crit Mod | \tValue ");
				px.nl();
				showWeapon(const_daggerName, const_daggerDice, const_daggerDamage, const_daggerCritical, const_daggerCritMod, const_daggerValue, iCount);
				showWeapon(const_maceName, const_maceDice, const_maceDamage, const_maceCritical, const_maceCritMod, const_maceValue, iCount);
				showWeapon(const_handaxeName, const_handaxeDice, const_handaxeDamage, const_handaxeCritical, const_handaxeCritMod, const_handaxeValue, iCount);
				showWeapon(const_scimitarName, const_scimitarDice, const_scimitarDamage, const_scimitarCritical, const_scimitarCritMod, const_scimitarValue, iCount);
				showWeapon(const_shortswordName, const_shortswordDice, const_shortswordDamage, const_shortswordCritical, const_shortswordCritMod, const_shortswordValue, iCount);
				showWeapon(const_morningstarName, const_morningstarDice, const_morningstarDamage, const_morningstarCritical, const_morningstarCritMod, const_morningstarValue, iCount);
				showWeapon(const_spearName, const_spearDice, const_spearDamage, const_spearCritical, const_spearCritMod, const_spearValue, iCount);
				showWeapon(const_longswordName, const_longswordDice, const_longswordDamage, const_longswordCritical, const_longswordCritMod, const_longswordValue, iCount);
				showWeapon(const_greatclubName, const_greatclubDice, const_greatclubDamage, const_greatclubCritical, const_greatclubCritMod, const_greatclubValue, iCount);
				showWeapon(const_halberdName, const_halberdDice, const_halberdDamage, const_halberdCritical, const_halberdCritMod, const_halberdValue, iCount);
				showWeapon(const_bastardswordName, const_bastardswordDice, const_bastardswordDamage, const_bastardswordCritical, const_bastardswordCritMod, const_bastardswordValue, iCount);
				showWeapon(const_greataxeName, const_greataxeDice, const_greataxeDamage, const_greataxeCritical, const_greataxeCritMod, const_greataxeValue, iCount);
				showWeapon(const_greatswordName, const_greatswordDice, const_greatswordDamage, const_greatswordCritical, const_greatswordCritMod, const_greatswordValue, iCount);
				
				// End weapon choices

				px.number(iCount, false);
				px.text(". Return to previous menu");

				px.getS(gString, "Choice: ");


				px.clrscr();


				ss.stringToNumber(gString, gInt);
				
				// Done
				if (gInt == iCount) // return to purchase weapon menu
				{
					bWeaponDone = true;
					break;
				}

				switch (gInt)
				{
				case 1:
					iValue = const_daggerValue;
					if (player.getGold() >= iValue)
					{
						px.text("Are you sure you want to buy this Dagger for ", false);
						px.number(iValue, false);
						px.getS(gString, "gp? Y or N ");
						if (gString == "y" || gString == "Y")
						{
							// Get, deduct and set gold
							gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
							cweapon.setValue(const_daggerValue);	cweapon.setCritical(const_daggerCritical);	cweapon.setCritMod(const_daggerCritMod);
							cweapon.setDamage(const_daggerDamage);	cweapon.setDice(const_daggerDice);
							player.addWeapon(cweapon);

							bWeaponDone = true;	break;
						}
						else	break;
					}
					else
						px.pause("You don't have enough gold for that.");
				break;
				case 2:
					iValue = const_maceValue;
					if (player.getGold() >= iValue)
					{
						px.text("Are you sure you want to buy this Mace for ", false);
						px.number(iValue, false);
						px.getS(gString, "gp? Y or N ");
						if (gString == "y" || gString == "Y")
						{
							// Get, deduct and set gold
							gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
							cweapon.setValue(const_maceValue);	cweapon.setCritical(const_maceCritical);	cweapon.setCritMod(const_maceCritMod);
							cweapon.setDamage(const_maceDamage);	cweapon.setDice(const_maceDice);
							player.addWeapon(cweapon);

							bWeaponDone = true;	break;
						}
						else	break;
					}
					else
						px.pause("You don't have enough gold for that.");
				break;
				case 3:
					iValue = const_handaxeValue;
					if (player.getGold() >= iValue)
					{
						px.text("Are you sure you want to buy this Handaxe for ", false);
						px.number(iValue, false);
						px.getS(gString, "gp? Y or N ");
						if (gString == "y" || gString == "Y")
						{
							// Get, deduct and set gold
							gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
							cweapon.setValue(const_handaxeValue);	cweapon.setCritical(const_handaxeCritical);	cweapon.setCritMod(const_handaxeCritMod);
							cweapon.setDamage(const_handaxeDamage);	cweapon.setDice(const_handaxeDice);
							player.addWeapon(cweapon);

							bWeaponDone = true;	break;
						}
						else	break;
					}
					else
						px.pause("You don't have enough gold for that.");
				break;
				case 4:
					iValue = const_shortswordValue;
					if (player.getGold() >= iValue)
					{
						px.text("Are you sure you want to buy this Shortsword for ", false);
						px.number(iValue, false);
						px.getS(gString, "gp? Y or N ");
						if (gString == "y" || gString == "Y")
						{
							// Get, deduct and set gold
							gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
							cweapon.setValue(const_shortswordValue);	cweapon.setCritical(const_shortswordCritical);	cweapon.setCritMod(const_shortswordCritMod);
							cweapon.setDamage(const_shortswordDamage);	cweapon.setDice(const_shortswordDice);
							player.addWeapon(cweapon);

							bWeaponDone = true;	break;
						}
						else	break;
					}
					else
						px.pause("You don't have enough gold for that.");
				break;
				case 5:
					iValue = const_scimitarValue;
					if (player.getGold() >= iValue)
					{
						px.text("Are you sure you want to buy this Scimitar for ", false);
						px.number(iValue, false);
						px.getS(gString, "gp? Y or N ");
						if (gString == "y" || gString == "Y")
						{
							// Get, deduct and set gold
							gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
							cweapon.setValue(iValue);	cweapon.setCritical(const_scimitarCritical);	cweapon.setCritMod(const_scimitarCritMod);
							cweapon.setDamage(const_scimitarDamage);	cweapon.setDice(const_scimitarDice);
							player.addWeapon(cweapon);

							bWeaponDone = true;	break;
						}
						else	break;
					}
					else
						px.pause("You don't have enough gold for that.");
				break;
				case 6:
					iValue = const_morningstarValue;
					if (player.getGold() >= iValue)
					{
						px.text("Are you sure you want to buy this Morningstar for ", false);
						px.number(iValue, false);
						px.getS(gString, "gp? Y or N ");
						if (gString == "y" || gString == "Y")
						{
							// Get, deduct and set gold
							gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
							cweapon.setValue(iValue);	cweapon.setCritical(const_morningstarCritical);	cweapon.setCritMod(const_morningstarCritMod);
							cweapon.setDamage(const_morningstarDamage);	cweapon.setDice(const_morningstarDice);
							player.addWeapon(cweapon);

							bWeaponDone = true;	break;
						}
						else	break;
					}
					else
						px.pause("You don't have enough gold for that.");
				break;
				case 7:
					iValue = const_spearValue;
					if (player.getGold() >= iValue)
					{
						px.text("Are you sure you want to buy this Spear for ", false);
						px.number(iValue, false);
						px.getS(gString, "gp? Y or N ");
						if (gString == "y" || gString == "Y")
						{
							// Get, deduct and set gold
							gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
							cweapon.setValue(iValue);	cweapon.setCritical(const_spearCritical);	cweapon.setCritMod(const_spearCritMod);
							cweapon.setDamage(const_spearDamage);	cweapon.setDice(const_spearDice);
							player.addWeapon(cweapon);

							bWeaponDone = true;	break;
						}
						else	break;
					}
					else
						px.pause("You don't have enough gold for that.");
				break;
				case 8:
					iValue = const_longswordValue;
					if (player.getGold() >= iValue)
					{
						px.text("Are you sure you want to buy this Longsword for ", false);
						px.number(iValue, false);
						px.getS(gString, "gp? Y or N ");
						if (gString == "y" || gString == "Y")
						{
							// Get, deduct and set gold
							gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
							cweapon.setValue(iValue);	cweapon.setCritical(const_longswordCritical);	cweapon.setCritMod(const_longswordCritMod);
							cweapon.setDamage(const_longswordDamage);	cweapon.setDice(const_longswordDice);
							player.addWeapon(cweapon);

							bWeaponDone = true;	break;
						}
						else	break;
					}
					else
						px.pause("You don't have enough gold for that.");
				break;
				case 9:
					iValue = const_greatclubValue;
					if (player.getGold() >= iValue)
					{
						px.text("Are you sure you want to buy this Greatclub for ", false);
						px.number(iValue, false);
						px.getS(gString, "gp? Y or N ");
						if (gString == "y" || gString == "Y")
						{
							// Get, deduct and set gold
							gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
							cweapon.setValue(iValue);	cweapon.setCritical(const_greatclubCritical);	cweapon.setCritMod(const_greatclubCritMod);
							cweapon.setDamage(const_greatclubDamage);	cweapon.setDice(const_greatclubDice);
							player.addWeapon(cweapon);

							bWeaponDone = true;	break;
						}
						else	break;
					}
					else
						px.pause("You don't have enough gold for that.");
				break;
				case 10:
					iValue = const_halberdValue;
					if (player.getGold() >= iValue)
					{
						px.text("Are you sure you want to buy this Halberd for ", false);
						px.number(iValue, false);
						px.getS(gString, "gp? Y or N ");
						if (gString == "y" || gString == "Y")
						{
							// Get, deduct and set gold
							gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
							cweapon.setValue(iValue);	cweapon.setCritical(const_halberdCritical);	cweapon.setCritMod(const_halberdCritMod);
							cweapon.setDamage(const_halberdDamage);	cweapon.setDice(const_halberdDice);
							player.addWeapon(cweapon);
							
							bWeaponDone = true;
							break;
						}
						else
							break;
					}
					else
						px.pause("You don't have enough gold for that.");
				break;
				case 11:
					iValue = const_bastardswordValue;
					if (player.getGold() >= iValue)
					{
						px.text("Are you sure you want to buy this Bastard Sword for ", false);
						px.number(iValue, false);
						px.getS(gString, "gp? Y or N ");
						if (gString == "y" || gString == "Y")
						{
							// Get, deduct and set gold
							gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);cweapon.setValue(iValue);	cweapon.setCritical(const_bastardswordCritical);	cweapon.setCritMod(const_bastardswordCritMod);
							cweapon.setDamage(const_bastardswordDamage);	cweapon.setDice(const_bastardswordDice);
							player.addWeapon(cweapon);

							bWeaponDone = true;	break;
						}
						else	break;
					}
					else
						px.pause("You don't have enough gold for that.");
				break;
				case 12:
					iValue = const_greataxeValue;
					if (player.getGold() >= iValue)
					{
						px.text("Are you sure you want to buy this Greataxe for ", false);
						px.number(iValue, false);
						px.getS(gString, "gp? Y or N ");
						if (gString == "y" || gString == "Y")
						{
							// Get, deduct and set gold
							gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
							cweapon.setValue(iValue);	cweapon.setCritical(const_greataxeCritical);	cweapon.setCritMod(const_greataxeCritMod);
							cweapon.setDamage(const_greataxeDamage);	cweapon.setDice(const_greataxeDice);
							player.addWeapon(cweapon);

							bWeaponDone = true;	break;
						}
						else	break;
					}
					else
						px.pause("You don't have enough gold for that.");
				break;
				case 13:
					iValue = const_greatswordValue;
					if (player.getGold() >= iValue)
					{
						px.text("Are you sure you want to buy this Greatsword for ", false);
						px.number(iValue, false);
						px.getS(gString, "gp? Y or N ");
						if (gString == "y" || gString == "Y")
						{
							// Get, deduct and set gold
							gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
							cweapon.setValue(iValue);	cweapon.setCritical(const_greatswordCritical);	cweapon.setCritMod(const_greatswordCritMod);
							cweapon.setDamage(const_greatswordDamage);	cweapon.setDice(const_greatswordDice);
							player.addWeapon(cweapon);

							bWeaponDone = true;	break;
						}
						else	break;
					}
					else
						px.pause("You don't have enough gold for that.");
				break;
				default:
					px.pause("Invalid choice.");
					break;
				}
			}
			bWeaponDone = false; // so access is still possible
		}
		else if (gString == "r" || gString == "R")	// Return
			bPurchaseDone = true;
		else
			px.pause("Invalid choice.");
	}
}

// fight enemies your level or lower

/*

//	Todo:
			Go thru the code and remake it proper
//  Bugs:

*/
void fight()
{
	cMonster enemy;
	cWeapon cweapon;

	int tmp;
	sint xpCalc;
	sint iArmorClass;

	sint iInitiative, eInitiative;
	sint iAttackRoll, eAttackRoll;
	sint iDamageRoll, eDamageRoll;

	sint roundCount = 1;

	sint eHP, eAC, eAP, eGold, eXP;
	sint iDexMod, iStrMod;

	bool bFightOver = false;
	bool bQuit = false;

	// Setup static stuff
	iStrMod = (player.getLevel() + player.getMod(player.getStrength()));
	iDexMod = (player.getLevel() + player.getMod(player.getDexterity()));


	// player AC
	gShort = player.getArmor();
	gShort += iDexMod;
	iArmorClass = gShort;



	string eName, eWeaponName;

	player.getWeapon(cweapon);

	if (player.mCreated == false) // no player
	{
		px.pause("No character found.");
		return;
	}

	while (!bQuit)
	{
		px.clrscr();
		
		for (gInt = 1; gInt <= player.getLevel(); gInt++)
		{
			px.number(gInt, false);
			px.text(". Fight level ", false);
			px.number(gInt);
		}

		px.number(gInt, false);
		px.text(". Leave arena");

		px.getS(gString, "Please make a choice: ");

		ss.stringToNumber(gString, tmp);

		bFightOver = false; // make sure you can fight


		// check for a quit selection
		if (tmp == gInt)
		{
			// quit
			px.getS(gString, "Are you sure you want to leave the arena? Y or N ");

			if (gString == "y" || gString == "Y")
				break;
		}

		while (!bFightOver)
		{

			// add one to exit
			if (tmp > (player.getLevel() + 1))
			{
				px.pause("Invalid choice.");
				break;
			}

			xpCalc = tmp;
			// Xp downgrade
			if (xpCalc == player.getLevel())
				xpCalc = 150;
			else if (xpCalc == (player.getLevel() - 1))
				xpCalc = 100;
			else if (xpCalc == (player.getLevel() - 2))
				xpCalc = 75;
			else if (xpCalc == (player.getLevel() - 3))
				xpCalc = 50;
			else if (xpCalc == (player.getLevel() - 4))
				xpCalc = 25;
			else
				xpCalc = 5;

			// Gold downgrade
			gInt = tmp;
			if (gInt == player.getLevel())
				gInt = 300;
			else if (gInt == (player.getLevel() - 1))
				gInt = 150;
			else if (gInt == (player.getLevel() - 2))
				gInt = 100;
			else if (gInt == (player.getLevel() - 3))
				gInt = 50;
			else if (gInt == (player.getLevel() - 4))
				gInt = 25;
			else
				gInt = 5;

			// extra random dont forget to change me when you add more enemies.
			for(int i = 0; i < 25; i++)
				px.rng(tmp, 5, 5);
			switch (tmp)
			{
			case 1:
				enemy.createEnemy("Orc", "Longsword", 20, 12, xpCalc, 3, 12, gInt);
				break;
			case 2:
				enemy.createEnemy("Orc", "Falchion", 35, 13, xpCalc, 5, 15, gInt);
				break;
			case 3:
				enemy.createEnemy("Orc", "Scimitar", 60, 14, xpCalc, 7, 18, gInt);
				break;
			case 4:
				enemy.createEnemy("Orc", "Broadsword", 85, 15, xpCalc, 9, 21, gInt);
				break;
			case 5:
				enemy.createEnemy("Orc", "Waraxe", 100, 16, xpCalc, 11, 24, gInt);
				break;
			default:
				px.pause("Invalid choice.");
				bFightOver = true;
				break;
			}

			if (bFightOver)
				break;

			eHP = enemy.getHealth();
			eAC = enemy.getArmor();
			eAP = enemy.getAP();
			eGold = enemy.getGold();
			eXP = enemy.getExperience();

			eName = enemy.getName();
			eWeaponName = enemy.getWeaponName();


			px.rng(iInitiative);
			px.rng(eInitiative);

			px.rng(iAttackRoll);
			px.rng(eAttackRoll);

			px.rng(iDamageRoll);
			px.rng(eDamageRoll);


			// add dex mod to player initiative roll
			iInitiative += iDexMod;

			// attack roll
			iAttackRoll += iStrMod;

			
			rollDamage(iDamageRoll, cweapon, iStrMod);
			px.rng(eDamageRoll, enemy.getAttack(), enemy.getAttack());

			px.clrscr();
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
				if (iAttackRoll >= eAC)
				{
					px.text("> ", false);
					px.text(player.getName(), false);
					px.text(" swings his ", false);
					px.text(player.getWeaponName(), false);
					px.text(" at his opponent ", false);
					px.text(eName, false); 
					
					if (iAttackRoll >= cweapon.getCritical()) // crit hit
					{
						for( int i = 0; i < cweapon.getCritMod(); i++)
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
				px.sleep(1250);
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
				px.sleep(1250);
			}

			// Rest of the battle after the first round until someone dies.

			while (eHP > 0)
			{
				if (player.getHealth() <= 0)
				{
					player.mCreated = false;
					player.setExperience(0);
					player.setGold(0);
					break;
				}
				px.clrscr();
				roundCount++;

				px.rng(iAttackRoll);
				px.rng(eAttackRoll);

				iAttackRoll += iStrMod;

				rollDamage(iDamageRoll, cweapon, iStrMod);
				px.rng(eDamageRoll, enemy.getAttack(), enemy.getAttack());

				// Round # (Player vs. enemy)
				// hp remaining: #
				// > Player swings his Weapon at enemy and misses
				// > Enemy swings his eWeapon at player for # damage

				px.text("Round ", false);
				px.number(roundCount, false);
				px.text(" (", false);
				px.text(player.getName(), false);
				px.text(" vs. ", false);
				px.text(eName, false);
				px.text(")");

				px.number(player.getHealth(), false);
				px.text("hp remaining");

				// player hit
				if (iAttackRoll >= eAC)
				{
					px.text("> ", false);
					px.text(player.getName(), false);
					px.text(" swings his ", false);
					px.text(player.getWeaponName(), false);
					px.text(" at his opponent ", false);
					px.text(eName, false);
					if (iAttackRoll >= cweapon.getCritical()) // crit hit
					{
						iDamageRoll = 0;
						for (int i = 0; i < cweapon.getCritMod(); i++)
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

				if (eHP <= 0) // enemy dead
					break;

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

				px.sleep(1250);
			}

			if (eHP <= 0) // enemy died
			{
				gShort = player.getGold();
				gShort += eGold;
				player.setGold(gShort);

				gShort = player.getExperience();
				gShort += eXP;
				player.setExperience(gShort);

				px.text(eName, false);
				px.text(" has lost. You have gained ", false);
				px.number(eGold, false);
				px.text(" gold and ", false);
				px.number(eXP, false);
				px.text(" experience.");
				px.pause();
				bFightOver = true;
				bQuit = true;
			}
			else // player died
				px.pause("You have died. Please bring back more bodies!");
			bFightOver = true;

		} // fight over while loop
	}	// bQuit while loop end

	if (player.getHealth() > 0) // Player is victorious!
	{
		// reset player health
		player.setHealth(player.getMaxHealth());
		player.level();
	}
}

// show inventory and equipped weapons
void equip()
{

}

void rollDamage(sint &in, cWeapon weapon, sint strmod, bool erase)
{
	if (erase)
		in = 0;

	for (int i = 0; i < weapon.getDice(); i++)
	{
		px.rng(gInt, weapon.getDamage(), weapon.getDamage());
		in += gInt;
	}
	in += strmod;
}

// Weapon name, weapon dice count, weapon damage dice, critical range, x2,x3 or x4, gp value and running count for display purposes
void showWeapon(string sName, int iDice, int iDamage, int iCrit, int iCritMod, int iValue, int &iCount)
{
	px.number(iCount, false);
	px.text(". ", false);
	px.text(sName, false);
	px.text(" ", false); // Add a space
	px.number(iDice, false);
	px.text("d", false);
	px.number(iDamage, false);
	px.text(" (", false);
	px.number(iCrit, false);
	px.text("/x", false);
	px.number(iCritMod, false);


	if (sName.length() <= 8 && iCount < 10)
		px.text(")\t\t\t", false); // triple for wicked short ones
	else if (sName.length() <= 8 && iCount >= 10)
		px.text(")\t\t", false); // account for double digits and short ones
	else if (sName.length() < 12 && sName.length() > 8 )
		px.text(")\t\t", false); // double tab short names
	else
		px.text(")\t\t", false); // to make stuff even
	px.number(iValue, false);
	px.text("gp");

	iCount++;
}

// Armor display when buying
// Armor name, AC, Dex Max, Value, running count for display purposes
void showArmor(string sName, int iAC, int iDex, int iValue, int &iCount)
{
	px.number(iCount, false);
	px.text(". ",false);
	px.text(sName, false);
	px.text(" ",false);	// Add a space
	px.text("AC ",false);
	px.number(iAC, false);
	px.text(" Dex Max ", false);
	px.number(iDex, false);
	px.text(" Value ", false);
	px.number(iValue, false);
	px.text("gp");
	
	iCount++;
}

// use to add weapons in batches
/*
	
	sint mDamage;
	sint mDice;
	sint mCritical;
	sint mCritMod;

	bool isEquipped; // Do i have this readied	
	string mItemName; // Basic name for display
	string mItemDesc; // When asked for details this is the output
	string mItemType; // Weapon, Armor, Potion

	sint mValue; // How much gold is this worth
*/
cWeapon addWeapon(string sName, string sDesc, int iDice, int iDamage, int iCrit, int iCritMod, int iValue)
{
	cWeapon tmp;	tmp.clear();
	tmp.setName(sName); tmp.setDesc(sDesc);	tmp.setDice(iDice);	tmp.setDamage(iDamage); tmp.setCritical(iCrit); tmp.setCritMod(iCritMod); tmp.setValue(iValue);
	tmp.setType(); // weapon default
	tmp.setEquipped(false);
	return tmp;
}

// use to add armor in batches
/*
	sint mDexMod;
	sint mArmorClass;
	bool isEquipped; // Am i wearing this?

	string mItemName; // Basic name for display
	string mItemDesc; // When asked for details this is the output
	string mItemType; // Weapon, Armor, Potion

	sint mValue; // How much gold is this worth
*/
cArmor addArmor(string sName, string sDesc, int iAC, int iDex, int iValue)
{
	cArmor tmp;		tmp.clear();
	tmp.setName(sName);	tmp.setDesc(sDesc);	tmp.setAC(iAC);	tmp.setMaxDex(iDex);	tmp.setValue(iValue);
	tmp.setType();	// armor default
	tmp.setEquipped(false);
	return tmp;
}