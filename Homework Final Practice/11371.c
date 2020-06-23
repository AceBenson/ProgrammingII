#include "11371.h"
#include <stdio.h>

int main(void){
	Node *p1=create(); //polynomial linked list1
	Node *p2=create(); //polynomial linked list2
	Node *mul=multiple(p1,p2);
	printNode(p1);
	printNode(p2);
	printf("PRINT\n");
	printNode(mul);
	destroy(mul);
	destroy(p2);
	destroy(p1);
	return 0;
}