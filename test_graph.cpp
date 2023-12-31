#include "airport.h"
#include "UndirectedGraphAirport.h"

using namespace std;


int main()
{
    Graph graph;
    //std::string id, std::string country, std::string name, std::string city, double longit, double latit
    Airport a("2789", "Peru", "Jorge Chavez Intl"            , "Lima", -77.114319, -12.021889);
    Airport b("2796", "Peru", "Pedro Canga"                  , "Tumbes", -80.381356, -3.552528);
    Airport c("6067", "Peru", "Fap David Figueroa"           , "Huanuco", -76.204797, -9.878811);
    Airport d("6066", "Peru", "Fap Armando Revoredo"         , "Cajamarca", -78.4894, -7.139183);
    Airport e("2808", "Peru", "Pedro Aldamiz"                , "Puerto Maldonado", -69.228611, -12.613611);
    Airport f("2809", "Peru", "Fap Guillermo Concha"         , "Piura", -80.616444, -5.20575);
    Airport g("2802", "Peru", "Rodriguez Ballon"             , "Arequipa", -71.583083, -16.341072);
    Airport h("2801", "Peru", "Coronel Franciso Secada Intl" , "Iquitos", -73.308806, -3.784739);
    Airport i("2806", "Peru", "Cadete Guillermo del Castillo", "Tarapoto", -76.373247, -6.508742);
    Airport j("2807", "Peru", "Coronel Carlos Ciriani Intl"  , "Tacna", -70.275833, -18.053333);

    // Insertar vértices por aeropuerto
    graph.insertVertex(a);
    graph.insertVertex(b);
    graph.insertVertex(c);
    graph.insertVertex(d);
    graph.insertVertex(e);
    graph.insertVertex(f);
    graph.insertVertex(g);
    graph.insertVertex(h);
    graph.insertVertex(i);
    graph.insertVertex(j);


    // Crear aristas
    graph.createEdge(a, f);
    graph.createEdge(a, b);
    graph.createEdge(b, c);
    graph.createEdge(b, d);
    graph.createEdge(c, d);
    graph.createEdge(c, e);
    graph.createEdge(d, e);
    graph.createEdge(e, i);
    graph.createEdge(e, j);
    graph.createEdge(f, g);
    graph.createEdge(f, h);
    graph.createEdge(g, i);
    graph.createEdge(h, i);
    graph.createEdge(i, j);
    

    // Mostrar el grafo
    graph.display();

    // Obtener densidad
    float density = graph.density();
    cout << "\nDensidad del grafo: " << density << endl;

    // Borrar vértice y arista
    cout<<"\nSe eliminara el aeropuerto Tumbes"<<endl;
    graph.deleteVertex(b);
    cout<<"Se eliminara la ruta entre los aeropuertos Huanuco y Cajamarca"<<endl<<endl;
    graph.deleteEdge(d, c);

    // Mostrar el grafo nuevamente
    graph.display();
    
    // Obtener densidad nuevamente
    density = graph.density();
    cout << "\nNueva densidad del grafo: " << density << endl;
    
    // Verificando la existencia del aeropuerto de Iquitos
    string v = h.Airport_ID;
    if (graph.existVertex(v))
    {
    	cout<<"\nExiste el aeropuerto "<<v<<" - "<<h.Name<<" - "<<h.City<<endl<<endl;
	} else {
		cout<<"\nNo existe el aeropuerto "<<v<<endl<<endl;
	}
  
    // Verificar si el grafo es denso
    if (graph.isDense())
        cout << "\nEl grafo es denso" << endl;
    else
        cout << "\nEl grafo no es denso" << endl;


	// Verificar si el grafo está vacío
    if (graph.empty())
        cout << "El grafo esta vacio" << endl;
    else
        cout << "El grafo no esta vacio" << endl;
    
    // Verificar si los aeropuertos x y y estan conectados
    Airport x = a, y = f; // a Lima, f Piura estan conectados, d Cajamarca, g Arequipa estan desconectados
    cout << "\nVerificando si los aeropuertos de " << x.City << " y " << y.City << " estan conectados" <<endl;
    double dist = graph.getDistance(x.Airport_ID, y.Airport_ID);
    if( dist >= 0 )
      cout << "Los aeropuertos " << x.City << " y " << y.City << " estan conectados" <<endl
           << "La distancia entre ellos es " << dist << " Km" << endl;
    else
	  cout << "Los aeropuertos " << x.City << " y " << y.City << " NO estan conectados" <<endl;       
   
      
    //Prueba Algoritmos
    cout << "--------Algoritmos--------" << endl;
    string origen = "2789"; // ID del aeropuerto de origen
    string destino = "2807"; // ID del aeropuerto de destino

    //Prueba Dijkstra
    cout << "--------Dijkstra" << endl;
    DijkstraResult resultDijkstra = dijkstra(graph, origen, destino);
    
    // Obtener los resultados de la ruta, distancia y número de iteraciones
    vector<string> rutaDijkstra = resultDijkstra.route;
    double distanciaDijkstra = resultDijkstra.distance;
    int iteracionesDijkstra = resultDijkstra.iterations;
    
    // Imprimir los resultados
    cout << "Ruta: ";
    for (const string& airportID : rutaDijkstra) {
        cout << airportID << " ";
    }
    cout << endl;
    
    cout << "Distancia: " << distanciaDijkstra << " Km" << endl;
    cout << "Número de iteraciones: " << iteracionesDijkstra << endl;

    //Prueba A*
    cout << "--------A*" << endl;
    AStarResult resultAstar = astar(graph, origen, destino);
    
    // Obtener los resultados de la ruta, distancia y número de iteraciones
    vector<string> rutaAstar = resultAstar.route;
    double distanciaAstar = resultAstar.distance;
    int iteracionesAstar = resultAstar.iterations;
    
    // Imprimir los resultados
    cout << "Ruta: ";
    for (const string& airportID : rutaAstar) {
        cout << airportID << " ";
    }
    cout << endl;
    
    cout << "Distancia: " << distanciaAstar << " Km" << endl;
    cout << "Número de iteraciones: " << iteracionesAstar << endl;

    //Prueba BFS
    cout << "--------BFS" << endl;
    AStarResult resultBFS = astar(graph, origen, destino);
    
    // Obtener los resultados de la ruta, distancia y número de iteraciones
    vector<string> rutaBFS = resultBFS.route;
    double distanciaBFS = resultBFS.distance;
    int iteracionesBFS = resultBFS.iterations;
    
    // Imprimir los resultados
    cout << "Ruta: ";
    for (const string& airportID : rutaBFS) {
        cout << airportID << " ";
    }
    cout << endl;
    
    cout << "Distancia: " << distanciaBFS << " Km" << endl;
    cout << "Número de iteraciones: " << iteracionesBFS << endl;

    // Limpiar el grafo
    graph.clear();

    return 0;
}

