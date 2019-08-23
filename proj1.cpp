/**Name: Ashley Ellis
 * Course: COP4530-0001 Spring 2019
 * Assignment: Project 1: Word, Number and Character Usage Statistics
 * Due Date: February 1, 2019
 **/

#include<vector>	//for vector and vector pair object
#include<iostream>	//input and output
#include<string>	//for vector pair containing strings

using namespace std;

int main()
{

	vector<char> charVector;
	vector< pair <char, int> > char_Stats_Vector;
	vector< pair <string, int> > num_Stats_Vector;
	vector< pair <string, int> > word_Stats_Vector;

	char c;
	//loop to read in characters from input redirection
	while(cin.get(c))
	{
		//add the character to the vector
		charVector.push_back(c); 
	}

	//loop to go through character vector and determine statistics
	for(unsigned int i = 0; i < charVector.size(); i++)
	{
		//variable to store the number of occurences of a character
		int counter = 1;
	
		//loop to search for identical characters in vector
		for(unsigned int j = i+1; j < charVector.size(); j++)
		{
			if(charVector[i] == charVector[j])
			{
				//occurence increases
				counter++;
			}

		}	

		//variable to store value and determine whether or not character is to be stored in array
		bool char_check;

		for(unsigned int k = 0; k < char_Stats_Vector.size(); k++)
		{
			//if another occurence of the character exists check is true
			//element is not added to the vector
			if(charVector[i] == char_Stats_Vector[k].first)
			{
				char_check = true;
				//break to get out of loop so check does not become
				//affected by other elements
				break;
			}
		
			else
				//character will be stored in vector
				char_check = false;
		}

		if(char_check == false)
		{
			//stores character in vector and pairs with counter value
			char_Stats_Vector.push_back(make_pair(charVector[i], counter));
		}

	}



	//loop to convert all alphabet characters to same case (lower-case)
	//words case insensitive
	for(unsigned int i= 0; i < charVector.size(); i++)
	{
		charVector[i] = tolower(charVector[i]);			
	}

	//variables to store parsed words and numbers
	string tempWord = "";
	string tempNum = "";
	
	//stores last seen character
	char lastSeen;

	//variable to store  number of occurences
	int counter = 1;

	//stores current character to add to string
	char currentCharacter;

	//variable to store whether or not number or word gets added to string
	bool num_check, word_check;

	
	//for-loop to iterate through character vector and find  numbers and words
	for(unsigned int i = 0; i < charVector.size(); i++)
	{

		currentCharacter = charVector[i];

		//at first iteration the first character becomes last seen
		//and is added to word or number based upon isdigit and isalpha
		if ((i == 0) && (isalpha(currentCharacter) != 0))
		{
			tempWord += currentCharacter;
			lastSeen = currentCharacter;
		}
	
		else if ((i == 0) && (isdigit(currentCharacter) != 0))
		{
			tempNum += currentCharacter;
			lastSeen = currentCharacter;
		}


		//works through middle of the vector positions
		else if ((i > 0) && (i <= (charVector.size() - 2)))
		{

			//conditional to look for numbers and calculate number stats
			if(isdigit(currentCharacter) != 0)
			{
				if(isdigit(lastSeen) != 0)
				{
					//continues adding to number if character is a digit
					//updates last seen character
					tempNum += currentCharacter;
					lastSeen = currentCharacter;
				}
	
				//if last seen is not a digit then a word has ended
				else
				{
					//begins new number
					//updates last seen character
					tempNum += currentCharacter;
					lastSeen = currentCharacter;
		
					//loop to calculate number of word's occurences
					for(unsigned int j = 0; j < word_Stats_Vector.size(); j++)
					{
						if(tempWord == word_Stats_Vector[j].first)
						{
							counter++;
							word_check = true;
							break;
						}
					
						else
							word_check = false;
					}	
				
					//word is added and temporary variable resets
					if(word_check == false)
					{
						word_Stats_Vector.push_back(make_pair(tempWord, counter));
						tempWord = "";
					}	
				}	

			}	
		

			//for alphabet characters
			else if(isalpha(currentCharacter) != 0)
			{	
	
				//if last seen is alphabet character
				//word is updated and last seen character becomes current character
				if(isalpha(lastSeen) != 0 )
				{
					tempWord += currentCharacter;
					lastSeen = currentCharacter;
				}	

				else
				{
					//if last seen was a number then a number has ended
					//word is updated
					//last seen is updated
					tempWord += currentCharacter;
					lastSeen = currentCharacter;
				
					//loop to calculate number of occurences and 
					//determine whether or not a word is to be added to the vector
					for(unsigned int j = 0; j < num_Stats_Vector.size(); j++)
					{
						if(tempNum == num_Stats_Vector[j].first)
						{
							counter++;
							num_check = true;
							break;
						}
					
						else
						{
							num_check = false;
						}	
					}
					
					//adds number and count to vector pair
					//resets num variable
					if(num_check == false)
					{
						num_Stats_Vector.push_back(make_pair(tempNum, counter));
						tempNum = "";
					}	

				}


			}
		}

		//conditional for last character in vector
		else if ( i == (charVector.size() - 1))
		{
			//if last character is part of the alphabet
			if(isalpha(currentCharacter) != 0)
			{
				
				if(isalpha(lastSeen) != 0)
				{	//update word
					tempWord += currentCharacter;
					
					//iterate through vector and evaluate count
					for(unsigned int l = 0; l < word_Stats_Vector.size(); l++)
					{
						if(tempWord == word_Stats_Vector[l].first)
							counter++;
					}
					
					//adds word and counter to vector
					word_Stats_Vector.push_back(make_pair(tempWord, counter));
				}

				else if (isdigit(lastSeen))
				{
					//updates word
					tempWord += currentCharacter;
				
					for(unsigned int l = 0; l < word_Stats_Vector.size(); l++)
					{
						if(tempWord == word_Stats_Vector[l].first)
							counter++;
					}
					//adds word and counter to vector
					word_Stats_Vector.push_back(make_pair(tempWord, counter));
				}

			}
	
			//if last character is a digit
			else if(isdigit(currentCharacter) != 0)
			{
				if(isdigit(lastSeen) != 0)
				{
					//updates number
					tempNum += currentCharacter;
					
					//looks for multiple occurences
					for(unsigned int l = 0; l < num_Stats_Vector.size(); l++)
					{
						if(tempNum == num_Stats_Vector[l].first)
							counter++;
					}

					//adds pair to vector	
					num_Stats_Vector.push_back(make_pair(tempNum, counter));
				}

				else if (isalpha(lastSeen) != 0)
				{
					//updates number
					tempNum += currentCharacter;

					//looks for multiple occurences
					for(unsigned int l = 0; l < num_Stats_Vector.size(); l++)
					{
						if(tempNum == num_Stats_Vector[l].first)						
							counter++;
					}
			
					//adds pair to vector
					num_Stats_Vector.push_back(make_pair(tempNum, counter));
				}
			}
		}
	}

	//conditionals for output and each vector

	//if less than 10 only iterate through the vector
	if(char_Stats_Vector.size() < 10)
	{	
		//Output for character statistics
		cout<<"Total " << char_Stats_Vector.size() << "  different characters, " << char_Stats_Vector.size() << "  most used characters";	  cout<<"\n";
	
		for(unsigned int i = 0; i < char_Stats_Vector.size(); i++)
		{

			if(char_Stats_Vector[i].first == ' ')
			{
				cout<<"No. "<< i <<": \\s"<< "\t" << char_Stats_Vector[i].second << "\n";
			}
	
			else if(char_Stats_Vector[i].first =='\n')
			{
				cout <<"No. " << i <<": \\n" <<"\t"<<char_Stats_Vector[i].second <<"\n";
			}

			else if(char_Stats_Vector[i].first == '\t')
			{
				cout<<"No. " << i << ": \\t" <<"\t"<< char_Stats_Vector[i].second<<"\n";
			}
	
			else
			{
			cout<<"No. " << i << ":\t"<<char_Stats_Vector[i].first << "\t" << char_Stats_Vector[i].second<<"\n";
			}	
		}	
	}

	//if size is greater than 10 then only print statistics for top 10
	else if (char_Stats_Vector.size() >= 10)
	{
		cout<<"Total " << char_Stats_Vector.size() << "  different characters, " << " 10 most used characters: " <<endl;
		
		for(unsigned int i = 0; i < 10; i++)
		{
		
			if(char_Stats_Vector[i].first == ' ')
			{
				cout<<"No. "<< i <<": \\s"<< "\t" << char_Stats_Vector[i].second << "\n";
			}			
	
			else if(char_Stats_Vector[i].first == '\n')
			{
				cout <<"No. " << i <<": \\n" <<"\t"<<char_Stats_Vector[i].second <<"\n";
			}

			else if(char_Stats_Vector[i].first == '\t')
			{
				cout<<"No. " << i << ": \\t" <<"\t"<< char_Stats_Vector[i].second<<"\n";
			}
	
			else
			{
				cout<<"No. " << i <<":\t" << char_Stats_Vector[i].first << "\t" << char_Stats_Vector[i].second<<"\n";
			}	
		}
	}

	cout<<"\n\n";
	//Output for word statistics

	//if words are less than 10 only iterate through size of vector
	if (word_Stats_Vector.size() < 10)
	{
		cout<<"Total " << word_Stats_Vector.size() << " different words, " << word_Stats_Vector.size() <<" most used words" << endl;
	
		for(unsigned int i = 0; i < word_Stats_Vector.size(); i++)
			cout<<"No. " << i <<": " << word_Stats_Vector[i].first <<"\t"<< word_Stats_Vector[i].second <<"\n";
	}

	//if there are more than 10 words then only iterate through top 10
	else if (word_Stats_Vector.size() >= 10)
	{
		cout<<"Total " << word_Stats_Vector.size() << " different words, 10 most used words" << endl;
		for(unsigned int i = 0; i < word_Stats_Vector.size(); i++)
			cout<<"No. " << i << ": " << word_Stats_Vector[i].first << "\t" << word_Stats_Vector[i].second << endl;
	}
	cout<<"\n\n";

	//Output for number statistics
	
	//if there are less than 10 numbers only iterate through the vector
	if (num_Stats_Vector.size() < 10)
	{
		cout<<"Total " << num_Stats_Vector.size() << "  different numbers, " << num_Stats_Vector.size() << "  most used numbers" << endl;
		
		for(unsigned int i = 0; i < num_Stats_Vector.size(); i++)
			cout<<"No. " << i <<": "<<num_Stats_Vector[i].first << "\t" << num_Stats_Vector[i].second <<"\n";
	}

	//if there are more than 10 numbers then only print top 10
	else if (num_Stats_Vector.size() >= 10)
	{
		cout <<"Total " << num_Stats_Vector.size() << " different numbers, " << 10 << " most used numbers" << endl;
		
		for(unsigned int i = 0; i < 10; i++)
			cout<<"No. " << i << ":" << num_Stats_Vector[i].first << "\t" << num_Stats_Vector[i].second << "\n";
	}	
}

