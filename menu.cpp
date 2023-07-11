#include<iostream>
#include "json.h"
#include "UndirectedGraphAirport.h"
/*
#include "grafic.h"
#include "dijkstra.h"
#include<unordered_map>
#include "astar.h"
#include "dfs.h"
#include "bfs.h"
*/
using namespace std;

Graph *g = nullptr;
JSON jsonparser;

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
	pause();
}

void consultarRutas() {
	cls();
	cout<<"Consulta de Rutas"<<endl;
	pause();
}

void mostrarSalidas() {
	cls();
	cout<<"Motrar los graficos y datos resultantes"<<endl;
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
			case 4: mostrarSalidas();
				break;
			case 5: eliminarVertice();
				break;
		}
	}while(opcion != 6);
	
	//system("cls");
	return 0;
}
