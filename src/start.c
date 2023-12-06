#include "../inc/start.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char * start_text =
"===================================================================================\n"
"\n"
"Este programa tiene la función de dadas ciertas direcciones, imprima el camino más \n"
"corto para recorrerlas. \n"
"Actualmente estan implementadas todas las calles del Centro de Concepción que se \n"
"encuentran entre Arturo Prat y Paicavi, y entre Chacabuco y Carrera. \n"
"\n"
"La entrada debe tener el siguiente formato: \n"
"rutas \"Dirección Inicial\" \"Dirección Final\" \"Dirección 3\" \"Dirección 4\" ... \n"
"\n"
"Donde cada dirección debe ingresarse de la siguiente forma: \n"
"[Nombre de la calle] [Número de inmueble] \n"
"\n"
"Ejemplo de uso: \n"
"rutas \"Orompello 100\" \"Rengo 400\" \"Paicavi 600\"\n"
"\n"
"Las calles que maneja el programa son: Carrera, Maipu, Freire, Barros Arana, \n"
"O'Higgins, San Martin, Cochrane, Chacabuco, Arturo Prat, Serrano, Salas, Angol, \n"
"Lincoyan, Rengo, Caupolican, Anibal Pinto, Colo Colo, Castellon, Tucapel, \n"
"Orompello, Ongolmo, Paicavi, Pedro Aguirre Cerda \n"
"Es importante que las calles se ingresen con exactamente los nombres anteriores. \n"
"\n"
"Puede utilizar el comando salir para detener la ejecución del programa. \n"
"\n"
"===================================================================================\n"
;

void print_start() {
    printf("%s", start_text);
}