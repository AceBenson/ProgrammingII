#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>

typedef struct _Node{
    char c;
    bool value;
    struct _Node* left;
    struct _Node* right;
    struct _Node* parent;
} Node;

Node** NodePtr;

void constructTree(Node** curNode);
void printTree(Node* curNode);
void reCal(Node* curNode);
void freeTree(Node* curNode);

int main(){
    int T;
    scanf("%d", &T);

    while(T--){
        int N, M;
        scanf("%d %d\n", &N, &M);

        NodePtr = (Node**)malloc(sizeof(Node*) * (M+1));

        Node* root = NULL;
        // getchar();
        constructTree(&root);
        root->parent = NULL;
        int i=0;
        for( i=0 ; i<M ; ++i){
            int num;
            scanf("%d", &num);
            NodePtr[num]->value = !NodePtr[num]->value;
            reCal(NodePtr[num]->parent);
            printf("%d\n", root->value);
        }
        free(NodePtr);
        freeTree(root);
    }
    return 0;
}

void constructTree(Node** curNode){
    char ch = getchar();
    switch(ch){
        case '\n':
            return;
        case '|':
        case '&':
            (*curNode) = (Node*)malloc(sizeof(Node));
            (*curNode)->c = ch;
            (*curNode)->value = false;
            constructTree(&((*curNode)->left));
            constructTree(&((*curNode)->right));
            ((*curNode)->left)->parent = (*curNode); //?
            ((*curNode)->right)->parent = (*curNode); //?
            break;
        case '[':
            ch = getchar();
            (*curNode) = (Node*)malloc(sizeof(Node));
            (*curNode)->c = ch;
            (*curNode)->value = false;
            (*curNode)->left = NULL;
            (*curNode)->right = NULL;

            int index = ch - '0';
            NodePtr[index] = (*curNode);

            getchar();
            break;
    }
}

void printTree(Node* curNode){
    if(!curNode)
        return;
    printf("%c ", curNode->c);
    printTree(curNode->left);
    printTree(curNode->right);
}

void reCal(Node* curNode){
    if(!curNode)
        return;
    if(curNode->c == '|'){
        bool newValue = curNode->left->value | curNode->right->value;
        if(newValue == curNode->value)
            return;
        else{
            curNode->value = newValue;
            reCal(curNode->parent);
        }
    }else if(curNode->c == '&'){
        bool newValue = curNode->left->value & curNode->right->value;
        if(newValue == curNode->value)
            return;
        else{
            curNode->value = newValue;
            reCal(curNode->parent);
        }
    }else{
    	
    }
}

void freeTree(Node* curNode){
    if(!curNode)
        return;
    freeTree(curNode->left);
    freeTree(curNode->right);
    free(curNode);
}
