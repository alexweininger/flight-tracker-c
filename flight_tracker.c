#include "flight_tracker.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <string.h>

void deleteFlightFromCLI(LLNode **listPtr, char *str) {
  LLNode *top = *listPtr;
  char lineCopy[255];
  char *token, *flightNumberStr;

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

void addFlightFromCLI(LLNode **listPtr, char *str) {
  LLNode *top = *listPtr;
  flight f;
  char d[2] = " ";
  char lineCopy[255];
  char *token, *airlinesStr, *flightNumberStr, *departureStr, *arrivalStr;
  strncpy(lineCopy, str, 254);

  token = strtok(lineCopy, d);
  airlinesStr = strtok(NULL, d);
  flightNumberStr = strtok(NULL, d);
  arrivalStr = strtok(NULL, d);
  departureStr = strtok(NULL, d);

  if (airlinesStr == NULL || flightNumberStr == NULL || arrivalStr == NULL ||
      departureStr == NULL) {
    printf("Invalid flight details. Cannot add flight.\n");
  } else {
    f.airlines[0] = airlinesStr[0];
    f.airlines[1] = airlinesStr[1];
    f.flightNumber = atoi(flightNumberStr);
    f.departureTime = atoi(departureStr);
    f.arrivalTime = atoi(arrivalStr);

    *listPtr = insert(*listPtr, f);
  }
}

// free linked list
void freeLList(LLNode *top) {
  // TODO free linked list
  LLNode *curr = top;
  LLNode *temp = NULL;
  while (curr != NULL) {
    temp = curr;
    curr = curr->next;
    free(temp->data);
    free(temp);
  }
  free(top);
}

// get user input for commands
int userInput(LLNode **listPtr) {
  LLNode *top = *listPtr;
  char *line = readline("> ");
  char lineCopy[255];
  char *token;
  char c;
  flight f;
  strcpy(lineCopy, line);

  // getting command from first letter of line
  token = strtok(line, " ");
  c = token[0];

  switch (c) {
  case 'a':
    // add flight from command line
    addFlightFromCLI(listPtr, lineCopy);

  case 'd':
    // delete flight given f num
    deleteFlightFromCLI(listPtr, lineCopy);

  case 'h':
    help(); // print help

  case 'p':
    printList(top); // print the flight list

  case 'q':
    printf("Quitting flight tracker...\n\n");
    printList(top); // print list
    freeLList(top); // free linked list
    exit(0);        // exit

  case 's':
    // save flight list to file
    printf("Save command\n");
    char *filename;
    filename = strtok(NULL, " ");
    if (NULL != filename) {
      saveToFile(top, filename);
    } else {
      printf("Invalid filename, could not save to file.\n");
    }
    printf("filename from token: %s\n", filename);

  default:
    printf("Invalid command \"%c\". Enter \"h\" for a list of commands.\n", c);
  }

  // if ('q' == c) {
  //   printf("Quitting flight tracker...\n\n");
  //   printList(top); // print list
  //   freeLList(top); // free linked list
  //   exit(0);        // exit
  // } else if ('h' == c) {
  //   help();
  // } else if ('p' == c) {
  //   printList(top); // print the flight list
  // } else if ('s' == c) {
  //   // save flight list to file
  //   printf("Save command\n");
  //   char *filename;
  //   filename = strtok(NULL, " ");
  //   if (NULL != filename) {
  //     saveToFile(top, filename);
  //   } else {
  //     printf("Invalid filename, could not save to file.\n");
  //   }
  //   printf("filename from token: %s\n", filename);
  // } else if ('a' == c) {
  //   // add flight from command line
  //   addFlightFromCLI(listPtr, lineCopy);
  // } else if ('d' == c) {
  //   // delete flight given f num
  //   deleteFlightFromCLI(listPtr, lineCopy);

  // } else {
  //   printf("Invalid command \"%c\". Enter \"h\" for a list of commands.\n", c);
  // }
  userInput(listPtr);
}

int saveToFile(LLNode *top, char *filename) {
  FILE *fp = NULL;
  fp = fopen(filename, "w");

  if (NULL == fp) {
    printf("Error opening file \"%s\" for writing\n", filename);
    return -1;
  }

  LLNode *curr = top;
  while (NULL != curr->next) {
    flight *f = curr->data;
    fprintf(fp, "%c%c   ", f->airlines[0], f->airlines[1]);
    fprintf(fp, "%04d   ", f->flightNumber);
    fprintf(fp, "%04d   %04d\n", f->arrivalTime, f->departureTime);
    curr = curr->next;
  }
  fclose(fp);
  return 1;
}

int main(int argc, char *argv[]) {
  // linked list
  LLNode *top = NULL;
  LLNode **listPtr = &top;
  FILE *fp;
  fp = NULL;

  if (argc == 2) {
    // try to open file
    fp = fopen(argv[1], "r");
    if (NULL == fp) {
      printf("Error: cannot open file: %s\n", argv[1]);
    } else {
      *listPtr = getFlightsFile(listPtr, fp);
    }
  }

  // initiated without arguments
  printf("--- Flight Tracker ---\n");
  help();
  userInput(listPtr);
}

LLNode *getFlightsFile(LLNode **listPtr, FILE *fp) {
  char string[255], atime[5], dtime[5];
  LLNode *node = malloc(sizeof(LLNode));
  while (fgets(string, 255, fp)) {
    flight *f = (flight *)malloc(sizeof(flight));

    sscanf(string, "%c%c %d", &f->airlines[0], &f->airlines[1],
           &f->flightNumber);

    if (f->flightNumber == 0) {
      printf("error\n");
    }

    sscanf(string, "%*c%*c %*s %4s %4s\n", atime, dtime);
    atime[4] = '\0';
    dtime[4] = '\0';
    strncpy(atime, atime, 4);
    f->departureTime = atoi(dtime);
    f->arrivalTime = atoi(atime);

    *listPtr = insert(*listPtr, *f);
  }
  printList(*listPtr);
  return *listPtr;
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