/**Name: Ashley Ellis
 * Course: COP4530 - 0001
 *Assignment: Project 2
 *Due date: February 15, 2019
*/
using namespace std;

template< typename T>
List< T >::const_iterator::const_iterator()
/**default zero parameter constructor
sets current to nullptr*/
{ current = nullptr;}

template< typename T>
const T& List< T >::const_iterator::operator*() const
/**returns reference to the corresponding element in the
list by calling retrieve() function*/
{  return retrieve( ); }

template< typename T>
typename List<T>::const_iterator& List< T >::const_iterator::operator++()
// prefix increament operator
{
	current = current->next;
	return *this;
}

template< typename T>
typename List<T>::const_iterator List< T >::const_iterator::operator++(int)
//postfix increment operator
{
	const_iterator old = *this;
	++(*this);
	return old;
}

template< typename T>
typename List<T>::const_iterator& List< T >::const_iterator::operator--()
//prefix increment operator
{
	current = current->prev;
	return *this;
}

template< typename T>
typename List<T>::const_iterator List< T >::const_iterator::operator--(int)
//postfix increment operator
{
	List<T>::const_iterator old = *this;
	--*this;
	return old;
}

template< typename T>
bool List< T >::const_iterator::operator==(const List<T>::const_iterator & rhs) const
//compares two iterators and returns true if iterators point to the same element
{
			return current == rhs.current;
}

template< typename T >
bool List< T >::const_iterator::operator!=(const List<T>::const_iterator & rhs) const
/**compares two iterators and returns true if they point to different elements
calls operator== to see if they are equal and returns opposite value */
{  return !(*this == rhs);  }

template< typename T>
T& List< T >::const_iterator::retrieve() const
//returns a reference to the corresponding element in the list
{  return current->data; }

template< typename T >
List< T >::const_iterator::const_iterator(Node* p)
//one-parameter constructor that sets pointer current equal to the given node pointer p
{  current = p;  }

template< typename T >
List< T >::iterator::iterator( )
//default zero-parameter constructor
{ }

template< typename T >
T & List<T>::iterator::operator*()
/** returns a reference to the corresponding element in the list by calling retrieve
function from const_iterator */
{   return const_iterator::retrieve();  }

template< typename T >
const T& List< T >::iterator::operator*( ) const
/**returns const reference to the corresponding element in the list
by calling operator* from const_iterator */
{   return const_iterator::operator*();  }

template< typename T >
typename List<T>::iterator& List< T >::iterator::operator++()
//prefix increment operator
{	this->current = this->current->next; }

template< typename T >
typename List<T>::iterator List< T >::iterator::operator++(int)
//postfix increment operator
{
	iterator old = *this;
	++( *this );
	return old;
}

template< typename T >
typename List<T>::iterator& List< T >::iterator::operator--()
//prefix decrement operator
{  this->current = this->current->prev; }

template< typename T >
typename List<T>::iterator List< T >::iterator::operator--(int)
//postfix decrement operator
{
	iterator old = *this;
	--*this;
	return old;
}

template<typename T>
List<T>::iterator::iterator(Node * p ) : const_iterator::current{ p }
//one-parameter constructor to set current equal to given node pointer p
{ }

template< typename T >
List< T >::List()
/** default zero parameter constructor that calls init() function
to initialize list member functions */
{  init( );  }

template< typename T >
List< T >::List( const List &rhs )
/** Copy constructor that creates new list using elements
in existing list rhs */
{
	init( );
	for( auto & x = rhs.begin( ): x != rhs.end( ) )
		push_back( x );
}

template< typename T >
List< T >::List( List &&rhs ): theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
//move constructor
{
	rhs.theSize = 0;
	rhs.head = nullptr;
	rhs.tail = nullptr;
}

template< typename T >
List< T >::List(int num, const T & val)
/** Constructs a list with num elements, all initialized with value val */
{
			init( );

			iterator itr = begin( );
			for(auto x = begin( ): x != end ( ) )
						push_front( val );
}

template< typename T >
List< T >::List(const_iterator start, const_iterator end)
/** constructs a List with elements from another list between start and end.
Including the element referred to by the start iterator, but not the end
iterator, that is [start, end) */
{
			init( );
			for(auto x = begin( ): x != end( ))
						push_front( x );
			pop_front( );
}

template< typename T >
List< T >::~List()
//desctructor
{
	clear( );
	delete head;
	delete tail;
}

template< typename T >
const List<T>& List< T >::operator=(const List &rhs)
//copy assignment operator
{
	List copy = rhs;
	std::swap( *this, copy );
	return *this;
}

template< typename T >
List<T>& List< T >::operator=(List &&rhs)
//move assignment operator
{
	std::swap( theSize, rhs.theSize);
	std::swap( head, rhs.head );
	std::swap( tail, rhs.tail );

	return *this;
}

