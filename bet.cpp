/** Name: Ashley Ellis
 * Course: COP4530-0001
 * Project 4: Binary Tree and Its Application
 * Due date: April 5, 2019
 * */
#include "bet.h"
// Default constructor
BET::BET() : root{nullptr}
{}

/** One-parameter constructor, where parameter "postfix" is a string
 * containing a postfix expression.  The tree should be built based on
 * the postfix expression.  Tokens in the the postfix expression are 
 * separated by a space.*/
BET::BET(const std::string postfix) : root{nullptr}
{ buildFromPostfix( postfix );   }

// Copy constructor
BET::BET(const BET& b) : root{ nullptr }
{
	if ( !empty( ) )
	{
		clear( );
	}

	root = clone( b.root );
	betStack.push( root );
	
}

// Destructor
BET::~BET()
{
	makeEmpty( root );
	clear( );

}

/** Parameter "postfix" is string containing a postfix expression.  The tree should be built based on the postfix 
 * expression.  Tokens in the postfix expression are separated by a space.  If the tree contains nodes before the
 *  function is called, you need to first delete the existing nodes.  Return true if the new tree is built successfully.  
 *  Return false if an error is encountered. */
bool BET::buildFromPostfix(const std::string postfix)
{	
	// Error checking for tree
	if ( !betStack.empty( ) )
	{ 
		makeEmpty( root ); 
		clear( );
	}

	// Initialize token string
	string token ="";

	// Loop to go through parameter string
	for( unsigned int i = 0 ; i < postfix.length() ; ++i)
	{
		// Add characters to the token
		token += postfix[i];

		// Make sure last character is an operator
		if ( i == postfix.length()-1 )
		{
			if ( postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '+' || postfix[i] == '-' )
			{	
				// Create left and right children
				BET::BinaryNode *leftTemp, *rightTemp;
			
				if ( !betStack.empty() )
				{
					// Set the top to right child
					rightTemp = betStack.top();
					betStack.pop();	

					// Error check
					if ( !betStack.empty() )
					{
						// Set the top to left child
						leftTemp = betStack.top();
						betStack.pop();
					}

					else
					{	return false;  }
				}

				else
				{	return false; }

				// Create temporary Node and add the left and right children
				BET::BinaryNode *rootTemp = new BET::BinaryNode( token, leftTemp, rightTemp ); 

				// Push Node to the stack
				betStack.push( rootTemp );
			}

			else
				return false;
		}
		else
		{
			// So spaces aren't pushed to the stack
			if ( postfix[i] == ' ' )
			{
				token.pop_back();
				
				// Reset token
				token = "";
			}
			
			else
			{
				// Is an operator
				if( postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '+' || postfix[i] == '-' )
				{
					// Temporary child nodes
					BET::BinaryNode *leftTemp, *rightTemp;

					// Error check
					if ( !betStack.empty() )
					{
						// Set top element as the right child **/
						rightTemp = betStack.top();
						betStack.pop();

						// Error check
						if ( !betStack.empty() )
						{
							// Set top element as the left child
							leftTemp = betStack.top();
							betStack.pop();
						}

						else
						{	return false; }
					}

			
					else
					{	return false; }

					// Temporary Node to create and store left and right children under
					BET::BinaryNode *rootTemp = new BET::BinaryNode( token, leftTemp, rightTemp );
				
					// Push to the stack
					betStack.push( rootTemp );

				}
				// Is an operand
				else
				{
					// Create new node
					// Operands should not have children
					BET::BinaryNode *tempNode = new BET::BinaryNode( token, nullptr, nullptr );
				
					// Push to the stack
					betStack.push( tempNode );
				}
			}
		
		}
				
	
	}
	// Make sure the size of stack isn't greater than 1
	if ( betStack.size() > 1 )
	{	return false;	}
	
	else
	{
		// Last token to be added is the root of the binary expression tree
		root = betStack.top();
	}

	// Binary expression tree successfully created
	return true;
}

