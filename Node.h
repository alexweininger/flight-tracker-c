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

Node *insert(Node *, flight);
int delete (Node **, int);
Node * makeNode(flight);
void printList(Node *);
void freeLList(Node *);