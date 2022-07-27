# Se importa el archivo .c
NAME_C = gato.c

# Se compila el archivo
all: compilar run
compilar:
	gcc $(NAME_C) -o ejecutable `pkg-config --cflags --libs gtk+-3.0` -rdynamic
# Se ejecuta el archivo
run:
	./ejecutable
