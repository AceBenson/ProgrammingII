#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    int data;
    int index;
    struct _Node* left;
    struct _Node* right;
} Node;

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    char* ans = (char*) malloc(sizeof(char) * N);

    Node* head = NULL;
    Node* prev = NULL;
    for(int i=0 ; i<N ; ++i){
        int num;
        scanf("%d", &num);
        Node* newNode = (Node*) malloc(sizeof(Node));
        newNode->index = i;
        newNode->data = num;
        newNode->left = NULL;
        newNode->right = NULL;

        if(!head){
            head = newNode;
            prev = head;
        }else{
            prev->right = newNode;
            newNode->left = prev;
            prev = newNode;
        }
    }
    Node* tail = prev;

    // Node* curNode = head;
    // while(curNode){
    //     printf("%d ", curNode->data);
    //     curNode = curNode->right;
    // }
    
    // Node** Array = (Node**) malloc(sizeof(Node*) * N);
    
    Node* curNode = head;
    Node* maxNode = head;
    while(curNode){
        if(curNode->data > maxNode->data)
            maxNode = curNode;
        curNode = curNode->right;
    }
    char curPerson = 'S';
    int flag = 1;
    while(flag == 1){
        ans[maxNode->index];

    }

    


    return 0;
}