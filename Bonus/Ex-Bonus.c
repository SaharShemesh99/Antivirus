/*********************************************************************************************\
* The purpose of the function is to find the virus in the file and copy it to the virus file. *
\*********************************************************************************************/

#include <stdio.h>
#include <stdio.h>
#include <string.h>

#define ZERO 0 //Setting variables
#define ONE 1 //Setting variables
#define FOUR 4 //Setting variables

int CreateVirus(FILE* myFile, FILE* virusFile, int whereToStart, int whereToFinish); //Definition of functions

int main(int argc, char** argv)
{
	FILE* virus = NULL; //Setting variables
	FILE* myFile = NULL; //Setting variables
	int ans = 0; //Setting variables
	int whereToStart = 0, whereToFinish = 0; //Setting variables
	int i = 0; //Setting variables

	//Checking The amount of parameters
	if (argc < FOUR)
	{
		printf("The program didn't receive all the parameters.\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	for (i = 0; i < strlen(argv[2]); i++)
	{
		whereToStart = whereToStart * 10 + (*(argv[2] + i) - '0'); //Convert string to number
	}

	for (i = 0; i < strlen(argv[2]); i++)
	{
		whereToFinish = whereToFinish * 10 + (*(argv[3] + i) - '0'); //Convert string to number
	}

	if (whereToStart > whereToFinish) //If the start place is bigger then the finish place, it is an error
	{
		printf("The program didn't receive the right parameters,\ncheck the places where you want to start and where you want to finish!.\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	myFile = fopen(argv[ONE], "rb"); //Opening file
	if (!myFile) //Testing if the opening of the file has been done successfully
	{
		printf("Error: the virus file doesn't exist.\n\n"); //Output
		system("PAUSE");
		return 1;
	}
	
	virus = fopen("virus.bin", "wb"); //Opening file
	if (!virus) //Testing if the opening of the file has been done successfully
	{
		printf("Error: the outputFile can't be created.\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	if (CreateVirus(myFile, virus, whereToStart, whereToFinish)) //Function call
	{
		//There was a problem in the function
		//The message to the user was written in the function
		return 1;
	}

	if (fclose(myFile) == EOF) //Closing file
	{
		//Testing if the closing of the file has been done successfully
		printf("Error closing the file\n\n"); //Output
		if (fclose(virus) == EOF) //Closing file
		{
			//Testing if the closing of the file has been done successfully
			printf("Error closing the file\n\n"); //Output
			system("PAUSE");
			return 1;
		}
		system("PAUSE");
		return 1;
	}

	if (fclose(virus) == EOF) //Closing file
	{
		//Testing if the closing of the file has been done successfully
		printf("Error closing the file\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	printf("Check the file \"virus.bin\", the virus is the there!\n\n"); //Output

	system("PAUSE");
	return 0;
}

/*
The purpose of the function is to find the virus in the file and copy it to the virus file.
Function accepts a file pointer, pointer of the virus file, the place where the virus starts, and where the virus ends.
The function returns 1 if there was a problem, otherwise it returns 0.
*/
int CreateVirus(FILE* myFile, FILE* virusFile, int whereToStart, int whereToFinish)
{
	char fileLetter = ' '; //Setting Variables
	int place = 0; //Setting Variables

	if (fseek(myFile, whereToStart, SEEK_SET) != ZERO) //Moving the pointer to the beginning of the file 
	{
		printf("There was an error in moving the pointer in the virus file.\n\n"); //Output
		system("PAUSE");
		return 1;
	}

	while ((fread(&fileLetter, sizeof(char), ONE, myFile) != ZERO) && (place <= whereToFinish)) //Reading letters from the file
	{
		if (fwrite(&fileLetter, sizeof(char), ONE, virusFile) == 0) //Writing letters to the virus file
		{
			printf("There was a problem with putting the character %c\n\n", fileLetter); //Output
			system("PAUSE");
			return 1;
		}
		place = ftell(myFile); //Checking where the pointer points
	}

	return 0;
}