// Assignment operator
const BET& BET::operator=(const BET& b)
{
	// Empties current stack contents
	if( !empty( )  )
	{
		clear( );
	}

	// Reinitializes the root
	root = b.root;

	// Pushes root to the stack
	betStack.push( b.root );
	
	return *this;
}

/** Call the private version of the printInfixExpression function to print out the infix expression. */
void BET::printInfixExpression()
{
	printInfixExpression( root );
}

/** Call the private version of the printPostfixExpression function to print out the postfix expression.*/
void BET::printPostfixExpression()
{
	printPostfixExpression( root );
}

/** Call the private version of the size function to return the number of nodes in the tree.*/
size_t BET::size()
{
	return size( root );
}

/** Call the private version of leaf_nodes function to return the number of leaf nodes in the tree.*/
size_t BET::leaf_nodes()
{
	return leaf_nodes( root );
}

/** Return true if empty.  Return false otherwise.*/
bool BET::empty()
{
	if ( size() == 0 )
	// If there are no nodes then the stack is empty
		return true;
	return false;
}

// Private interfaces
// Must be implemented recursively

/** Print to the standard output the corresponding infix expression note the you may need to add 
 * parentheses depending on the precedence of operators.  You should not have unnecessary parentheses.*/
void BET::printInfixExpression(BET::BinaryNode *n)
{
	// Error check
	if ( n != nullptr )
	{
		// If the node is not the root, there needs to be parentheses
		if ( (n->data == "*" || n->data == "/" || n->data == "+" || n->data == "-") && n != root )
			cout << "( ";
		// Recursion for left child
		printInfixExpression( n->left );

		// Print data
		cout<< n->data << " ";

		// Recursion for right child
		printInfixExpression( n->right );

		// Close parentheses
		if ( (n->data == "*" || n->data == "/" || n->data == "+" || n->data == "-") && n != root )
			cout << ") ";
	}
}

/** Delete all nodes in the subtree pointed to by t.  Called by functions such as the destructor.*/
void BET::makeEmpty(BET::BinaryNode* &t)
{

	if ( t != nullptr )
	{
		// Check child nodes first and delete them before parent
		makeEmpty( t->left );
		makeEmpty( t->right );

		// Delete the pointer
		delete t;
	}

	// Make node point to null value
	t = nullptr;
}

/** Clone all nodes in the subtree pointed to by t.  Called by functions such
 * as the assignment operator=.*/
BET::BinaryNode* BET::clone(BET::BinaryNode *t) const
{
	if ( t == nullptr )
	// Returns a null value for already null pointers
	{
		return nullptr;
	}

	else
	// Creates the node and recursively calls to create children
		return new BET::BinaryNode{ t->data, clone( t->left ), clone( t->right ) } ; 

}

/** Print to standard output the corresponding postfix expression.*/
void BET::printPostfixExpression(BET::BinaryNode* n)
{
	// Error check
	if( n != nullptr )
	{
		// Recursion to print left child
		printPostfixExpression(n->left);

		// Recursion to print right child
		printPostfixExpression(n->right);

		// Print data stored in the node	
		cout<<n->data<<" ";
	}
}

/** Return the number of nodes in the subtree pointed to by t.*/
size_t BET::size(BET::BinaryNode *t)
{
	if ( t == nullptr )				// If t holds null value, then there is no node
		return 0;

	else						// Else look at node and its children
		return 1 + size( t->left ) + size( t->right );
	
}

/** Return the number of leaf nodes in the subtree pointed to by t.*/
size_t BET::leaf_nodes( BET::BinaryNode *t )
{
	if ( t == nullptr )				// If t holds null value, then there is no node to evaluate
		return 0;

	if ( leaf_nodes( t->left ) == 0 && leaf_nodes( t->right ) == 0 )	//if both return 0, then t is a leaf
		return 1;

	else									
	// In case where left or right child is either both not null or one is null 
	{
		return 0 + leaf_nodes( t->left ) + leaf_nodes( t->right );
	}
}  

void BET::clear()
{
	while ( ! empty( ) )
	{
		betStack.pop();
	}
}