template< typename T >
int List< T >::size() const
//returns the number of elements in the list
{  return theSize; }

template< typename T >
bool List< T >::empty() const
//returns true if List size is 0 and false otherwise
{  return size( ) == 0;  }

template< typename T >
void List< T >::clear()
//deletes all the elements in the list
{
		while( !empty ())
			pop_front( );
}

template< typename T >
void List< T >:: reverse()
/** reverses the order of the elements in the list.  That is,
the original first element becomes the last, while the last
becomes the first */
{
					current = head;
					prev = nullptr;
					next = nullptr;

					while( current != nullptr )
					{
							next = current->next;
							current->next = prev;
							prev = current;
							current = next;
					}

					head = prev;
}
template< typename T >
T& List< T >::front()
//returns reference to the first element
{  return *begin (); }

template< typename T >
const T& List< T >::front() const
//returns const reference to the first element
{  return *begin();  }

template< typename T >
T& List< T >::back()
//returns reference to the last element
{  return *--end();  }

template< typename T >
const T &  List< T >::back() const
//returns const reference to the last element
{  return *--end();  }

template< typename T >
void List< T >::push_front(const T&val)
//inserts val at the be first position of the list
{ insert( begin(), val); }

template< typename T >
void List< T >::push_front(T && val)
//move version
{  insert( begin(), std::move(val));  }

template< typename T >
void List< T >::push_back(const T& val)
//inserts val at the last position of the list
{  insert( end(), val); }

template< typename T >
void List< T >::push_back(T && val)
//move version
{  insert(end(), std::move(val)); }

template< typename T >
void List< T >::pop_back()
//deletes last element in the list
{  erase( --end());  }

template< typename T >
void List< T >::pop_front()
//deletes first element in the list
{  erase(--begin());  }

template< typename T >
void List< T >::remove(const T & val)
/** removes nodes equal to val from the list */
{
	for(List<T>::iterator itr = begin(); itr != end(); ++itr)
	{
		if (itr.current->data == val)
			erase(itr);
	}
}

template< typename T >
void List< T >::print(std::ostream &os, char ofc) const
/** prints all elements in the list, using character ofc as the delimiter
between elements */
{
	for(List<T>::const_iterator itr = begin(); itr != end(); ++itr)
	{
		os << itr.current->data << ofc;
	}
}

template< typename T >
typename List<T>::iterator List< T >::begin()
//returns iterator to the first element of the list
{  return { head->next }; }


template< typename T >
typename List<T>::const_iterator List< T >::begin() const
//returns const_iterator to the first element of the list
{  return { head->next };  }

template< typename T >
typename List<T>::iterator List< T >::end()
//returns iterator to the last element of the list
{  return { tail };  }

template< typename T >
typename List<T>::const_iterator List< T >::end() const
//returns const_iterator to the last element of the list
{ return { tail }; }

template< typename T >
typename List<T>::iterator List< T >::insert(iterator itr,const T & val)
/** inserts value val ahead of the node referred to by itr */
{
				Node *p = itr.current;
				theSize++;
				return { p->prev = p->prev->next = new Node{ val, p->prev, p } };
}

template< typename T >
typename List<T>::iterator List< T >::insert(iterator itr, T && val)
//move version
{
			Node *p = itr.current;
			theSize++;
			return { p->prev = p->prev->next = new Node{std::move(val), p->prev, p} };
}

template< typename T >
typename List<T>::iterator List< T >::erase(iterator itr)
//deletes the node referred to by itr
{
			Node *p = current;
			iterator returnValue{ p->next };
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
			theSize--;

			return returnValue;
}

template< typename T >
typename List<T>::iterator List< T >::erase(iterator start, iterator end)
/**Deletes all nodes between start and end, including start but not end, all
elements in the range [start,end ) */
{
			for ( iterator itr = start; itr != end)
					itr = erase( itr );

			return end;
}

template< typename T >
void List< T >::init()
//initialize member variables of the list
{
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
}

template < typename T >
bool operator==(const List<T> & lhs, const List<T> & rhs)
/** Check if two lists contain the same sequence of elements.
Two lists are equal if they have the same size and the elements at the
corresponding position are equal */
{
			if(lhs.size() != rhs.size())
						return false;


			else
			{
								iterator itr;
								for(auto x = lhs.begin(); x != lhs.end())
								{
										if(*lhs == *rhs)
													++itr;
										else
												return false;
								}
			}

			return true;
}

template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs)
//opposite of operator==()
{
			if(lhs == rhs)
						return false;

			return true;
}

template <typename T>
std::ostream& operator<<(ostream & os, const List<T> & l)
//print out all elements in list l by calling List<T>::print() function
{
						l.print(os);
						return os;
}
