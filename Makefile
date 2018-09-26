FLAGS=-g -Wall
LIBS=-lglut -lGLU -lGL -lm
EXEC=cg1
CC=gcc

all: main.o plyreader.o
# @echo "Compilando programa principal: \""$(EXEC)\" #
	$(CC) $(FLAGS) -o $(EXEC) $^ $(LIBS)

%.o: %.c
# @echo "Resolvendo dependência: \""$@"\"" "a partir de" $<"." #
	$(CC) $(FLAGS) -c -o $@ $< $(LIBS)

clean:
	rm -f *.o
	rm -f $(EXEC)