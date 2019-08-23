/** Name: Ashley Ellis
* Course: COP4530-0001
* Assignment: Project #3
* Due Date: March 8, 2019
*/

using namespace std;

template< typename T >
// Default zero-parameter instructor
 Stack< T >:: Stack() : stackVector( )
{ }
template< typename T >
Stack< T >::~Stack()
// Destructor
{ clear( ); }

template< typename T >
Stack< T >::Stack(const Stack<T> & rhs)
// Copy constructor
{ stackVector = rhs.stackVector; }

template< typename T >
Stack< T >::Stack(Stack<T> && rhs) : stackVector{rhs.stackVector}
// Move constructor
{ rhs.stackVector = std::vector<T>(); }

template< typename T >
bool Stack< T >::empty() const
{ return (size()==0);}

template< typename T >
void Stack< T >::clear()
{
  while(!empty())
    pop();
}

template< typename T >
void Stack<T>::push(const T& x)
{ stackVector.push_back(x); }

template< typename T >
void Stack< T >::push( T&& x)
{ stackVector.push_back(std::move(x)); }

template< typename T >
void Stack<T>::pop()
{ stackVector.pop_back(); }

template< typename T >
T& Stack< T >::top()
{ return (stackVector.back()); }

template< typename T >
const T& Stack<T>::top() const
{ return (stackVector.back()); }

template< typename T >
int Stack< T >::size() const
{  return (stackVector.size()); }

template< typename T >
void Stack< T >::print(std::ostream& os, char ofc) const
{
	Stack< T > temp = *this;
	
	while(!(temp.empty()))
	{
		os << temp.top();
		os << ofc;
		temp.pop();
	}
}

template< typename T >
Stack< T >& Stack<T>::operator=(const Stack<T> & rhs)
{
  Stack< T > temp = rhs;
  std::swap(*this, temp);
	return *this;
}

template< typename T >
Stack<T>&  Stack< T >::operator=(Stack< T >  && rhs)
{ std::swap(stackVector, rhs.stackVector);
	return *this;
 }

template< typename T >
std::ostream& operator<<(std::ostream& os, const Stack< T > &a)
{
	a.print(os);

	return os;
}

template< typename T >
bool operator==(const Stack< T > &a, const Stack< T > &b )
{
    Stack<T> tempA = a, tempB = b;

    while( !(tempA.empty()) && !(tempB.empty()))
    {
        if( tempA.top() != tempB.top())
          return false;

        tempA.pop();
        tempB.pop();
    }

    return true;
}

template< typename T >
bool operator!=( const Stack<T> & a, const Stack<T> &b)
{ return !(a==b); }

template< typename T >
bool operator<=( const Stack< T > &a, const Stack<T> & b)
{
  if( a==b )
    return true;

  else{
      Stack<T> tempA = a, tempB = b;

      while( !(tempA.empty()) && !(tempB.empty()))
      {
          if ( tempA.top() > tempB.top())
            return false;

          tempA.pop();
          tempB.pop();
      }
  }
  return true;
}
