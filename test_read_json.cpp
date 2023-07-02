// Test JSON
#include "json.h"
#include "grafic.h"

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

    grafic mapa(x,y,jsonparser.lat_min,jsonparser.lat_max,jsonparser.lon_min,jsonparser.lon_max,g);

    //g.display();

    //initgraph(&gd, &gm,(char*)"");
    initwindow(x, y, "Grafos");
    //g.get_graficAirports(x,y,jsonparser.lat_min,jsonparser.lat_max,jsonparser.lon_min,jsonparser.lon_max);
    //g.get_graficGraph(x,y,jsonparser.lat_min,jsonparser.lat_max,jsonparser.lon_min,jsonparser.lon_max);
    //g.get_graficEdges(x,y,jsonparser.lat_min,jsonparser.lat_max,jsonparser.lon_min,jsonparser.lon_max);

    //mapa.get_graficAirports(); //solo dibuja los vertices
    //mapa.get_graficEdges(); // solo dibuja las aristas
    mapa.get_graficGraph(); //dibuja el grafo completo

    return 0;
}

