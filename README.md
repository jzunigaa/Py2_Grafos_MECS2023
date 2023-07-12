# RUTA AÉREA ÓPTIMA CON GRAFOS Y ALGORITMOS DE BÚSQUEDA

Proyecto 02 del curso Estructuras de Datos, Maestría en Computer Science - UTEC 2023.

- Alfredo Minchez
- Jeyson Lino Nicho
- Jose Zuñiga Avila
- Juan Herencia

#### Gestión de Rutas/Destinos y Aeropuertos

- Implementado en POOr
- Se ha usado Lenguaje C++ v17


### 1. Introducción
------------
El presente proyecto se encuentra desarrollado en C++ y consta de dos grandes etapas: La implementación de algoritmos para interconectar distintos aeropuertos (desde la estructuración de los datos brindados de los aeropuertos hasta el algoritmo mismo) y la realización de un programa para mostrar los distintos algoritmos usados, además de compararlos entre ellos.


### 2. Descripción del caso de estudio planteado
------------
El proyecto consta de unos datos iniciales de aeropuertos (nacionales e internacionales) las cuales incluyen su ubicación, nombre e Id entre otros pero siendo los tres primeros nuestros pilares, esto nos lleva primero a usar de un parser para “leer” los datos y luego agruparlo en nuestra estructura de datos que hemos convenido que sea un grafo ya que nos permite el uso de nuestros algoritmos, para simplificar el modelo se asume que las conexiones (aristas) sean bi-direccionales entre aeropuertos (vértices), habiendo algunos algoritmos que requieren peso entonces este será la distancia entre los aeropuertos y se tiene en cuenta la curvatura terrestre.


### 3. Importancia del proyecto
------------
Este proyecto ayuda a comprender de mejor manera los distintos algoritmos de búsqueda y rutas, para un posterior desarrollo funcional debería tener algunas variaciones, tendría como objetivo ayudar a un viajero inexperto y teniendo en cuenta que el dispositivo más usado es el celular no podría tener un algoritmo tan pesado como es Dijkstra entonces usaría un A*.


### 4. Explicación de la estructura de datos y algoritmos de búsqueda
------------

## Clases

- **Airport** - Sirve como base para el soporte de información del aeropuerto
- **Graph** - Es la clase grafo para la gestión de Aueropuertos y sus destinos, cada aeropuerto es un vértice y cada destino o conexión es una arista
- **Posicion** - Se usa para gestionar las posiciones geográficas a base de Longitud y Latitud, con ell ase obtiene la distancia geográfica entre dos puntos o localizaciones geográficas.

### 4.1 Clase AIRPORT.h: Aeropuertos obtenidos del Json

```cpp
struct Airport {
  	std::string Airport_ID;    // 2792,
 	std::string Country;       // Peru,
  	std::string Name;          // Juliaca,  
  	std::string City;          // Juliaca,  
  	double Longitude;          // -70.158169,
  	double Latitude;           // -15.467103,
  	std::string DBTZ;          // U,
  	std::string IATA_FAA;      // JUL,
  	std::string ICAO;          // SPJL,
  	int Timezone;              // 12552,
  	std::string DST;           // -5,
  	std::vector<std::string> destinations; // Lista de IDs de Airports
	}
	struct Posicion {
		double longitud;
    		double latitud;
	};
```

| Método | Descripción |
| ------ | ------ |
| distancia (Posicion origen, Posicion destino) | Obtencion de la distancia geográfica usando la formula de Haversine |


### 4.2 UndirectedGraphAirpot.h: Grafo de los aeropuertos

```cpp
struct Edge {
    	Vertex* vertexes[2];
    	double distancia;
	};//Una arista siempre se compone de vertices

	struct Vertex {
    	Airport data;
   	 std::list<Edge*> edges;
	};//los vertices guardan sus listas de aristas

	class Graph{
	double lat_min = 1000,lat_max = -1000,lon_min = 1000,lon_max = -1000;
	//estos valores serán importantes al momento de graficar
	std::unordered_map<string, Vertex*>  vertexes;
	}}//el key del hashtable es el Airport ID para simplificar los recorridos
```

