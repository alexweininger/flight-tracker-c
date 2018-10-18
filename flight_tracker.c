/**
 * flight_tracker.c - main programming logic for the flight tracker program
 * author: Alex Weininger
 * modified: 10/18/2018
 */

#include "flight_tracker.h"

int main(int argc, char *argv[]) {
  Node *top = NULL;
  Node **listPtr = &top; // list pointer

  if (argc == 2) { // if filename provided
    FILE *fp = NULL;
    fp = fopen(argv[1], "r"); // open file for reading
    if (NULL == fp) {
      printf("Error: cannot open file named \"%s\".\n", argv[1]);
    } else {
      // load flights from file into list
      *listPtr = getFlightsFile(listPtr, fp);
    }
  }
  printf("--- Flight Tracker ---\n");
  userInput(listPtr); // get command from user
}

// get flight details from user and add flight
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
    printf("Invalid flight details. Cannot add flight.\n");
  } else {
    // store details in flight
    f.airlines[0] = airlStr[0];
    f.airlines[1] = airlStr[1];
    f.flightNumber = atoi(numStr);
    f.departureTime = atoi(depStr);
    f.arrivalTime = atoi(arrStr);

    *listPtr = insert(*listPtr, f);
  }
}

// get flight number from user and delete flight
void deleteFlightFromCLI(Node **listPtr, char *str) {
  Node *top = *listPtr;
  char lineCopy[255], *token, *flightNumberStr;

  strncpy(lineCopy, str, 254);
  token = strtok(lineCopy, " ");
  flightNumberStr = strtok(NULL, " ");

  if (flightNumberStr == NULL) {
    printf("Cannot delete. Missing flight number. For help enter \"h\".\n");
  } else {
    delete (listPtr, atoi(flightNumberStr));
    printList(*listPtr);
  }
}

// get user input for commands
int userInput(Node **listPtr) {
  Node *top = *listPtr;
  char *token, *filename, c, lineCopy[255];
  char *line = readline("> ");

  strcpy(lineCopy, line); // make copy of line for later

  // getting command from first letter of line
  token = strtok(line, " ");
  c = token[0];

  // switch statement for handling commands
  switch (c) {
  case 'a':
    // add flight from cli
    addFlightFromCLI(listPtr, lineCopy);
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
    printf("Quitting flight tracker...\n");
    printList(top); // print list
    freeLList(top); // free linked list
    exit(0);        // exit
    break;
  case 's':
    // save flight list to file
    filename = strtok(NULL, " ");
    if (NULL != filename) {
      saveToFile(top, filename);
    } else {
      printf("Invalid filename \"%s\", could not save to file.\n", filename);
    }
    break;
  default:
    printf("Invalid command \"%c\". Enter \"h\" for a list of commands.\n", c);
    break;
  }
  userInput(listPtr); // call userInput again
}

Node *getFlightsFile(Node **listPtr, FILE *fp) {
  Node *node = (Node *)malloc(sizeof(Node)); // allocate node
  char line[255], atime[5], dtime[5];

  while (fgets(line, 255, fp)) { // reads file 1 line at a time
    flight *f = (flight *)malloc(sizeof(flight)); // allocate flight
    sscanf(line, "%c%c %d", &f->airlines[0], &f->airlines[1], &f->flightNumber);

    if (f->flightNumber == 0)
      printf("Error: invalid flight number.\n");

    sscanf(line, "%*c%*c %*s %4s %4s\n", atime, dtime);
    strncpy(atime, atime, 4);
    f->departureTime = atoi(dtime);
    f->arrivalTime = atoi(atime);

    *listPtr = insert(*listPtr, *f);
  }
  printList(*listPtr);
  return *listPtr;
}

int saveToFile(Node *top, char *filename) {
  printf("Saving to file \"%s\"...\n", filename);
  FILE *fp = NULL;
  fp = fopen(filename, "w");

  if (NULL == fp) {
    printf("Error: Could not open file \"%s\" for writing.\n", filename);
    return -1;
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
  return 1;
}

void help() { // print the help commands
  printf("\nFlight Tracker commands:\n");
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