LIBS=-lglut -lGLU -lGL -lm
EXEC=cg1
CC=gcc

all: main.o pontos.o
# @echo "Compilando programa principal: \""$(EXEC)\" #
	@$(CC) -o $(EXEC) $^ $(LIBS)

%.o: %.c
# @echo "Resolvendo dependência: \""$@"\"" "a partir de" $<"." #
	@$(CC) -c -o $@ $< $(LIBS)

clean:
	@rm -f *.o
	@rm -f $(EXEC)