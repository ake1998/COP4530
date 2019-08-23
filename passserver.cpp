/**Name: Ashley Ellis
 * Course: COP4540-0001
 * Assignment: Project 5
 * Due date: April 19, 2019
 */

#include "passserver.h"

using namespace cop4530;

// constructor, create a hash table of the specified size.
//   You just need to pass this size parameter to the 
//   constructor of the HashTable.  Therefore, the real
//   hash table size could be different from the parameter size
//   ( because prime_below() will be called in the constructor
//   of HashTable
PassServer::PassServer( size_t size ) : HashTable<std::string, std::string>(size)
{ }

// destructor.
PassServer::~PassServer()
{ }

// load a password file into the HashTable object.  Each
// line contains a pair of username and encrypted password.
bool PassServer::load( const char *filename )
{
	return HashTable<std::string,std::string>::load( filename );
}

// Add a new username and password.  The password passed in is in plaintext,
// it should be encrypted before insertion.  The pair should not be added if
// the username already exists in the hashtable.
bool PassServer::addUser( std::pair<std::string, std::string> &kv )
{
	// encrypt the password before adding to hash table
	std::pair< std::string, std::string > encryptedkv = std::make_pair( kv.first, encrypt( kv.second ) );
	if( HashTable< std::string, std::string >::insert( encryptedkv ) )
		return true;
		
	else
	// user is not added to hash table
		return false;
}

// Move version.
bool PassServer::addUser( std::pair< std::string, std::string > && kv )
{
	return addUser( std::move( kv ) );	
}

// delete an existing user with username k
bool PassServer::removeUser( const std::string &k )
{
	return HashTable< std::string, std::string >::remove( k );
}

// change an existing user's password.  Note that both passwords
// passed in are in plaintext.  They should be encrypted before you
// interact with the hashtable.  If the user is not in the hash
// table , return false.  If p.second does not match the current
// password , return false.  Also return false if the new password
// and new password are the same (i.e., we cannot update the 
// password.
bool PassServer::changePassword( const std::pair< std::string, std::string > &p, const std::string &newpassword )
{
	std::pair< std::string, std::string > encryptedkv = std::make_pair( p.first, encrypt( p.second ) );

	if ( HashTable< std::string, std::string >::match( encryptedkv )  )
	{
		if ( p.second != newpassword )
		{
			std::pair< std::string, std::string > newkv = std::make_pair( p.first, encrypt( newpassword ) );
			HashTable< std::string, std::string >::insert( newkv );

			return true;
		}
		
		else
			return false;
	}

	else
		return false;
}

// check if a user exists ( if the user is in the hash table )
bool PassServer::find( const std::string &user ) const
{
	return HashTable< std::string, std::string >::contains( user );
}

// show the structure and contents of the HashTable object
// to the screen.  Same format as dump() function in the HashTable class
// template
void PassServer::dump()
{
	HashTable< std::string, std::string >::dump();
}

//Return the size of the HashTable (the number of username/password pairs in the table
size_t PassServer::size() const
{
	return HashTable< std::string, std::string >::size();
}

// Save the username and password combination into a file.  Same format as the
// write_to_file() function in the HashTable class template.
bool PassServer::write_to_file( const char *filename ) const
{
	return HashTable< std::string, std::string >::write_to_file( filename );
}

// Encrypt the parameter str and return the encrypted string
std::string PassServer::encrypt( const std::string &str ) 
{
	// variables to store aspects of password
	char *salt=nullptr, *dollarSign=nullptr, *passWord=nullptr;

	// copy salt charactes into salt variable
	strcpy( salt,"$1$########");

	// third dollar sign
	strcpy( dollarSign, "$");
	
	// copy dollar sign onto the salt
	strcpy( salt, dollarSign );

	// copy into the password after encryption
	strcpy( passWord, crypt( str.c_str(), salt ) );
	
	// store in string
	std::string pw ( passWord );
	
	// password only contains the last 22 characters
	pw = pw.substr( 12, 33 );

	// return encrypted string
	return pw; 

}

