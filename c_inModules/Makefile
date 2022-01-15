SRC= $(wildcard *.c)
LIBS= $(wildcard libs/*.c)

LIBFILES= $(LIBS:.c=.o)
OBJFILES= $(SRC:.c=.o)
COMPILER= gcc
PROGRAMNAME= prog.exe

all: $(OBJFILES)
	$(COMPILER) -g $(LIBFILES) $(OBJFILES) -o $(PROGRAMNAME)
	make clean
	

%.o: %.c
	$(COMPILER) -g -c $< -o $@

clean:
	rm $(OBJFILES)

commit:
	rm prog.exe
	rm -d -r Data*