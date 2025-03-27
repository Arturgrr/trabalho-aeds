CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lncurses

SRCS = main.c ordenacao.c
OBJS = $(SRCS:.c=.o)
TARGET = roteiro_turistico

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

# Regras para desenvolvimento
debug: CFLAGS += -g
debug: all

# Regras para valgrind
valgrind: debug
	valgrind --leak-check=full ./$(TARGET) 