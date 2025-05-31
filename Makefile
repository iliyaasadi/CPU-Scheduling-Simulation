CC = gcc
CFLAGS = -Wall -lm
TARGET = scheduler_test
SRC = scheduler.c scheduler_test.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)