#ifndef ITEM_HPP
#define ITEM_HPP

#include "phatx.hpp"
#include "phatSS.hpp"


// The basic template for all wearable items for offenes and defense
class cItem
{
protected:
	string mItemName; // Basic name for display
	string mItemDesc; // When asked for details this is the output
	string mItemType; // Weapon, Armor, Potion

	sint mValue; // How much gold is this worth
public:
	cItem();
	sint getValue() { return mValue; }
	void setValue(sint num) { mValue = num; }
	virtual void clear(); // Reset all values
};

// make potion.cpp/hpp
class cPotion : public cItem
{

};





#endif
