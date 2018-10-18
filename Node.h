#include <stdio.h>
#include <stdlib.h>
#include "flight.h"

typedef struct Node {
  struct Node *next;
  struct flight *data;
} Node;

Node *insert(Node *, flight);
Node * makeNode(flight);
int delete (Node **, int);
void printList(Node *);
void freeLList(Node *);