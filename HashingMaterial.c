#include<stdio.h>
//#include<stdlib.h>

//fungsi awal:
int division(int num,int size){
    return num%size;
}

int lenNumber(int num){
    int l = 0;
    while(num>0){
        num /= 10;
        l++;
    }
    return l;
}

int midSquare(int num, int size){
    int square = num*num;
    int l = lenNumber(square);
    int k = lenNumber(size);
    int trimEnd = (l-k)/2;
    while(square>0&&trimEnd>0){
        square /= 10;
        trimEnd--;
    }
    int take=1;
    while(k>0){
        k--;
        take*=10;
    }
    return(square%take)%size;
}

int folding(int num, int size){
    int k = lenNumber(size);
    int total=0;
    int take=1;
    while(k>0){
        k--;
        take *= 10;
    }
    printf("%d\n", num);
    while(num>0){
        printf("%d ",num%take);
        total+=num%take;
        num /= take;
    }
    printf("\n");
    return total%size;
}

//sesuai namanya
int strToAscii(char kata[]){
    int total=0;
    for(int i=0;kata[i]!='\0';i++){
        total+=kata[i];
    }
    return total;
}

void toLower(char kata[]){
    for(int i=0;kata[i]!='\0';i++){
        if('A'<=kata[i]&&kata[i]<='Z'){
            kata[i]+='a'-'A';
        }
    }
}

int main(){
char kata[] = "Filbert";
	printf("Name : %s\n", kata);
	toLower(kata);
	printf("Lower Case: %s\n", kata);
	int total = strToAscii(kata);
	printf("Total: %d\n", total);
	printf("Division: %d\n", division(total, 20));
	printf("Mid Square: %d\n", midSquare(total, 20));
	printf("Folding: %d\n", folding(total, 20));
	printf("Folding from square: %d\n", folding(total * total, 20));
    return 0;
}