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

    //grafic mapa(x,y,jsonparser.lat_min,jsonparser.lat_max,jsonparser.lon_min,jsonparser.lon_max,g);
/*
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
    DijkstraResult dr = dijkstra(g,"5490","3246"); // 6924 -> 4305

/*
    DijkstraResult dr;
    int mayor = 5;
    std::vector<std::string> ruta_may;
    for(auto v: g.getVertexes()){
        for(auto v2: g.getVertexes()){
            dr = dijkstra(g,v.second->data.Airport_ID,v2.second->data.Airport_ID);
            if(dr.route.size() > mayor){
                mayor = dr.route.size();
                ruta_may.clear();
                ruta_may = dr.route;
                cout<<"Cantidad aeropuertos: "<<mayor<<endl;
                cout<<"desde: "<<ruta_may[0]<<" - hasta: "<<ruta_may[ruta_may.size()-1]<<endl;
                mayor = mayor + 2;
            }
        }
    }

    cout<<"Cantidad aeropuertos: "<<mayor<<endl;
    cout<<"desde: "<<ruta_may[0]<<" - hasta: "<<ruta_may[ruta_may.size()-1]<<endl;
*/

    for(const auto& id: dr.route){
        dijkstra_result.insertVertex(g.findById(id));
    };

    for(int i = 0; i < dr.route.size() - 1; i++){
        dijkstra_result.createEdge(dijkstra_result.findById(dr.route[i]),dijkstra_result.findById(dr.route[i+1]));
    };

    //bfs
    AStarResult astar_ = astar(g,"5490","3246");

    for(const auto& id: astar_.route){
        AStar_Result.insertVertex(g.findById(id));
    };

    for(int i = 0; i < astar_.route.size() - 1; i++){
        AStar_Result.createEdge(AStar_Result.findById(astar_.route[i]),AStar_Result.findById(astar_.route[i+1]));
    };

    //graficar resultado del algoritmo
    initwindow(x, y, "----Resultados----");
    grafic dj_result(x,y,dijkstra_result);
    grafic g_AStarResult(x,y,AStar_Result);

    char mensaje_1[1000];
    char mensaje_2[1000];
    char mensaje_0[1000];
    std::string mensaje_str_1 = "DIJKSTRA -> distancia: " + to_string(round(dr.distance*100)/100.0) + " Km | iteraciones: " + to_string(dr.iterations) \
                                + " | # aeropuertos: " + to_string(dr.route.size());

    std::string mensaje_str_2 = "ASTAR -> distancia: " + to_string(round(astar_.distance*100)/100.0) + " Km | iteraciones: " + to_string(astar_.iterations) \
                                + " | # aeropuertos: " + to_string(astar_.route.size());

    strcpy(mensaje_1,mensaje_str_1.c_str());
    strcpy(mensaje_2,mensaje_str_2.c_str());

    dj_result.get_graficGraph(); // grafica el resultado de dikjstra
    g_AStarResult.get_graficGraph(); // grafica el resultado de astar

    //cabecera
    std::string mensaje_cabecera = "Ruta desde '" + dijkstra_result.findById(dr.route[0]).City + "' hasta '" + dijkstra_result.findById(dr.route[astar_.route.size()-1]).City;
    strcpy(mensaje_0,mensaje_cabecera.c_str());
    setusercharsize( 1, 2, 3, 4 ); // 50% de ancho; 75% de alto
    dj_result.mensajeHeader(mensaje_0,50,20,RED,YELLOW,0);
    dj_result.mensajeHeader(mensaje_1,50,40,BLUE,WHITE,0);
    dj_result.mensajeHeader(mensaje_2,50,60,BLUE,WHITE,0);

    // Wait for the user to press a key.
    getch();

    // Close the gr3aphics window.
    closegraph();

    return 0;
}

