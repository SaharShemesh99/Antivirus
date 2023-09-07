#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define ZERO 0 //Setting variables
#define ONE 1 //Setting variables
#define TWO 2 //Setting variables
#define THREE 3 //Setting variables
#define FOUR 4 //Setting variables
#define FIVE 5 //Setting variables
#define ARRAY_SIZE 5 //Setting variables
#define LEN_OF_NAME 20 //Setting variables
#define LEN_OF_STR_FILE_PATE 100 //Setting variables

int lengthTest(int* lenOfFile, int lenOfVirus, FILE* myFile); //Definition of functions
int calculating20Percents(int lenOfFile); //Definition of functions
int inputFunction(char name[]); //Definition of functions
int	buildArray(char* arr, FILE* virusFile, int lenOfVirus); //Definition of functions
int lengthOfTheVirus(FILE* virusFile, int* lenOfVirus); //Definition of functions
int checkByArray(char arr[], FILE* myFile, int lenOfFile, FILE* virusFile, int lenOfVirus); //Definition of functions
int deepCheck(FILE* myFile, FILE* virusFile, int whereToStart); //Definition of functions
int quickCheck(char arr[], FILE* myFile, int lenOfFile, FILE* virusFile, int lenOfVirus); //Definition of functions
int outputFun(FILE* outputFile, char** arg, char name[], int searchType); //Definition of functions

