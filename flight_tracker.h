/**
 * flight_tracker.h
 */

#include "LLNode.h"

// function declarations
int validateCommand(char);
void readFile(LLNode *, FILE *);
LLNode *getFlightsFile(LLNode **, FILE *);
int saveToFile(LLNode *, char *);
void help();