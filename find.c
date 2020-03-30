/* 
	***   find.exe version 1.0   ***   author : Klaudia Jaros  ***
	
	C program to search a given .txt file for a specified word.
	The word replacement mode replaces the specified word from the .txt file with another(provided by a user), 
	this mode produces an output.txt file with an amended version of the original file where it saves all the changes.
	The case-insensitive mode tells the application to ignore case while searching for a word.
	
	***   last modified: 28/02/2020   ***
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define LINESIZE 1000
#define STRINGSIZE 100
/* 
 findIndex() - a function which finds the index within a string of a given substring, provided that substring exists.
 If the substring occurs more than once, the function returns the index of the first occurence of that substring. 
 - parameters:
 wordToFind - a substring which location the function will be looking for
 stringToSearch - the string to search
 caseSensitive - boolean, if true, the search is case-sensitive, if false, the search is case-insensitive
 - returns:
 index of type int - an index within the string, where the given substring begins, 
    or -1 if there is no such substring in the string. 
*/
int findIndex(char *wordToFind, char *stringToSearch, int caseSensitive)
{
	// for the search:
	int wordSize = strlen(wordToFind);
	int stringSize = strlen(stringToSearch);
	int wordIndex =0;
	int stringIndex =0;	
	int wordLastIndex = 0;
	// booleans:
	int match = 0;  
	int checkAgain = 0;
	
	// for the case-insensitive mode:
	char wordCopy[STRINGSIZE];
	char stringCopy[STRINGSIZE];
	strcpy(wordCopy, wordToFind);
	strcpy(stringCopy, stringToSearch);
	
	if (!caseSensitive) // case-insensitive mode
	{
		for (int i =0; i<strlen(wordCopy); i++)
		{
			wordCopy[i]=tolower(wordCopy[i]);
		}
		for (int j =0; j<strlen(stringCopy); j++)
		{
			stringCopy[j]=tolower(stringCopy[j]);
		}
	}
	
	// if the substring is bigger than the string, return -1:
	if (wordSize>stringSize)
	{
		return -1;
	}
	else
	{   // ensure the word you're looking for fits into the searched array:
		while (wordIndex<wordSize && (stringSize-stringIndex)>=(wordSize-wordIndex))
		{
			if (wordCopy[wordIndex] == stringCopy[stringIndex])
			{
				match=1;
				checkAgain=1;
				// only increment the word index if there is a match:
				wordIndex++;
				// save the index of the substring's last character:
				wordLastIndex = stringIndex;
			}
			else
			{
				match=0;
				wordIndex=0;
				// if the letter before was a match, but the current letter isn't, 
				// check the current letter again with a reset index(multiple same-letter occurences case):
				if (checkAgain==1)
				{
					stringIndex--;
					checkAgain=0;
				}				
			}
			// move to the next character:
			stringIndex++;
		}	
		if (match)
		{	
			// return the location in the string where the searched word begins:
			return wordLastIndex-wordSize+1;
		}
		else
		{
			return -1;
		}
	}
	
}
/* 
 noPunctuation() - a function to delete punctuation characters(except for an apostrophe)
 and a new line character from the end of a given string.
 example: "therefore," becomes "therefore"
 - parameters:
 str - a string to modify 
*/
void noPunctuation(char *str)
{
	int len = strlen(str);
	for (int i=(len-1); i>0; i--)
	{
		if ((ispunct(str[i]) || str[i] == '\n' ) && str[i]!='\'')
		{
			str[i]='\0';
		}
		else
		{
			break;
		}
	}	
}
/*  
 simpleSearch() - a search function for find.exe, finds occurences of a word in .txt file
 - parameters:
 keyword - the word to find
 fileName - the file to search
 caseSensitive - boolean to determine case-sensitivity
 */
void simpleSearch(char *keyword, char *fileName, int caseSensitive)
{
	int found = 0;  // boolean, the word found or not
	int count =0; // results count
	char line[LINESIZE];
	char *splitLine;
	
	if (caseSensitive)
		printf("** Search for a word, case-sensitive mode. **\n");
	else
		printf("** Search for a word, case-insensitive mode. **\n");
	
	// open the input file:
	FILE *inputFile = fopen(fileName, "r");
	if (errno>0)
	{
		printf("** Error message : %s **\n", strerror(errno));
	}
	printf("** Your results: \n");
	// get a line from the input file and search it:
	while(fgets(line, LINESIZE, inputFile) != NULL)
	{
		splitLine = strtok(line, " ");
		while(splitLine!=NULL)
		{
			noPunctuation(splitLine); // deletes punctuation and \n
			if (findIndex(keyword, splitLine, caseSensitive) !=-1)
			{
				found =1;
				count++;			
				printf(" %s",splitLine);
				printf("\n");
			}
			splitLine= strtok(NULL, " ");
		}
	}
	if (!found)
	{
		printf("** No matches found. **\n");
	}
	fclose(inputFile);
	printf("\n** Found %d result/s. **\n", count);
}
/*  
 searchAndReplace() - the search and replace function for find.exe, it searches the document for a given word, 
 creates a new document where it replaces the given word with a replacement word provided by the user,
 and prints both words to the console.
 - parameters:
 keyword - the word to find
 fileName - the file to search
 replacementWord - the word that replaces the keyword
 caseSensitive - boolean to determine case-sensitivity
 */
