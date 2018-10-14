# notes

tracking flights with linked lists

reading a text file with flights in it

use `scanf` and `fscanf`

insert flights in order recursively ascending order by flight number

and then support delete, insert, and for bonus implement sort by column data of choice

due week after fall break Sunday 10/28

## From pdf

Your code files (.h and .c files), makefile, 10 sample inputs that represent different flight lists you used for testing your code.

Create a sorted list of flights that are either read from file or from cli

The command line instructions include
./flight

- a <flight information> # add a flight, no duplicate flight numbers are allowed
- d <flight number> # for deleting a flight with the given <flight number:int>
- s <file name> # saves the current content of the LList into a file
- p # print the list of flights
- q # quit the flight tracker and de-allocate memory

store data in struct called `flight` with the following fields

- airlines: string of 2 chars
- flight number: int
- arrival time: int
- departure time: int

all flights must be stored on heap in a linked list

`LLNode` struct has two fields

- next: LLNode*
- data: flight*

1. After every valid operation (a, d), the program prints the list of flights.
2. If a valid operation (a, d) cannot be carried out OR operation does not exist (not a or d), print appropriate error message. Also if the flight data to be stored contains information with incorrect format or is missing, print an error message and omit the insertion of the flight to the list.
3. If you delete a flight or quit the program the link list must be de-allocated – each data struct of type flight as well as the LLNode struct have to be property de-allocated from the heap
4. The program will allow for any number of flights to be entered and stored in the llist for tracking.
5. The input file (for example flights.txt) is an optional parameter to the program – if the file name is passed into the program at the execution time, the file contains flights to be inserted to the llist. If no file is specified, read instructions with data from the command line. The input file contains one flight’s information per line, and after you read the line into a struct flight , then insert this struct into the llist of flights. Usage: . /flight <file name> OR ./flight
6. Inserting of a flight has to be in a non-decreasing order of the flight number.
7. Insertion of a flight has to be a recursive algorithm.
8. You are not allowed to use any arrays to store your data, only malloc-ed structs.
9. You must keep the linked list in a sorted order – when read and insert flights, they have to be inserted into the correct place in the linked list. Also, when you delete a flight, the list should still be in order.
10. Print each flight as you read it into your program, then print the final sorted list before ending your program.
11. Functions should be used to insert, print, save, and delete the flight structures.