int main(int argc, char** argv)
{
	int lenOfFile = 0, lenOfVirus = 0; //Setting variables
	HANDLE myFolder; //Setting variables
	WIN32_FIND_DATA dataInFile; //Setting variables
	int searchType = 0; //Setting variables
	FILE* myFile = NULL; //Setting variables
	FILE* outputFile = NULL; //Setting variables
	FILE* virus = NULL; //Setting variables
	char arr[ARRAY_SIZE] = { 0 }; //Setting variables
	int ans = 0; //Setting variables
	char strFilePath[LEN_OF_STR_FILE_PATE]; //Setting variables
	char name[LEN_OF_NAME] = { 0 };

	//Checking The amount of parameters
	if (argc < THREE)
	{
		printf("The program didn't receive all the parameters.\n\n"); //Output
		system("PAUSE");
		return 1;
	}
	
	virus = fopen(argv[TWO], "rb"); //Opening file
	if (!virus) //Testing if the opening of the file has been done successfully
	{
		printf("Error: the virus file doesn't exist.\n\n"); //Output
		system("PAUSE");
		return 1;
	}
	
	sprintf(strFilePath, "%s\\%s", argv[ONE], "output_file.txt");
	outputFile = fopen(strFilePath, "w"); //Opening file
	if (!outputFile) //Testing if the opening of the file has been done successfully
	{
		printf("Error: the outputFile can't be created.\n\n"); //Output
		system("PAUSE");
		return 1;
	}
	
	searchType = inputFunction(name); //function call
	if (searchType == ZERO)
	{
		printf("%s, you chose the regular search!\n", name); //Output
	}
	else
	{
		printf("%s, you chose the quick search!\n", name); //Output
	}

	if (outputFun(outputFile, argv, name, searchType))
	{
		//There was a problem in the function
		//The message to the user was written in the function
		return 1;
	}

	printf("The search starts now:\n"); //Output

	if (lengthOfTheVirus(virus, &lenOfVirus)) //Function call
	{
		//There was a problem in the function
		//The message to the user was written in the function
		return 1;
	}

	if (lenOfVirus > ZERO) //If the virus is emptu I don't need to build an array because there is no virus
	{
		if (buildArray(arr, virus, lenOfVirus)) //Function call
		{
			//The message to the user was written in the function
			return 1;
		}
	}
	
	
	sprintf(strFilePath, "%s\\*.*", argv[ONE]); //Creating the name, to open the file with this name in the next command
	if ((myFolder = FindFirstFile(strFilePath, &dataInFile)) != INVALID_HANDLE_VALUE) //Opening the folder
	{
		do
		{
			//There are 2 more names in the folder that are "." and "..", (It is something in the folder),
			//so if that are the names I don't chack them at all.
			if ((strcmp(dataInFile.cFileName, ".") != ZERO) && (strcmp(dataInFile.cFileName, "..")) && (strcmp(dataInFile.cFileName, "output_file.txt") != ZERO))
			{
				printf("Checking the file \"%s\"...\n", dataInFile.cFileName); //Output
				sprintf(strFilePath, "%s\\%s", argv[ONE], dataInFile.cFileName); //Creating the name, to open the file with this name in the next command
				myFile = fopen(strFilePath, "rb"); //Opening file
				if (!myFile) //Testing if the opening of the file has been done successfully
				{
					printf("Error: the file doesn't exist.\n\n"); //Output
					system("PAUSE");
					return 1;
				}
				ans = lengthTest(&lenOfFile, lenOfVirus, myFile, virus); //function call
				switch (ans)
				{
					case 0:
						ans = fprintf(outputFile, "%s -- Not infected\n", strFilePath); //Writing in to the file
						if (ans < ZERO) //Checking if the writing in to the file succeeded
						{
							printf("Error writing in the output file.\n"); //Output
							system("PAUSE");
							return 1;
						}
						break;
					case 1:
						//There was a problem in the function
						//The message to the user was written in the function
						return 1;
					case 2:
						//Maybe there is an virus in this file
						if (searchType == ZERO)
						{
							if (lenOfVirus > ZERO) //Checking if I should check the virus
							{
								ans = checkByArray(arr, myFile, lenOfFile, virus, lenOfVirus); //Function call
							}
							else
							{
								ans = ZERO; //If the length of the virus is 0 there is no virus
							}
							switch (ans)
							{
								case 0:
									//There is no virus
									ans = fprintf(outputFile, "%s -- Not infected\n", strFilePath); //Writing in to the file
									if (ans < ZERO) //Checking if the writing in to the file succeeded
									{
										printf("Error writing in the output file.\n"); //Output
										system("PAUSE");
										return 1;
									}
									break;
								case 1:
									//There was a problem in the function
									//The message to the user was written in the function
									return 1;
								case 2:
									//There is a virus
									ans = fprintf(outputFile, "%s -- Infected!\n", strFilePath); //Writing in to the file
									if (ans < ZERO) //Checking if the writing in to the file succeeded
									{
										printf("Error writing in the output file.\n"); //Output
										system("PAUSE");
										return 1;
									}
									break;
							}
						}
						else //quick check
						{
							if (lenOfVirus > ZERO) //Checking if I should check the virus
							{
								ans = quickCheck(arr, myFile, lenOfFile, virus, lenOfVirus); //Function call
							}
							else
							{
								ans = ZERO; //If the length of the virus is 0 there is no virus
							}
							switch (ans)
							{
								case 0:
									//There is no virus
									ans = fprintf(outputFile, "%s -- Not infected\n", strFilePath); //Writing in to the file
									if (ans < ZERO) //Checking if the writing in to the file succeeded
									{
										printf("Error writing in the output file.\n"); //Output
										system("PAUSE");
										return 1;
									}
									break;
								case 1:
									//There was a problem in the function
									//The message to the user was written in the function
									return 1;
								case 2:
									//There is a virus in the first 20%
									ans = fprintf(outputFile, "%s -- Infected! (found in the first 20%% of the file)\n", strFilePath); //Writing in to the file
									if (ans < ZERO) //Checking if the writing in to the file succeeded
									{
										printf("Error writing in the output file.\n"); //Output
										system("PAUSE");
										return 1;
									}
									break;
								case 3:
									//There is a virus in the last 20%
									ans = fprintf(outputFile, "%s -- Infected! (found in the last 20%% of the file)\n", strFilePath); //Writing in to the file
									if (ans < ZERO) //Checking if the writing in to the file succeeded
									{
										printf("Error writing in the output file.\n"); //Output
										system("PAUSE");
										return 1;
									}
									break;
								case 4:
									//There is a virus in the middle
									ans = fprintf(outputFile, "%s -- Infected! (found in the middle of the file)\n", strFilePath); //Writing in to the file
									if (ans < ZERO) //Checking if the writing in to the file succeeded
									{
										printf("Error writing in the output file.\n"); //Output
										system("PAUSE");
										return 1;
									}
									break;
							}
						}
						break;
				}

				if (fclose(myFile) == EOF) //Closing file
				{
					//Testing if the closing of the file has been done successfully
					printf("Error closing the file\n\n"); //Output
					system("PAUSE");
					return 1;
				}
			}
		} while (FindNextFile(myFolder, &dataInFile));
		if (!FindClose(myFolder)) //Closing the folder
		{
			printf("There was a prblem in closing the folder.\n\n"); //Output
			system("PAUSE");
			return 1;
		}
	}
	
	if (fclose(virus) == EOF) //Closing file
	{
		//Testing if the closing of the file has been done successfully
		printf("Error closing the virus file\n\n"); //Output
		
		if (fclose(outputFile) == EOF) //Closing file
		{
			//Testing if the closing of the file has been done successfully
			printf("Error closing the output file\n\n"); //Output
			system("PAUSE");
			return 1;
		}
		
		system("PAUSE");
		return 1;
	}

	if (fclose(outputFile) == EOF) //Closing file
	{
		//Testing if the closing of the file has been done successfully
		printf("Error closing the output file\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	system("PAUSE");
	return 0;
}

/*
Function test of whether the file is shorter than the virus length:
The function will get the file that is tested, the length of the virus file and pointer to the length of the file.
The function will check what is the length of the file and update the value in the pointer so the other functions shouldn't do it again.
If a virus test file longer function returns 0 (no chance that the virus would be found in File).
If there was an error the function returns 1.
Otherwise, if the virus file is longer, it will return 2 (there is a chance that the virus is inside).
*/
int lengthTest(int *lenOfFile, int lenOfVirus, FILE* myFile)
{
	int ans = 0; //Setting Variables

	//Checking the length of the current file
	if (fseek(myFile, ZERO, SEEK_END) != ZERO) //Moving the pointer to the end of the file to check its length
	{
		printf("There was an error in checking the length of the current file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}
	*lenOfFile = ftell(myFile); //Checking what is the last byte in the file
	if (*lenOfFile == EOF) //Checking if the command of the function ftell succeeded
	{
		printf("There was an error in checking the length of the current file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}
	if (*lenOfFile < lenOfVirus)
	{
		ans = ZERO; //The virus can't be inside of the file
	}
	else
	{
		ans = TWO; //The virus can be inside of the file
	}
	return ans;
}

/*
Function returning 20% of the file:
The function is called by quick scan function.
The function gets the length of the file and the file that should be scanned.
The function returns the number of bytes that are 20% of the file.
*/
int calculating20Percents(int lenOfFile)
{
	int ans = 0; //Setting Variables

	ans = (int)(lenOfFile / FIVE); //Calculating 20% of the length of the file

	return ans;
}

/*
The purpose of the function is to calculate the length of the virus file.
The function receives a pointer to the length of the virus, and the virus file.
The function returns a 1 if there was a problem, otherwise the function returns 0.
*/
int lengthOfTheVirus(FILE* virusFile, int* lenOfVirus)
{
	//Checking the length of the virus file
	if (fseek(virusFile, ZERO, SEEK_END) != ZERO) //Moving the pointer to the end of the file to check its length
	{
		printf("There was an error in checking the length of the virus file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}
	*lenOfVirus = ftell(virusFile); //Checking what is the last byte in the file
	if (*lenOfVirus == EOF) //Checking if the command of the function ftell succeeded
	{
		printf("There was an error in checking the length of the virus file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	return 0;
}

/*
Input function:
Function that asks the user what type of scan he wants, and receives his answer and check if the answer is OK.
The function doesn't accept any parameters.
The function returns 0 if the user wants a normal scan and 1 if he wants a quick scan.
*/
int inputFunction(char name[])
{
	int ans = 0; //Setting Variables

	printf("Hello!\n");
	printf("Welcome to my antivirus program!\n");
	printf("Please enter your name:");
	fgets(name, LEN_OF_NAME - ONE, stdin);
	name[strlen(name) - ONE] = ZERO;
	printf("Hello %s!\n", name);
	printf("Which search do you prefer?\n"); //Output
	printf("Press 0 for regular search and 1 for quick search\n"); //Output
	printf("Your choise is: "); //Output
	scanf("%d", &ans); //Intput

	while ((ans != ZERO) && (ans != ONE)) //Input check
	{
		printf("Your choise is wrong! Please choose again: "); //Output
		scanf("%d", &ans); //Intput
	}
	
	return ans;
}

/*
A function of building an array:
The function will receive the virus and a pointer to an array of numbers.
The function will put in about 5 characters of a virus:
the first character, the character which is 20% after the first,
the middle character, the character which is at the beginning of the last 20% of the file and the last character.
The function returns a 1 if there was a problem or not this function returns 0.
*/
int	buildArray(char* arr, FILE* virusFile, int lenOfVirus)
{
	if (fseek(virusFile, ZERO, SEEK_SET) != ZERO) //Moving the pointer to the beginning of the file 
	{
		printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}
	if (fread(arr, sizeof(char), ONE, virusFile) == ZERO) //Check for successful input of character
	{
		printf("There was a problem in reading from the virus file.\n"); //Output
		system("PAUSE");
		return 1;
	}
	
	if (fseek(virusFile, (int)(lenOfVirus / FIVE), SEEK_SET) != ZERO) //Moving the pointer to 20% after the beginning of the file
	{
		printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}
	if (fread(arr + ONE, sizeof(char), ONE, virusFile) == ZERO) //Check for successful input of character
	{
		printf("There was a problem in reading from the virus file.\n"); //Output
		system("PAUSE");
		return 1;
	}
	
	if (fseek(virusFile, (int)(lenOfVirus / TWO), SEEK_SET) != ZERO) //Moving the pointer to the middle of the file
	{
		printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}
	if (fread(arr + TWO, sizeof(char), ONE, virusFile) == ZERO) //Check for successful input of character
	{
		printf("There was a problem in reading from the virus file.\n"); //Output
		system("PAUSE");
		return 1;
	}
	
	if (fseek(virusFile, (((int)(lenOfVirus / FIVE)) * -ONE), SEEK_END) != ZERO) //Moving the pointer to 20% before the end of the file
	{
		printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}
	if (fread(arr + 3, sizeof(char), ONE, virusFile) == ZERO) //Check for successful input of character
	{
		printf("There was a problem in reading from the virus file.\n"); //Output
		system("PAUSE");
		return 1;
	}

	if (fseek(virusFile, -ONE, SEEK_END) != ZERO) //Moving the pointer to the end of the file
	{
		printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}
	if (fread(arr + FOUR, sizeof(char), ONE, virusFile) == ZERO) //Check for successful input of character
	{
		printf("There was a problem in reading from the virus file.\n"); //Output
		system("PAUSE");
		return 1;
	}

	return 0;
}

/*
A function of checking by the array of the function buildArray:
If the function see a character that is equal to the first character in the array(that is the first character in the virus file).
so the function will check the character which is 20% after the first, the middle character,
the character which is at the beginning of the last 20% of the file and the last character in the virus file by the array.
it helps to know better if there is achanch that there is a virus or it is just similar to the virus.
The function uses the array to do the check faster.
If all the five characters are equal so the function will call another function to check this better(every character in the virus).
If there was a problem the function will returns 1,
if there is no virus the function will returns 0,
and if there is a virus the function returns 2.
*/
int checkByArray(char arr[], FILE* myFile, int lenOfFile, FILE* virusFile, int lenOfVirus)
{
	int temp = 0, twentyPercent = 0, ans = 0, flag = 0; //Setting Variables
	char letter = ' '; //Setting Variables
	int result = 0; //Setting Variables

	twentyPercent = calculating20Percents(lenOfVirus); //Function call

	if (fseek(myFile, ZERO, SEEK_SET) != ZERO) //Moving the pointer to the beginning of the file 
	{
		printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	while (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
	{
		temp = ftell(myFile);
		if (lenOfFile - temp < lenOfVirus)
		{
			//If the number of characters left to examine smaller than the length of the virus, so the virus can not be on this file.
			break; //There is no chance that there is a virus in this file
		}

		if (letter == arr[ZERO])
		{
			if (fseek(myFile, temp + twentyPercent - ONE, SEEK_SET) != ZERO) //Moving the pointer
			{
				printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
				system("PAUSE");
				return 1;
			}
			if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
			{
				if (letter == arr[ONE])
				{
					if (fseek(myFile, temp + (int)(lenOfVirus / TWO) - ONE, SEEK_SET) != ZERO) //Moving the pointer
					{
						printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
						system("PAUSE");
						return 1;
					}
					if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
					{
						if (letter == arr[TWO])
						{
							if (fseek(myFile, temp + (lenOfVirus - twentyPercent) - ONE, SEEK_SET) != ZERO) //Moving the pointer
							{
								printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
								system("PAUSE");
								return 1;
							}
							if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
							{
								if (letter == arr[3])
								{
									if (fseek(myFile, temp + (lenOfVirus - ONE) - ONE, SEEK_SET) != ZERO) //Moving the pointer
									{
										printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
										system("PAUSE");
										return 1;
									}
									if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
									{
										if (letter == arr[FOUR])
										{
											ans = deepCheck(myFile, virusFile, temp - ONE); //Function call
											switch (ans)
											{
												case 0:
													//There is no virus
													break;
												case 1:
													//There was a problem in the function
													//The message to the user was written in the function
													return 1;
												case 2:
													//There is a virus
													flag = ONE;
													break;
											}
										}
										if (flag) //Checking if there is an virus
										{
											result = TWO;//There is a virus
											break; //break from the while
										}
									}
								}
							}
						}
					}
				}
			}	
		}
		if (fseek(virusFile, temp, SEEK_SET) != ZERO) //Moving the pointer
		{
			printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
			system("PAUSE");
			return 1;
		}
	}
	return result;
}

/*
The purpose of the function is to make a thorough examination file which may contain a virus.
The function begins to check from specific place, whom she accepts as an input parameter.
In addition, the function receives the file that it checks, and the file of the virus.
The function returns 1 if there was a problem, the function returns 0 if no virus, and the function returns 2 if there is a virus.
*/
int deepCheck(FILE* myFile, FILE* virusFile, int whereToStart)
{
	char fileLetter = ' ', virusLetter = ' '; //Setting Variables
	int flag = TWO; //Setting Variables

	if (fseek(virusFile, ZERO, SEEK_SET) != ZERO) //Moving the pointer to the beginning of the file 
	{
		printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	if (fseek(myFile, whereToStart, SEEK_SET) != ZERO) //Moving the pointer to the beginning of the file 
	{
		printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	while (fread(&fileLetter, sizeof(char), ONE, myFile) != ZERO && fread(&virusLetter, sizeof(char), ONE, virusFile) != ZERO) //Reading letters from the file
	{
		if (fileLetter != virusLetter)
		{
			flag = ZERO; //There is no virus
			break;
		}
	}

	return flag;
}

/*
The purpose of the function is to check the file quickly.
At first, the function will check the first 20% of the file.
It then checks the final 20% of the file.
Finally it will examine the middle.
The function uses an array to do the check faster.
The function will recognize a virus even if it starts in the middle and ends at the end,
and if it starts at the beginning and ends in the middle.
Function accepts an array, file to check, the length of the checked file, virus file, and the length of the virus file.
If there was a problem the function will returns 1,
if there is no virus the function will returns 0,
and if there is a virus the function returns 2/3/4.
If the virus is in the first 20% of the file - the function returns 2.
If the virus is in the last 20% of the file - the function returns 3.
And if the virus is in the middle of the file - the function returns 4.
*/
int quickCheck(char arr[], FILE* myFile, int lenOfFile, FILE* virusFile, int lenOfVirus)
{
	int twentyPercentVirus = 0, twentyPercentFile = 0, temp = 0; //Setting Variables
	int ans = 0, flag = 0, result = 0; //Setting Variables
	char letter = ' '; //Setting Variables

	twentyPercentFile = calculating20Percents(lenOfFile); //Function call
	twentyPercentVirus = calculating20Percents(lenOfVirus); //Function call

	if (fseek(myFile, ZERO, SEEK_SET) != ZERO) //Moving the pointer to the beginning of the file 
	{
		printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	//Checking the 20% of the beginning///
	while (fread(&letter, sizeof(char), ONE, myFile) != ZERO && temp <= twentyPercentFile)
	{
		temp = ftell(myFile);
		if (lenOfFile - temp < lenOfVirus)
		{
			//If the number of characters left to examine smaller than the length of the virus, so the virus can not be on this file.
			break; //There is no chance that there is a virus in this file
		}

		if (letter == arr[ZERO])
		{
			if (fseek(myFile, temp + twentyPercentVirus - ONE, SEEK_SET) != ZERO) //Moving the pointer
			{
				printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
				system("PAUSE");
				return 1;
			}
			if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
			{
				if (letter == arr[ONE])
				{
					if (fseek(myFile, temp + (int)(lenOfVirus / TWO) - ONE, SEEK_SET) != ZERO) //Moving the pointer
					{
						printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
						system("PAUSE");
						return 1;
					}
					if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
					{
						if (letter == arr[TWO])
						{
							if (fseek(myFile, temp + (lenOfVirus - twentyPercentVirus) - ONE, SEEK_SET) != ZERO) //Moving the pointer
							{
								printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
								system("PAUSE");
								return 1;
							}
							if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
							{
								if (letter == arr[3])
								{
									if (fseek(myFile, temp + (lenOfVirus - ONE) - ONE, SEEK_SET) != ZERO) //Moving the pointer
									{
										printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
										system("PAUSE");
										return 1;
									}
									if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
									{
										if (letter == arr[FOUR])
										{
											ans = deepCheck(myFile, virusFile, temp - ONE); //Function call
											switch (ans)
											{
											case 0:
												//There is no virus
												break;
											case 1:
												//There was a problem in the function
												//The message to the user was written in the function
												return 1;
											case 2:
												//There is a virus
												flag = ONE;
												break;
											}
										}
										if (flag) //Checking if there is an virus
										{
											result = TWO;//There is a virus
											break; //break from the while
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (fseek(myFile, temp, SEEK_SET) != ZERO) //Moving the pointer
		{
			printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
			system("PAUSE");
			return 1;
		}
	}

	if (fseek(myFile, (twentyPercentFile * -ONE), SEEK_END) != ZERO) //Moving the pointer to 20% before the end of the file
	{
		printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	//Checking the 20% of the end///
	while (result == ZERO && fread(&letter, sizeof(char), ONE, myFile) != ZERO)
	{
		//I check the result because if the virus was found the result would be 2 and not 0
		temp = ftell(myFile);
		if (lenOfFile - temp < lenOfVirus)
		{
			//If the number of characters left to examine smaller than the length of the virus, so the virus can not be on this file.
			break; //There is no chance that there is a virus in this file
		}

		if (letter == arr[ZERO])
		{
			if (fseek(myFile, temp + twentyPercentVirus - ONE, SEEK_SET) != ZERO) //Moving the pointer
			{
				printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
				system("PAUSE");
				return 1;
			}
			if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
			{
				if (letter == arr[ONE])
				{
					if (fseek(myFile, temp + (int)(lenOfVirus / TWO) - ONE, SEEK_SET) != ZERO) //Moving the pointer
					{
						printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
						system("PAUSE");
						return 1;
					}
					if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
					{
						if (letter == arr[TWO])
						{
							if (fseek(myFile, temp + (lenOfVirus - twentyPercentVirus) - ONE, SEEK_SET) != ZERO) //Moving the pointer
							{
								printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
								system("PAUSE");
								return 1;
							}
							if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
							{
								if (letter == arr[3])
								{
									if (fseek(myFile, temp + (lenOfVirus - ONE) - ONE, SEEK_SET) != ZERO) //Moving the pointer
									{
										printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
										system("PAUSE");
										return 1;
									}
									if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
									{
										if (letter == arr[FOUR])
										{
											ans = deepCheck(myFile, virusFile, temp - ONE); //Function call
											switch (ans)
											{
											case 0:
												//There is no virus
												break;
											case 1:
												//There was a problem in the function
												//The message to the user was written in the function
												return 1;
											case 2:
												//There is a virus
												flag = ONE;
												break;
											}
										}
										if (flag) //Checking if there is an virus
										{
											result = 3;//There is a virus
											break; //break from the while
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (fseek(myFile, temp, SEEK_SET) != ZERO) //Moving the pointer
		{
			printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
			system("PAUSE");
			return 1;
		}
	}

	if (fseek(myFile, twentyPercentFile, SEEK_SET) != ZERO) //Moving the pointer to 20% after the beginning 
	{
		printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}
	temp = ftell(myFile);
	//Checking the middle of the file///
	while (result == ZERO && fread(&letter, sizeof(char), ONE, myFile) != ZERO && temp < (lenOfFile - twentyPercentFile))
	{
		//I check the result because if the virus was found the result would be 2 and not 0
		temp = ftell(myFile);
		if (lenOfFile - temp < lenOfVirus)
		{
			//If the number of characters left to examine smaller than the length of the virus, so the virus can not be on this file.
			break; //There is no chance that there is a virus in this file
		}

		if (letter == arr[ZERO])
		{
			if (fseek(myFile, temp + twentyPercentVirus - ONE, SEEK_SET) != ZERO) //Moving the pointer
			{
				printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
				system("PAUSE");
				return 1;
			}
			if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
			{
				if (letter == arr[ONE])
				{
					if (fseek(myFile, temp + (int)(lenOfVirus / TWO) - ONE, SEEK_SET) != ZERO) //Moving the pointer
					{
						printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
						system("PAUSE");
						return 1;
					}
					if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
					{
						if (letter == arr[TWO])
						{
							if (fseek(myFile, temp + (lenOfVirus - twentyPercentVirus) - ONE, SEEK_SET) != ZERO) //Moving the pointer
							{
								printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
								system("PAUSE");
								return 1;
							}
							if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
							{
								if (letter == arr[3])
								{
									if (fseek(myFile, temp + (lenOfVirus - ONE) - ONE, SEEK_SET) != ZERO) //Moving the pointer
									{
										printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
										system("PAUSE");
										return 1;
									}
									if (fread(&letter, sizeof(char), ONE, myFile) != ZERO)
									{
										if (letter == arr[FOUR])
										{
											ans = deepCheck(myFile, virusFile, temp - ONE); //Function call
											switch (ans)
											{
											case 0:
												//There is no virus
												break;
											case 1:
												//There was a problem in the function
												//The message to the user was written in the function
												return 1;
											case 2:
												//There is a virus
												flag = ONE;
												break;
											}
										}
										if (flag) //Checking if there is an virus
										{
											result = FOUR;//There is a virus
											break; //break from the while
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (fseek(myFile, temp, SEEK_SET) != ZERO) //Moving the pointer
		{
			printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
			system("PAUSE");
			return 1;
		}
	}

	return result;
}

/*
The purpose of the function is to print into the output file.
The function receives a pointer to the output file, array which includes the name of the main folder,
and an array which includes the user's name.
The function returns 1 if it was a problem, otherwise it returns 0.
*/
int outputFun(FILE* outputFile, char** argv, char name[], int searchType)
{
	int ans = 0; //Setting Variables

	ans = fprintf(outputFile, "%s's Anti-Virus Scanning Results:\n", name); //Writing in to the file
	if (ans < ZERO)//Checking if the writing in to the file succeeded
	{
		printf("Error writing in the output file.\n"); //Output
		system("PAUSE");
		return 1;
	}

	ans = fprintf(outputFile, "-----------------------------------------\n"); //Writing in to the file
	if (ans < ZERO) //Checking if the writing in to the file succeeded
	{
		printf("Error writing in the output file.\n"); //Output
		system("PAUSE");
		return 1;
	}
	ans = fprintf(outputFile, "\nFolder to scan: %s\n", argv[ONE]); //Writing in to the file
	if (ans < ZERO) //Checking if the writing in to the file succeeded
	{
		printf("Error writing in the output file.\n"); //Output
		system("PAUSE");
		return 1;
	}
	ans = fprintf(outputFile, "\nVirus signature: %s\\%s\n", argv[ONE], argv[TWO]); //Writing in to the file
	if (ans < ZERO) //Checking if the writing in to the file succeeded
	{
		printf("Error writing in the output file.\n"); //Output
		system("PAUSE");
		return 1;
	}

	if (searchType == ZERO)
	{
		ans = fprintf(outputFile, "\nScanning option: Regular\n");
		if (ans < ZERO)
		{
			printf("Error writing in the output file.\n");
			system("PAUSE");
			return 1;
		}
	}
	else
	{
		ans = fprintf(outputFile, "\nScanning option: Quick Scan\n");
		if (ans < ZERO)
		{
			printf("Error writing in the output file.\n");
			system("PAUSE");
			return 1;
		}
	}

	ans = fprintf(outputFile, "\nResults:\n"); //Writing in to the file
	if (ans < ZERO) //Checking if the writing in to the file succeeded
	{
		printf("Error writing in the output file.\n"); //Output
		system("PAUSE");
		return 1;
	}

	return 0;
}
