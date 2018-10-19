/**
 * Node.h
 * author: Alex Weininger
 * modified: 10/18/2018
 */

#include <stdio.h>
#include <stdlib.h>
#include "flight.h"

typedef struct Node {
  struct Node *next;
  struct flight *data;
} Node;

Node * insertR(Node **, Node *, Node *, Node *);
Node *insert(Node *, flight);
Node * deleteR(Node **, Node *, Node *, int);
int delete (Node **, int);
Node *makeNode(flight);
void printNode(Node *);
void printList(Node *);
void freeLList(Node *);