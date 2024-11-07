
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "q1_data.h"

#define TABLE_SIZE 805

typedef enum
{
    red,
    black
} Color;

typedef struct Node
{
    int key;
    Color color;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;



struct node {
    int data;
    struct node* next;
};

Node NULL_NODE = {0, black, NULL, NULL, NULL};

Node *createNode(int key)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL)
    {
        newNode->key = key;
        newNode->color = red;
        newNode->parent = NULL;
        newNode->left = &NULL_NODE;
        newNode->right = &NULL_NODE;
    }
    return newNode;
}

void leftRotate(Node **root, Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left != &NULL_NODE)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        *root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rightRotate(Node **root, Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    if (x->right != &NULL_NODE)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL)
    {
        *root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

Node *rbSearch(Node *root, int key)
{
    while (root != &NULL_NODE && key != root->key)
    {
        if (key < root->key)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return root;
}

void rbInsertFixup(Node **root, Node *z)
{
    while (z->parent != NULL && z->parent->color == red)
    {
        if (z->parent == z->parent->parent->left)
        {
            Node *y = z->parent->parent->right;
            if (y->color == red)
            {

                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {

                    z = z->parent;
                    leftRotate(root, z);
                }

                z->parent->color = black;
                z->parent->parent->color = red;
                rightRotate(root, z->parent->parent);
            }
        }
        else
        {

            Node *y = z->parent->parent->left;
            if (y->color == red)
            {

                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {

                    z = z->parent;
                    rightRotate(root, z);
                }

                z->parent->color = black;
                z->parent->parent->color = red;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = black;
}

void rbInsert(Node **root, int key)
{
    Node *z = createNode(key);
    Node *y = NULL;
    Node *x = *root;

    while (x != &NULL_NODE)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == NULL)
    {
        *root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    rbInsertFixup(root, z);
}

Node *findMinimum(Node *x)
{
    while (x->left != &NULL_NODE)
    {
        x = x->left;
    }
    return x;
}

void rbDeleteFixup(Node **root, Node *x)
{
    while (x != *root && x->color == black)
    {
        if (x == x->parent->left)
        {
            Node *w = x->parent->right;
            if (w->color == red)
            {

                w->color = black;
                x->parent->color = red;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == black && w->right->color == black)
            {
                w->color = red;
                x = x->parent;
            }
            else
            {
                if (w->right->color == black)
                {

                    w->left->color = black;
                    w->color = red;
                    rightRotate(root, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = black;
                w->right->color = black;
                leftRotate(root, x->parent);
                x = *root;
            }
        }
        else
        {

            Node *w = x->parent->left;
            if (w->color == red)
            {

                w->color = black;
                x->parent->color = red;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == black && w->left->color == black)
            {

                w->color = red;
                x = x->parent;
            }
            else
            {
                if (w->left->color == black)
                {

                    w->right->color = black;
                    w->color = red;
                    leftRotate(root, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = black;
                w->left->color = black;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = black;
}

void rbTransplant(Node **root, Node *u, Node *v)
{
    if (u->parent == NULL)
    {
        *root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void rbDelete(Node **root, int key)
{
    Node *z = rbSearch(*root, key);
    if (z == &NULL_NODE)
    {
        printf("element %d not present in the RBT.\n", key);
        return;
    }

    Node *y = z;
    Node *x;
    Color yOriginalColor = y->color;

    if (z->left == &NULL_NODE)
    {
        x = z->right;
        rbTransplant(root, z, z->right);
    }
    else if (z->right == &NULL_NODE)
    {
        x = z->left;
        rbTransplant(root, z, z->left);
    }
    else
    {
        y = findMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            rbTransplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (yOriginalColor == black)
    {
        rbDeleteFixup(root, x);
    }
}

void inOrderTraversal(Node *root)
{
    if (root != &NULL_NODE)
    {
        inOrderTraversal(root->left);
        printf("%d ", root->key);
        inOrderTraversal(root->right);
    }
}


//******************************Hashing******************************************//

struct node* createNode_h(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insert_h(struct node* hashTable[], int value) {
    int index = value % TABLE_SIZE;
    struct node* newNode = createNode_h(value);
    
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        struct node* current = hashTable[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}


void delete_h(struct node* hashTable[], int value) {
    int index = value % TABLE_SIZE;
    struct node* current = hashTable[index];
    struct node* prev = NULL;
    
    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Value %d not found in the hash table\n", value);
        return;
    }
    
    if (prev == NULL) {
        hashTable[index] = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current);
    printf("Value %d deleted from the hash table\n", value);
}


struct node* lookup(struct node* hashTable[], int value) {
    int index = value % TABLE_SIZE;
    struct node* current = hashTable[index];
    
    while (current != NULL) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}



int main()
{
    int insert_element[] = {99957, 71164, 53575, 26164, 600};
    int search_element[] = {18, 7791, 13000, 99824, 51375};
    int delete_element[] = {51, 24168, 51164, 72145, 93160};
    int size = sizeof(insert_element) / sizeof(insert_element[0]);
    int size2 = sizeof(search_element) / sizeof(search_element[0]);
    int size3 = sizeof(delete_element) / sizeof(delete_element[0]);

    printf("\n********************Red Black Tree********************\n\n");

    Node *root = &NULL_NODE;
    struct timeval start, end;
    extern int data[];
    int n = sizeof(data) / sizeof(data[0]);
    for (int i = 0; i < n; i++)
    {
        rbInsert(&root, data[i]);
    }

    gettimeofday(&start, NULL);
    for (int i = 0; i < size; i++)
    {
        rbInsert(&root, insert_element[i]);
        printf("element %d inserted in the RBT.\n", insert_element[i]);
    }
    gettimeofday(&end, NULL);

    long seconds = (end.tv_sec - start.tv_sec);
    long micro = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    float milli = (float)micro / 1000.0;
    printf("\nTime taken for insertion in RBT of the given node %0.2f microseconds\n\n", milli);

    gettimeofday(&start, NULL);
    for (int i = 0; i < size2; i++)
    {
        Node *result = rbSearch(root, search_element[i]);
        if (result != &NULL_NODE)
        {
            printf("element %d is found in the RBT.\n", search_element[i]);
        }
        else
        {
            printf("element %d is not found in the RBT.\n", search_element[i]);
        }
    }

    printf("\n");
    gettimeofday(&end, NULL);

    long t_second = (end.tv_sec - start.tv_sec);
    long t_micro = ((t_second * 1000000) + end.tv_usec) - (start.tv_usec);

    float t_milli = (float)t_micro / 1000.0;
    printf("\nTime taken for searching in RBT of the given node %0.2f microseconds\n\n", t_milli);

    gettimeofday(&start, NULL);
    for (int i = 0; i < size3; i++)
    {
        rbDelete(&root, delete_element[i]);
        printf("element %d is deleted from RBT\n", delete_element[i]);
    }

    gettimeofday(&end, NULL);

    long second = (end.tv_sec - start.tv_sec);
    long del = ((second * 1000000) + end.tv_usec) - (start.tv_usec);

    float count = (float)del / 1000.0;
    printf("\nTime taken for deletion in RBT of the given node %0.2f microseconds\n", count);

// Hashing start


    printf("\n\n********************Custom data strucure: Hashing**********************\n\n");
    struct node* hashTable[TABLE_SIZE] = {NULL};
    for (int i = 0; i < n; i++)
    {
        insert_h(hashTable, data[i]);
    }

    //given element
    gettimeofday(&start, NULL);
    for (int i = 0; i < size; i++)
    {
        insert_h(hashTable, insert_element[i]);
          printf("element %d is inserted in Hash Table\n",insert_element[i]);
    }

    gettimeofday(&end, NULL);

    long insert_time = (end.tv_sec - start.tv_sec);
    long f_time = ((insert_time * 1000000) + end.tv_usec) - (start.tv_usec);

    float m_sec = (float)f_time / 1000.0;
    printf("\nTime taken for insertion in Hash Table of the given node %0.2f microseconds\n", m_sec);
    printf("\n");

    gettimeofday(&start, NULL);

    for(int i=0;i<size2;i++){
        int valueToLookup = search_element[i];
        struct node* result = lookup(hashTable, valueToLookup);
        
        if (result) {
            printf("Value %d found in the hash table at index %d\n", valueToLookup, valueToLookup % TABLE_SIZE);
        } 
        
        else {
            printf("Value %d not found in the hash table\n", valueToLookup);
        }
    }

      gettimeofday(&end, NULL);

    long m_second = (end.tv_sec - start.tv_sec);
    long s_time = ((m_second * 1000000) + end.tv_usec) - (start.tv_usec);

    float time = (float)s_time / 1000.0;
    printf("\nTime taken for searching in Hash Table of the given node %0.2f microseconds\n", time);

     gettimeofday(&start, NULL);
    printf("\n");
    for(int i=0;i<size3;i++){
        delete_h(hashTable, delete_element[i]);
    }

    gettimeofday(&end, NULL);

    long sec = (end.tv_sec - start.tv_sec);
    long c_sec = ((sec * 1000000) + end.tv_usec) - (start.tv_usec);

    float count_sec = (float)c_sec / 1000.0;
    printf("\nTime taken for deletion in Hash Table of the given node %0.2f microseconds\n", count_sec);

    return 0;
}
