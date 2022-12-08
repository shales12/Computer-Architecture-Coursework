#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX_LINE_SIZE 10000

void freeEntireArray(int** arr, int dimensionLength){
	for(int a=0; a<dimensionLength; a++){
		free(arr[a]);
	}
	free(arr);
}

void mexp(int dimensionLength, int **arr, int exponent){
	int a=0, l=0;

	int **result = (int**)malloc(dimensionLength*sizeof(*result));
	for(a=0; a<dimensionLength; a++){
		result[a] = (int*)malloc(dimensionLength*sizeof(int));
	}

	for(a=0; a<dimensionLength; a++){
		for(l=0; l<dimensionLength; l++)
		{
			result[a][l] = arr[a][l];
		}
	}

	for(l=1;l<exponent;l++){
		int **currentResult= (int**)malloc(dimensionLength*sizeof(*currentResult));
		for(a=0; a<dimensionLength; a++){
			currentResult[a] = (int*)malloc(dimensionLength*sizeof(int));
		}
		for(int u=0; u<dimensionLength; u++){
			for(int v=0; v<dimensionLength; v++){
				currentResult[u][v] = 0;
			}
		}
		for (int x = 0; x < dimensionLength; ++x){
			for (int y = 0; y < dimensionLength; ++y){
				for (int z = 0; z < dimensionLength; ++z){
					currentResult[x][y] += result[x][z] * arr[z][y];
				}
			} 
		}
		freeEntireArray(result,dimensionLength);
		result = currentResult;
	}

	for (int i = 0; i < dimensionLength; ++i){
		for (int j = 0; j < dimensionLength; ++j){
			if(j == 0)
				printf("%d", result[i][j]); 
			else
				printf(" %d", result[i][j]); 
		}
		printf("\n");
	}
	freeEntireArray(arr, dimensionLength);
	freeEntireArray(result, dimensionLength);
	return;
}

int main(int argc, char* argv[]){
	if(argc < 2){
		return EXIT_FAILURE;
	}

	FILE *filePointer;
	char nextRow[MAX_LINE_SIZE];
	int returnCode=0;
	int dimensionLength=0;
	int exponent = 0;
	
	filePointer = fopen(argv[1], "r");
	if (filePointer == NULL) {
		return EXIT_FAILURE;
	}

	returnCode = fscanf(filePointer, "%d\n", &dimensionLength);
	if (returnCode != 1) {
		return EXIT_FAILURE;
	}
	int **matrix = (int**)malloc(dimensionLength*sizeof(int*));

	for(int i=0; i<dimensionLength; i++)
		matrix[i] = (int*)malloc(dimensionLength*sizeof(int));
	for(int i=0; i<dimensionLength; i++) {
		if (fgets(nextRow, MAX_LINE_SIZE, filePointer) == NULL) {
			freeEntireArray(matrix, dimensionLength);
			EXIT_FAILURE;
		}
		matrix[i][0] = atoi(strtok(nextRow," "));

		for(int j=1; j<dimensionLength; j++){			
			matrix[i][j] = atoi(strtok(NULL," "));
		}
	}
	
	returnCode = fscanf(filePointer, "%d\n", &exponent);
	if (returnCode != 1) {
		freeEntireArray(matrix, dimensionLength);
		EXIT_FAILURE;
	}

	mexp(dimensionLength, matrix, exponent);
	EXIT_SUCCESS;
}