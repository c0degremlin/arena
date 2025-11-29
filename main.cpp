#include "main.hpp"
#include "armor.hpp"
#include "player.hpp"
#include "weapon.hpp"

pxWindow px;
pxSStream ss;

cPlayer player;

void testing()
{
	// Make a player, set him up with a dagger for a mock inventory
	cWeapon tmp(const_daggerDamage, const_daggerDice, const_daggerCritical,
		const_daggerCritMod, const_daggerValue, const_daggerName, const_daggerDesc, "weapon");
	player.addWeapon(tmp);
	player.equipWeapon();
	player.setName("Faldor"); 
	player.mCreated = true; player.setLevel(3);
	player.setGold(5000);	// extra gold for purchases
	player.setArmorClass(const_baseAC);

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
		px.text("R. Return to previous menu");
		px.text("==============================");

		px.getS(gString, "Choice: ");
		if (gString == "a" || gString == "A")
			nameCharacter();
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
	px.text("Hit points: ", false);		// Hit points: curr / max
	px.shortNumber(player.getHealth(), false);
	px.text(" / ", false);
	px.shortNumber(player.getMaxHealth());
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
		px.text("w. Purchase weapon");
		px.text("R. Return to previous menu");
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
				
				showArmor(const_paddedName, const_paddedAC, const_paddedValue, iCount);
				showArmor(const_leatherName, const_leatherAC, const_leatherValue, iCount);
				showArmor(const_hideName, const_hideAC, const_hideValue, iCount);
				showArmor(const_studdedName, const_studdedAC, const_studdedValue, iCount);
				showArmor(const_scaleName, const_scaleAC, const_scaleValue, iCount);
				showArmor(const_chainshirtName, const_chainshirtAC, const_chainshirtValue, iCount);
				showArmor(const_chainmailName, const_chainmailAC, const_chainmailValue, iCount);
				showArmor(const_breastplateName, const_breastplateAC, const_breastplateValue, iCount);
				showArmor(const_splintName, const_splintAC, const_splintValue, iCount);
				showArmor(const_bandedName, const_bandedAC, const_bandedValue, iCount);
				showArmor(const_halfplateName, const_halfplateAC, const_halfplateValue, iCount);
				showArmor(const_fullplateName, const_fullplateAC, const_fullplateValue, iCount);
				
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
				switch(gInt)
				{
					// 		showArmor(const_paddedName, const_paddedAC, const_paddedDex, const_paddedValue, iCount);
					case 1:
						iValue = const_paddedValue;
						if (player.getGold() >= iValue)
						{
							px.text("Are you sure you want to buy this Padded Armor for ", false);
							px.number(iValue, false);
							px.getS(gString, "gp? Y or N ");
							if (gString == "y" || gString == "Y")
							{
								// Get, deduct and set gold
								gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
								carmor.setName(const_paddedName); carmor.setDesc(const_paddedDesc);
								carmor.setAC(const_paddedAC);	carmor.setValue(const_paddedValue);
								carmor.setType();

								player.addArmor(carmor, player.getArmorCount());
								player.equipArmor(player.getArmorCount());
	
								bArmorDone = true;	break;
							}
							else	break;
						}
						else
							px.pause("You don't have enough gold for that.");
					break;
					//		showArmor(const_leatherName, const_leatherAC, const_leatherDex, const_leatherValue, iCount);
					case 2:
						iValue = const_leatherValue;
						if (player.getGold() >= iValue)
						{
							px.text("Are you sure you want to buy this Leather Armor for ", false);
							px.number(iValue, false);
							px.getS(gString, "gp? Y or N ");
							if (gString == "y" || gString == "Y")
							{
								// Get, deduct and set gold
								gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
								carmor.setName(const_leatherName); carmor.setDesc( const_leatherDesc );
								carmor.setAC(const_leatherAC);	carmor.setType();	carmor.setValue(iValue);
								
								player.addArmor(carmor, player.getArmorCount());
								player.equipArmor(player.getArmorCount());
	
								bArmorDone = true;	break;
							}
							else	break;
						}
						else
							px.pause("You don't have enough gold for that.");
					break;
					//		showArmor(const_hideName, const_hideAC, const_hideDex, const_hideValue, iCount);
					case 3:
						iValue = const_hideValue;
						if (player.getGold() >= iValue)
						{
							px.text("Are you sure you want to buy this Hide Armor for ", false);
							px.number(iValue, false);
							px.getS(gString, "gp? Y or N ");
							if (gString == "y" || gString == "Y")
							{
								// Get, deduct and set gold
								gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
								carmor.setName(const_hideName); carmor.setDesc( const_hideDesc );
								carmor.setAC(const_hideAC);	carmor.setType();	carmor.setValue(iValue);
								
								player.addArmor(carmor, player.getArmorCount());
								player.equipArmor(player.getArmorCount());
	
								bArmorDone = true;	break;
							}
							else	break;
						}
						else
							px.pause("You don't have enough gold for that.");
					break;
					//		showArmor(const_studdedName, const_studdedAC, const_studdedDex, const_studdedValue, iCount);
					case 4:
						iValue = const_studdedValue;
						if (player.getGold() >= iValue)
						{
							px.text("Are you sure you want to buy this Studded Armor for ", false);
							px.number(iValue, false);
							px.getS(gString, "gp? Y or N ");
							if (gString == "y" || gString == "Y")
							{
								// Get, deduct and set gold
								gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
								carmor.setName(const_studdedName); carmor.setDesc( const_studdedDesc );
								carmor.setAC(const_studdedAC);	carmor.setType();	carmor.setValue(iValue);
								
								player.addArmor(carmor, player.getArmorCount());
								player.equipArmor(player.getArmorCount());
	
								bArmorDone = true;	break;
							}
							else	break;
						}
						else
							px.pause("You don't have enough gold for that.");
					break;
					//		showArmor(const_scaleName, const_scaleAC, const_scaleDex, const_scaleValue, iCount);
					case 5:
						iValue = const_scaleValue;
						if (player.getGold() >= iValue)
						{
							px.text("Are you sure you want to buy this Scale Armor for ", false);
							px.number(iValue, false);
							px.getS(gString, "gp? Y or N ");
							if (gString == "y" || gString == "Y")
							{
								// Get, deduct and set gold
								gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
								carmor.setName(const_scaleName); carmor.setDesc( const_scaleDesc );
								carmor.setAC(const_scaleAC);	carmor.setType();	carmor.setValue(iValue);
								
								player.addArmor(carmor, player.getArmorCount());
								player.equipArmor(player.getArmorCount());
	
								bArmorDone = true;	break;
							}
							else	break;
						}
						else
							px.pause("You don't have enough gold for that.");
					break;
					//		showArmor(const_chainshirtName, const_chainshirtAC, const_chainshirtDex, const_chainshirtValue, iCount);
					case 6:
						iValue = const_chainshirtValue;
						if (player.getGold() >= iValue)
						{
							px.text("Are you sure you want to buy this Chain Shirt Armor for ", false);
							px.number(iValue, false);
							px.getS(gString, "gp? Y or N ");
							if (gString == "y" || gString == "Y")
							{
								// Get, deduct and set gold
								gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
								carmor.setName(const_chainshirtName); carmor.setDesc( const_chainshirtDesc );
								carmor.setAC(const_chainshirtAC);	carmor.setType();	carmor.setValue( iValue);
								
								player.addArmor(carmor, player.getArmorCount());
								player.equipArmor(player.getArmorCount());
	
								bArmorDone = true;	break;
							}
							else	break;
						}
						else
							px.pause("You don't have enough gold for that.");
					break;
					//		showArmor(const_chainmailName, const_chainmailAC, const_chainmailDex, const_chainmailValue, iCount);
					case 7:
						iValue = const_chainmailValue;
						if (player.getGold() >= iValue)
						{
							px.text("Are you sure you want to buy this Chain Mail Armor for ", false);
							px.number(iValue, false);
							px.getS(gString, "gp? Y or N ");
							if (gString == "y" || gString == "Y")
							{
								// Get, deduct and set gold
								gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
								carmor.setName(const_chainmailName); carmor.setDesc( const_chainmailDesc );
								carmor.setAC(const_chainmailAC);	carmor.setType();	carmor.setValue( iValue);
								
								player.addArmor(carmor, player.getArmorCount());
								player.equipArmor(player.getArmorCount());
	
								bArmorDone = true;	break;
							}
							else	break;
						}
						else
							px.pause("You don't have enough gold for that.");
					break;
					//		showArmor(const_breastplateName, const_breastplateAC, const_breastplateDex, const_breastplateValue, iCount);
					case 8:
						iValue = const_breastplateValue;
						if (player.getGold() >= iValue)
						{
							px.text("Are you sure you want to buy this Breast Plate Armor for ", false);
							px.number(iValue, false);
							px.getS(gString, "gp? Y or N ");
							if (gString == "y" || gString == "Y")
							{
								// Get, deduct and set gold
								gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
								carmor.setName(const_breastplateName); carmor.setDesc( const_breastplateDesc );
								carmor.setAC(const_breastplateAC);	carmor.setType();	carmor.setValue( iValue);
								
								player.addArmor(carmor, player.getArmorCount());
								player.equipArmor(player.getArmorCount());
	
								bArmorDone = true;	break;
							}
							else	break;
						}
						else
							px.pause("You don't have enough gold for that.");
					break;
					//		showArmor(const_splintName, const_splintAC, const_splintDex, const_splintValue, iCount);
					case 9:
						iValue = const_splintValue;
						if (player.getGold() >= iValue)
						{
							px.text("Are you sure you want to buy this Splint Mail Armor for ", false);
							px.number(iValue, false);
							px.getS(gString, "gp? Y or N ");
							if (gString == "y" || gString == "Y")
							{
								// Get, deduct and set gold
								gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
								carmor.setName(const_splintName); carmor.setDesc( const_splintDesc );
								carmor.setAC(const_splintAC);	carmor.setType();	carmor.setValue( iValue);
								
								player.addArmor(carmor, player.getArmorCount());
								player.equipArmor(player.getArmorCount());
	
								bArmorDone = true;	break;
							}
							else	break;
						}
						else
							px.pause("You don't have enough gold for that.");
					break;
					//		showArmor(const_bandedName, const_bandedAC, const_bandedDex, const_bandedValue, iCount);
					case 10:
						iValue = const_bandedValue;
						if (player.getGold() >= iValue)
						{
							px.text("Are you sure you want to buy this Banded Splint Mail Armor for ", false);
							px.number(iValue, false);
							px.getS(gString, "gp? Y or N ");
							if (gString == "y" || gString == "Y")
							{
								// Get, deduct and set gold
								gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
								carmor.setName(const_bandedName); carmor.setDesc( const_bandedDesc );
								carmor.setAC(const_bandedAC);	carmor.setType();	carmor.setValue( iValue);
								
								player.addArmor(carmor), player.getArmorCount();
								player.equipArmor(player.getArmorCount());
	
								bArmorDone = true;	break;
							}
							else	break;
						}
						else
							px.pause("You don't have enough gold for that.");
					break;
					//		showArmor(const_halfplateName, const_halfplateAC, const_halfplateDex, const_halfplateValue, iCount);
					case 11:
						iValue = const_halfplateValue;
						if (player.getGold() >= iValue)
						{
							px.text("Are you sure you want to buy this Half Plate Suit for ", false);
							px.number(iValue, false);
							px.getS(gString, "gp? Y or N ");
							if (gString == "y" || gString == "Y")
							{
								// Get, deduct and set gold
								gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
								carmor.setName(const_halfplateName); carmor.setDesc( const_halfplateDesc );
								carmor.setAC(const_halfplateAC);	carmor.setType();	carmor.setValue( iValue);
								
								player.addArmor(carmor);
								player.equipArmor(player.getArmorCount());
	
								bArmorDone = true;	break;
							}
							else	break;
						}
						else
							px.pause("You don't have enough gold for that.");
					break;
					//		showArmor(const_fullplateName, const_fullplateAC, const_fullplateDex, const_fullplateValue, iCount);
					case 12:
						iValue = const_fullplateValue;
						if (player.getGold() >= iValue)
						{
							px.text("Are you sure you want to buy this Full Plate Suit for ", false);
							px.number(iValue, false);
							px.getS(gString, "gp? Y or N ");
							if (gString == "y" || gString == "Y")
							{
								// Get, deduct and set gold
								gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
								carmor.setName(const_fullplateName); carmor.setDesc( const_fullplateDesc );
								carmor.setAC(const_fullplateAC);	carmor.setType();	carmor.setValue( iValue);
								
								player.addArmor(carmor, player.getArmorCount());
								player.equipArmor(player.getArmorCount());
	
								bArmorDone = true;	break;
							}
							else	break;
						}
						else
							px.pause("You don't have enough gold for that.");
					break;
				}
			}
		}
		else if (gString == "w" || gString == "W")	// Weapon
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
							cweapon.setName(const_daggerName); 	cweapon.setDesc(const_daggerDesc);
							cweapon.setValue(const_daggerValue);	cweapon.setCritical(const_daggerCritical);	
							cweapon.setCritMod(const_daggerCritMod);
							cweapon.setDamage(const_daggerDamage);	cweapon.setDice(const_daggerDice);
							player.addWeapon(cweapon, player.getWeaponCount());

							player.equipWeapon(player.getWeaponCount());
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
							cweapon.setName(const_maceName);	cweapon.setDesc(const_maceDesc);
							cweapon.setValue(const_maceValue);	cweapon.setCritical(const_maceCritical);	cweapon.setCritMod(const_maceCritMod);
							cweapon.setDamage(const_maceDamage);	cweapon.setDice(const_maceDice);
							player.addWeapon(cweapon, player.getWeaponCount());

							player.equipWeapon(player.getWeaponCount());

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
							cweapon.setName(const_handaxeName);	cweapon.setDesc(const_handaxeDesc);
							cweapon.setValue(const_handaxeValue);	cweapon.setCritical(const_handaxeCritical);	cweapon.setCritMod(const_handaxeCritMod);
							cweapon.setDamage(const_handaxeDamage);	cweapon.setDice(const_handaxeDice);
							player.addWeapon(cweapon, player.getWeaponCount());
							player.equipWeapon(player.getWeaponCount());

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
							cweapon.setName(const_shortswordName);		cweapon.setDesc(const_shortswordDesc);
							cweapon.setValue(const_shortswordValue);	cweapon.setCritical(const_shortswordCritical);	cweapon.setCritMod(const_shortswordCritMod);
							cweapon.setDamage(const_shortswordDamage);	cweapon.setDice(const_shortswordDice);
							player.addWeapon(cweapon, player.getWeaponCount());
							player.equipWeapon(player.getWeaponCount());

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
							cweapon.setName(const_scimitarName);	cweapon.setDesc(const_scimitarDesc);
							cweapon.setValue(iValue);	cweapon.setCritical(const_scimitarCritical);	cweapon.setCritMod(const_scimitarCritMod);
							cweapon.setDamage(const_scimitarDamage);	cweapon.setDice(const_scimitarDice);
							player.addWeapon(cweapon, player.getWeaponCount());
							player.equipWeapon(player.getWeaponCount());

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
							cweapon.setName( const_morningstarName);	cweapon.setDesc(const_morningstarDesc);
							cweapon.setValue(iValue);	cweapon.setCritical(const_morningstarCritical);	cweapon.setCritMod(const_morningstarCritMod);
							cweapon.setDamage(const_morningstarDamage);	cweapon.setDice(const_morningstarDice);
							player.addWeapon(cweapon, player.getWeaponCount());
							player.equipWeapon(player.getWeaponCount());

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
							cweapon.setName(const_spearName);	cweapon.setDesc(const_spearDesc);
							cweapon.setValue(iValue);	cweapon.setCritical(const_spearCritical);	cweapon.setCritMod(const_spearCritMod);
							cweapon.setDamage(const_spearDamage);	cweapon.setDice(const_spearDice);
							player.addWeapon(cweapon, player.getWeaponCount());
							player.equipWeapon(player.getWeaponCount());

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
							cweapon.setName(const_longswordName);	cweapon.setDesc(const_longswordDesc);
							cweapon.setValue(iValue);	cweapon.setCritical(const_longswordCritical);	cweapon.setCritMod(const_longswordCritMod);
							cweapon.setDamage(const_longswordDamage);	cweapon.setDice(const_longswordDice);
							player.addWeapon(cweapon, player.getWeaponCount());
							player.equipWeapon(player.getWeaponCount());

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
							cweapon.setName(const_greatclubName);	cweapon.setDesc(const_greatclubDesc);
							cweapon.setValue(iValue);	cweapon.setCritical(const_greatclubCritical);	cweapon.setCritMod(const_greatclubCritMod);
							cweapon.setDamage(const_greatclubDamage);	cweapon.setDice(const_greatclubDice);
							player.addWeapon(cweapon, player.getWeaponCount());
							player.equipWeapon(player.getWeaponCount());

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
							cweapon.setName(const_halberdName);	cweapon.setDesc(const_halberdDesc);
							cweapon.setValue(iValue);	cweapon.setCritical(const_halberdCritical);	cweapon.setCritMod(const_halberdCritMod);
							cweapon.setDamage(const_halberdDamage);	cweapon.setDice(const_halberdDice);
							player.addWeapon(cweapon, player.getWeaponCount());
							player.equipWeapon(player.getWeaponCount());
							
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
							gShort = player.getGold();	gShort -= iValue;	player.setGold(gShort);
							cweapon.setName(const_bastardswordName);	cweapon.setDesc(const_bastardswordDesc);
							cweapon.setValue(iValue);	cweapon.setCritical(const_bastardswordCritical);	cweapon.setCritMod(const_bastardswordCritMod);
							cweapon.setDamage(const_bastardswordDamage);	cweapon.setDice(const_bastardswordDice);
							player.addWeapon(cweapon, player.getWeaponCount());
							player.equipWeapon(player.getWeaponCount());

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
							cweapon.setName(const_greataxeName);	cweapon.setDesc(const_greataxeDesc);
							cweapon.setValue(iValue);	cweapon.setCritical(const_greataxeCritical);	cweapon.setCritMod(const_greataxeCritMod);
							cweapon.setDamage(const_greataxeDamage);	cweapon.setDice(const_greataxeDice);
							player.addWeapon(cweapon, player.getWeaponCount());
							player.equipWeapon(player.getWeaponCount());

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
							cweapon.setName(const_greatswordName);	cweapon.setDesc(const_greatswordDesc);
							cweapon.setValue(iValue);	cweapon.setCritical(const_greatswordCritical);	cweapon.setCritMod(const_greatswordCritMod);
							cweapon.setDamage(const_greatswordDamage);	cweapon.setDice(const_greatswordDice);
							player.addWeapon(cweapon, player.getWeaponCount());
							player.equipWeapon(player.getWeaponCount());

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

	bool bFightOver = false;
	bool bMenu = false;
	bool bPickWeapon = false;

	int tmp;
	string sTmp;
	sint xpCalc;
	sint goldCalc;

	sint pAttackRoll, eAttackRoll;
	sint pDamageRoll, eDamageRoll;

	sint roundCount = 1;

	sint eHP, eAC, eGold, eXP, eAttack;
	string eName, eWeaponName;
	string pName, pWeaponName;

	sint pAttack, pHP, pAC;


	// Setup static stuff
	pAC = player.getArmorClass();
	pHP = player.getMaxHealth();
	pAttack = 0; // for debug purposes

	pName = player.getName();




	// Pick out a weapon
	while(!bPickWeapon)
	{
		px.clrscr();
		player.showWeaponInventory();
		px.getS(sTmp,"Please pick a weapon to use: ");
		ss.stringToNumber(sTmp, tmp);	// to prevent bugs 

		if( player.getWeaponCount() >= tmp)
		{
			player.getWeapon(cweapon, tmp-1); 	// tmp is index i.e. doesnt line up with array
			player.equipWeapon(tmp-1);					// ^^^^
			px.text("Do you want to use this weapon, the ", false); px.text(cweapon.getName(), false);
			px.text("?  > ", false);
			px.getS(sTmp);
			if( sTmp == "y" || sTmp == "Y" )
				bPickWeapon = true;
		}
		else
		{
			px.pause("Invalid choice, try again.");
		}
	}

	pWeaponName = player.getWeaponName();
	
	
	if (player.mCreated == false) // no player
	{
		px.pause("No character found.");
		return;
	}

	while (!bMenu)
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

		
		// downgrades if fighting below level
		xpCalc = fightXPDowngrade( gInt, player.getLevel());
		goldCalc = fightGoldDowngrade( gInt, player.getLevel());

		// Pick a random enemy
		fightEnemyRNG(enemy, xpCalc, goldCalc);

		
		eHP = enemy.getHealth();
		eAC = enemy.getArmorClass();
		eGold = enemy.getGold();
		eXP = enemy.getExperience();	
		eAttack = enemy.getAttack();

		eName = enemy.getName();
		eWeaponName = enemy.getWeaponName();

		// check for a quit selection
		if (tmp == gInt){
			px.getS(gString, "Are you sure you want to leave the arena? Y or N ");
			if (gString == "y" || gString == "Y")	{	bMenu = true; bFightOver = true;	break;	}	
		}
		if( tmp < gInt )
		{
			bMenu = true;	// go onto fight, enemy level picked
			break;
		}
	}
	while (!bFightOver)
	{
		px.rng(pAttackRoll);
		px.rng(eAttackRoll);

		rollDamage(pDamageRoll, cweapon);
		px.rng(eDamageRoll, eAttack-1, eAttack);

		px.clrscr();

			
		// Round # (Player vs. enemy)
		// hp remaining: #
		// > Player swings his Weapon at enemy and misses
		// > Enemy swings his eWeapon at player for # damage
		px.text("Round ", false);
		px.number(roundCount, false);
		px.text(" (", false);
		px.text(pName, false);
		px.text(" vs. ", false);
		px.text(eName, false);
		px.text(")");

		px.number(pHP, false);
		px.text("hp remaining");

		px.sleep(5000);
			

		// hit
		if (pAttackRoll >= eAC)
		{
			px.text("> ", false);
			px.text(pName, false);
			px.text(" swings his ", false);
			px.text(pWeaponName, false);
			px.text(" at his opponent ", false);
			px.text(eName, false); 
					
			if (pAttackRoll >= cweapon.getCritical()) // crit hit
			{
				for( int i = 0; i < cweapon.getCritMod(); i++)
					rollDamage(pDamageRoll, cweapon, 0, false);

				px.text(" and critically hits for ", false);
				px.number(pDamageRoll, false);
				px.text(" damage!");
			}
			else
			{
				px.text(" and hits for ", false);
				px.number(pDamageRoll, false);
				px.text(" damage.");
			}
			eHP -= pDamageRoll;
			}
			
		else	// miss
		{
			px.text("> ", false);
			px.text(pName, false);
			px.text(" swings his ", false);
			px.text(pWeaponName, false);
			px.text(" at his opponent ", false);
			px.text(eName, false);
			px.text(" and misses.");
		}
			
		px.sleep(1250);
		
		if (eAttackRoll > pAC)		// enemy hit
		{
			px.text("> ", false);
			px.text(eName, false);
			px.text(" swings his ", false);
			px.text(eWeaponName, false);
			px.text(" at ", false);
			px.text(pName, false);
			px.text(" and hits for ", false);
			px.number(eDamageRoll, false);
			px.text(" damage.");

			pHP -=eDamageRoll;
			player.setHealth(pHP);
		}
			
		else		// enemy miss
		{
			px.text("> ", false);
			px.text(eName, false);
			px.text(" swings his ", false);
			px.text(eWeaponName, false);
			px.text(" at ", false);
			px.text(pName, false);
			px.text(" and misses.");
		}
			
		px.pause("End of round.");
		roundCount++;


		// do enemy and player health checks, reward or kill player accordingly
			
		if (pHP <= 0) // player died, reset XP but keep gold only
		{
			player.mCreated = false;
			player.setExperience(0);
			player.delWeapon(2);	player.delWeapon(1);	player.delWeapon(0);
			player.delArmor(2);		player.delArmor(1);		player.delArmor(0);
			// remove potions once they are added.
			px.pause("You have died. Please bring back more bodies!");
			bFightOver = true;
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
			px.text(" has died. You have gained ", false);
			px.number(eGold, false);
			px.text(" gold and ", false);
			px.number(eXP, false);
			px.text(" experience.");
			px.pause();
			px.sleep(5000);

			
			player.setHealth(player.getMaxHealth());
			player.level();
			bFightOver = true;

		}		

	}		// bFightOver
}	// fight()

