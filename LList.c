/**
 * LList.c - handles linked list logic
 * author: Alex Weininger
 * modified: 10/18/2018
 */
#include "Node.h"

/**
 * insertR - recursive insert
 */
Node *insertR(Node **listPtr, Node *curr, Node *prev, Node *np) {

  // base case 1: if list is empty
  if (*listPtr == NULL) {
    np->next = *listPtr;
    return np;
  }

  // base case 2: end of list is reached
  if (curr == NULL) {
    prev->next = np;
    return *listPtr;
  }

  // base case 3: found duplicate flight number
  if (np->data->flightNumber == curr->data->flightNumber) {
    printf("Error: could not add flight.\n");
    printf("Flight %d already exists.\n", np->data->flightNumber);
    return *listPtr;
  }

  if (np->data->flightNumber <= curr->data->flightNumber) {
    if (prev == NULL) {
      // insert at head
      np->next = *listPtr;
      return np;
    }
    prev->next = np;
    np->next = curr;
    return *listPtr;
  }

  // recursive case
  return insertR(listPtr, curr->next, curr, np);
}

/**
 * insert - insert node into linked list, maintaining order
 */
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

Node *deleteR(Node **listPtr, Node *curr, Node *prev, int flightNumber) {
  // base case 1: list is empty
  if (NULL == *listPtr) {
    printf("Error: cannot delete flight from empty list.\n");
    return *listPtr;
  }
  // base case 2: did not find node
  if (NULL == curr->next) {
    printf("Error: flight %d not found.\n", flightNumber);
    return *listPtr;
  }
  // base case 3: found node
  if (flightNumber == curr->data->flightNumber) {
    if (prev == NULL) {
      return (*listPtr)->next;
    }
    prev->next = curr->next;
    free(curr);
    return *listPtr;
  }
  // recursive case:
  return deleteR(listPtr, curr->next, curr, flightNumber);
}

/**
 * delete - delete node from list given flight number
 */
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

/**
 * makeNode - allocate a node with given flight and return the node
 */
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

void printNode(Node *np) {
  flight *f;
  f = np->data;
  printf("%c%c   ", f->airlines[0], f->airlines[1]);
  printf("%04d   ", f->flightNumber);
  printf("%04d   %04d\n", f->arrivalTime, f->departureTime);
}

/**
 * printList - print linked list
 */
void printList(Node *node) {

  printf("\n----- Flight list -----\n");
  if (node == NULL) {
    printf("\n");
  } else {
    flight *f;
    while (node != NULL) {
      printNode(node);
      node = node->next;
    }
  }
  printf("-----------------------\n\n");
}

/**
 * freeLList - free linked list
 */
void freeLList(Node *top) {
  Node *curr = top;
  Node *temp = NULL;
  while (curr != NULL) {
    temp = curr;
    curr = curr->next;
    free(temp->data);
    free(temp);
  }
}