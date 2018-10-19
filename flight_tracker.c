/**
 * flight_tracker.c - main programming logic for the flight tracker program
 * author: Alex Weininger
 * modified: 10/18/2018
 */

#include "flight_tracker.h"

/**
 * main - initiates userInput loop and if needed starts file reading
 */
int main(int argc, char *argv[]) {
  printf("\n---- Flight Tracker ---\n\n");
  Node *top = NULL;
  Node **listPtr = &top; // list pointer

  if (argc == 2) { // if filename provided
    FILE *fp = NULL;
    fp = fopen(argv[1], "r"); // open file for reading
    if (NULL == fp) {
      printf("Error: cannot open file named \"%s\".\n", argv[1]);
    } else {
      // load flights from file into list
      printf("Loading flights from \"%s\"...\n\n", argv[1]);
      *listPtr = getFlightsFromFile(listPtr, fp);
    }
  }
  userInput(listPtr); // get command from user
}

/**
 * addFlightFromCLI - get flight details from user input and add flight to list
 */
void addFlightFromCLI(Node **listPtr, char *line) {
  Node *top = *listPtr;
  char *tok, *airlStr, *numStr, *depStr, *arrStr, lineCopy[255];
  strncpy(lineCopy, line, 254);

  // tokenize user input
  tok = strtok(line, " ");
  airlStr = strtok(NULL, " ");
  numStr = strtok(NULL, " ");
  arrStr = strtok(NULL, " ");
  depStr = strtok(NULL, " ");

  flight f;
  if (airlStr == NULL || numStr == NULL || arrStr == NULL || depStr == NULL) {
    printf("\nInvalid flight details. Cannot add flight.\n");
  } else {
    // store details in flight
    f.airlines[0] = airlStr[0];
    f.airlines[1] = airlStr[1];
    f.flightNumber = atoi(numStr);
    f.departureTime = atoi(depStr);
    f.arrivalTime = atoi(arrStr);
    Node *np = makeNode(f);
    printf("\nAdding flight:   ");
    printNode(np);
    *listPtr = insertR(listPtr, *listPtr, NULL, np);
  }
}

/**
 *  deleteFlightFromCLI - get flight number from user input and delete flight
 */
void deleteFlightFromCLI(Node **listPtr, char *str) {
  Node *top = *listPtr;
  char lineCopy[255], *token, *flightNumberStr;

  strncpy(lineCopy, str, 254);
  token = strtok(lineCopy, " ");
  flightNumberStr = strtok(NULL, " ");

  if (flightNumberStr == NULL) {
    printf("Cannot delete. Missing flight number. For help enter \"h\".\n");
  } else {
    printf("\nDeleting flight %d...\n", atoi(flightNumberStr));
    *listPtr = deleteR(listPtr, *listPtr, NULL, atoi(flightNumberStr));
    printList(*listPtr);
  }
}

/**
 * userInput - gets command from user input and handles command execution
 */
int userInput(Node **listPtr) {
  Node *top = *listPtr;
  char *token, *filename, c, lineCopy[255];
  char *line = readline("> ");

  strcpy(lineCopy, line); // make copy of line for later

  // getting command from first letter of line
  token = strtok(line, " ");
  if (NULL == token)
    return userInput(listPtr);
  c = token[0];

  // switch statement for handling commands
  switch (c) {
  case '\n':
    userInput(listPtr);
  case 'a':
    // add flight from cli
    addFlightFromCLI(listPtr, lineCopy);
    printList(*listPtr);
    break;
  case 'd':
    // delete flight given flight number
    deleteFlightFromCLI(listPtr, lineCopy);
    break;
  case 'h':
    help(); // print help
    break;
  case 'p':
    printList(top); // print the flight list
    break;
  case 'q':
    printList(top); // print list
    printf("\nQuitting flight tracker...\n\n");
    freeLList(top); // free linked list
    exit(0);        // exit
    break;
  case 's':
    // save flight list to file
    filename = strtok(NULL, " ");
    if (NULL != filename) {
      saveToFile(top, filename);
    } else {
      printf("\nInvalid filename \"%s\", could not save to file.\n", filename);
    }
    break;
  default:
    printf("\nInvalid command \"%c\". Enter \"h\" for a list of commands.\n",
           c);
    break;
  }
  userInput(listPtr); // call userInput again
}

/**
 * getFlightsFromFile - reads file line by line, and inserts flights into list
 */
Node *getFlightsFromFile(Node **listPtr, FILE *fp) {
  Node *node = (Node *)malloc(sizeof(Node)); // allocate node
  char line[255], atime[5], dtime[5];

  while (fgets(line, 255, fp)) { // reads file 1 line at a time
    flight *f = (flight *)malloc(sizeof(flight));
    sscanf(line, "%c%c %d", &f->airlines[0], &f->airlines[1], &f->flightNumber);

    if (f->flightNumber == 0)
      printf("\nError: invalid flight number.\n");

    sscanf(line, "%*c%*c %*s %4s %4s\n", atime, dtime);
    f->departureTime = atoi(dtime);
    f->arrivalTime = atoi(atime);
    Node *np = makeNode(*f);
    *listPtr = insertR(listPtr, *listPtr, NULL, np); // insert flight into list
  }
  printList(*listPtr);
  return *listPtr;
}
/**
 * saveToFile - given a list and name, saves  list to file (if valid)
 */
int saveToFile(Node *top, char *filename) {
  printf("\nSaving to file \"%s\"...\n\n", filename);
  FILE *fp = NULL;
  fp = fopen(filename, "w");

  if (NULL == fp) {
    printf("Error: Could not open file \"%s\" for writing.\n", filename);
    return -1; // return -1 for error
  }

  Node *curr = top;
  while (NULL != curr->next) {
    flight *f = curr->data;
    // write flight details to file
    fprintf(fp, "%c%c   ", f->airlines[0], f->airlines[1]);
    fprintf(fp, "%04d   ", f->flightNumber);
    fprintf(fp, "%04d   %04d\n", f->arrivalTime, f->departureTime);
    curr = curr->next;
  }
  fclose(fp); // close file
  printf("Successfully saved flight list to \"%s\".\n", filename);
  return 1; // return 1 for success
}

/**
 * help - prints the commands and options for each command
 */
void help() {
  printf("\nflight tracker commands:\n");
  // a <flight information> add flight, no duplicate flight numbers
  printf("  a [flightInfo]\tadd a flight\n");
  // d <flight number> for deleting a flight
  printf("  d [flightNumber]\tdelete flight\n");
  // s saves  current content of the LList into a file
  printf("  s [filename]\t\tsave current flights as a file\n");
  // p print the list of flights
  printf("  p\t\t\tprint current flight list\n");
  // q # quit the flight tracker and deallocate memory
  printf("  q\t\t\tquit flight tracker\n");
  // show help
  printf("  h\t\t\tshow commands\n\n");
}