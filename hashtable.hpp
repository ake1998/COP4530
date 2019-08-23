/**Name: Ashley Ellis
 * Course: COP4530-0001
 * Assignment: Project 5
 * Due date: April 19, 2019
 */

// constructor.
// Create a hashtable where the size of the vector is sete to prime_below(size)
// ( where size is default to 101 ), where prime_below() is a private member function
//  of the HashTable and provided to you
template <typename K, typename V>
HashTable<K,V>::HashTable(size_t size) : theLists{ prime_below(size) }, sizeOf{0}
{ }

// destructor.
// Delete all elements in hash table
template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
	clear( );
}

// Check if key k is in the hash table
template <typename K, typename V>
bool HashTable<K, V>::contains( const K &k ) const
{
	// variable to store return value
	bool flag;
	
	// if size is 0 then k is not in the hash table
	if ( size() == 0 )
		return false;

	// iterates through hash table and looks for the first element of pair
	for( auto thisList : theLists )
	{
		typename std::list< std::pair< K, V> >::iterator itr;
		// iterates through list to look for first element in the current list
		for( itr = thisList.begin( ) ; itr != thisList.end( ); ++itr )
		{
			if ( (*itr).first == k )
			{
				// k is in the hash table and break from loop
				flag = true;
				break;
			}
			else
				flag = false;
		}
	}
	
	return flag;
}

// Check if key-value pair is in the hash table
template<typename K, typename V>
bool HashTable<K, V>::match( const std::pair<K, V> &kv ) const
{
	// variable to store return value
	bool flag;

	if ( size() == 0 )
		return false;

	// iterate through the hash table
	for( auto thisList : theLists )
	{
		// create iterator
		typename std::list< std::pair< K, V>>::iterator itr;

		// iterate through list to look for the pair
		for( itr = thisList.begin( ) ; itr != thisList.end( ); ++itr ) 
		{
			// first elements match
			if( (*itr).first == kv.first )
			{	
				// second elements match
				if ( (*itr).second == kv.second )
				{
					// change flag and break from loop
					flag = true;
					break;
				}
				
			}	
			else
			// pair not in the hash table
				flag = false;
		}
	}
	
	return flag;
}

// add the key-value pair kv into the hash table.  Don't
// add if kv is already in the hash table.  If the key is the hash
// table but with a different value, the value should be updated 
// to the new one with kv.  Return true if kv is inserted or value
// is updated; return false otherwise ( i.e., if kv is in the hash
// table
template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair< K, V> &kv )
{
	auto& whichList = theLists[ myhash( kv.first ) ];

	// if first element is already in the list then don't insert it
	if ( contains( kv.first ) )
		return false;

	// insert into the hashtable
	whichList.push_back( kv );

	// rehash
	if ( ++sizeOf > theLists.size( ) )
		rehash( ); 

	return true;
}

// move version of insert
template <typename K, typename V>
bool HashTable<K, V>::insert( std::pair< K, V> &&kv )
{	
	auto& whichList = theLists[ myhash( kv.first ) ];

	// if first element is already in the list then don't insert it
	if ( contains( kv.first ) )
		return false;

	// insert into the hashtable
	whichList.push_back( std::move(kv) );

	// rehash
	if ( ++sizeOf > theLists.size( ) )
		rehash( ); 

	return true;
}

// delete the key k and the corresponding value if it is in
// the hash table.  Return true if k is deleted, return false
// otherwise (i.e., if key k is not in the hash table).
template <typename K, typename V>
bool HashTable<K, V>::remove( const K &k )
{
	auto& whichList = theLists[myhash( k )];

	typename std::list<std::pair<K, V> >::iterator itr;

	// if k is not in the hash table it cannot be removed
	if ( !contains( k ) )
		return false;

	// iterate through list to find the element
	for( itr = whichList.begin( ) ; itr != whichList.end(   ); ++itr )
	{
		// dereference to compare to k
		if( (*itr).first == k )
		{
			// If this doesnt work then move erase line into loop
			break;
		}
	}

	// false if it is equal to iterator at end of list
	if ( itr == whichList.end( ))
		return false;

	// erase from list and decrement size
	whichList.erase( itr );
	--sizeOf;
	
	return true;
}

// delete all elements of the hash table
template <typename K, typename V>
void HashTable<K, V>::clear()
{
	makeEmpty( );
}

// load the content of the file with name filename into the hash table.  In the file,
// each line contains a single pair of key and value, separated by a white
// space.
template <typename K, typename V>
bool HashTable<K, V>::load( const char* filename )
{
	std::ifstream in;
	
	// open the file	
	in.open( filename );
	
	std::string str;
	// read in file elements
	while( std::getline( in, str ) )
	{
		// create variables to store in the pai
		std::string userName, passWord;
		// read in username until the space
		std::getline( in, userName,' ');
		//read in password
		std::getline( in, passWord);
		// create pair with the elements
		std::pair< std::string, std::string> input = std::make_pair( userName, passWord );	
		
		// insert into the hashtable
		insert( input );
	}

	// close the file
	in.close();

	return true;
	
}

// display all entries in the hash table.  If an entry contains multiple
// key-value pairs, separate them by a semicolon character
template <typename K, typename V>
void HashTable<K, V>::dump( ) const
{
	// iterate through table
	for( auto& thisList : theLists )
	{
		int i = 0;
		// iterate through list
		for( auto& kvp : thisList )
		{	// output put first element and second element of pair separated by space
			std::cout << kvp.first << " " << kvp.second;
			++i;

			// output semicolon if there are multiple key-value pairs
			if ( i > 1 )
				std::cout <<";";
		}
	}  
}

// return the number of elements in the hash table
template <typename K, typename V>
size_t HashTable<K, V>::size() const
{	return sizeOf;	}

// write all elements in the hash table into a file with name filename.
// similar to the file file format in the load functon, each line
// contains a pair of key-value pair, separated by a white space.
template <typename K, typename V>
bool HashTable<K, V>::write_to_file( const char *filename ) const
{
	std::ofstream out;
	// open the file
	out.open( filename );

	// iterate through table
	for( auto &thisList : theLists )
	{
		// iterate through list
		for( auto &kvp : thisList )
			// send to the output file and separate by a white space
			out << kvp.first << " " << kvp.second << std::endl;
	}
	
	// close the file
	out.close();

	return true;
	
}

// delete all elements in the hash table. The public interface
// clear() will call this function
template <typename K, typename V>
void HashTable<K, V>::makeEmpty()
{
	// Iterates through vector and clears each individual list
	for( auto& thisList : theLists )
		thisList.clear();
}

// Rehash function.  Called when the number of elements in the hash 
// table is greater than the size of the vector.
template <typename K, typename V>
void HashTable<K, V>::rehash()
{
	std::vector<std::list<std::pair<K,V> > > oldLists = theLists;

	// Create new double-sized, empty table
	theLists.resize( prime_below( 2*theLists.size() ) );

	makeEmpty( );

	// Copy table over
	sizeOf = 0;
	for ( auto& thisList : oldLists )
	{
		for ( auto& x : thisList )
			insert( std::move( x ) );
	}
}

// Return the index of the vector entry where k should be stored
template <typename K, typename V>
size_t HashTable<K, V>::myhash( const K &k ) const
{
	// create the variable for the index
	size_t index = 0;
	
	// create the hash
	static std::hash<K> h;

	// mod the hash( key ) by the size of the list
	index = h( k ) %  theLists.size();

	return index;
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
  {
	if (vprimes[i] == 1)
		for(j = i + i ; j < n; j += i)
			vprimes[j] = 0;
  }
}
