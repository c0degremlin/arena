#include "item.hpp"

cItem::cItem()
{
	mItemName.clear();	mItemDesc.clear();	mItemType.clear();
	mValue = 0; 
}

// Add checks
cWeapon::cWeapon( sint damage, sint dice, sint crit, sint critmod, sint value, string name, string desc, string type )
{
	mDamage = damage;
	mDice = dice;
	mCritical = crit;
	mCritMod = critmod;
	mValue = value;
	mItemName = name;
	mItemDesc = desc;
	mItemType = type;
	isEquipped = false;
}

cArmor::cArmor( sint dex, sint ac, sint value, string name, string desc, string type )
{
	mDexMod = dex;
	mArmorClass = ac;
	mValue = value;
	mItemName = name;
	mItemDesc = desc;
	mItemType = type;
	isEquipped = false;
}
