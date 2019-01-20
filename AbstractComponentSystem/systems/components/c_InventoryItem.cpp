//Evan Gordon
//Alexander Frisk

#include "c_InventoryItem.h"

c_InventoryItem::c_InventoryItem() :
/*MAX_STACK(0),type(""),*/ isEmpty(true), ID(0)
{}


c_InventoryItem::c_InventoryItem(unsigned int itemID/*, const int MAX_STACK, std::string type*/) :
/*MAX_STACK(MAX_STACK), type(type),*/ isEmpty(false), ID(itemID)
{}

