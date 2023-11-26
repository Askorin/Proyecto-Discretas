#include <stdio.h>
//Para legibilidad
#define true 1
#define false 0
//Necesitamos reservar un numero para el vertice nulo. TODO: Pensar mejor esta parte
#define nullvertex -1;

int main() {
    //Sea el digrafo de n vertices
    int n = 6;
    //Definamos un vertice inicial
    int s = 0; //Es importante que "s" este entre [0, n-1]
    
    //Notar que a lo maximo un vertice tiene n arcos salientes
    int graph[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    //Necesitamos definir una distancia infinita, o practicamente infinita (muy grande)
    //TODO: Pensar mejor esta aprte
    int const INF = 9999;

    //grade[i] es el grado de salida del vertice i
    int grade[n];
    for (int i = 0; i < n; i++) {
        grade[i] = 0;
    }

    /// Caracterizamos nuestro grafo
    graph[0][0] = 1; graph[0][1] = 5; grade[0] = 2;
    graph[1][0] = 5; grade[1] = 1;
    graph[2][0] = 3; grade[2] = 1;
    graph[3][0] = 4; grade[3] = 1;
    grade[4] = 0;
    graph[5][0] = 2; grade[5] = 1;

    /// Algoritmo de Dijkstra

    //Inicializamos algunas variables
    int distancia[n];
    int visto[n];
    int padre[n];
    for (int i = 0; i < n; i++) {
        distancia[i] = INF;
        visto[i] = false;
        padre[i] = nullvertex;
    }
    distancia[s] = 0;

    //Bucle principal
    int existeVerticeNoVisto = true;
    while (existeVerticeNoVisto) {
        //Tomamos como vertice al que tenga la menor distancia y no este visto
        int u;
        for (int i = 0; i < n; i++) {
            if (visto[i] == false) {
                u = i; //Vertice no visto cualquiera
            }
        }
        for (int i = 0; i < n; i++) {
            if (visto[i] == false) {
                if (distancia[i] < distancia[u]) {
                    u = i; //Vertice no visto menor
                }
            }
        }

        //Ahora u es visto
        visto[u] = true;

        //Para la vecindad de salida de u
        for (int i = 0; i < grade[u]; i++) {
            if (distancia[graph[u][i]] > distancia[u] + 1) {
                distancia[graph[u][i]] = distancia[u] + 1;
                padre[graph[u][i]] = padre[u];
            }
        }

        //Condición para salir del bucle
        existeVerticeNoVisto = false;
        for (int i = 0; i < n; i++) {
            if (visto[i] == false) {
                existeVerticeNoVisto = true;
            }
        }
    }

    //Imprimimos la distancia mas larga
    int max_distance = 0;
    for (int i = 0; i < n; i++) {
        if (distancia[i] > max_distance) {
            max_distance = distancia[i];
        }
    }
    printf("La distancia maxima es: %d", max_distance);
    return 0;
}