TARGET = Kinux
OBJ = main.c command_parser.c 
CFLAGS = -Wall -Wextra -Werror // They tell GCC how to compile your C program and what kinds of warnings to report.
CC = gcc
all :
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) // gcc -Wall -Wextra -Werror -o KNEXT main.c command_parser.c helpers.c
clean : 
	rm -f *.o
fclean : 
	rm -f $(TARGET)
re : fclean all