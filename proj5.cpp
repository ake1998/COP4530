/**Name: Ashley Ellis
 * Assignment: Project 5
 * Due date: April 22, 2019
 */

#include "passserver.h"
using namespace cop4530;
using namespace std;
void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

int main()
{
	// variable to store user submitted choice
	char choice;

	// variable to store user submitted capacity
	size_t preferredCapacity;
	
	// prompt user for capacity
	cout<<"Enter preferred hash table capacity: ";
	cin >> preferredCapacity;

	//create object with user entered capacity
	PassServer ps( preferredCapacity );
	
	// print menu to user
	Menu();

	// loop to read in choice
	while( cin >> choice )
	{
		if( choice == 'l' )
		{
			char* f = nullptr;
	
			// prompt user for file name
			cout<<"Enter password file to load from: ";
			cin >> f;
			
			// if loaded then output load is completed
			if( ps.load( f ) )
				cout<<"Load complete\n";

			// if error is encountered
			else
				cout<<"Error loading file entry is incorrect\n";
		
			//print menu
			Menu();
		}	

		else if ( choice == 'a' )
		{
			// create pair
			pair< string, string > newUser;
	
			cout<<"Enter username: ";
			// read in first element
			cin >> newUser.first;
			cout<<"\nEnter password: ";
			// read in second element
			cin >> newUser.second;

			// if user is successfully added output success
			if ( ps.addUser( newUser ) )
			{
				cout<<"\nUser " << newUser.first << " added.";
			}
			// error encountered
			else
				cout<<"\n*****Error: User already exists. Could not add user."; 
			
			// print menu
			Menu();
		}	

		else if ( choice == 'r' )
		{
			// string to store user input
			string user;

			cout<<"Enter username: ";
			// read input
			cin>>user;
	
			// if user is successfully removed output success
			if ( ps.removeUser( user ) )
				cout<<"\nUser " << user <<" deleted.";
			// error encountered
			else
				cout<<"\n*****Error: User could not be found. Could not delete user.";

			// print menu
			Menu();	
		}	

		else if ( choice == 'c' )
		{
			// create pair
			pair< string, string > userPair;
			// variable to store new password
			string newPass;	

			cout<<"Enter username: ";

			// read in first element
			cin >> userPair.first;

			cout<<"\nEnter password: ";

			//read in second element
			cin>>userPair.second;


			cout<<"\nEnter new password: ";

			// read in new password
			cin >> newPass;

			// if password is successfully changed output success
			if ( ps.changePassword( userPair , newPass ) )
				cout<<"\nPassword changed for user " << userPair.first;
			// error encountered
			else
				cout<<"\n*****Error: Could not change user password.";
			//print menu
			Menu();
		
		}	

		else if ( choice == 'f' )
		{
			// variable to store username
			string user;
		
			cout<<"\nEnter username: ";
			cin >> user;
		
			// if user is found in hash table output success
			if ( ps.find( user ) )
				cout<<"\nUser '" << user <<"' found.";

			// error encountered
			else
			 	cout<<"\nUser '" << user <<"' not found.";

			// print menu
			Menu();
			
		}

		else if ( choice == 'd' )
		{
			// call dump function
			ps.dump();

			// print menu
			Menu();	
			
		}

		else if ( choice == 's' )
		{
			// call size function and print value
			cout<<"\nSize of hashtable:" << ps.size();
			// print menu
			Menu();		
		}

		else if ( choice == 'w' )
		{
			// string to store user entered filename
			string f;

			cout<<"\nEnter password file name to write to: ";
			cin >> f;

			// convert to char* and call function
			ps.write_to_file( f.c_str() );

			// print menu
			Menu();
		}

		else if ( choice == 'x' )
		{
			// break from loop and exit program
			break;
		}

		else
		{
			// error encountered in user entry
			cout<<"*****Error: Invalid entry. Try again.\n";

			// print menu
			Menu();
		}
	}
}	
