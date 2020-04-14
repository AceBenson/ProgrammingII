#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Something like Python
>> y = 2
>> z = 2
>> x = 3*y + 4/(2*z)

*/

/*
the only type: integer
everything is an expression

	statement 	:= END | expr END
	expr      	:= term expr_tail
	expr_tail 	:= ADD_SUB_AND_OR_XOR term expr_tail | NiL
	term      	:= factor term_tail
	term_tail 	:= MUL_DIV factor term_tail|NiL
	factor    	:= INT | ADD_SUB INT | ADD_SUB ID | ID ASSIGN expr| ID | LPAREN expr RPAREN

*/

#define MAXLEN 256
#define TBLSIZE 64


typedef enum {MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, DEVIDEBYZERO} ErrorType;
typedef enum {UNKNOWN, END, INT, ID, ORANDXOR, ADDSUB, MULDIV, ASSIGN, LPAREN, RPAREN, ENDFILE} TokenSet;

typedef struct {
    char name[MAXLEN];
    int val;
} Symbol;

Symbol table[TBLSIZE];

typedef struct _Node {
    char lexeme[MAXLEN];
    TokenSet data;
    int val;
    struct _Node *left, *right;
} BTNode ;

TokenSet lookahead = UNKNOWN;
char lexeme[MAXLEN];

BTNode* factor(void);
BTNode* term(void);
BTNode* term_tail(BTNode *);
BTNode* expr(void);
BTNode* expr_tail(BTNode *);
void statement(void);
char* getLexeme(void) ;
TokenSet getToken(void) ;
void advance(void) ;
void error(ErrorType) ;
int match(TokenSet) ;
int evaluateTree(BTNode *) ;
void printPrefix(BTNode *) ;
void freeTree(BTNode *);
BTNode* makeNode(TokenSet, const char *);
int getval(void);
int setval(char *, int);

// myFunc
bool isValid(BTNode* root);
bool checkTree(BTNode* root);

void resetNode(BTNode* node, int newVal);
void reconstructTree(BTNode* root);

void printAssembly(BTNode* root);

int main(void)
{
    /*
    freopen( "input.in" , "r" , stdin ) ;
    freopen( "output.out" , "w" , stdout ) ;
    */
    printf(">> ");
    while (1) {
        statement();
    }
    return 0;
}

int sbcount = 0; // 目前的變數有多少個
int getval(void) // 回傳INT || ID 的值
{
    int i, retval, found;

    if (match(INT)) { //如果是數字
        retval = atoi(getLexeme());
    } else if (match(ID)) { // 如果是變數
        i = 0; found = 0; retval = 0;
        while (i<sbcount && !found) { //去table找變數的值
            if (strcmp(getLexeme(), table[i].name)==0) {
                retval = table[i].val;
                found = 1;
                break;
            } else {
                i++;
            }
        }
        if (!found) { // 如果找完都沒找到，就創建這個變數
            if (sbcount < TBLSIZE) {
                strcpy(table[sbcount].name, getLexeme());
                table[sbcount].val = 0;
                sbcount++;
            } else {
                error(RUNOUT);
            }
        }
    }
    return retval;
}
int setval(char *str, int val) // 設置變數str的值為val
{
    int i, retval;
    i = 0;
    while (i<sbcount) {
        if (strcmp(str, table[i].name)==0) {
            table[i].val = val;
            retval = val;
            break;
        } else {
            i++;
        }
    }
    return retval;
}

int evaluateTree(BTNode *root)
{
    int retval = 0, lv, rv;
    if (root != NULL)
    {
        switch (root->data)
        {
        case ID:
        case INT:
            retval = root->val;
            break;
        case ASSIGN:
        case ADDSUB:
        case MULDIV:
        case ORANDXOR:
            lv = evaluateTree(root->left);
            rv = evaluateTree(root->right);
            if (strcmp(root->lexeme, "+") == 0)
                retval = lv + rv;
            else if (strcmp(root->lexeme, "-") == 0)
                retval = lv - rv;
            else if (strcmp(root->lexeme, "*") == 0)
                retval = lv * rv;
            else if (strcmp(root->lexeme, "/") == 0)
                retval = lv / rv;
            else if (strcmp(root->lexeme, "=") == 0)
                retval = setval(root->left->lexeme, rv);
            // TODO
            else if (strcmp(root->lexeme, "|") == 0)
                retval = lv | rv;
            else if (strcmp(root->lexeme, "&") == 0)
                retval = lv & rv;
            else if (strcmp(root->lexeme, "^") == 0)
                retval = lv ^ rv;
            break;
        default:
            retval = 0;
        }
    }
    return retval;
}


