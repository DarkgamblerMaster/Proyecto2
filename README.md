# Proyecto 2
## Proyecto 2 del curso IE-0117 Programación Bajo Plataformas Abiertas
###### Dania Castillo Montenegro B61621
###### Freddy Zúñiga Cerdas A45967

### Librerias
##
Para la implementación del juego gato en el lenguaje de programación C se utilizaron las siguientes librerías:
- gtk/gtk.h: conjunto de ficheros utilizados para crear las interfaces gráficas de los entornos de escritorio y de diferentes programas.
- stdio.h: contiene las definiciones de las macros, las constantes, las declaraciones de funciones de la biblioteca estándar del lenguaje de programación C para hacer operaciones, estándar, de entrada y salida.
- math.h: está diseñado para implementar las operaciones matemáticas básicas.
- stdbool.h: permite usar bool como un tipo de datos booleano, donde True es 1 y False corresponde a 0.

Las librerías al ser archivos de cabecera .h se colocan en el encabezado del archivo .c de la siguiente manera:

```
#include <librería.h>
```

## Partes fundamentales del proyecto

### gato.c
En este archivo .c se definen y conectan los elementos correspondientes de la interfaz gráfica creada, además se definen las funciones encargadas de determinar el ganador del juego, resetear el juego y para que el usuario logré seleccionar el simbolo deseado (X o O).

### gato.glade
Archivo que contiene la GUIs del juego gato. La interfaz contiene la ventana principal, etiquetas que brindan información al usuario, botones para los números que indican la posición en el tablero del juego, para el reset, el cambio de simbolo (X o O) y para cerrar el programa, iconos y otros objetos de interfaz de usuario, como resultado se obtiene lo que se presenta en la siguiente imagen:

![DEP](https://github.com/DarkgamblerMaster/Proyecto2/blob/master/interfaz.png)

### Makefile
Es un fichero que contiene las órdenes para compilar y posteriormente ejecutar el archivo .c de una forma más directa. Para ello es necesario ejecutar en la terminal la utilidad ```make```. 
