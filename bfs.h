#ifndef __BFS_H
#define __BFS_H

#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include "UndirectedGraphAirport.h"

struct BFSResult {
    std::vector<Airport> route;
    double distance;
    int iterations;
};

BFSResult bfs(Graph& graph, Airport origin, Airport destination) {
    BFSResult result;
    std::unordered_map<std::string, Vertex*> vertexes = graph.getVertexes();
    std::unordered_map<std::string, bool> visited;
    std::unordered_map<std::string, std::string> parent;
    std::unordered_map<std::string, double> distances;
    std::queue<Airport> queue;

    result.iterations = 0;
    result.distance = 0.0;

    //for (const auto& vertex : graph.vertexes) {
    for (const auto& vertex : vertexes) {
        visited[vertex.first] = false;
        parent[vertex.first] = "";
        distances[vertex.first] = std::numeric_limits<double>::infinity();
    }

    visited[origin.Airport_ID] = true;
    distances[origin.Airport_ID] = 0.0;
    queue.push(origin);

    while (!queue.empty()) {
        result.iterations++;

        Airport current = queue.front();
        queue.pop();

        if (current.Airport_ID == destination.Airport_ID) {
            
            std::string id = current.Airport_ID;
            while (id != "") {
                result.route.push_back(graph.findById(id));
                id = parent[id];
            }
            std::reverse(result.route.begin(), result.route.end());
            result.distance = distances[current.Airport_ID];
            return result;
        }

        //Vertex* vertex = graph.vertexes[current.Airport_ID];
        Vertex* vertex = vertexes[current.Airport_ID];
        for (auto& edge : vertex->edges) {
            Vertex* adjacent = (edge->vertexes[0] == vertex) ? edge->vertexes[1] : edge->vertexes[0];
            Airport adjacentAirport = adjacent->data;

            if (!visited[adjacentAirport.Airport_ID]) {
                visited[adjacentAirport.Airport_ID] = true;
                parent[adjacentAirport.Airport_ID] = current.Airport_ID;
                distances[adjacentAirport.Airport_ID] = distances[current.Airport_ID] + edge->distancia;
                queue.push(adjacentAirport);
            }
        }
    }

    result.distance = std::numeric_limits<double>::infinity();
    return result;
}

#endif