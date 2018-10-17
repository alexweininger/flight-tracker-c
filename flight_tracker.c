#include "flight_tracker.h"
#include "LLNode.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// functions
int validateCommand(char c);
void printList(LLNode *);
void help();
flight getFlightFromCommandLine();
void readFile(LLNode *, FILE *fp);
LLNode *getFlightsFile(LLNode *, FILE *);
LLNode *insert(LLNode *node, flight);
void del(LLNode *node, int flightNumber);
LLNode *createNode(flight f);

LLNode *makeNode(flight *f) {
  LLNode *nodePtr = (LLNode *)malloc(sizeof(LLNode));
  nodePtr->next = NULL;
  nodePtr->data = f;
  return nodePtr;
}

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
  LLNode *np = makeLLNode(f);
  LLNode *prev = NULL;
  LLNode *curr = top;
  int n = f.flightNumber;
  while (curr != NULL && n >= curr->data->flightNumber) {
    if (n == curr->data->flightNumber) {
      printf("Cannot add flight, duplicate flight number: %04d\n",
             f.flightNumber);
      return top;
    }
    prev = curr;
    curr = curr->next;
  }
  printf("Adding flight:   %c%C   ", f.airlines[0], f.airlines[1]);
  printf("%04d   %04d   %04d\n", f.flightNumber, f.arrivalTime,
         f.departureTime);
  if (prev == NULL) { // new number must be added at the top
    np->next = top;
    return np; // the top of the list has changed to the new node
  }
  np->next = curr;
  prev->next = np;
  return top; // the top of the list has not changed
}

flight parseLine(char line[]) {
  char atime[5];
  char dtime[5];

  flight f;

  printf("parseLine() - input line: %s\n", line);
  sscanf(line, "%*c %c%c %d", &f.airlines[0], &f.airlines[1], &f.flightNumber);

  if (f.flightNumber == 0) {
    printf("error\n");
  }

  sscanf(line, "%*c%*c %*s %4s %4s\n", atime, dtime);
  atime[4] = '\0';
  dtime[4] = '\0';
  strncpy(atime, atime, 4);
  f.departureTime = atoi(dtime);
  f.arrivalTime = atoi(atime);

  printf("Recieved flight details from add command:\n");
  printf("%c%c   ", f.airlines[0], f.airlines[1]);
  printf("%04d   ", f.flightNumber);
  printf("%04d   %04d\n", f.arrivalTime, f.departureTime);

  return f;
}

int userInput(LLNode *top) {
  char *line = readline(">");
  char lineCopy[255];
  strcpy(lineCopy, line);

  // getting command from first letter of line
  char c = lineCopy[0];
  printf("command character: %c\n", c);

  flight f;
  // command logic chain
  if ('q' == c) {
    printf("Quitting...\n");
    exit(0);
  } else if ('p' == c) {
    printList(top);
  } else if ('s' == c) {
    printf("Save command\n");
  } else if ('a' == c) {
    printf("Add flight\n");
    f = parseLine(lineCopy);
  } else if ('d' == c) {
    printf("Delete flight\n");
  } else {
    printf("Invalid command\n");
  }

  insert(top, f);
  userInput(top);
}

int main(int argc, char *argv[]) {
  // linked list
  LLNode *top = (LLNode *)malloc(sizeof(LLNode));
  top->next = NULL;
  top->data = (flight *)malloc(sizeof(flight));

  userInput(top);

  FILE *fp;
  fp = NULL;

  if (argc == 2) {
    // try to open file
    fp = fopen(argv[1], "r");
    if (NULL == fp) {
      printf("Error: cannot open file: %s\n", argv[1]);
    } else {
      top = getFlightsFile(top, fp);
    }
  }

  // initiated without arguments
  printf("--- Flight Tracker ---\n");
  help();

  char commandChar;
  char *line;
  while (1) {

    scanf("%s", line);
    printf("%s\n", line);

    commandChar = getchar();

    if ('q' == commandChar) {
      free(top);
      printf("Quitting Flight Tracker...\n");
      exit(0); // exit
    } else if ('p' == commandChar) {
      printList(top);
    } else if ('a' == commandChar) { // add flight to list
      printf("Enter flight details:\n");
      flight f;
      scanf("%c%c", &f.airlines[0], &f.airlines[1]);
      scanf("%4d %4d %4d\n", &f.flightNumber, &f.arrivalTime, &f.departureTime);
      LLNode *node = malloc(sizeof(LLNode));
      top = insert(top, f);
      printList(top);
    } else if ('d' == commandChar) {
      // delete flight
      int flightNumber = -1;
      scanf("%d", &flightNumber);
      printf("deleting flightNumber: %d\n", flightNumber);

    } else if ('s' == commandChar) {
      // save file
    } else if ('h' == commandChar) {
      help(); // print help
    } else if ('\n' == commandChar) {

    } else {
      printf("Command \"%c\" not found.\n", commandChar);
    }
  }
}

flight getFlightFromCommandLine() {
  char atime[5];
  char dtime[5];
  flight f;

  scanf("a %c%c %4d", &f.airlines[0], &f.airlines[1], &f.flightNumber);
  printf("found: %c%c %04d", f.airlines[0], f.airlines[2], f.flightNumber);
  if (f.flightNumber == 0) {
    printf("error\n");
  }

  scanf("%*c%*c %*s %4s %4s\n", atime, dtime);

  atime[4] = '\0';
  dtime[4] = '\0';
  strncpy(atime, atime, 4);
  printf("%s\n", atime);
  f.departureTime = atoi(dtime);
  f.arrivalTime = atoi(atime);

  scanf(" %c%c %d %d %d", &f.airlines[0], &f.airlines[1], &f.flightNumber,
        &f.departureTime, &f.arrivalTime);
  printf("%c%c %d %d %d\n", f.airlines[0], f.airlines[1], f.flightNumber,
         f.departureTime, f.arrivalTime);
  return f;
}

LLNode *getFlightsFile(LLNode *top, FILE *fp) {
  char string[255];
  char atime[5];
  char dtime[5];
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

    top = insert(top, *f);
  }
  printList(top);
  return top;
}

void printList(LLNode *top) {
  printf("----- Flight list -----\n");
  LLNode *curr = top->next;
  while (NULL != curr) {
    flight *f = curr->data;
    printf("%c%c   ", f->airlines[0], f->airlines[1]);
    printf("%04d   ", f->flightNumber);
    printf("%04d   %04d\n", f->arrivalTime, f->departureTime);
    curr = curr->next;
  }
}

void help() { // print the help commands
  printf("Flight Tracker commands: \n");
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
  printf("  h\t\t\tshow commands\n");
}