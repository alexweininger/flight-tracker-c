# CC = gcc
CFLAGS = -g -lreadline
DEPS = LLNode.h flight_tracker.h
OBJ = flight_tracker.c

ft: flight_tracker.o
	gcc -o ft flight_tracker.o -lreadline

flight_tracker.o: flight_tracker.c flight_tracker.h LLNode.h
	gcc -c -lreadline flight_tracker.c

# %.o: %.c $(DEPS)
# 	$(CC) $(CFLAGS) -c -o $@ $<

# ft: $(OBJ)
# 	gcc $(CFLAGS) -o $@ $^

clean:
	rm -f *.o ft f

