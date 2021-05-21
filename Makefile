CC 		= gcc
CFLAGS  = -Wall -Wextra -I./ -g

OBJ		= main.o conway.o readfile.o
TARGET	= conway

.PHONY=all
all: $(TARGET)

.PHONY=debug
debug: $(TARGET)
	gdb -q -ex "r" $(TARGET)
	make clean > /dev/null

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY=clean
clean:
	rm *.o $(TARGET)

cursor:
	printf "\e[?25h"