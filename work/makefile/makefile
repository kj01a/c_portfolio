CC = gcc
CFLAGS = -g -Wall -DNDEBUG -Iheader

test_main: test_main.o edi_parser.o
	$(CC) -o test_main test_main.o edi_parser.o -Iheader

clean: 
	rm -f *.o
	rm -f test_main
