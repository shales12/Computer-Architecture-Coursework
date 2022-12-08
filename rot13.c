#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main(int argc, char** argv){
int i;

for(i=0;i<strlen(argv[1]);i++){
    if(isalpha(argv[1][i])){
        if(argv[1][i] > 97){
            int off = argv[1][i] - 97;
            int new = (off + 13)%26;
            printf("%c",(new + 97));
            }

        else{
            int off = argv[1][i] - 65;
            int new = (off + 13)%26;
            printf("%c",(new + 65));
            }
        }

        else{
            printf("%c",argv[1][i]);
        }
    }

printf("\n");
}