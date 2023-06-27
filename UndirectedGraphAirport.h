#ifndef __UNDIRECTGRAPH_H
#define __UNDIRECTGRAPH_H
#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include "airport.h"

using namespace std;

//template<typename TV, typename TE>
struct Edge;

//template<typename TV, typename TE>
struct Vertex;

//template<typename TV, typename TE>
class Graph;

//////////////////////////////////////////////////////

//template<typename TV, typename TE>
struct Edge {
    Vertex* vertexes[2];
    double distancia;
};

//template<typename TV, typename TE>
struct Vertex {
    Airport data;
    std::list<Edge*> edges;
};

//template<typename TV, typename TE>
class Graph{
private:    
    std::unordered_map<string, Vertex*>  vertexes;
    
public:
	
	/**
	  Insertar nuevo vértice que es Aeropuerto
	**/
    bool insertVertex(Airport vertex)
    {
    	// Si ya existe, salir!
		if (existVertex(vertex.Airport_ID))
			return false;

        Vertex* newVertex = new Vertex;
        newVertex->data = vertex;
        vertexes[vertex.Airport_ID] = newVertex;

        return true;
    }
    
    /**
      Verificar si existe un vértice (por id)
    **/
    bool existVertex(string id)
    {
    	// Si el vértice id No existe (end es nulo)
    	if (vertexes.find(id) == vertexes.end()) 
    		return false;
    	return true;	
	}
	
	/**
	  Crear nueva arista entre los vértices aeropuertos a1 y a2
	  Internamente se calculará el peso (distancia)
	**/
    bool createEdge(Airport a1, Airport a2)
    {
    	// Si no existe uno o los dos vértices, salir!
		if (!existVertex(a1.Airport_ID) || !existVertex(a2.Airport_ID))
            return false;    
        
        Vertex* v1 = vertexes[a1.Airport_ID];
        Vertex* v2 = vertexes[a2.Airport_ID];
        
		// nueva arista de v1 a v2 con distancia de peso
        Edge* newEdge = new Edge; 
        Posicion aux;
        
        newEdge->vertexes[0] = v1;
        newEdge->vertexes[1] = v2;
        newEdge->distancia = aux.distancia(Posicion(a2.Longitude, a2.Latitude), Posicion(a1.Longitude, a1.Latitude));

		// Agregar la arista anterior a cada vértice
        v1->edges.push_back(newEdge);
        v2->edges.push_back(newEdge);

        return true;
    }
    
    /**
      Eliminar la arista (si existe) que tenga id
    **/
    bool deleteVertex(Airport a)
    {
    	// Si no existe, salir!
		if (!existVertex(a.Airport_ID))
			return false;
		
		// Obtener el vértice a eliminar
        Vertex* vertexToDelete = vertexes[a.Airport_ID];

        // Recorrer las aristas del vértice a eliminar
		for (auto edge : vertexToDelete->edges) {
			// Cada arista tiene 2 vértices v1 y v2
			if(edge->vertexes[0] == vertexToDelete)
			{
				Vertex* otherVertex = edge->vertexes[1];
				otherVertex->edges.remove(edge); // de v2 de esta arista, se elimina su arista v2v1
			}
			else {
				Vertex* otherVertex = edge->vertexes[0];
				otherVertex->edges.remove(edge); // de v1 de esta arista, se elimina su arista v1v2
			}
            
            delete edge; // se elimina esta arista
        }

        vertexes.erase(a.Airport_ID); // Borrar de la tabla hash
        delete vertexToDelete; // Borrar esta arista del grafo

        return true;
    }
    
