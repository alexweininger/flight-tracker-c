/*
 * flight_tracker.h
 * author: Alex Weininger
 * modified: 10/18/2018
 */

// includes
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <string.h>
#include "Node.h"

// function declarations
void addFlight(Node **, char *, int);
void deleteFlight(Node **, char *);
int commands(Node **);
Node *loadFile(Node **, FILE *);
int saveToFile(Node *, char *);
void help();
