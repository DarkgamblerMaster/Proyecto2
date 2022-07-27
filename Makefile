NAME_C = gato.c

all: compilar run
compilar:
	gcc $(NAME_C) -o ejecutable `pkg-config --cflags --libs gtk+-3.0` -rdynamic
run:
	./ejecutable
