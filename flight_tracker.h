/**
 * flight_tracker.h
 */

#include "Node.h"

// function declarations
int validateCommand(char);
void readFile(Node *, FILE *);
Node *getFlightsFile(Node **, FILE *);
int saveToFile(Node *, char *);
void help();
int userInput(Node **);