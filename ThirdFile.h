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
