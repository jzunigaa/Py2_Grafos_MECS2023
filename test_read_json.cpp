// Test JSON
#include "json.h"
#include "grafic.h"
#include "dijkstra.h"
#include<unordered_map>
#include "UndirectedGraphAirport.h"
#include "astar.h"

using namespace std;

int main() {
    int gd=DETECT, gm;
    int a;
    int x = 1300;
    int y = 680;

	Graph g;
    JSON jsonparser;

    std::cout << "Leyendo archivo de datos ..." << std::endl;
    if (jsonparser.read_JSON(g, "airports.json"))  //  pe.json, airports.json
    {
        std::cout << "Datos cargados correctamente..." << std::endl;
    }
/*
    //grafic mapa(x,y,jsonparser.lat_min,jsonparser.lat_max,jsonparser.lon_min,jsonparser.lon_max,g);

    grafic mapa(x,y,g);

    //g.display();

    //grafico
    initwindow(x, y, "Grafos");
    mapa.get_graficGraph(); //dibuja el grafo completo
*/

    //eliminaciones
    g.deleteVertex(g.findById("1638")); //lisboa
    g.deleteVertex(g.findById("2564"));//sao paulo

    //algoritmos
    Graph dijkstra_result;
    Graph AStar_Result;

    //Dijkstra
    DijkstraResult dr = dijkstra(g,"6924","4305");

    for(const auto& id: dr.route){
        dijkstra_result.insertVertex(g.findById(id));
    };

    for(int i = 0; i < dr.route.size() - 1; i++){
        dijkstra_result.createEdge(dijkstra_result.findById(dr.route[i]),dijkstra_result.findById(dr.route[i+1]));
    };

    //bfs
    AStarResult astar_ = astar(g,"6924","4305");

    for(const auto& id: astar_.route){
        AStar_Result.insertVertex(g.findById(id));
    };

    for(int i = 0; i < astar_.route.size() - 1; i++){
        AStar_Result.createEdge(AStar_Result.findById(astar_.route[i]),AStar_Result.findById(astar_.route[i+1]));
    };

    //graficar resultado del algoritmo
    initwindow(x, y, "ResultadoDijkstra");
    grafic dj_result(x,y,dijkstra_result);
    grafic g_AStarResult(x,y,AStar_Result);

    char mensaje_1[1000];
    char mensaje_2[1000];
    std::string mensaje_str_1 = "DIJKSTRA: Ruta desde '" + dijkstra_result.findById(dr.route[0]).City + "' hasta '" + dijkstra_result.findById(dr.route[astar_.route.size()-1]).City \
                                + "' || distancia: " + to_string(round(dr.distance*100)/100.0) + " Km || iteraciones: " + to_string(dr.iterations);

    std::string mensaje_str_2 = "ASTAR: Ruta desde '" + AStar_Result.findById(astar_.route[0]).City + "' hasta '" + AStar_Result.findById(astar_.route[astar_.route.size()-1]).City \
                                + "' || distancia: " + to_string(round(astar_.distance*100)/100.0) + " Km || iteraciones: " + to_string(astar_.iterations);

    strcpy(mensaje_1,mensaje_str_1.c_str());
    strcpy(mensaje_2,mensaje_str_2.c_str());

    dj_result.mensajeHeader(mensaje_1,100,20);
    dj_result.get_graficGraph();

    dj_result.mensajeHeader(mensaje_2,100,40);
    g_AStarResult.get_graficGraph();

    // Wait for the user to press a key.
    getch();

    // Close the gr3aphics window.
    closegraph();
    return 0;
}

