/**Name: Ashley Ellis
 * Course: COP4530-0001
 * Assignment: Project 5
 * Due date: April 19, 2019
 */
#include<iostream>
#include<cstring>
#include<crypt.h>
#include "hashtable.h"

namespace cop4530{
	class PassServer : public HashTable<std::string, std::string>
	{
		public:
			PassServer( size_t size = 101 );
			~PassServer();
			bool load( const char *filename );
			bool addUser( std::pair<std::string, std::string> &kv );
			bool addUser( std::pair<std::string, std::string> &&kv );
			bool removeUser( const std::string &k );
			bool changePassword( const std::pair< std::string, std::string > & p, const std::string &newPassword );
			bool find( const std::string &user ) const;
			void dump( );
			size_t size() const;
			bool write_to_file( const char *filename ) const;
			
		private:
			std::string encrypt( const std::string &str );
	};
}
