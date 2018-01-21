/*

//	Todo:

//  Bugs:

fight doesnt reset half the time, and he loses his weapons and stuff if he dies... should honestly rewrite the whole part after the first round tbh.

*/
#ifndef MAIN_H
#define MAIN_H


#include "phatSS.hpp"
#include "phatx.hpp"
#include "player.hpp"
#include "item.hpp"
#include "weapon.hpp"
#include "inventory.hpp"
#include "armor.hpp"

cPlayer player;

void createCharacter(); // rolls for stats and assign name 
void nameCharacter(); 	// name player object
void rollStats(); 	// fills the variables for players
void showStats(bool clrscr = true);
void purchase();	// purchase armor and weapons
void fight();		// fight enemies
void equip();		// equip stuff

void rollDamage(sint &in, cWeapon weapon, sint strmod = 0, bool erase = true);

void testing(); //	for new features

void showWeapon(string sName, int iDice, int iDamage, int iCrit, int iCritMod, int iValue, int &iCount);
void showArmor(string sName, string sDesc, int iAC, int iDex, int iValue, int &iCount);

void addWeapon(string sName, string sDesc, int iDice, int iDamage, int iCrit, int iCritMod, int iValue);
void addArmor(string sName, string sDesc, int iAC, int iDex, int iValue);

#endif // MAIN_H
