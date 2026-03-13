#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10 // Ukuran table (bisa diubah)

// 1. Definisikan struktur data untuk menampung key (nama)
struct Node {
    char name[50];
    struct Node *next; // Pointer untuk Chaining (Linked List)
};

// 2. Deklarasi Table Hash (Array of Pointers)
struct Node *hashTable[SIZE];

// --- FUNGSI MILIKMU (DIPERTAHANKAN) ---

int division(int num, int size) {
    return num % size;
}

int lenNumber(int num) {
    int l = 0;
    while(num > 0) { num /= 10; l++; }
    return l;
}

int midSquare(int num, int size) {
    int square = num * num;
    int l = lenNumber(square);
    int k = lenNumber(size);
    int trimEnd = (l - k) / 2;
    while(square > 0 && trimEnd > 0) {
        square /= 10;
        trimEnd--;
    }
    int take = 1;
    for(int i = 0; i < k; i++) take *= 10;
    return (square % take) % size;
}

int strToAscii(char kata[]) {
    int total = 0;
    for(int i = 0; kata[i] != '\0'; i++) total += kata[i];
    return total;
}

void toLower(char kata[]) {
    for(int i = 0; kata[i] != '\0'; i++) {
        if('A' <= kata[i] && kata[i] <= 'Z') kata[i] += 'a' - 'A';
    }
}

// --- FUNGSI IMPLEMENTASI BARU ---

// Fungsi untuk memasukkan data ke table
void insert(char *name) {
    char tempName[50];
    strcpy(tempName, name);
    toLower(tempName);

    // Langkah A: Hitung index menggunakan salah satu fungsimu (Contoh: Division)
    int asciiValue = strToAscii(tempName);
    int index = division(asciiValue, SIZE);

    // Langkah B: Siapkan node baru
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    newNode->next = NULL;

    // Langkah C: Chaining (Jika index penuh, sambungkan di depan/Push Head)
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
    printf("Data '%s' berhasil masuk ke Index [%d]\n", name, index);
}

// Fungsi untuk menampilkan isi table
void display() {
    printf("\n=== ISI HASH TABLE (CHAINING) ===\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Index [%d]: ", i);
        struct Node *curr = hashTable[i];
        while (curr != NULL) {
            printf("%s -> ", curr->name);
            curr = curr->next;
        }
        printf("NULL\n");
    }
    printf("=================================\n");
}

int main() {
    // Inisialisasi table menjadi kosong (NULL)
    for (int i = 0; i < SIZE; i++) hashTable[i] = NULL;

    // Contoh Input Data
    insert("Filbert");
    insert("Budi");
    insert("Alice");
    insert("Tono");
    insert("Ani");
    insert("Ayanami rei"); // Ani mungkin akan tabrakan dengan Tono/Budi tergantung SIZE

    display();

    return 0;
}