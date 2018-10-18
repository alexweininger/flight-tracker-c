
#include "LLNode.h"

LLNode *makeLLNode(flight f) {
  LLNode *LLNodePtr = (LLNode *)malloc(sizeof(LLNode));
  LLNodePtr->next = NULL;
  LLNodePtr->data = (flight *)malloc(sizeof(flight));
  LLNodePtr->data->airlines[0] = f.airlines[0];
  LLNodePtr->data->airlines[1] = f.airlines[1];
  LLNodePtr->data->flightNumber = f.flightNumber;
  LLNodePtr->data->arrivalTime = f.arrivalTime;
  LLNodePtr->data->departureTime = f.departureTime;
  return LLNodePtr;
}

LLNode *insert(LLNode *top, flight f) {
  LLNode *np, *curr, *prev;
  np = makeLLNode(f);
  prev = NULL;
  curr = top;
  int n = f.flightNumber;
  while (curr != NULL && n > curr->data->flightNumber) {
    prev = curr;
    curr = curr->next;
  }
  if (prev == NULL) {
    top = np;
    top->next = curr;
    return top;
  }
  if (prev->data->flightNumber == n) {
    printf("Duplicate flight number\n");
    return top;
  }
  np->next = curr;
  prev->next = np;

  printf("Adding flight:   %c%C   ", f.airlines[0], f.airlines[1]);
  printf("%04d   %04d   %04d\n", f.flightNumber, f.arrivalTime,
         f.departureTime);
  return top;
}

int delete (LLNode **listPtr, int flightNumber) {
  printf("Attempting to delete flight %d.\n", flightNumber);
  LLNode *list = *listPtr;

  // if deleting first node
  if ((*listPtr)->data->flightNumber == flightNumber) {
    printf("node to delete is first in list\n");
    LLNode *temp = list->next;
    *listPtr = temp;
    // free(list); // free the node
    return 1; // node was deleted
  }

  LLNode *prev = list;
  list = list->next;

  while (list != NULL) {
    if (flightNumber == list->data->flightNumber) {
      // redo pointers and then free memory
      prev->next = list->next;
      free(list);
      return 1; // deleted node
    }
    prev = list; // update prev
    list = list->next;
  }
  return -1; // node not found
}

void printList(LLNode *node) {
  printf("\n----- Flight list -----\n");
  flight *f;
  while (node->next != NULL) {
    f = node->data;
    printf("%c%c   ", f->airlines[0], f->airlines[1]);
    printf("%04d   ", f->flightNumber);
    printf("%04d   %04d\n", f->arrivalTime, f->departureTime);
    node = node->next;
  }
  printf("-----------------------\n\n");
}
