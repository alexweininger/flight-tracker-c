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
LLNode * del(LLNode *node, int flightNumber);
LLNode *createNode(flight f);

LLNode * del()

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
    printf("Quitting flight tracker...\n");
    // TODO free
    exit(0);
  } else if ('p' == c) {
    // print the flight list
    printList(top);
  } else if ('s' == c) {
    // save flight list to file
    printf("Save command\n");
  } else if ('a' == c) {
    // add flight from command line
    f = parseLine(lineCopy);
    if (top != NULL) {
      top = insert(top, f);
    }
  } else if ('d' == c) {
    // delete flight given f num
    printf("Delete flight\n");
  } else {
    printf("Invalid command \"%c\". Enter \"h\" for a list of commands.\n", c);
  }

  userInput(top);
}

int main(int argc, char *argv[]) {
  // linked list
  LLNode *top = (LLNode *)malloc(sizeof(LLNode));
  top->next = NULL;
  top->data = (flight *)malloc(sizeof(flight));

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
  userInput(top);
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