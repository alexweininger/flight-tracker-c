#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LLNode.h"
#include "flight_tracker.h"

void insert(struct LLNode *, struct flight *);
void del(struct LLNode *, int);

int main(int argc, char *argv[]) {
  // linked list
  LLNode *top = (LLNode *)malloc(sizeof(LLNode));
  // flight struct
  flight *data = (flight *)malloc(sizeof(flight));

  top->data = data;

  FILE *fp;
  fp = NULL;

  if (argc == 2) {
    // try to open file
    fp = fopen(argv[1], "r");
    if (NULL == fp) {
      printf("Error: cannot open file: %s\n", argv[1]);
    } else {
      readFile(top, fp);
    }
  }

  // initiated without arguments
  printf("--- Flight Tracker ---\n");
  help();

  char commandChar;

  while (1) {
    scanf("%c", &commandChar);

    if ('q' == commandChar) {

      free(top);
      printf("Quitting Flight Tracker...\n");
      exit(0); // exit
    } else if ('p' == commandChar) {

      printList(&top);
    } else if ('a' == commandChar) {
      printf("Add flight\n");
      int flightNumber = -1;

      flight *f;
      f = getFlightInfo(fp);
      top->data->airlines[0] = f->airlines[0];
      top->next = NULL;
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

flight *getFlightInfo() {
  flight *f = malloc(sizeof(flight));
  scanf(" %c%c %d %d %d", &f->airlines[0], &f->airlines[1], &f->flightNumber,
        &f->departureTime, &f->arrivalTime);
  printf("%c%c %d %d %d\n", f->airlines[0], f->airlines[1], f->flightNumber,
         f->departureTime, f->arrivalTime);
  return f;
}

void readFile(LLNode *top, FILE *fp) {
  size_t len = 0;
  ssize_t read;

  char *line = NULL;

  while ((read = getline(&line, &len, fp)) != -1) {
    // printf("%s", line);
    char str[len];
    strcpy(str, line);
    flight *f = malloc(sizeof(flight));
    sscanf(str, "%c%c %d %d %d", &f->airlines[0], &f->airlines[1],
           &f->flightNumber, &f->departureTime, &f->arrivalTime);
    LLNode *node = malloc(sizeof(LLNode));
    node->next = top->next;
    node->data = f;
    top->next = node;
  }
  fclose(fp);
  if (line)
    free(line);
}

void printList(LLNode *top) {
  printf("--- Flight list ---\n");
  while (NULL != top) {
    printf("%c%c %d %d %d\n", top->data->airlines[0], top->data->airlines[1],
           top->data->flightNumber, top->data->departureTime,
           top->data->arrivalTime);
    top = top->next;
  }
}

LLNode *makeNode(LLNode * top, flight f) {
  LLNode *node = malloc(sizeof(LLNode));
  node->next = top->next;
  node->data = &f;
  return node;
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