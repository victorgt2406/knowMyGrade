SRC= $(wildcard *.c)
OBJFILES= $(SRC:.c=.o)
COMPILER= gcc
all: $(OBJFILES)
%.o: %.c
	$(COMPILER) -g -c $< -o $@

clean:
	rm $(OBJFILES)