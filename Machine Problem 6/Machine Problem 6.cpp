#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

fstream outFile;

struct Flower
{
	int recordNum;
	char name[15];
	int quantity;
	float cost;
};

Flower emptyFlower;

void enterData(Flower& flower)
{
	cout << "Plase enter flower name: " << endl;
	cin >> flower.name;
	cout << "Please enter flower quantity: " << endl;
	cin >> flower.quantity;
	cout << "Please enter flower cost: " << endl;
	cin >> flower.cost;
};

void writeFile(int id, Flower flower)
{
	outFile.seekp(id * sizeof(Flower));
	outFile.write(reinterpret_cast<char*>(&flower), sizeof(Flower));
}

void readFile(int id, Flower& flower)
{
	outFile.seekp(id * sizeof(Flower));
	outFile.read(reinterpret_cast<char*>(&flower), sizeof(Flower));
}

void initializeFile()
{
	outFile.open("flowers.dat");
	emptyFlower.recordNum = 0;
	strcpy(emptyFlower.name, "");
	emptyFlower.quantity = 0;
	emptyFlower.recordNum = 0;

	for (int i = 0; i < 50; i++)
	{
		writeFile(i, emptyFlower);
	}
};



void listFlowers()
{
	Flower flower;

	cout << right << setw(23) << setfill(' ') << "Record Number (FIN)";
	cout << right << setw(17) << setfill(' ') << "Flower Name";
	cout << right << setw(13) << setfill(' ') << "Quantity";
	cout << right << setw(13) << setfill(' ') << "Cost" << endl;

	for (int i = 0; i < 50; i++)
	{
		readFile(i, flower);
		if (strcmp(flower.name, "") == 0 && flower.cost == 0 && flower.quantity == 0)
		{
			continue;
		}
		cout << right << setw(23) << setfill(' ') << flower.recordNum;
		cout << right << setw(17) << setfill(' ') << flower.name;
		cout << right << setw(13) << setfill(' ') << flower.quantity;
		cout << right << setw(13) << setfill(' ') << flower.cost << endl;
	}

};

void handleChoice(int choice, int& flowerID, Flower& flower)
{
	if (choice >= 1 && choice <= 5)
	{
		while (true)
		{
			cout << "Enter record number of flower: " << endl;
			cin >> flowerID;

			if (flowerID < 0 || flowerID >= 50)
			{
				cout << "Not valid record number." << endl;
				continue;
			}
			break;
		}
	}

	switch (choice)
	{
	case 1:
		enterData(flower);
		flower.recordNum = flowerID;
		writeFile(flowerID, flower);
		break;
	case 2:
		writeFile(flowerID, emptyFlower);
		break;
	case 3:
		cout << "Enter new flower name: " << endl;
		readFile(flowerID, flower);
		cin >> flower.name;
		writeFile(flowerID, flower);
		break;
	case 4:
		cout << "Enter new flower quantity: " << endl;
		readFile(flowerID, flower);
		cin >> flower.quantity;
		writeFile(flowerID, flower);
		break;
	case 5:
		cout << "Enter new flower cost: " << endl;
		readFile(flowerID, flower);
		cin >> flower.cost;
		writeFile(flowerID, flower);
		break;
	case 6:
		listFlowers();
		break;
	}
}


int main()
{
	initializeFile();
	while (true)
	{
		int choice;
		int flowerID;
		Flower flower;
		cout << "What would you like to do?" << endl;
		cout << "1. Create new record." << endl;
		cout << "2. Delete Record." << endl;
		cout << "3. Update Flower Name." << endl;
		cout << "4. Update Flower Quanitity." << endl;
		cout << "5. Update Flower Cost." << endl;
		cout << "6. List Flowers" << endl;
		cin >> choice;
		handleChoice(choice, flowerID, flower);
	}



}

