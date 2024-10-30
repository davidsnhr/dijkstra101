#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Definimos una constante para representar "infinito"
const int INF = numeric_limits<int>::max();

// Función de Dijkstra
vector<int> dijkstra(int n, int origen, const vector<vector<pair<int, int>>>& grafo) {
    // Vector de distancias, inicializado en "infinito" para todos los nodos
    vector<int> distancias(n, INF);
    distancias[origen] = 0;

    // Cola de prioridad para seleccionar el nodo con la distancia mínima
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, origen}); // La cola almacena pares {distancia, nodo}

    while (!pq.empty()) {
        int distancia_actual = pq.top().first; // distancia minima actual
        int nodo_actual = pq.top().second; // nodo esa distancia
        pq.pop(); // sacar el elemento

        // Ignoramos nodos ya procesados
        if (distancia_actual > distancias[nodo_actual]) continue;

        // Exploramos los vecinos del nodo actual
        for (const auto& vecino : grafo[nodo_actual]) {
            int nodo_vecino = vecino.first;
            int peso_arista = vecino.second;

            // Calculamos la nueva distancia al vecino
            int nueva_distancia = distancia_actual + peso_arista;

            // Si encontramos una distancia más corta, la actualizamos
            if (nueva_distancia < distancias[nodo_vecino]) {
                distancias[nodo_vecino] = nueva_distancia;
                pq.push({nueva_distancia, nodo_vecino});
            }
        }
    }

    return distancias;
}

int main() {
    int n = 5; // Número de nodos
    vector<vector<pair<int, int>>> grafo(n);

    // Añadir aristas al grafo {nodo_destino, peso}
    grafo[0].push_back({1, 10});
    grafo[0].push_back({2, 5});
    grafo[1].push_back({2, 2});
    grafo[1].push_back({3, 1});
    grafo[2].push_back({1, 3});
    grafo[2].push_back({3, 9});
    grafo[2].push_back({4, 2});
    grafo[3].push_back({4, 4});
    grafo[4].push_back({3, 6});
    grafo[4].push_back({0, 7});

    int origen = 0;
    vector<int> distancias = dijkstra(n, origen, grafo);

    // Imprimir las distancias mínimas desde el nodo de origen
    cout << "Distancias desde el nodo " << origen << ":" << endl;
    for (int i = 0; i < n; ++i) {
        if (distancias[i] == INF)
            cout << "Nodo " << i << ": Inalcanzable" << endl;
        else
            cout << "Nodo " << i << ": " << distancias[i] << endl;
    }

    return 0;
}
