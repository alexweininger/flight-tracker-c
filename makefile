# CC = gcc
CFLAGS = -g
POSTFLAGS = -lreadline
DEPS = Node.h flight_tracker.h
OBJ = flight_tracker.c LList.c

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(POSTFLAGS)

ft: $(OBJ)
	gcc $(CFLAGS) -o $@ $^ $(POSTFLAGS)

clean:
	rm -f *.o ft

# ft: flight_tracker.o LList.o
# 	gcc -g -o ft flight_tracker.o LList.o -lreadline
# flight_tracker.o: flight_tracker.c flight_tracker.h Node.h
# 	gcc -g -c -lreadline flight_tracker.c
# LList.o: LList.c Node.h flight_tracker.h flight.h
# 	gcc -g -c LList.c