#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  WORD_LENGTH  30
#define  INITIAL_ARRAY_MAX 50

void TakeOut(char*** wordArray, int* wordcount, char* wordPtr);
void removeWord(char ****wordarray, int *wordcount, int *capacity);
void Insert(char ****wordarray, int *wordcount, int *capacity);
void saveDictionary(char ***wordarray, char *output, int wordcount);
void searchWord(char ***wordarray, int *wordcount);
void Count(int wordcount);
void GoTo(char*** wordArray, int *capacity, int *wordcount, char* output, char operation);
void menu(char*** wordArray, int *capacity, int *wordcount, char* output);
void doubleArray(char ***wordArray,int *capacity,int *wordcount);
void Sort(char*** wordArray, int* wordcount, char* wordPtr);
void loadDictionary(char*** wordArray, int* capacity, int* wordcount, char* file);


int main(int argc, char* argv[])
{
    	char **wordArray; 
    	int capacity = INITIAL_ARRAY_MAX;
    	int wordcount = 0;
    	if (argc != 3)
    	{
        	fprintf(stderr,"Usage: %s inputfile outputfile\n", argv[0]);
        	return 1;
    	}
	wordArray = (char**)malloc(sizeof(char*) * (capacity));
	char* file = argv[1];
	char* output = argv[2];
	loadDictionary(&wordArray, &capacity, &wordcount, file);
	printf("\n  Finished loading %d words.\n", wordcount);
	menu(&wordArray, &capacity, &wordcount, output);

    return 0;
}

void loadDictionary(char*** wordArray, int* capacity, int* wordcount, char* file){	
	char word[WORD_LENGTH];
	char *ptr;
	FILE *fp = fopen(file,"r");
	int i=0;
	if(fp == NULL)
	{
		printf("couldn't open input file");
		exit(0);
	}
	while (fscanf(fp, "%s", word) == 1)
   	{
		if ((*wordcount) >= (*capacity))
		{
			doubleArray(wordArray,capacity,wordcount);
		}
		ptr = (char*)malloc(sizeof(word));
		strcpy(ptr,word);
		Sort(wordArray, wordcount, ptr);
		(*wordcount)++;
	}
	fclose(fp);
}



void Sort(char*** wordArray, int* wordcount, char* wordPtr){
	int i = 0;
	int insert = 0;
	int result;
	int position;
	char* tempPtr;
	int pos;
	if(((*wordArray)[0]) == NULL)
	{
		(*wordArray)[0]= wordPtr;
	}
	else
	{
		while(i < (*wordcount) & (insert != 1))
		{
			if(strcmp(wordPtr, (*wordArray)[i]) == 0)
			{
				(*wordcount)--;
				break;
			}
			if(strcmp(wordPtr, (*wordArray)[i]) < 0)
			{	
				pos = i;
				position = (*wordcount);
				while(pos < (*wordcount))
				{
					tempPtr = (*wordArray)[position-1];
					(*wordArray)[position] = tempPtr;
					pos++;
					position--;
				}
    				(*wordArray)[(i)] = wordPtr;
				insert = 1;
			}
			i++;
		}
			if(insert == 0)
			{
				(*wordArray)[(i)] = wordPtr; 
			}	

	}
}

void doubleArray(char ***wordArray,int *capacity,int *wordcount){
	char **array;
	*capacity = (*capacity) * 2;
	array = (char**)malloc(sizeof(char*) * (*capacity));
	int i;
	for(i=0;i<(*wordcount);i++)
	{
		(array)[i] = (*wordArray)[i];
	}
	free(*wordArray);
	*wordArray = array;
}	

void menu(char*** wordArray, int *capacity, int *wordcount, char* output){
	int i =0;
	printf("------------------MENU--------------------------");
	printf("\n1) press S to search for a word");
	printf("\n2) press I to insert a word");
	printf("\n3) press R to remove a word");
	printf("\n4) press C to count number of words");
	printf("\n5) press Q to Quit");
	printf("\nEnter: ");
	char operation;
	char stuff;
	operation = getchar();
	while(operation == '\n')
	{
		operation = getchar();
	}
	printf("\n");
	GoTo(wordArray, capacity, wordcount,output,operation);
}
	