void searchAndReplace(char *keyword, char *fileName, char *replacementWord, int caseSensitive)
{
	int count =0; // results count
	int found = 0;  // boolean, the word found or not
	
	if (caseSensitive)
		printf("** Search for a word, case-sensitive mode. **\n");
	else
		printf("** Search for a word, case-insensitive mode. **\n");
	
	// open the input file:
	FILE *inputFile = fopen(fileName, "r");
	if (errno>0)
	{	
		printf("** Error message : %s **\n", strerror(errno)); // error message if file not present
	}
	// check if the user provided the replacement word:
	if (replacementWord == NULL)
	{
		printf("** Error message : No replacement word provided. **\n");  
	}
	else
	{	
		printf("** Your results: \n");
		// to store the lines and words from the inputFile:
		char line[LINESIZE];
		char *splitLine;
		
		// create an output file:
		FILE *outputFile;
		outputFile = fopen("output.txt", "w");
		
		// get a line from the input document:
		while(fgets(line, LINESIZE, inputFile) != NULL)
		{
			// split sentences into words using space character:
			splitLine = strtok(line, " ");
			while(splitLine!=NULL)
			{					
				// check if a word contains the user's keyword:
				if (findIndex(keyword, splitLine, caseSensitive) !=-1)
				{
					found = 1;
					count++;
					// output the found word to the console:
					char printWord[STRINGSIZE];
					strcpy(printWord, splitLine);
					noPunctuation(printWord); // deletes punctuation
					printf(" %s ", printWord);  

					// save the location of the right keyword substring:
					int index=0;
					index = findIndex(keyword, splitLine, caseSensitive);
					
					while (index!=-1)
					{
					// save the first part of the word to the outputFile and print it to the console:
						for (int i = 0; i<index; i++)
						{
							fprintf (outputFile, "%c", splitLine[i]);
							printf("%c", splitLine[i]);
						}
						// add the replacement word:
						fprintf (outputFile, "%s", replacementWord);
						printf ("%s", replacementWord);					
					
						// add offset and look for the word again(in case of multiple occurences of the substring),
						// ensure the offset is not outside of the string:
						int len = strlen(splitLine);
						if((splitLine+index+strlen(keyword)) < &splitLine[len])
						{	
							// change where the pointer points:
							splitLine = splitLine+index+strlen(keyword);
						}
						else
							break;
							
						index = findIndex(keyword, splitLine, caseSensitive);
						
						// if no substring found, go back to the previous pointer:
						if (index<0)
						{
							splitLine = splitLine-index-strlen(keyword);
						}		
					}							
					//no more substrings to find, print the rest of the word:
					
					// get the index of the last occurence of a substring:			
					index = findIndex(keyword, splitLine, caseSensitive);
					int len = strlen(splitLine);
					for (int j = index+strlen(keyword); j<len; j++)
					{
						// save all characters to the outputFile:
						fprintf (outputFile, "%c", splitLine[j]);
						// do not print space or punctuation chars to the console:
						if (isspace(splitLine[j]) || ispunct(splitLine[j]) && splitLine[j]!='\'')
							continue;
						else
							printf("%c", splitLine[j]);
						
					}
					// add whitespace to the outputFile, but not if the word has 'new line' as its last character:
					if (splitLine[len-1]!='\n')
					{
						fprintf (outputFile, " ");
					}
					printf("\n");
				}
				else
				{
					// print the no-match word to the outputFile,
					// do not add whitespace, if the word has 'new line' as its last character:
					int len = strlen(splitLine);
					if(splitLine[len-1]=='\n')
					{
						fprintf (outputFile, "%s", splitLine);
					}
					else
					{
						fprintf (outputFile, "%s", splitLine);
						fprintf (outputFile, " ");
					}
				}
				// move to the next word in the line:
				splitLine= strtok(NULL, " ");  
			}
		}
		if (!found)
		{
			printf("** No matches found. **\n");
		}
		fclose(inputFile);	
		fclose(outputFile);
	}	
	printf("\n** Found %d result/s. **\n", count);
}

// main find.exe function to determine which function should be called based on the user's input from the command line:
int main (int argc, char **argv)
{
	// booleans to check, in which mode the program should run:
	int caseSensitive = 1 ;  // default
	int replaceWord = 0;
	// char arrays to store user's input:
	char *wordReplacement;
	char *fileName;
	char *keyword = argv[1];
	
	if (argc<3 || argc >7)
	{
		printf("** Invalid or missing arguments. Please read readme file. **\n");
	}
	else
	{
		for (int i=1; i<argc; i++) // loop over command line arguments
		{
			if (strcmp(argv[i],"-c") == 0)
			{
				caseSensitive=0;
			}
			if (strcmp(argv[i], "-r") == 0 )
			{
				replaceWord =1 ;
				wordReplacement = argv[i+1];  // error handling in methods
			}
			if (strcmp(argv[i], "-i") == 0)
			{
				fileName = argv[i+1]; // error handling in methods
			}
		}		
		if (replaceWord && caseSensitive || replaceWord && !caseSensitive)
		{
			searchAndReplace(keyword, fileName, wordReplacement, caseSensitive);
		}
		else if (!replaceWord)
		{
			simpleSearch(keyword, fileName, caseSensitive); 
		}
		else if (fileName == NULL )
		{
			printf( "** Error: File not found. **\n");
		}
	}
	return 0;
}

// References:
// Error handling: https://www.geeksforgeeks.org/error-handling-c-programs/