// show inventory and equipped weapons
void equip()
{
	bool bEquipDone = false;
	bool bArmorDone = false;
	bool bWeaponDone = false;
	
	int iMenuCount = 1;
	sint iWeaponValue = 0;
	sint iArmorValue = 0;
	
	cWeapon cweapon;
	cArmor carmor;
	
	while(!bEquipDone)
	{
		px.text("==============================");
		px.text("Equip Menu");
		px.text("==============================");
		px.nl(1);
		px.text("A. Equip Armor");
		px.text("W. Equip Weapons");
		px.text("R. Return to prev menu");
		px.getS(gString, "Choice: ");
	
		if(gString == "a" || gString == "A")		// Armor
		{
		}
		else if (gString == "w" || gString == "W")	// Weapon
		{
		}
		else if(gString == "r" || gString == "R")
			bEquipDone=true;
		else
		px.pause("Invalid choice.");
	}
}

sint fightXPDowngrade(int tmp, sint level)
{	
	sint xpCalc;
	if (tmp > level )	// Double xp
		xpCalc = 300;
	else if (tmp == level)
		xpCalc = 150;
	else if (tmp == (level - 1))
		xpCalc = 100;
	else if (tmp == (level - 2))
		xpCalc = 75;
	else if (tmp == (level - 3))
		xpCalc = 50;
	else if (tmp == (level - 4))
		xpCalc = 25;
	else
		xpCalc = 5;
	return xpCalc;
}

