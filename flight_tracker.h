/**
 * flight_tracker.h
 * author: Alex Weininger
 * modified: 10/18/2018
 */

#include "Node.h"

// function declarations
void addFlightFromCLI(Node **, char *);
void deleteFlightFromCLI(Node **, char *);
int userInput(Node **);
Node *getFlightsFile(Node **, FILE *);
int saveToFile(Node *, char *);
void help();