void GoTo(char*** wordArray, int *capacity, int *wordcount, char* output, char operation){
	int exit = 1;
	if(operation == ('S' | 's'))
	{	
		searchWord(wordArray, wordcount);
	}
	else if(operation ==('I' | 'i'))
	{
		Insert(&wordArray,wordcount,capacity);
	}
	else if(operation ==('R' | 'r'))
	{
		removeWord(&wordArray,wordcount,capacity);
	}
	else if(operation ==('C' | 'c'))
	{
		Count(*wordcount);
	}
	else if(operation ==('Q' | 'q'))
	{
		saveDictionary(wordArray,output,*wordcount);
		exit = 0;
	}
	if(exit)
	{
		menu(wordArray, capacity, wordcount,output);
	}
}

void Count(int wordcount){
		printf("The current word count is: ");
		printf("%d",wordcount);
		printf("\n");
}

void searchWord(char ***wordarray, int *wordcount){
	char garbage;
	garbage = getchar();
	while(garbage != '\n')
	{
		garbage = getchar();
	}
	printf("Enter word: ");
	char *text = (char*)malloc(sizeof(char*));
	scanf("%s" ,text);
	int i = 0;
	int yes =0;
	while((i < (*wordcount)) & !yes)
	{
		if(strcmp(text,(*wordarray)[i]) == 0)
		{
			yes = 1;
			printf("found");
			printf("\n");
		}
		i++;
	}
	if(!yes)
	{
		printf(" Not found");
		printf("\n");
	}
	free(text);
	fflush(stdin);
}

void saveDictionary(char ***wordarray, char *output, int wordcount){
	printf("---ENDING PROGRAM: WRITING TO FILE NOW----------"); 
	FILE *fp = fopen(output, "w");
	int i = 0;
	while(i < wordcount)
	{
		fprintf(fp,(*wordarray)[i]);
		fprintf(fp,"\n");	
		i++;
	}
	i =0;
	fclose(fp);
	while(i<wordcount)
	{
		free((*wordarray)[i]);
		i++;
	}
}

void Insert(char ****wordarray, int *wordcount, int *capacity){
	char garbage;
	garbage = getchar();
	while(garbage != '\n')
	{
		garbage = getchar();
	}
	int count = *wordcount;
	printf("Enter word to Insert: ");
	char *text = (char*)malloc(sizeof(char*));
	char word[30];
	scanf("%s" ,word);
	strcpy(text, word);
	Sort(&(**wordarray), wordcount, text);
	(*wordcount)++;
	if(count != (*wordcount))
	{
		printf("word inserted");
		printf("\n");
	}else
	{
		printf("word already in Dictionary");
		printf("\n");
	}
}
void removeWord(char ****wordarray, int *wordcount, int *capacity){
	char garbage;
	garbage = getchar();
	while(garbage != '\n')
	{
		garbage = getchar();
	}
	printf("Enter word to Remove: ");
	char *text = (char*)malloc(sizeof(char*));
	char word[30];
	int i = 0;
	int count = *wordcount;
	scanf("%s" ,word);
	strcpy(text, word);
	while((i < (*wordcount)))
	{
		if(strcmp(text,(**wordarray)[i]) == 0)
		{
			TakeOut(&(**wordarray), wordcount, text);
			(*wordcount)--;
		}
		i++;
	}
	if(count != (*wordcount))
	{
		printf("word deleted");
		printf("\n");
	}else
	{
		printf("word not in Dictionary");
		printf("\n");
	}
}

void TakeOut(char*** wordArray, int* wordcount, char* wordPtr){
	int i = 0;
	int remove = 0;
	int result;
	int position;
	char* tempPtr;
	int pos;
	while(i < (*wordcount) & (remove != 1))
	{
		if(strcmp(wordPtr, (*wordArray)[i]) == 0)
		{	
			pos = i;	
			while(pos < (*wordcount))
			{
				tempPtr = (*wordArray)[pos + 1];
				free((*wordArray)[pos]);
				(*wordArray)[pos] = tempPtr;
				pos++;
				remove = 1;
			}
		}
		i++;
	}
}
