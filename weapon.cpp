#include "weapon.hpp"

// Add checks
cWeapon::cWeapon(sint damage, sint dice, sint crit, sint critmod, sint value, string name, string desc, string type)
{
	if (damage > 0)
		mDamage = damage;
	else
		mDamage = SHRT_MAX;

	if (dice > 0)
		mDice = dice;
	else
		mDice = SHRT_MAX;

	if (crit >= 18)
		mCritical = crit;
	else
		mCritical = SHRT_MAX;

	if (critmod > 1)
		mCritMod = critmod;
	else
		mCritMod = SHRT_MAX;

	if (mValue >= 0)
		mValue = value;
	else
		mValue = SHRT_MAX;
	if (!name.empty())
		mItemName = name;

	if (!desc.empty())
		mItemDesc = desc;

	if (!type.empty())

		mItemType = type;

	isEquipped = false;
}

void cWeapon::clear()
{
	mDamage = 0;
	mDice = 0;
	mCritical = 0;
	mCritMod = 0;
	mValue = 0;
	isEquipped = false;
	mItemName.clear();
	mItemDesc.clear();
	mItemType.clear();
}
