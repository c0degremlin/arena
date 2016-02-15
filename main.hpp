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
void showStats( bool clrscr = true );
void purchase();	// purchase armor and weapons
const float const_hpScaling = 1.2f;	// Constitution bonus
const float const_manaScaling = 1.5;	// Intelligence bonus
const sint const_baseAC = 10;		// Without armor

void testing(); //	for new features

#endif // MAIN_H
