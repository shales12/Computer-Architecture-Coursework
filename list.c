#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct intNode {
    int intVal;
    struct intNode *nextNode;
};

struct intNode *insertN(int newVal, struct intNode *headerPointer){
	struct intNode *newNode = (struct intNode *)malloc(sizeof(struct intNode));
	newNode->intVal = newVal;
	newNode->nextNode = NULL;

	if (headerPointer == NULL) 
		headerPointer = newNode;
	else{
		if (headerPointer->intVal == newVal){
			free(newNode);
			return(headerPointer);
		}
		
		if (headerPointer->intVal > newVal){
		 	newNode->nextNode = headerPointer;
		 	headerPointer = newNode;
			return(headerPointer);
		}
		
		struct intNode *currentPointer = headerPointer; 
		while ((currentPointer->nextNode != NULL) && (currentPointer->nextNode->intVal < newVal))
		{
			currentPointer = currentPointer->nextNode;
		}
		if (currentPointer->nextNode != NULL && currentPointer->nextNode->intVal == newVal) 
		{
			free(newNode);
			return(headerPointer);
		}

		newNode->nextNode = currentPointer->nextNode;
		currentPointer->nextNode = newNode;
	}
	return(headerPointer);
}



struct intNode *deleteN(int deleteVal, struct intNode *headerPointer)
{
	if (headerPointer == NULL) 
		return(headerPointer);

	struct intNode *currentPointer = headerPointer; 
	struct intNode *deleteNodePointer = NULL;

	if (currentPointer->intVal == deleteVal) 
	{
		headerPointer = headerPointer->nextNode;
		free(currentPointer);
	}
	else 
	{
		while ((currentPointer->nextNode != NULL) && (currentPointer->nextNode->intVal != deleteVal)) 
		{
			currentPointer = currentPointer->nextNode;
		}

		if (currentPointer->nextNode != NULL) 
		{
			deleteNodePointer = currentPointer->nextNode;
			currentPointer->nextNode = currentPointer->nextNode->nextNode;
			free(deleteNodePointer);
		}
	}
	return(headerPointer);
}



int main(int argc, char* argv[]) 
{
	char operation[2];
	int inputVal;
	struct intNode *currentPointer = NULL;
	struct intNode *headerPointer = NULL;
	int lengthOfList; 

	while(scanf("%s %d", operation, &inputVal) != EOF)   
	{
		if (operation[0] == 'i')
			headerPointer = insertN(inputVal, headerPointer);
		else if (operation[0] == 'd')
			headerPointer = deleteN(inputVal, headerPointer);

		lengthOfList = 0;
		currentPointer = headerPointer;
		while(currentPointer != NULL)
		{
			lengthOfList++;
			currentPointer = currentPointer->nextNode;
		}
		printf("%d :", lengthOfList);   


		currentPointer = headerPointer;
		while(currentPointer != NULL)
		{
			printf(" %d", currentPointer->intVal);
			currentPointer = currentPointer->nextNode;
		}
		printf("\n");
	}
	
	while(headerPointer)
	{
		currentPointer = headerPointer;
		headerPointer = headerPointer->nextNode;
		free(currentPointer);
	}
	EXIT_SUCCESS;
}