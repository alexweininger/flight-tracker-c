/*
 * flight_tracker.c - main programming logic for the flight tracker program
 * author: Alex Weininger
 * modified: 10/18/2018
 */

#include "flight_tracker.h"

/*
 * main - initiates commands loop and if needed starts file reading
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
      *listPtr = loadFile(listPtr, fp);
      printf("\nSuccessfully loaded flights from \"%s\".\n", argv[1]);
      fclose(fp);
      printList(*listPtr);
    }
  }
  return commands(listPtr); // get command from user
}

/*
 * addFlight - get flight details from user input and add flight to list
 */
void addFlight(Node **listPtr, char *line, int fromFile) {
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
    // store data in flight struct
    f.airlines[0] = airlStr[0];
    f.airlines[1] = airlStr[1];
    f.flightNumber = atoi(numStr);
    f.departureTime = atoi(depStr);
    f.arrivalTime = atoi(arrStr);
    Node *np = makeNode(f); // make Node for flight
    printf("\nAdding flight:   ");
    printNode(np);
    *listPtr = insert(listPtr, *listPtr, NULL, np); // insert into list
  }
}

/*
 * deleteFlight - get flight number from user input and delete flight
 */
void deleteFlight(Node **listPtr, char *str) {
  Node *top = *listPtr;
  char lineCopy[255], *token, *flightNumberStr;

  strncpy(lineCopy, str, 254);
  token = strtok(lineCopy, " ");
  flightNumberStr = strtok(NULL, " ");

  if (flightNumberStr == NULL) {
    printf("Cannot delete. Missing flight number. For help enter \"h\".\n");
  } else {
    printf("\nDeleting flight %d...\n", atoi(flightNumberStr));
    *listPtr = delete (listPtr, *listPtr, NULL, atoi(flightNumberStr));

    printList(*listPtr);
  }
}

/*
 * commands - gets command from user input and handles command execution
 */
int commands(Node **listPtr) {
  char *token, *filename, c, lineCopy[255], line2[255];
  char *line = (char *)NULL;

  line = (char *)readline("> ");
  if (!line) {
    return commands(listPtr);
  }
  strncpy(lineCopy, line, 254); // make copy of line for later
  strncpy(line2, line, 254);    // make copy of line for later

  // getting command from first letter of line
  token = strtok(line2, " ");
  if (NULL == token) {
    free(token);
    return commands(listPtr);
  }
  c = token[0];

  // switch statement for handling commands
  switch (c) {
  case '\n':
    break;
  case 'a':
    // add flight from cli
    addFlight(listPtr, lineCopy, 0);
    printList(*listPtr);
    break;
  case 'd':
    // delete flight given flight number
    deleteFlight(listPtr, lineCopy);
    break;
  case 'h':
    help(); // print help
    break;
  case 'p':
    printList(*listPtr); // print the flight list
    break;
  case 'q':
    printf("\nQuitting flight tracker...\n");
    printList(*listPtr); // print list
    freeLList(*listPtr); // free linked list
    exit(0);
    break;
  case 's':
    // save flight list to file
    filename = strtok(NULL, " ");
    if (NULL != filename) {
      saveToFile(*listPtr, filename);
    } else {
      printf("\nInvalid filename \"%s\", could not save to file.\n", filename);
    }
    break;
  default:
    printf("\nInvalid command \"%c\". Enter \"h\" for a list of commands.\n",
           c);
    break;
  }
  return commands(listPtr); // call commands again
}

/*
 * loadFile - reads file line by line, and inserts flights into list
 */
Node *loadFile(Node **listPtr, FILE *fp) {
  char line[255], atime[5], dtime[5];

  while (fgets(line, 255, fp)) { // reads file 1 line at a time
    flight f;
    sscanf(line, "%c%c %d", &f.airlines[0], &f.airlines[1], &f.flightNumber);

    if (f.flightNumber == 0)
      printf("\nError: invalid flight number.\n");

    sscanf(line, "%*c%*c %*s %4s %4s\n", atime, dtime);
    f.departureTime = atoi(dtime);
    f.arrivalTime = atoi(atime);
    Node *np = makeNode(f);
    printf("Adding flight:   ");
    printNode(np);
    *listPtr = insert(listPtr, *listPtr, NULL, np); // insert flight into list
  }
  return *listPtr;
}

/*
 * saveToFile - given a list and name, saves  list to file (if valid)
 */
int saveToFile(Node *top, char *filename) {
  printf("\nSaving to file \"%s\"...\n\n", filename);
  FILE *fp = NULL;
  fp = fopen(filename, "w");

  if (NULL == fp) {
    printf("Error: Couldn't open file \"%s\" for writing.", filename);
    printf("Enter \"h\" for help.\n");
    return -1; // return -1 for error
  }

  Node *curr = top;
  while (NULL != curr) {
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

/*
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
