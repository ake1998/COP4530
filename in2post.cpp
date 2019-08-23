/** Name: Ashley Ellis
 * Course: COP4530-001
 * Assignment: Project 3
 * Due date: March 8, 2019
 */

#include "stack.h"
#include <string>
#include<vector>
#include<cmath>
#include<cctype>

using namespace std;
using namespace cop4530;

void calculateExpression(Stack<string> opS, int e);
void postFixExpression(std::vector<string> v);

int main()
{
	string expression;										// stores current expression
	std::vector<string> infix;									// Space separated strings
	char c;												// stores individual character

	// Prompts user for infix expression
	cout<< "Enter the infix expression(\"exit\" to quit): ";

	// If expression is "exit" stay out of loop
	while ( expression != "exit" && cin.get(c))
	{
		if( c == ' ' )
		{
				infix.push_back(expression);						//Add expression to vector
				expression = "";							// Empty the expression

		}
		else if ( c == '\n' )
		{
			infix.push_back(expression);							// Add expression to vector
			postFixExpression(infix);
			expression = "";								// Empty the expression
			infix.clear();									// Clear the vector
		}

		else if ( c == '(' || c == ')')
		{
			string temp = "";								// Initialize empty temp string
			temp += c;									// Add the parentheses to the string
			infix.push_back(temp);								// Add individual parentheses to the vector
		}

		else
		{  expression += c; }									// Concatenate expression
	}

		return 0;
}


void postFixExpression(std::vector<string> v)
// Outputs the postfix expression
{
	Stack<string> postStack;									// Stack to store postfix
	Stack<string> operandStack;									// Stack to send to evaluation
	int numParens =0, error = 0;									// Holds number of parentheses. and type of error occurring
	cout<<"\nPostfix expression: ";

	for(unsigned int i = 0; i < v.size()-1; ++i)
	{
			// Conditionals for what each string consists of
			if ( v[i] == "(" )								
			{
				postStack.push(v[i]);
				operandStack.push(v[i]);
				numParens++;
			}

			else if (v[i] == "*" || v[i] == "/" || v[i] == "+" || v[i]== "-")
			{
				if(v[i] == "*" || v[i] == "/" )
				{
					while( !(postStack.empty()) && postStack.top() != "(" && postStack.top() != "+" && postStack.top() != "-" )
					{
						cout<<postStack.top()<< " ";
						postStack.pop();
					}
					postStack.push(v[i]);
					operandStack.push(v[i]);
				}

				else if( v[i] == "+" || v[i] == "-")
				{
					while(!(postStack.empty()) && postStack.top() != "(")
					{
						cout<<postStack.top() << " ";
						postStack.pop();
					}
					postStack.push(v[i]);
					operandStack.push(v[i]);
				}
			}

			else if ( v[i] == "" || v[i] == " ")
			{ continue; }

			else if( v[i] == ")")
			{
				numParens++;
				if(v[i-1] == "*" || v[i-1] == "/"|| v[i-1] == "+" || v[i-1] == "-")
				{
						error = 1;		// Missing operand
						break;			// Leaves loop
				}

				else
				{
					// Prints until empty or ( occurs
					while(!(postStack.empty()) && postStack.top() != "("  )
					{
						cout<<postStack.top()<< " ";
						postStack.pop();

					}
			
					postStack.pop();				
					operandStack.push(v[i]);


				}
			}	

			else
			{
				// Pushes operands
				postStack.push(v[i]);
				operandStack.push(v[i]);
			}

	}

	// Looks at last elements of the vector
	if( v[v.size() -1] == "" || v[v.size() - 1] == " ")
 	{
		// Missing operand
		if(v[v.size()-2] == "*" || v[v.size()-2] == "/" || v[v.size()-2] == "+" || v[v.size()-2]== "-" )
		{ error = 1; }

		// Mismatched parentheses
		else if (v[v.size()-2] == "(")
		{ error = 2; }

		// Prints the rest of the elements
		else if (v[v.size()-2] != "*" && v[v.size()-2] != "/" && v[v.size()-2] != "+" && v[v.size()-2]!= "-" && v[v.size()-2] != "(")
		{
				if( postStack.top() != "(" && postStack.top() != ") ")
				{	cout<<postStack.top() << " ";		}
				
				postStack.pop();
				cout<<postStack.top() << " ";
	
		}
	}

	// Looks at last element of the vector
	else if (v[v.size() -1] != "" || v[v.size() - 1] != " ")
	{
	
			// Pushes element since it did not reach it in loop
			postStack.push(v[v.size()-1]);
			operandStack.push(v[v.size()-1]);
			// Prints and deletes the element
			cout<<postStack.top() << " ";
			postStack.pop();

			// Missing operand
			if(v[v.size()-1] == "*" || v[v.size()-1] == "/" || v[v.size()-1] == "+" || v[v.size()-1]== "-" )
			{ error = 1; }

			// Mismatched parentheses
			else if (v[v.size()-1] == "(")
			{ error = 2; }

			// Prints the rest of the elements
			else if (v[v.size()-1] != "*" && v[v.size()-1] != "/" && v[v.size()-1] != "+" && v[v.size()-1]!= "-" && v[v.size()-1] != "(")
			{
				
							if ( postStack.top() != "(" && postStack.top() != ") ")
								cout<<postStack.top() << " ";
							postStack.pop();
							
			}

	}

		// Printing the errors that occur
		if( error == 1 )
			cout<< "\nError: Missing operand in postfix string.";

		else if ( error == 2 )
		{
			cout<<"\nError: Infix expression: ";
			for( unsigned int i = 0; i < v.size(); ++i)
								cout<< v[i] << " ";

			cout<<" has mismatched parens!";
		}

		if( numParens % 2 != 0 )
		{
			error = 2;
			cout<<"\nError: Infix expression: ";
		 		for( unsigned int i = 0; i < v.size(); ++i)
					cout<< v[i] << " ";

				cout<<" has mismatched parens!";
		}

		// Sends the Stack to be calculated
		calculateExpression(operandStack, error);

}