| Método | Descripción |
| ------ | ------ |
| bool insertVertex(Airport vertex) | Insertar nuevo vértice que es Aeropuerto |
| bool existVertex(string id) | Verificar si existe un vértice (por id) |
| bool createEdge(Airport a1, Airport a2) | Crear nueva arista entre los vértices aeropuertos a1 y a2 |
| bool deleteVertex(Airport a) | Eliminar la arista (si existe) que tenga id |
| void recalculateFrontiers() | Recalcular los limites maximos y minimos de longitudes y latitudes del grafo |
| bool deleteEdge(Airport a1, Airport a2) | Borrar la arista que tiene vértices id1 e id2 ***(importante ya que usa un select) |
| int getNumVertices() | Método que muestra los valores de los nodos de la lista circular doble. |
| int getNumEdges() | Método que retorna la cantidad dde nodos existentes en la lista circular doble. |
| float density() | Método que retorna el valor del nodo anterior al head. |
| bool isDense(float threshold = 0.5) |  |
| bool empty() |  |
| void display() |  |
| void displayVertex(Airport a) |  |
| Airport findById(string id) |  |
| double getDistance(string id1, string id2) |  |
| unordered_map<string, Vertex*> getVertexes() |  |


## Algoritmos

### 4.3 BFS
Se define estructura llamada "BFSResult" la cual contiene tres campos: "route" (una lista de cadenas que representa la ruta desde el origen hasta el destino), "distance" (la distancia total de la ruta) e "iterations" (el número de iteraciones realizadas durante la búsqueda).

La función "bfs" toma como entrada el grafo, el aeropuerto de origen y el aeropuerto de destino. Devuelve un objeto "BFSResult" que contiene la ruta más corta y la distancia.

El bucle principal del algoritmo de BFS comienza y se ejecuta mientras la cola no esté vacía. En cada iteración, se extrae un aeropuerto de la cola y se verifica si es el aeropuerto de destino. Si es así, se reconstruye la ruta desde el aeropuerto de destino hasta el origen utilizando el mapa "parent", se invierte la ruta y se guarda en el campo "route" del resultado. También se almacena la distancia total en el campo "distance" y se devuelve el resultado.

Si el aeropuerto extraído de la cola no es el destino, se obtiene el vértice correspondiente al aeropuerto y se exploran sus vecinos. Si un vecino no ha sido visitado, se marca como visitado, se actualiza su padre, se actualiza la distancia acumulada y se encola en la cola.

Si se llega al final del bucle sin encontrar el aeropuerto de destino, se establece la distancia en infinito para indicar que no se encontró una ruta válida.

### 4.4 ASTAR
Se define una estructura llamada "AStarResult" la cual ontiene tres campos: "route" (una lista de cadenas que representa la ruta desde el origen hasta el destino), "distance" (la distancia total de la ruta) y "iterations" (el número de iteraciones realizadas durante la ejecución del algoritmo).

La función "heuristic" implementa una función heurística para estimar la distancia entre dos vértices. En este caso, se utiliza la distancia euclidiana entre las coordenadas de latitud y longitud de los vértices.

La función "astar" toma como entrada el grafo, el aeropuerto de origen y el aeropuerto de destino. Devuelve un objeto "AStarResult" que contiene la ruta más corta y la distancia.

El bucle principal del algoritmo A* comienza y se ejecuta mientras la cola de prioridad no esté vacía. En cada iteración, se extrae el vértice con la menor prioridad de la cola y se verifica si es el vértice de destino. Si es así, se detiene el algoritmo.

Si el vértice extraído no es el destino, se obtiene el vértice correspondiente y se recorren sus aristas. Se calcula la distancia total desde el origen hasta el vértice adyacente a través de la arista actual. Si esta distancia es menor que la distancia almacenada en el mapa de distancias para el vértice adyacente, se actualiza la distancia y se agrega el vértice adyacente a la cola de prioridad con una prioridad calculada como la suma de la distancia y la función heurística hasta el destino.

