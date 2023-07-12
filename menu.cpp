#include<iostream>
#include "json.h"
#include "UndirectedGraphAirport.h"
#include "grafic.h"
#include "dijkstra.h"
/*
#include<unordered_map>
#include "astar.h"
#include "dfs.h"
#include "bfs.h"
*/
using namespace std;

Graph *g = nullptr;
JSON jsonparser;
DijkstraResult r;
int gd=DETECT, gm;
int a;
int x = 1300;
int y = 680;


void cls() {
	system("cls");
}

void pause() {
	system("pause");
}

int menu()
{
	int opcion;

	while(true)
	{
	    cls();
		cout<<"-----------------------------------------------------"<<endl;
		cout<<"\tRutas Aereas - Estructura de Datos MECS2023"<<endl;
		cout<<"-----------------------------------------------------"<<endl<<endl;

		cout<<"\t1. Cargar y mostrar la data de Peru"<<endl;
		cout<<"\t2. Cargar y mostrar la data del mundo"<<endl;
		cout<<"\t3. Consultar rutas optimas"<<endl;
		/*
			3.1. Ingresas origen y destino
			3.2. Elegir el/los algoritmo(s)
				a. Dijkstra
				b. Astar
				c. DFS
				d. BFS
			     Ingrese la(s) opciones separadas por guion (ej. a-b o a-c): */
		cout<<"\t4. Mostrar salida de los algoritmos"<<endl;
		/*
			4.1. Ver grafico // ejecutar los algoritmos seleccionados
			4.2. Ver resultados // ejecutar los algoritmos seleccionados, muestra codigo y ciudad y kilometraje
			*/
		cout<<"\t5. Eliminar un vertice"<<endl;
		cout<<"\t6. Salir"<<endl<<endl;
			//6.1. Ingresar ID de aeropuerto
		cout<<"\t\tIngrese una opcion : "; cin>>opcion;
		if(opcion >= 1 and opcion <= 6)  {
			return opcion;
		} else {
			cout<<"\n\n\tIngrese la opcion correcta!"<<endl<<endl;
			pause();
		}
	}

	return opcion;
}

// Re asignar memoria para el Grafo
void resetMemGraph()
{
	if(g != nullptr) {
		//g->clear();
		delete g;
		g = nullptr;
	}
	g = new Graph;
}

void mostrarGrafo(){
    cls();
    cout<<"Mostrar grafo completo"<<endl;
    grafic mapa(x,y,*g);
    //grafico
    initwindow(x, y, "Mapa");
    mapa.get_graficGraph(); //dibuja el grafo completo
    // Wait for the user to press a key.
    getch();

    // Close the gr3aphics window.
    closegraph();
}
/*
void calculoAlgoritmos(){

}
*/
void cargarDataPeru() {
	cls();
    cout<<"-----------------------------------------------------"<<endl;
	cout<<"\tCargar y mostrar datos del Peru"<<endl;
	cout<<"-----------------------------------------------------"<<endl<<endl;
	cout << "Leyendo archivo de datos ..." << endl;
	resetMemGraph();
    if (jsonparser.read_JSON(*g, "pe.json"))  //  pe.json, airports.json
    {
        cout<<"Numero de aeropuertos : "<< g->getNumVertices()<<endl;
        cout<<"Numero de destinos    : "<< g->getNumEdges()<<endl;
    }
    mostrarGrafo();
	pause();
}

void cargarDataMundo() {
	cls();
    cout<<"-----------------------------------------------------"<<endl;
	cout<<"\tCargar y mostrar datos del Mundo"<<endl;
	cout<<"-----------------------------------------------------"<<endl<<endl;
	cout << "Leyendo archivo de datos ..." << endl;
	resetMemGraph();
    if (jsonparser.read_JSON(*g, "airports.json"))  //  pe.json, airports.json
    {
        cout<<"Numero de aeropuertos : "<< g->getNumVertices()<<endl;
        cout<<"Numero de destinos    : "<< g->getNumEdges()<<endl;
    }
    mostrarGrafo();
	pause();
}

void mostrarSalidas(Graph dijkstra_graf,DijkstraResult dijkstra_result  ) {
	cls();
	char mensaje_1[1000];
    char mensaje_2[1000];
    char mensaje_3[1000];
    char mensaje_4[1000];
    char mensaje_0[1000];
    cout<<"Motrar los graficos y datos resultantes"<<endl;
    initwindow(x, y, "Resultados");
    grafic dj_result(x,y,dijkstra_graf);
    std::string mensaje_str_1 = "DIJKSTRA -> distancia: " + to_string(round(dijkstra_result.distance*100)/100.0) + " Km | iteraciones: " + to_string(dijkstra_result.iterations) \
                                + " | # aeropuertos: " + to_string(dijkstra_result.route.size());
    std::string mensaje_cabecera = "Ruta desde '" + dijkstra_graf.findById(dijkstra_result.route[0]).City + "' hasta '" + dijkstra_graf.findById(dijkstra_result.route[dijkstra_result.route.size()-1]).City;
    strcpy(mensaje_0,mensaje_cabecera.c_str());
    strcpy(mensaje_1,mensaje_str_1.c_str());
    dj_result.get_graficGraph();
    setusercharsize( 1, 2, 3, 4 ); // 50% de ancho; 75% de alto
    dj_result.mensajeHeader(mensaje_0,50,20,RED,YELLOW,0);
    dj_result.mensajeHeader(mensaje_1,50,40,BLUE,WHITE,0);


	// Wait for the user to press a key.
    getch();

    // Close the gr3aphics window.
    closegraph();
}

void consultarRutas() {
	cls();
	std::string id_ini;
	std::string id_fin;
	std::string rpta;

	cout<<"Consulta de Rutas"<<endl;
	cout<<"Ingrese aeropuerto de partida (ID): ";
	cin>>id_ini;
	cout<<"\nIngrese aeropuerto de llegada (ID): ";
	cin>>id_fin;
	cout<<"Ingrese el(los) algoritmos que desea utilizar separados por guion (a-b-c):"<<endl;
	cout<<"a. Dijkstra   b. Astar   c. DFS  d. BFS"<<endl;
	cout<<endl;
	cin>>rpta;

	//algoritmos
    Graph dijkstra_graf;
    Graph AStar_graf;
    Graph dfs_graf;
    Graph bfs_graf;

    //Dijkstra
    DijkstraResult dijkstra_result = dijkstra(*g,id_ini,id_fin);

    for(const auto& id: dijkstra_result.route){
        dijkstra_graf.insertVertex(g->findById(id));
    };

    for(int i = 0; i < dijkstra_result.route.size() - 1; i++){
        dijkstra_graf.createEdge(dijkstra_graf.findById(dijkstra_result.route[i]),dijkstra_graf.findById(dijkstra_result.route[i+1]));
    };
	mostrarSalidas(dijkstra_graf,dijkstra_result );
	pause();
}

void eliminarVertice() {
	cls();
	cout<<"Eliminar vertice"<<endl;
	pause();
}


int main()
{
	int opcion;
	do {
		opcion = menu();
		switch(opcion)
		{
			case 1: cargarDataPeru();
				break;
			case 2: cargarDataMundo();
				break;
			case 3: consultarRutas();
				break;
			case 4: mostrarSalidas(*g,r);
				break;
			case 5: eliminarVertice();
				break;
		}
	}while(opcion != 6);

	//system("cls");
	return 0;
}
