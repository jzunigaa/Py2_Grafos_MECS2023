#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>
#include <cmath>
#include "UndirectedGraphAirport.h"

struct AStarResult {
    std::vector<std::string> route;
    double distance;
    int iterations;
};

// Función heurística (distancia euclidiana entre dos vértices)
double heuristic(const Vertex* vertex1, const Vertex* vertex2) {
    double dx = vertex1->data.Latitude - vertex2->data.Latitude;
    double dy = vertex1->data.Longitude - vertex2->data.Longitude;
    return std::sqrt(dx * dx + dy * dy);
}

AStarResult astar(const Graph& graph, const std::string& source, const std::string& destination) {
    std::unordered_map<std::string, Vertex*> vertexes = graph.getVertexes();

    std::unordered_map<std::string, double> distance;
    std::unordered_map<std::string, std::string> previous;
    std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<std::pair<double, std::string>>> pq;

    // Inicializar las distancias y asignar un valor infinito a todos los vértices excepto al origen
    for (const auto& vertex : vertexes) {
        const std::string& vertexId = vertex.first;
        distance[vertexId] = std::numeric_limits<double>::infinity();
        previous[vertexId] = "";
    }
    distance[source] = 0.0;

    // Agregar el vértice de origen a la cola de prioridad con la función heurística como prioridad
    pq.push(std::make_pair(heuristic(vertexes[source], vertexes[destination]), source));

    // Realizar el algoritmo A*
    int iterations = 0;
    while (!pq.empty()) {
        iterations++;
        std::string currentVertex = pq.top().second;
        pq.pop();

        // Verificar si se ha alcanzado el vértice de destino
        if (currentVertex == destination) {
            break;
        }

        Vertex* vertex = vertexes[currentVertex];

        // Recorrer las aristas del vértice actual
        for (auto edge : vertex->edges) {
            Vertex* adjacentVertex = edge->vertexes[0] == vertex ? edge->vertexes[1] : edge->vertexes[0];
            double edgeDistance = edge->distancia;
            double totalDistance = distance[currentVertex] + edgeDistance;

            // Si se encuentra una distancia más corta hacia el vértice adyacente, actualizar la distancia y el vértice previo
            if (totalDistance < distance[adjacentVertex->data.Airport_ID]) {
                distance[adjacentVertex->data.Airport_ID] = totalDistance;
                previous[adjacentVertex->data.Airport_ID] = currentVertex;
                double priority = totalDistance + heuristic(adjacentVertex, vertexes[destination]);
                pq.push(std::make_pair(priority, adjacentVertex->data.Airport_ID));
            }
        }
    }

    // Construir la ruta y calcular la distancia total
    std::vector<std::string> route;
    double totalDistance = distance[destination];
    std::string currentVertex = destination;
    while (!currentVertex.empty()) {
        route.push_back(currentVertex);
        currentVertex = previous[currentVertex];
    }
    std::reverse(route.begin(), route.end());

    AStarResult result;
    result.route = route;
    result.distance = totalDistance;
    result.iterations = iterations;

    return result;
}

#endif  // ASTAR_H