/* print a tree by pre-order. */
void printPrefix(BTNode *root)
{
    if (root != NULL)
    {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}


/* create a node without any child.*/
BTNode* makeNode(TokenSet tok, const char *lexe){
    BTNode *node = (BTNode*) malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TokenSet getToken(void)
{
    int i;
    char c;

    while ( (c = fgetc(stdin)) == ' ' || c == '\t' );  // 忽略空白字元

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i<MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ADDSUB;
    } else if (c == '|' || c == '&' || c =='^') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ORANDXOR;
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isalpha(c) || isdigit(c) || c == '_') {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

/* factor := INT | ADD_SUB INT | ADD_SUB ID | ID ASSIGN expr| ID | LPAREN expr RPAREN */

BTNode* factor(void)
{
    // printf("In factor function\n");
    BTNode* retp = NULL;
    char tmpstr[MAXLEN];

    if (match(INT)) { // INT
        retp =  makeNode(INT, getLexeme());
        retp->val = getval();
        advance();
    }
    else if (match(ID)) { // ID
        BTNode* left = makeNode(ID, getLexeme());
        left->val = getval();
        strcpy(tmpstr, getLexeme());
        advance();
        if (match(ASSIGN)) { // ID ASSIGN expr // ex. x = expr
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->right = expr();
            retp->left = left;
        } else {
            retp = left;
        }
    }
    else if (match(ADDSUB)) {
    	strcpy(tmpstr, getLexeme());
        advance();
        if (match(ID) || match(INT)) { // ADD_SUB INT // ADD_SUB ID
            retp = makeNode(ADDSUB, tmpstr);
            if (match(ID))
                retp->right = makeNode(ID, getLexeme());
            else
                retp->right = makeNode(INT, getLexeme());
            retp->right->val = getval();
            retp->left = makeNode(INT, "0");
            retp->left->val = 0;
            advance();
        } else {
            error(NOTNUMID);
        }
    }
    else if (match(ORANDXOR)){
        // TODO
        // maybe do nothing (?)
    }
    else if (match(LPAREN)) { // LPAREN expr RPAREN
        advance();
        retp = expr();
        if (match(RPAREN)) {
            advance();
        } else {
            error(MISPAREN);
        }
    } else {
        error(NOTNUMID);
    }
    return retp;
}

/* term := factor term_tail */
BTNode* term(void)
{
    // printf("In term function\n");
    BTNode *node;

    node = factor();

    return term_tail(node);
}

/* term_tail := MUL_DIV factor term_tail | NiL */
BTNode* term_tail(BTNode *left)
{
    // printf("In term_tail function\n");
    BTNode *node;

    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();

        node->left = left;
        node->right = factor();

        return term_tail(node);
    }
    else
        return left;
}

/* expr := term expr_tail */
BTNode* expr(void)
{
    // printf("In expr function\n");
    BTNode *node;

    node = term();

    return expr_tail(node);
}

/* expr_tail := ADD_SUB_AND_OR_XOR term expr_tail | NiL */
BTNode* expr_tail(BTNode *left)
{
    // printf("In expr_tail function\n");
    BTNode *node;

    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();

        node->left = left;
        node->right = term();

        return expr_tail(node);
    }else if(match(ORANDXOR)){
        // TODO
        node = makeNode(ORANDXOR, getLexeme());
        advance();

        node->left = left;
        node->right = term();

        return expr_tail(node);
    }
    else
        return left;
}

