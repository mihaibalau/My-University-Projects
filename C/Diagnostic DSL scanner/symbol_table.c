#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char symbol[100];         
    int position;         
    struct Node* left;
    struct Node* right;
} Node;

Node* root = NULL;           
int currentPos = 0;        

Node* createNode(char* symbol, int pos) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->symbol, symbol);
    newNode->position = pos;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* node, char* symbol) {
    if (node == NULL) {
        return createNode(symbol, currentPos++);
    }
    if (strcmp(symbol, node->symbol) < 0)
        node->left = insert(node->left, symbol);
    else if (strcmp(symbol, node->symbol) > 0)
        node->right = insert(node->right, symbol);
    return node;
}

int search(Node* node, char* symbol) {
    if (node == NULL)
        return -1;
    if (strcmp(symbol, node->symbol) == 0)
        return node->position;
    if (strcmp(symbol, node->symbol) < 0)
        return search(node->left, symbol);
    return search(node->right, symbol);
}

int addSymbol(char* symbol) {
    int pos = search(root, symbol);
    if (pos == -1) {
        root = insert(root, symbol);
        pos = currentPos - 1;
    }
    return pos;
}

void printTree(Node* node) {
    if (node != NULL) {
        printTree(node->left);
        printf("%s -> %d\n", node->symbol, node->position);
        printTree(node->right);
    }
}

void saveSymbolTable(Node* node, FILE* f) {
    if (node != NULL) {
        saveSymbolTable(node->left, f);
        fprintf(f, "%s -> %d\n", node->symbol, node->position);
        saveSymbolTable(node->right, f);
    }
}

int main() {
    addSymbol("carModel");
    addSymbol("error_codes");
    addSymbol("tempSensor");
    addSymbol("\"E101\"");
    addSymbol("90");
    addSymbol("50");
    addSymbol("\"OK\"");

    printf("\nSymbol Table (BST):\n");
    printTree(root);

    FILE* f = fopen("st.txt", "w");
    saveSymbolTable(root, f);
    fclose(f);

    printf("\nThe table was saved in st.txt\n");
    return 0;
}
