CC=gcc
CFLAGS= -Wall -g
OBJECT=hebra.o
EXEC=hebra
all: $(EXEC)


$(EXEC): $(OBJECT)
	$(CC) $(OBJECT) -o $@ -pthread


clean:
	
	rm -f $(OBJECT)
	
	rm -f $(EXEC)