#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct bTree {
  int value;
  struct bTree *childleft;
  struct bTree *childright;
};

typedef struct bTree bstnode;


bstnode* insertN(bstnode *par, int val){
	if (par == NULL){
		par = (bstnode*)malloc(sizeof(bstnode));
		par->value = val;
		par->childleft = NULL;
		par->childright = NULL;
		printf("inserted\n");
		return (par);
	}
	if (par->value == val){
		printf("not inserted\n");
		return par; 
	}

	else if (val < par->value){
		par->childleft = insertN(par->childleft, val);
	}
	
	else if (val > par->value){
		par->childright = insertN(par->childright, val);
	}
	
	return(par);
}


void searchN(bstnode *par, int val){
	if (par == NULL) {
		printf("absent\n");
		return;
	}

	if (par->value == val){
		printf("present\n");
		return;
	}

	if (val > par->value){
		searchN(par->childright, val);
  	}

	else if(val < par->value){
		searchN(par->childleft, val);
  	}
}

bstnode* maxValInLeftTree(bstnode *par){
	if(par == NULL){
    return par;
  	}
	else if(par->childright != NULL){
		return maxValInLeftTree(par->childright); 
  	}
	
	return par;
}


void printBTree(bstnode *node){
	if (node == NULL) 
		return;
	
	printf("(");
	printBTree(node->childleft);
	printf("%d", node->value);
	printBTree(node->childright);
	printf(")");
}


bstnode * deleteN(bstnode *par, int val){
	
	if(par == NULL){
		printf("absent\n");
		return par;
	}
	if(par->value > val){
		par->childleft = deleteN(par->childleft, val);
  	}
	else if(par->value < val){
		par->childright = deleteN(par->childright, val);
  	}
	else{
		if(par->childleft == NULL && par->childright == NULL){
			printf("deleted\n");
			free(par);
			return NULL;
		}
		else if(par->childleft == NULL || par->childright == NULL){
			bstnode *replacement;
			if(par->childright == NULL){
				replacement = par->childleft;
			}
			else if(par->childleft==NULL){
				replacement = par->childright;
			}
			printf("deleted\n");
			free(par);
			return replacement;
		}
		else{
      	bstnode *replacement = maxValInLeftTree(par->childleft);
      	par->value = replacement->value;
      	par->childleft = deleteN(par->childleft, replacement->value);
		}
	}
	
	return par;
}

void freeEntireTree(bstnode *par){
	if (par == NULL){
		return;
	}

	else{
		freeEntireTree(par->childleft);
		freeEntireTree(par->childright);
		free(par);
	}

	return;
}



int main() {
	char inputStr[100];
	char operation[2];  
	int value;
	int buffsize = 99;
	bstnode *parPointer = NULL;
	while(fgets(inputStr, buffsize, stdin) != NULL){
		operation[0] = inputStr[0];
		if (operation[0] == 'p'){
			printBTree(parPointer);
			printf("\n");
		}

		else{
			value = atoi(inputStr+2);
			if (operation[0] == 'i'){
				parPointer = insertN(parPointer, value);
			}
			else if (operation[0] == 's'){
				searchN(parPointer, value);
			}
			else if (operation[0] == 'd'){
				parPointer = deleteN(parPointer, value);
			}
    }
	}
	freeEntireTree(parPointer);
	EXIT_SUCCESS;
}