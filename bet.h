/** Name: Ashley Ellis
 * Course: COP4530-0001
 * Assignment: Project 4: Binary Tree and Its Application
 * Due date: April 5, 2019
 **/

#include<stack>
#include<string>
#include<iostream>

using namespace std;

	class BET{
		private:
			struct BinaryNode{
				string data;
				BinaryNode *left;
				BinaryNode *right;
				
				// Constructors
				BinaryNode() : left{nullptr}, right{nullptr} {}
				BinaryNode( const std::string& d, BinaryNode *l, BinaryNode *r ) : data{d}, left{l}, right{r} {}					
				};

		public:
			BET();								// Default zero-parameter constructor
			BET( const std::string postfix );					// One-parameter constructor
			BET( const BET& );						// Copy constructor
			~BET( );							// Destructor
			bool buildFromPostfix(const std::string postfix);			// Build tree based upon postfix expression
			const BET& operator=(const BET& );				// Assignment operator
			void printInfixExpression();					// Call private version to print
			void printPostfixExpression();					// Call private version to print
			size_t size();							// Call private version
			size_t leaf_nodes();						// Call private version
			bool empty();							// Return true if tree is empty, returns false otherwise
			void clear();							// Clears the stack
		private:
			void printInfixExpression(BET::BinaryNode *n);			// Print to standard output the infix expression
			void makeEmpty(BET::BinaryNode* &t);					// Delete all nodes in the subtree pointed to by t, called by destructor
			BET::BinaryNode* clone(BET::BinaryNode *r) const;				// Clone all of the nodes in the subtree pointed to by t, called by operator=
			void printPostfixExpression(BET::BinaryNode* n);			// Print to the standard output the corresponding postfix expression
			size_t size(BET::BinaryNode *t);					// Return the number of nodes in the subtree pointed to by t
			size_t leaf_nodes(BET::BinaryNode *t);				// Return number of leaf nodes in the subtree pointed to by t

			stack<BET::BinaryNode*> betStack;					// Contain the tree
			BET::BinaryNode *root;						// Points to tree root


};

