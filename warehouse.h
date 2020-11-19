#include <iostream>
#include <string>

using namespace std;

/*
Simon Devlin-Beadle
October 13th 2020
Warehouse.h Specification File
*/

//Size of ItemRec array.

const int SIZE = 25;

//ItemRec Struct.

struct ItemRec
{
	int itemCode;
	string description;
	int qoh;
};

//Declare a new Class called Warehouse

class Warehouse
{
public:

	//Non-Default Constructor, Passed fileName and maxItems. Intializes New Object of Warehouse Class.
	Warehouse(string /*fileName*/, int = SIZE);

	//showItem Function, Passed itemCode. Display Item's Description and Qoh.
	void showItem(int /*itemCode*/);

	//writeWarehouseItems Function, Passed Output Stream. Writes Data to Output File.
	void writeWarehouseItems(ostream& /*fileName*/);

	//getNoItems Function, Const. Returns noItems.
	int getNoItems() const { return noItems; }

	//addItem Function, Passed itemCode, Description, and Qoh. Adds Item to Array.
	void addItem(int /*itemCode*/, string /*description*/, int /*qoh*/);

private:

	//items, Array of class ItemRec called items.
	ItemRec items[SIZE];

	//maxItems, Maximum number of items for an instance of the class.
	int maxItems;

	//noItems, Actual number of items in the array (array length).
	int noItems;

	//findItem Function, Passed itemCode. Search items Array For A Specific Item.
	int findItem(int /*itemCode*/);
};
