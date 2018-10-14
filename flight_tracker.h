// flight struct
typedef struct flight {
  char airlines[2];
  int flightNumber;
  int arrivalTime;
  int departureTime;
} flight;

// functions
int validateCommand(char c);
void printList(LLNode ** list);
void help();
flight * getFlightInfo();
void readFile(LLNode *, FILE * fp);