Una vez que se ha alcanzado el vértice de destino o se ha completado el bucle, se construye la ruta desde el aeropuerto de destino hasta el origen utilizando el mapa de vértices previos. La ruta se invierte y se guarda en el campo "route" del resultado. La distancia total se obtiene del mapa de distancias y se guarda en el campo "distance". El número de iteraciones realizado se almacena en el campo "iterations".

### 4.5 DIJKSTRA
Se define una estructura llamada "DijkstraResult" la cual contiene tres campos: "route" (una lista de cadenas que representa la ruta desde el origen hasta el destino), "distance" (la distancia total de la ruta) y "iterations" (el número de iteraciones realizadas durante la ejecución del algoritmo).

La función "dijkstra" toma como entrada el grafo, el aeropuerto de origen y el aeropuerto de destino. Devuelve un objeto "DijkstraResult" que contiene la ruta más corta y la distancia.

Dentro de la función "dijkstra", se realiza una verificación inicial para asegurarse de que los aeropuertos de origen y destino existan en el grafo. Si alguno de ellos no existe, se muestra un mensaje de error y se devuelve un resultado vacío.

El bucle principal del algoritmo de Dijkstra comienza y se ejecuta mientras la cola de prioridad no esté vacía. En cada iteración, se extrae el vértice con la menor distancia de la cola y se verifica si es el vértice de destino. Si es así, se detiene el algoritmo.

Si el vértice extraído no es el destino, se obtiene el vértice correspondiente y se recorren sus aristas. Se calcula la distancia total desde el origen hasta el vértice adyacente a través de la arista actual. Si esta distancia es menor que la distancia almacenada en el mapa de distancias para el vértice adyacente, se actualiza la distancia y se agrega el vértice adyacente a la cola de prioridad.

Una vez que se ha alcanzado el vértice de destino o se ha completado el bucle, se construye la ruta desde el aeropuerto de destino hasta el origen utilizando el mapa de vértices previos. La ruta se invierte y se guarda en el campo "route" del resultado. La distancia total se obtiene del mapa de distancias y se guarda en el campo "distance". El número de iteraciones realizado se almacena en el campo "iterations".


### 5. Análisis de la complejidad en notación Big O de los algoritmos de búsqueda
------------

### 5.1 BFS
En cuanto a la complejidad, el algoritmo BFS tiene una complejidad de tiempo de O(V + E), donde V es el número de vértices y E es el número de aristas en el grafo. Esto se debe a que el algoritmo visita cada vértice y cada arista una vez en el peor caso. El acceso a los vértices y aristas se realiza mediante el uso de mapas y colas, lo que ayuda a mantener la complejidad en O(V+E).

### 5.2 ASTAR
El algoritmo tiene una complejidad de tiempo de O((V + E) log V), donde V es el número de vértices y E es el número de aristas en el grafo. Esto se debe a la utilización de una cola de prioridad para seleccionar el vértice con la menor prioridad en cada iteración. Las operaciones de inserción y extracción en la cola de prioridad tienen un tiempo logarítmico. El acceso a los vértices y aristas se realiza mediante mapas y colas, lo que contribuye a mantener la complejidad.

### 5.3 DIJKSTRA
En cuanto a la complejidad, el algoritmo de Dijkstra tiene una complejidad de tiempo de O((V + E) log V), donde V es el número de vértices y E es el número de aristas en el grafo. Esto se debe a la utilización de una cola de prioridad para seleccionar el vértice con la menor distancia en cada iteración. Las operaciones de inserción y extracción en la cola de prioridad tienen un tiempo logarítmico. El acceso a los vértices y aristas se realiza mediante mapas y colas, lo que contribuye a mantener la complejidad.

### 6. Conclusiones
------------


### 7. Bibliografía
------------
