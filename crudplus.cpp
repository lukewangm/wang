#include <iostream>
#include <map>
#include <string>
using namespace std;


class Item
{
	public:
		Item(int price_, string name_);
		string name;
		int price;
		string deletionComment;
};

Item::Item(int price_, string name_):
	name(name_), price(price_), deletionComment("")
{}

void display(map<string, Item> inventory);

int main()
{
	char input = 'z';	
	map<string, Item> inventory;
	map<string, Item> recently_deleted;
	string temp_name = "";
	int temp_price;

	while(input != 'q')
	{
		cout << "What would you like to do?" << endl;
		cout << "(n) Create new item" << endl;
		cout << "(e) Edit an Item" << endl;
		cout << "(d) Delete an Item" << endl;
		cout << "(v) View inventory" << endl;
		cout << "(r) View recently deleted" << endl;
		cout << "(q) Quit" << endl;
		
		cin >> input;

		if(input == 'n')
		{
			cout << "What is the name of your item?" << endl;
			cin >> temp_name;
			char choice = 'o';

			if(inventory.find(temp_name) != inventory.end())
			{
				
				while(choice != 'y' && choice != 'n')
				{
					cout << "Item exists, would you like to replace it? (y/n)" << endl;
					cin >> choice;
					if(choice == 'y')
					{
						cout << "What is the price?" << endl;
						cin >> temp_price;
						inventory.find(temp_name)->second.price = temp_price;
						cout << endl;
					}
				}
			}
			else
			{
				cout << "What is the price?" << endl;
				cin >> temp_price;
				Item newItem(temp_price, temp_name);
				inventory.insert ( make_pair(temp_name, newItem) );
				cout << endl;
			}
			
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
							change = 'e';
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
							change = 'e';
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
				string comment;
				cin >> temp_name;
				if(inventory.find(temp_name) == inventory.end())
				{
					cout << endl;
					cout << temp_name << " does not exist" << endl;
					cout << endl;
				}
				else
				{	
					Item newItem(inventory.find(temp_name)->second.price, temp_name);
					inventory.erase(temp_name);
					cout << "Deletion comment: ";
					cin>>ws;
					getline(cin, comment);
					newItem.deletionComment = comment;
					recently_deleted.insert(make_pair(temp_name, newItem));
					
				}				
			}	
		}
		else if(input == 'v')
		{
			display(inventory);
		}	
		else if(input == 'r')
		{
			cout << endl;

			if(recently_deleted.empty())
			{
				cout << "Recently_deleted is empty" << endl;
				cout << endl;
			}
			else
			{
				cout << "Recently deleted:" << endl;
				for(map<string, Item>::const_iterator rit = recently_deleted.cbegin(); rit != recently_deleted.cend(); ++rit)
				{
				    cout << rit->first << ": " << rit->second.deletionComment << endl;
				}			
				cout << endl;	
				cout << "Would you like to recover items? (y/n)" << endl;

				char choice = 'o';
				while (choice != 'n')
				{
					cin >> choice;
					if(choice == 'y')
					{
						cout << "Which item?" << endl;
						string recover;
						cin >> recover;

						if(recently_deleted.find(recover) != recently_deleted.end())
						{
							Item newItem(recently_deleted.find(recover)->second.price, recover);
							inventory.insert ( make_pair(recover, newItem) );	
							recently_deleted.erase(recover);					
						}
						else
						{
							cout << recover << " does not exist" << endl;
						}
						choice = 'n';
					}			
				}
			}
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

