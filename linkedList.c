#include<stdio.h>
#include<stdlib.h>

//Buat nodenya
typedef struct Node{
    int num;
    struct Node* next;
}Node;

Node* head = NULL;
Node* tail = NULL;

Node* createNode(int number){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->num=number;
    newNode->next=NULL;
    return newNode;
}

//untuk memasukkan angka di depan
void pushHead(int number){
    Node* newNode= createNode(number);
    if(head==NULL){
        head=tail=newNode;
    } else {
        newNode->next=head;
        head=newNode;
    }
}

//untuk memasukkan angka di belakang
void pushTail(int number){
    Node* newNode = createNode(number);
    if(head==NULL){
        head=tail=newNode;
    } else {
        tail->next=newNode;
        tail=newNode;
    }
}

//untuk menghapus nilai paling depan (head)
void popHead(){
//Tidak perlu parameter
    if(head==NULL){
        printf("Empty data\n");
    } else if(head==tail){
        free(head);
        head=tail=NULL;
    } else {
        Node* temp = head;
        head=head->next;
        free(temp);
    }
    //Berhasil popHead
}

//Untuk menghapus nilai paling belakang
void popTail(){
    if(head==NULL){
        printf("Empty data\n");
    } else if(head==tail){
        free(head);
        head=tail=NULL;
    } else {
        //Perbedaannya ada disini
        Node* temp = head;
        while(temp->next!=tail){
            temp=temp->next;
        }
        //Kalau sudah mencapai sebelum tail
        free(tail);
        tail=temp;
        tail->next=NULL;
    }
    //Berhasil di popTail
}

//Untuk menghapus semua list:
void popAll(){
    while(head!=NULL){
        popHead();
    }
    printf("All list deleted\n");
}

//buat fungsi untuk bisa print semuanya
void printList(){
    Node* temp = head;
    while(temp!=NULL){
        printf("%d ", temp->num);
        temp=temp->next;
    }
    printf("\n");
}


int main(){
    //untuk angka pertama
    pushHead(1);
    pushHead(2);
    pushHead(3);
    pushHead(4);
    //untuk menambahkan dari belakang
    pushTail(10);
    pushTail(11);
    pushTail(12);
    pushTail(13);

    //List sekarang= 4 3 2 1 10 11 12 13

    //menghapus "kepalanya"
    popHead();
    //menghapus "Ekornya"
    popTail();

    // sekarang: 3 2 1 10 11 12

    //di print dulu semua listnya
    printList();
    //menghapus semua malloc
    popAll();

    return 0;
}