sint fightGoldDowngrade(int tmp, sint level)
{
	sint goldCalc;
	if (tmp > level)	// 1.5x gold
		goldCalc = 450;
	else if (tmp == level)
		goldCalc = 300;
	else if (tmp == (level - 1))
		goldCalc = 150;
	else if (tmp == (level - 2))
		goldCalc = 100;
	else if (tmp == (level - 3))
		goldCalc = 50;
	else if (tmp == (level - 4))
		goldCalc = 25;
	else
		goldCalc = 5;
	return goldCalc;
}

void fightEnemyRNG(cMonster &in, sint xp, sint gold)
{
	// extra random dont forget to change me when you add more enemies.
	for(int i = 0; i < 25; i++)
		px.rng(gInt, 1, 5);
		
	switch (gInt)
	{
	case 1:
		in.createEnemy("Orc", "Longsword", 20, 12, gold, 3, xp, 1);
		break;
	case 2:
		in.createEnemy("Orc", "Falchion", 35, 13, gold, 5, xp, 1);
		break;
	case 3:
		in.createEnemy("Orc", "Scimitar", 60, 14, gold, 7, xp, 1);
		break;
	case 4:
		in.createEnemy("Orc", "Broadsword", 85, 15, gold, 9, xp, 1);
		break;
	case 5:
		in.createEnemy("Orc", "Waraxe", 100, 16, gold, 11, xp, 1);
		break;
	}
}
void rollDamage(sint &in, cWeapon weapon, sint strmod, bool erase)
{
	if (erase)
		in = 0;

	for (int i = 0; i < weapon.getDice(); i++)
	{
		px.rng(gInt, weapon.getDamage()-1, weapon.getDamage());
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
void showArmor(string sName, int iAC, int iValue, int &iCount)
{
	px.number(iCount, false);
	px.text(". ",false);
	px.text(sName, false);
	px.text(" ",false);	// Add a space
	px.text("AC ",false);
	px.number(iAC, false);
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
	tmp.setName(sName); tmp.setDesc(sDesc);	tmp.setDice(iDice);	tmp.setDamage(iDamage); 
	tmp.setCritical(iCrit); tmp.setCritMod(iCritMod); tmp.setValue(iValue);
	tmp.setType(); // weapon default
	tmp.setEquipped(false);
	return tmp;
}

// use to add armor in batches
/*]
	sint mArmorClass;
	bool isEquipped; // Am i wearing this?

	string mItemName; // Basic name for display
	string mItemDesc; // When asked for details this is the output
	string mItemType; // Weapon, Armor, Potion

	sint mValue; // How much gold is this worth
*/
cArmor addArmor(string sName, string sDesc, int iAC, int iValue)
{
	cArmor tmp;		tmp.clear();
	tmp.setName(sName);	tmp.setDesc(sDesc);	tmp.setAC(iAC);	tmp.setValue(iValue);
	tmp.setType();	// armor default
	tmp.setEquipped(false);
	return tmp;
}
