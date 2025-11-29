#include "armor.hpp"


cArmor::cArmor(sint ac, sint value, string name, string desc, string type)
{
	
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

	mItemType = type;

	isEquipped = false;
}

void cArmor::clear()
{
	mArmorClass = 0;
	mValue = 0;
	isEquipped = false;
	mItemName.clear();
	mItemDesc.clear();
}
