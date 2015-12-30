#include "player.hpp"

cMonster::cMonster()
{
    mHealth = 0; mArmor = 0; mGold = 0; mAttack = 0; mAP = 0;
    gNumOfMonsters += 1; monsterCanRun = false; // mostly only prey can run...
}

cMonster::cMonster(sint iHealth, sint iArmor, sint iGold, sint iAttack, sint iAP, bool iCanRun)
{
    // use functions for cleaner error checking such as 0 health, 0 attack, 0 armor
    setHealth(iHealth); setArmor(iArmor); setGold(iGold); setAttack(iAttack); setAP(iAP);

    monsterCanRun = iCanRun; gNumOfMonsters += 1;
}

cMonster::~cMonster()
{
    gNumOfMonsters -= 1;
}

bool cMonster::delAP(sint num)
{
    gShort = (mAP -= num);
    if(gShort>=0)
    { mAP = gShort; return true; }
    else
    { px.pause("Can't do that. You are too tired.\nPress enter to continue..."); return false; }
}

cPlayer::cPlayer()
{

}


cPlayer::~cPlayer()
{

}

