#include "warehouse.h"
#include <fstream>
#include <iomanip>


/*
Simon Devlin-Beadle
October 13th 2020
Implementation File for warehouse.h
*/

//Non-Default Constructor for Warehouse Class, Passed fileName and maxItems.
//maxItems has a default value of SIZE (25) if no value is passed.

/*This comment is for the CommunityConnectionsAssignment*/

void CommunityConnections()
{
	cout << "This is for the community connections assignment." endl;
}

Warehouse::Warehouse(string fileName, int maxItems)
{
	//Validate number of maxItems. Cannot be larger than SIZE (25) or smaller than 0.

	if (maxItems > noItems || maxItems < 0)
	{
		maxItems = SIZE;
	}

	//Open Input File.

	ifstream fin(fileName);
	if (!fin.is_open())
	{
		//Display error message and crash the program.

		cout << "error opening " << fileName << " - contact systems.";
		system("pause");
		exit(-2);
	}

	//Fill The Items Array.

	for (noItems = 0; noItems <= maxItems; noItems++)
	{
		//Ensure array is not overfilled.
		
		if (noItems == maxItems)
		{
			break;
		}
		else
		{
			//Read in itemCode, description and qoh.

			fin >> items[noItems].itemCode;
			fin.ignore(80, '\n');
			getline(fin, items[noItems].description);
			fin >> items[noItems].qoh;

			//If at end of file, break.

			if (fin.eof())
			{
				break;
			}
		}
	}
}

//findItem Function, Passed itemCode. Search items Array For A Specific Item.

int Warehouse::findItem(int itemCode)
{
	//Set position in array to equal the number of items.

	int posInArray = noItems;
	
	//Search array for itemCode.

	for (int ctr = 0; ctr < noItems; ctr++)
	{
		if (items[ctr].itemCode == itemCode)
		{
			posInArray = ctr;	//Assign posInArray to equal current position in items array.
			break;				//Break out of for loop.
		}
	}
	return posInArray;			//Return position in array.
}

//showItem Function, Passed itemCode. Display Item's Description and Qoh.


void Warehouse::showItem(int itemCode)
{
	//If item was not found, display error message.
	//Otherwise, display appropriate item data.
	
	if (findItem(itemCode) == noItems)
	{
		cout << "Item with Item Code: " << itemCode << " was not found." << endl;
	}
	else
	{
		cout << "Description: " << items[findItem(itemCode)].description << endl;
		cout << "Quantity On Hand: " << items[findItem(itemCode)].qoh << endl;
	}
}

//writeWarehouseItems Function, Passed Output Stream. Writes Data to Output File.

void Warehouse::writeWarehouseItems(ostream& outputFile)
{
	//Write Item Code, Description, and QOH column headers.

	outputFile << left << setw(15) << "Item Code" << setw(15)
		<< "Description" << setw(20)
		<< "Quantity on hand" << endl << endl;

	//Display output data under each appropriate column.

	for (int ctr = 0; ctr < noItems; ctr++)
	{
		outputFile << left << setw(15) << items[ctr].itemCode << setw(15)
			<< items[ctr].description << setw(20) << items[ctr].qoh << endl;
	}

	//Display the number of items in items array.

	outputFile << endl << "Number of items: " << noItems << endl;
}

//addItem Function, Passed itemCode, Description, and Qoh. Adds Item to Array.

void Warehouse::addItem(int itemCode, string description, int qoh)
{
	//Ensure array is not full.

	if (noItems == SIZE)
	{
		cout << "Cannot Add Item. Item array is already full." << endl;
	}
	else
	{
		if (findItem(itemCode) < noItems)
		{
			//itemCode already exists in array. Display error message.

			cout << "Item Code: " << itemCode << " already exists in array." << endl;
		}
		else
		{
			//Add item itemCode, description and qoh to array.
			
			items[noItems].itemCode = itemCode;
			items[noItems].description = description;
			items[noItems].qoh = qoh;

			//Increase noItems in array.

			noItems++;

			//Display item added message.

			cout << "Item, " << itemCode << " Added Successfully." << endl;
		}
	}
}