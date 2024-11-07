# Red-Black Tree Implementation

This project implements a Red-Black Tree (RBT) and a Hash Table in C. The Red-Black Tree is a self-balancing binary search tree, while the Hash Table uses separate chaining to handle collisions. Both data structures support insertion, deletion, and search operations, and the project measures the time taken for these operations.

## Features

- **Red-Black Tree (RBT)**
  - Self-balancing binary search tree with efficient insertion, deletion, and search.
  - Uses color properties and rotations to maintain balance.
  - Outputs timing metrics for insertion, search, and deletion.

- **Hash Table**
  - Implements a simple hash table using modulo hashing and separate chaining.
  - Supports insertion, deletion, and search with constant-time complexity on average.
  - Outputs timing metrics for insertion, search, and deletion.

## Code Structure

### 1. Red-Black Tree (RBT)

The Red-Black Tree uses nodes with a `color` property to maintain balance.

#### Data Structure

```c
typedef enum {red,black} Color;

typedef struct Node {
    int key;
    Color color;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;
