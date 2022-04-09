CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lncurses

chrono: chrono.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm chrono
