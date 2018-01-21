#include "armor.hpp"


cArmor::cArmor(sint dex, sint ac, sint value, string name, string desc, string type)
{
	if (dex >= 0)
		mDexMod = dex;
	else
		mDexMod = SHRT_MAX;

	if (ac >= 0)
		mArmorClass = ac;
	else
		mArmorClass = SHRT_MAX;

	if (value >= 0)
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

void cArmor::clear()
{
	mDexMod = 0;
	mArmorClass = 0;
	mValue = 0;
	isEquipped = false;
	mItemName.clear();
	mItemDesc.clear();
	mItemType.clear();
}
