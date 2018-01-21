#include "item.hpp"

cItem::cItem()
{
	mItemName.clear();	mItemDesc.clear();	mItemType.clear();
	mValue = 0;
}

void cItem::clear()
{
	mItemName.clear();	mItemDesc.clear();	mItemType.clear();
	mValue = 0;
}

