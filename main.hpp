#ifndef MAIN_H
#define MAIN_H

#define LINUX


#include "phatSS.hpp"
#include "phatx.hpp"
#include "player.hpp"

cPlayer player;

void createCharacter(); // rolls for stats and assign name 
void nameCharacter(); 	// name player object
void rollStats(); 	// fills the variables for players
void showStats(bool clrscr = true);
void purchase();	// purchase armor and weapons
void fight();		// fight enemies

void rollDamage(sint &in, cWeapon weapon, sint strmod = 0, bool erase = true);

void testing(); //	for new features

#endif // MAIN_H
