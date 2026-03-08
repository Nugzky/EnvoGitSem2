#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//KUrang lebihnya
char stack[100];
int n = 0;

void push(char a) {
	stack[n] = a;
	n++;
}

char pop() {
	if (n == 0) return 0;
	n--;
	return stack[n];
}

char top() {
	if (n==0) return 0;
	return stack[n-1];
}

char* infixToPostfix(char infix[]) {
	int l = strlen(infix);
	// FIX: Menggunakan strlen + 1 agar memori dinamis dan sesuai panjang string
	char* output = (char*)malloc((l + 1) * sizeof(char));
	int j = 0;
	int level[300];
	level['('] = 1;
	level[')'] = 1;
	level['+'] = 6;
	level['-'] = 6;
	level['*'] = 5;
	level['/'] = 5;
	level['%'] = 5;
	
	n = 0; // FIX: Pastikan stack kosong sebelum mulai
	
	for(int i=0; i<l; i++) {
		char c = infix[i];
		if(('0' <= c && c <= '9') ||
			('a' <= c && c <= 'z') ||
			('A' <= c && c <= 'Z')) { // operand
			output[j] = c;
			j++;
		} else { // operator
			if (c == ')') {
				while (top() != '(') {
					output[j] = pop();
					j++;
				}
				pop();
			} else {
				while (n > 0 && top() != '(' && level[(int)top()] <= level[(int)c]) {
					output[j] = pop();
					j++;
				}
				push(c);
			}
		}
	}
	while (n > 0) {
		output[j] = pop();
		j++;
	}
	output[j] = '\0'; // FIX: Gunakan karakter null terminator standar C
	return output;
}

char *reverse(char *str) {
	int l = strlen(str);
	// FIX: Menggunakan strlen + 1, bukan sizeof(pointer)
	char *result = (char*)malloc((l + 1) * sizeof(char));
	for (int i=0; i<l; i++){
		result[i] = str[l-i-1];
	}
	result[l] = '\0'; // FIX: Tambahkan null terminator di akhir string hasil reverse
	return result;
}

char* infixToPrefix(char infix[]) {
	int l = strlen(infix);
	// FIX: Menggunakan strlen + 1, bukan sizeof(pointer)
	char* output = (char*)malloc((l + 1) * sizeof(char));
	int j = 0;
	int level[300];
	level['('] = 1;
	level[')'] = 1;
	level['+'] = 6;
	level['-'] = 6;
	level['*'] = 5;
	level['/'] = 5;
	level['%'] = 5;
	
	n = 0; // FIX: Pastikan stack kosong sebelum mulai

	for(int i=l-1; i>=0; i--) {
		char c = infix[i];
        if (c == ' ') continue; // Abaikan spasi dan lanjut ke karakter berikutnya
		if(('0' <= c && c <= '9') ||
			('a' <= c && c <= 'z') ||
			('A' <= c && c <= 'Z')) { // operand
			output[j] = c;
			j++;
		} else { // operator
			if (c == '(') {
				while (top() != ')') {
					output[j] = pop();
					j++;
				}
				pop();
			} else {
				while (n > 0 && top() != ')' && level[(int)top()] < level[(int)c]) {
					output[j] = pop();
					j++;
				}
				push(c);
			}
		}
	}
	while (n > 0) {
		output[j] = pop();
		j++;
	}
	output[j] = '\0'; // FIX: Gunakan karakter null terminator
	
	// FIX: Simpan hasil reverse, lalu free output yang lama untuk mencegah memory leak
	char* finalResult = reverse(output);
	free(output); 
	
	return finalResult;
}

int main() {
	char infix[100] = "4*(7+2/3)";
	printf("Infix  : %s\n", infix);
	
	char* postfix1 = infixToPostfix(infix);
	printf("Postfix: %s\n", postfix1);
	free(postfix1); // Praktik baik: bebaskan memori setelah selesai digunakan
	
	char* prefix1 = infixToPrefix(infix);
	printf("Prefix : %s\n\n", prefix1);
	free(prefix1);
	
	strcpy(infix, "1*2*3*4*5+6");
	printf("Infix  : %s\n", infix);
	char* postfix2 = infixToPostfix(infix);
	char* prefix2 = infixToPrefix(infix);
	printf("Postfix: %s\n", postfix2);
	printf("Prefix : %s\n\n", prefix2);
	free(postfix2); free(prefix2);
	
	strcpy(infix, "a*(b+c)/d");
	printf("Infix  : %s\n", infix);
	char* postfix3 = infixToPostfix(infix);
	char* prefix3 = infixToPrefix(infix);
	printf("Postfix: %s\n", postfix3);
	printf("Prefix : %s\n", prefix3);
	free(postfix3); free(prefix3);
	
	return 0;
}