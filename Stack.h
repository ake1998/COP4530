/**Name: Ashley Ellis
 * Course: COP4530-0001
 * Assignment: Project 3
 * Due Date: March 8, 2019
 */

#include<iostream>
#include<vector>
namespace cop4530 {
	template <typename T>
		class Stack{

			public:
				//constructor, destructor, copy constructor
				Stack();	//zero-parameter constructor
				~Stack();	//destructor
				Stack(const Stack<T> & rhs);	//copy constructor
				Stack(Stack<T> && rhs);	//move constructor

				//copy assignment operator
				Stack<T>& operator=( const Stack<T> &);
				//move assignment operator
				Stack<T> & operator=( Stack<T> &&);

				bool empty() const;	//check if stack is empty
				void clear();		//deletes all elements from the stack
				void push(const T& x);	//adds x to the stack.. copy version
				void push( T&& x);	//adds x to the stack.. move version
				void pop();		//removes and discards most recently added element of the stack
				T& top();		//mutator that returns a reference to the most
							//recently added element of the stack
				const T& top() const;	// accessor the returns the most recently added element of the stack
				int size() const;	//returns the number of elements in the stack
				void print(std::ostream &os, char ofc = ' ') const;	//prints elements of Stack to ostream os
											//ofc is the separator between elements in
											//the stack when they are printed out
				private:
					std::vector<T> stackVector;

		};

	//overloading insertion operator
	template <typename T>
		std::ostream& operator<<(std::ostream &os, const Stack<T> &a);	//invokes print() method to print the Stack<T> a
										//in the specified ostream
	template<typename T>
		bool operator==(const Stack<T> &, const Stack<T> &);		//returns true if two compared Stacks have the
										//same elements in the same order
	template <typename T>
		bool operator!=(const Stack<T> &, const Stack<T> &);		//opposite of operator==

	template <typename T>
		bool operator<=(const Stack<T> &a, const Stack<T> &b);		//returns true if every element in Stack a is smaller
										//than or equal to the corresponding element of Stack b
	//include implementation file here
#include"Stack.hpp"
}	//end of namespace 4530
