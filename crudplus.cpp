#include <iostream>
#include <map>
using namespace std;


class Item
{
	public:
		Item(int price_, string name_);
		string name;
		int price;
};

Item::Item(int price_, string name_):
	name(name_), price(price_)
{}

void display(map<string, Item> inventory);

int main()
{
	char input = 'z';	
	map<string, Item> inventory;
	string temp_name = "";
	int temp_price;

	while(input != 'q')
	{
		cout << "What would you like to do?" << endl;
		cout << "(n) Create new item" << endl;
		cout << "(e) Edit an Item" << endl;
		cout << "(d) Delete an Item" << endl;
		cout << "(v) View inventory" << endl;
		cout << "(q) Quit" << endl;
		
		cin >> input;

		if(input == 'n')
		{
			cout << "What is the name of your item?" << endl;
			cin >> temp_name;
			cout << "What is the price?" << endl;
			cin >> temp_price;
			Item newItem(temp_price, temp_name);
			inventory.insert ( make_pair(temp_name, newItem) );

			cout << endl;
		}
		else if (input == 'e')
		{
			if(inventory.empty())
			{
				cout << endl;
				cout << "Inventory is empty" << endl;
				cout << endl;
			}
			else
			{
				cout << "Which item would you like to edit?" << endl;
				display(inventory);
				cin >> temp_name;
				if(inventory.find(temp_name) != inventory.end())
				{
					char change ='o';
					while (change != 'e')
					{
						cout << "(n) change name" << endl;
						cout << "(p) change price" << endl;			
						cout << "(e) exit" << endl;

						cin >> change;
						if(change == 'p')
						{
							cout << "New price: ";
							cin >> temp_price;
							inventory.find(temp_name)->second.price = temp_price;
						}
						else if(change == 'n')
						{
							inventory.find(temp_name)->second.price = temp_price;
							cout << "New name: ";
							string newName ="";
							cin >> newName;

							inventory.erase(temp_name);
							Item newItem(temp_price, newName);
							inventory.insert ( make_pair(newName, newItem) );
						}
						else if(change == 'e')
						{
							break;
						}
						else
						{
							cout << endl;
							cout << "the options are n, p , or q" << endl;
							cout << endl;
						}
					}
				}
				else
				{
					cout << endl;
					cout << temp_name << " does not exist" << endl;
					cout << endl;
				}				
			}
		}
		else if(input == 'd')
		{
			if(inventory.empty())
			{
				cout << endl;
				cout << "Inventory is empty" << endl;
				cout << endl;
			}
			else
			{
				cout << "What item would you like to delete?" << endl;
				display(inventory);
				cin >> temp_name;
				if(inventory.find(temp_name) == inventory.end())
				{
					cout << endl;
					cout << temp_name << " does not exist" << endl;
					cout << endl;
				}
				else
				{
					inventory.erase(temp_name);
				}				
			}	
		}
		else if(input == 'v')
		{
			display(inventory);
		}	

		else if(input == 'q')
		{
			break;
		}	
		else
		{
			cout << endl;
			cout << "the options are n, d, v, or q." << endl;
			cout << endl;
		}
	}
	return 0;
}

void display(map<string, Item> inventory)
{
	cout << endl;

	if(inventory.empty())
	{
		cout << "Inventory is empty" << endl;
	}
	else
	{
		cout << "Inventory:" << endl;
		for(map<string,Item>::const_iterator it = inventory.cbegin(); it != inventory.cend(); ++it)
		{
		    cout << it->second.name << " " << it->second.price << endl;
		}
	}
	cout << endl;	
}