    /**
      Borrar la arista que tiene vértices id1 e id2
    **/
    bool deleteEdge(Airport a1, Airport a2)
    {
    	// Si no existe vértices id1 y/o id2, salir!!!
        if (!existVertex(a1.Airport_ID) || !existVertex(a2.Airport_ID))
            return false;    

        // Con los ids obtener los vértices v1 y v2
		Vertex* v1 = vertexes[a1.Airport_ID];
        Vertex* v2 = vertexes[a2.Airport_ID];

        Edge* edgeToDelete = nullptr;

        // recorrer las aristas de v1
		for (auto edge : v1->edges) {
			// Si esta arista es v1v2 o v2v1 
            if ((edge->vertexes[0] == v1 && edge->vertexes[1] == v2) || (edge->vertexes[0] == v2 && edge->vertexes[1] == v1)) {
                edgeToDelete = edge; // considerar la arista para eliminar
                break;
            }
        }

        // Si no se encontró la arista o son vértices desconectados, salir!!!
		if (edgeToDelete == nullptr)
            return false;

        // borrar la arista que conecta de v1 a v2 o de v2 a v1
		v1->edges.remove(edgeToDelete);
        v2->edges.remove(edgeToDelete);
        delete edgeToDelete; // borrar la arista del grafo

        return true;
    }
    
    /**
      Obtiene el nro de vértices
    **/
    int getNumVertices()
    {
    	int numVertices = vertexes.size();

        if (numVertices <= 1)
            numVertices = 0;
        return numVertices;    
	}
    
    /**
      Obtiene el nro de aristas
    **/
    int getNumEdges()
    {
    	int numEdges = 0;
    	
    	for (const auto& vertex : vertexes) {
            numEdges += vertex.second->edges.size();
        }
        numEdges = numEdges / 2; // en este caso es NO dirigido solo existe una conexión entre vértices

        return numEdges;
	}
    
    /**
      Calcula la densidad de las conexiones entre vértices
    **/
    float density()
    {
        int numVertices = getNumVertices();
        int numEdges = getNumEdges();

        // Si es grafo vacío 
        if (numVertices <= 1)
            return 0.0;

        float maxNumEdges = (numVertices * (numVertices - 1)) / 2;
        
        cout<<"Numero de aristas que conectan actualmente : "<<numEdges<<endl;
        cout<<"Numero de aristas que deberian conectar todos los vertices: "<<maxNumEdges<<endl;
        return numEdges / maxNumEdges;
    }
    
    /**
      Es denso si es igual o mayor a 0.5 
    **/
    bool isDense(float threshold = 0.5)
    {
        return density() >= threshold;
    }
    
    /**
      Devuelve true si está vacío el grafo
	**/
    bool empty()
    {
        return vertexes.empty();
    }
    
    /**
      Borrar todos los vértices y aristas del grafo
	**/
    void clear()
    {
        for (auto& vertex : vertexes) {
            for (auto& edge : vertex.second->edges) {
                delete edge;
            }
            delete vertex.second;
        }

        vertexes.clear();
    }
    
	/**
	  Mostrar los vértices y sus aristas
	**/  
    void display()
    {
    	// Recorrer el hash table de vértices
        for (const auto& vertex : vertexes) {
            cout << "Aeropuerto ID " << vertex.first << ", Ciudad " << vertex.second->data.Name <<", tiene conexiones con:"<<endl;
            cout << "Rutas: ";
            for (auto& edge : vertex.second->edges) {
                cout << "(" << edge->vertexes[0]->data.City << " - " << edge->vertexes[1]->data.City << ", distancia " << edge->distancia << " Km) ";
            }
            cout << endl;
        }
    }
    
    /**
      Mostrar un vértice
    **/
    void displayVertex(Airport a)
    {
        if (!existVertex(a.Airport_ID)) {
            cout << "Aeropuerto con el ID "<<a.Airport_ID<<" no encontrado" << endl;
            return;
        }

        Vertex* vertex = vertexes[a.Airport_ID];
        cout << "Aeropuerto " << a.Airport_ID << ": " << a.Name << endl;
        cout << "Conexiones: ";
        for (auto& edge : vertex->edges) {
            cout << "(" << edge->vertexes[0]->data.Name << " - " << edge->vertexes[1]->data.Name << ", distancia " << edge->distancia << " Km) ";
        }
        cout << endl;
    }
    
    /**
      Buscar el vértice por id y devolver la data
	**/
    Airport findById(string id)
    {
        if (!existVertex(id))
            throw out_of_range("Aeropuerto con el ID " + id + " no encontrado");

        return vertexes[id]->data;
    }
};

#endif