void advance(void)
{
    lookahead = getToken();
}

int match(TokenSet token)
{
    if (lookahead == UNKNOWN) advance();
    return token == lookahead;
}

char* getLexeme(void)
{
    return lexeme;
}

/* statement := END | expr END */

void statement(void)
{
    BTNode* retp;

    if (match(ENDFILE)) {

        exit(0);

    } else if (match(END)) {

        printf(">> ");
        advance();

    } else {

        retp = expr();
        if (match(END)) {

            int valid = isValid(retp);
            if(!valid){
                printf("EXIT 1\n");
                exit(0);
            }
            
            // printf("%d\n", evaluateTree(retp));
            // printPrefix(retp); 
            // printf("\n");

            reconstructTree(retp);

            // printf("%d\n", evaluateTree(retp));
            // printPrefix(retp); 
            // printf("\n");

            // TODO

            freeTree(retp);

            printf(">> ");
            advance();
        }

    }
}
void error(ErrorType errorNum)
{
    switch (errorNum) {
    case MISPAREN:
        fprintf(stderr, "Mismatched parenthesis\n");
        break;
    case NOTNUMID:
        fprintf(stderr, "Number or identifier expected\n");
        break;
    case NOTFOUND:
        fprintf(stderr, "%s not defined\n", getLexeme());
        break;
    case RUNOUT:
        fprintf(stderr, "Out of memory\n");
        break;
    case DEVIDEBYZERO:
        fprintf(stderr, "Devide by zero");
        break;
    }
    printf("EXIT 1\n");
    exit(0);
}
/* clean a tree.*/
void freeTree(BTNode *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// myFunc
bool isValid(BTNode* root){
    printf("In isValid function\n");
    if(root->data == ASSIGN && root->left->data == ID){ // ID ASSIGN expr
        if(checkTree(root->right))
            return true;
    }
    return false;
}

bool checkTree(BTNode* root){
    if(!root) return false;
    if(root->data == ID){
        int i = 0;
        while (i<sbcount) { //去table找變數的值
            if (strcmp(root->lexeme, table[i].name)==0) {
                return true;
            }
            ++i;
        }
        return false;
    }else if(root->data == INT){
        return root->left == NULL && root->right == NULL;
    }else if(root->data == ASSIGN){
        // printf("EXIT 1\n");
        // exit(0);
        return false;
    }else{
        return checkTree(root->left) && checkTree(root->left);
    }
}


void resetNode(BTNode* node, int newVal){ //將原本應該是符號的node直接轉成常數
    node->data = INT;
    node->left = NULL;
    node->right = NULL;
    sprintf(node->lexeme, "%d", newVal);
    node->val = newVal;
}
void reconstructTree(BTNode* root){ //將常數部分先結合起來
    if(!root)
        return;
    // printf("reconstructTree, root = '%s'\n", root->lexeme);
    reconstructTree(root->left);
    reconstructTree(root->right);
    if(root->left && root->right && root->left->data == INT && root->right->data == INT){ //make sure root->left != NULL && root->right != NULL
        switch(root->data){
        case ORANDXOR:
            if(root->lexeme[0]== '&'){
                resetNode(root, root->left->val & root->right->val);
            }
            else if(root->lexeme[0] == '|'){
                resetNode(root, root->left->val | root->right->val);
            }
            else if(root->lexeme[0] == '^'){
                resetNode(root, root->left->val ^ root->right->val);
            }
            break;
        case ADDSUB:
            if(root->lexeme[0]== '+'){
                resetNode(root, root->left->val + root->right->val);
            }
            else if(root->lexeme[0] == '-'){
                resetNode(root, root->left->val - root->right->val);
            }
            break;
        case MULDIV:
            if(root->lexeme[0]== '*'){
                resetNode(root, root->left->val * root->right->val);
            }
            else if(root->lexeme[0] == '/'){
                if(root->right->val == 0){
                    error(DEVIDEBYZERO);
                }else 
                    resetNode(root, root->left->val / root->right->val);
            }
            break;
        }
    }
}

void printAssembly(BTNode* root){
    
}