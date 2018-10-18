# CC = gcc
CFLAGS = -g -lreadline
DEPS = LLNode.h flight_tracker.h
OBJ = flight_tracker.c

ft: flight_tracker.o LList.o
	gcc -g -o ft flight_tracker.o LList.o -lreadline

flight_tracker.o: flight_tracker.c flight_tracker.h LLNode.h
	gcc -g -c -lreadline flight_tracker.c

LList.o: LList.c LLNode.h flight_tracker.h flight.h
	gcc -g -c LList.c

# %.o: %.c $(DEPS)
# 	$(CC) $(CFLAGS) -c -o $@ $<

# ft: $(OBJ)
# 	gcc $(CFLAGS) -o $@ $^

clean:
	rm -f *.o ft f

