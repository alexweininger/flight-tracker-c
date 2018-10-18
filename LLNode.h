#include <stdio.h>
#include <stdlib.h>
#include "flight.h"

typedef struct LLNode {
  struct LLNode *next;
  struct flight *data;
} LLNode;

LLNode *insert(LLNode *top, flight);
LLNode * makeLLNode(flight);
int delete (LLNode **, int);
void printList(LLNode *);