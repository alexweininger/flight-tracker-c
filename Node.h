/*
 * Node.h
 * author: Alex Weininger
 * modified: 10/18/2018
 */

#include <stdio.h>
#include <stdlib.h>
#include "flight.h"

// linked list Node struct
typedef struct Node {
  struct Node *next;
  struct flight *data;
} Node;

// function declarations
Node * insert(Node **, Node *, Node *, Node *);
Node * delete(Node **, Node *, Node *, int);
Node *makeNode(flight);
void printNode(Node *);
void printList(Node *);
void freeLList(Node *);