void calculateExpression(Stack<string> opS, int e)
// Outputs the total of the calculated expression
{
	float total = 0;
	Stack<float> oStack;		// Stack to be printed
	Stack<string> temp = opS;	// Temporary stack to look for non-numerical operands																
	char operatr = ' ';		// Stores the operation to be performed on the Stack

	// Loop to determine whether or not the stack can be evaluated
	for( int j = 0;j < temp.size(); ++j)
	{
				if (temp.top() != "*" && temp.top() != "/" && temp.top() != "+" && temp.top() != "-")
				{
							if ( temp.top() != "" && temp.top() != " ")
							{
										if ( temp.top() != "(" && temp.top() != ")" )
										{
												string s = temp.top();

												for( unsigned int i = 0; i < s.length(); ++i )
												{
														if( s[i] != '0' && s[i] != '1' && s[i] != '2' && s[i] != '3' && s[i] != '4' && s[i] != '5' && s[i] != '6' && s[i] != '7' && s[i] != '8' && s[i] != '9')
														 {
															// Error for not being able to be evaluated
															  e = 1;
																break;
														}
														else
														{
															// No errors, Stack can be evaluated
															e = 0;
														}
												}
										}
							}
				}
				temp.pop();	// Deletes top element
	}

	temp = opS;		// Restores temp so we can look at each element

	if ( opS.size() == 0 )							// Empty Stack evaluates to 0
	{
		cout<<"\nPostfix evaluation: ";
		cout << opS;
		cout <<" = ";
			cout << "0";
		}

	else if ( opS.size() == 1 )						// Stack of 1 element evaluates to itself
	{
		cout<<"\nPostfix evaluation: ";
		cout << opS;
		cout <<" = ";
		cout << opS;
	}

	else if ( opS.size() > 1 )						// Stack can now be evaluated
	{

		if ( e == 0 )							// Stacks with no errors
		{
			cout<<"\nPostfix evaluation: ";
			cout << opS;
			cout <<" = ";
			// Prints the postfix

			for( int i = 0; i < temp.size(); i++)
			{
				// Deletes parentheses
				if (opS.top() == "(" ||  opS.top() == ")" || opS.top() == "\n")
				{
					opS.pop();
				}

				// Changes operator to + so total is summed
				else if( opS.top() == "+" )
				{
					operatr = '+';
					opS.pop();
				}

				// Operator changes to - so total is a difference
				else if( opS.top() == "-" )
				{
					operatr = '-';
					opS.pop();
				}

				// Operator changes to * so total is a product
				else if (opS.top() == "*")
				{
					operatr = '*';
					opS.pop();
				}

				// Operator changes to / so total is a quotient
				else if ( opS.top() == "/" )
				{
					operatr = '/';
					opS.pop();
				}

				// Space or empty element is ignored and deleted
				else if( opS.top() == " " || opS.top() == "")
				{
					opS.pop();
				}
				else
				// Converts string to char to float value
				{
						string str = opS.top();
       					float operand = 0,temp1 = 0, temp2 = 1;
					for( unsigned int j = 0; j < str.length(); j++)
					{
						temp1 = str[j] - '0';
						temp2 = pow(10.0, (str.length() - (j+1) ));
						temp2 *= temp1;
						operand += temp2;
						temp2 = 1;
					}
					oStack.push(operand);
					opS.pop();		// Deletes element from first stack
				}

				if ( operatr == '+')
				{
					// Calculates sum
					if ( total == 0 )
					{
						total = oStack.top();
							oStack.pop();
					}

					else
						total += oStack.top();

					if( !oStack.empty())
					{
						oStack.pop();
					}
				}

				else  if ( operatr == '-')
				{
					// Calculates difference
					total -= oStack.top();

					if( !oStack.empty())
					{
						total -= oStack.top();
						oStack.pop();
					}


				}

				if ( operatr == '*')
				{
					// Calculates product
					if ( total == 0 )
						total++;

					total *= oStack.top();

					if( !oStack.empty())
					{
						total *= oStack.top();
						oStack.pop();
					}

				}

				else if ( operatr == '/')
				{
					// Calculates quotient
						if ( total == 0)
								total = oStack.top();
						else
							total /= oStack.top();

					if( !oStack.empty())
					{
						total /= oStack.top();
						oStack.pop();
					}
				}


		}
			cout << total;						// Prints the total
			total = 0;						// Restores total to 0
		}

		else if ( e == 1 )
		{ cout << " Unable to evaluate postfix string!";}		// Can't be evaluated

		else if ( e == 2 )						// No output
		{ cout << "\n"; }

	}
	oStack.clear();								// Empties stack for next input
	cout <<"\nEnter the infix expression(\"exit\" to quit): ";		// Prompt user input for next expression
}
