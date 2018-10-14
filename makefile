CC = gcc
CFLAGS = -g
DEPS = LLNode.h flight_tracker.h
OBJ = flight_tracker.c

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

ft: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -f *.o ft f