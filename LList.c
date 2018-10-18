#include "Node.h"

// insert node into linked list, keeping order
Node *insert(Node *top, flight f) {
  Node *np, *curr, *prev;
  np = makeNode(f);
  prev = NULL;
  curr = top;

  while (curr != NULL && f.flightNumber >= curr->data->flightNumber) {
    if (curr->data->flightNumber == f.flightNumber) {
      printf("Flight %d already exists, did not add flight.\n", f.flightNumber);
      return top;
    }
    prev = curr;
    curr = curr->next;
  }
  if (prev == NULL) {
    top = np;
    top->next = curr;
    return top;
  }

  np->next = curr;
  prev->next = np;

  printf("Adding flight:   %c%C   ", f.airlines[0], f.airlines[1]);
  printf("%04d   %04d   %04d\n", f.flightNumber, f.arrivalTime,
         f.departureTime);
  return top;
}

// delete node from list given flight number
int delete (Node **listPtr, int flightNumber) {
  printf("Deleting flight %d...\n", flightNumber);
  Node *list = *listPtr;

  // if deleting first node
  if ((*listPtr)->data->flightNumber == flightNumber) {
    printf("node to delete is first in list\n");
    Node *temp = list->next;
    *listPtr = temp;
    // free(list); // free the node
    return 1; // node was deleted
  }

  Node *prev = list;
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

// allocate a node with given flight and return the node
Node *makeNode(flight f) {
  Node *np = (Node *)malloc(sizeof(Node));
  np->data = (flight *)malloc(sizeof(flight));
  np->data->airlines[0] = f.airlines[0];
  np->data->airlines[1] = f.airlines[1];
  np->data->flightNumber = f.flightNumber;
  np->data->arrivalTime = f.arrivalTime;
  np->data->departureTime = f.departureTime;
  np->next = NULL;
  return np;
}

// print linked list
void printList(Node *node) {
  flight *f;
  printf("\n----- Flight list -----\n");
  while (node->next != NULL) {
    f = node->data;
    printf("%c%c   ", f->airlines[0], f->airlines[1]);
    printf("%04d   ", f->flightNumber);
    printf("%04d   %04d\n", f->arrivalTime, f->departureTime);
    node = node->next;
  }
  printf("-----------------------\n\n");
}

// free linked list
void freeLList(Node *top) {
  // TODO free linked list
  Node *curr = top;
  Node *temp = NULL;
  while (curr != NULL) {
    temp = curr;
    curr = curr->next;
    free(temp->data);
    free(temp);
  }
}