// Test JSON
#include "json.h"

int main() {

	Graph g;
    JSON jsonparser;
    
    std::cout << "Leyendo archivo de datos ..." << std::endl;
    if (jsonparser.read_JSON(g, "airports.json"))  //  pe.json, airports.json
    {
        std::cout << "Datos cargados correctamente..." << std::endl;
    }
    
    g.display();

    return 0;
}

