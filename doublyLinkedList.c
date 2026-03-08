#include<stdio.h>
#include<stdlib.h>

//untuk buat structnya
typedef struct Node{
    int num;
    struct Node* next;
    struct Node* prev;
}Node;

//inisialisasi head dan tailnya
//INGATT:
//Selalu tambahkan [index] setelah tail atau head
Node* head[5]={NULL};
Node* tail[5]={NULL};

//Buat createNode
Node* createNode(int number){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->num=number;
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}

//buat menambahkan sesuai index dan number di gerbong terdepan
void pushHead(int index, int number){
    Node* newNode=createNode(number);
    if(head[index]==NULL){
        head[index]=tail[index]=newNode;
    } else {
        newNode->next=head[index];
        head[index]->prev=newNode;
        head[index]=newNode;
    }
}

//Menambahkan nilai di belakang di index tertentu
void pushTail(int index, int number){
    Node* newNode = createNode(number);
    if(head[index]==NULL){
        head[index]=tail[index]=newNode;
    } else {
        //Disini yang berbeda dengan pushHead
        tail[index]->next=newNode;
        newNode->prev=tail[index];
        tail[index]=newNode;
    }
}

//untuk menghapus nilai paling depan (head)
void popHead(int index){
    //Perlu index saja
    if(head[index]==NULL){
        printf("Empty list\n");
    } else if (head[index]==tail[index]){
        free(head[index]);
        head[index]=tail[index]=NULL;
    } else {
        Node* temp = head[index];
        head[index]=head[index]->next;
        head[index]->prev=NULL;
        free(temp);
    }
}

//untuk menghapus nilai terakhir di suatu index
void popTail(int index){
    if(head[index]==NULL){
        printf("Empty list\n");
    } else if (head[index]==tail[index]){
        free(head[index]);
        head[index]=tail[index]=NULL;
    } else {
        //Bagian disini yang beda
        Node* temp = tail[index];
        tail[index]=tail[index]->prev;
        tail[index]->next=NULL;
        free(temp);
    }
}

//untuk menggabungkan list-> mergeList(a,b) = list a kemudian ditambahkan b di belakangnya
void mergeList(int a, int b){
    if(head[b]==NULL){
        printf("Tidak perlu dilakukan apa2 karena list yang ingin ditambahkan kosong");
        return;
    }
    if(head[a]==NULL){
        //List yang dituju kosong:
        head[a]=head[b];
        tail[a]=tail[b];
    } else {
        //menyambungkan antara tail a dengan head b
        tail[a]->next=head[b];
        head[b]->prev=tail[a];
        //akhir list a jadi akhir list b
        tail[a]=tail[b];
    }
    head[b]=tail[b]=NULL;
}

//Menghapus semua list dalam suatu index
void popAll(int index){
    while(head[index]!=NULL){
        popHead(index);
    }
    printf("Deleted list in index: %d\n", index);
}

void printList(int index){
    Node* temp = head[index];
    if(temp==NULL){
        printf("Empty list\n");
        return;
    }
    printf("List di index ke-%d: ", index);
    while(temp!=NULL){
        printf("%d ",temp->num);
        temp=temp->next;
    }
    printf("\n");
}

int main(){
	//list arr index ke-0
	pushHead(0,1);
	pushHead(0,2);
	pushHead(0,3);
	pushHead(0,4);
	pushTail(0,10);
	pushTail(0,20);
	popHead(0);
	popTail(0);
	//list arr index ke-1
	pushHead(1,11);
	pushHead(1,12);
	pushHead(1,13);
	pushHead(1,14);
	pushHead(1,15);
	pushTail(1,20);
	pushTail(1,30);
	popHead(1);
	popTail(1);
	
	printList(0);
	printList(1);
	
	//mergelistnya
	mergeList(0,1);
	printf("Setelah hasil merge:\n");
	printList(0);
	printList(1);
	
	
	popAll(1);
	popAll(0);

    return 0;
}