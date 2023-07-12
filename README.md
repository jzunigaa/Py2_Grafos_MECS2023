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
El proyecto consta de unos datos iniciales de aeropuertos (nacionales e internacionales) las cuales incluyen su ubicación, nombre e Id entre otros pero siendo los tres primeros nuestros pilares, esto nos lleva primero a usar de un parser para “leer” los datos y luego agruparlo en nuestra estructura de datos que hemos convenido que sea un grafo ya que nos permite el uso de nuestros algoritmos, para simplificar el modelo se asume que las conexiones (aristas) sean bi-direccionales entre aeropuertos (vertices), habiendo algunos algoritmos que requieren peso entonces este será la distancia entre los aeropuertos y se tiene en cuenta la curvatura terrestre.


### 3. Importancia del Blockchain en el dominio de datos elegido
------------
Este proyecto ayuda a comprender de mejor manera los distintos algoritmos de búsqueda y rutas, para un posterior desarrollo funcional debería tener algunas variaciones, tendría como objetivo ayudar a un viajero inexperto y teniendo en cuenta que el dispositivo más usado es el celular no podría tener un algoritmo tan pesado como es Dijkstra entonces usaría un A*.

### 4. Implementación
------------

#### 4.1 Arquitectura
Para lograr el cumplimiento de los requerimientos se ha desarrollado 4 capas dentro de la arquitectura de programas en C++.
Se explica en orden de los procesos de construcción del Blockchain: Capa Kernel, Capa Base de Datos, Capa BlockChain y Capa Vista.
En vista de los requerimientos del proyecto vimos conveniente usar unos grafos (vértice, arista).

### 4.2 Clase AIRPORT.h: Aeropuertos obtenidos del Json

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

### 4.3 UndirectedGraphAirpot.h: Grafo de los aeropuertos

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


### 4. Explicación de la estructura de datos y algoritmos de búsqueda
------------

## Clases

- **Airport** - Sirve como base para el soporte de información del aeropuerto
- **Graph** - Es la clase grafo para la gestión de Aueropuertos y sus destinos, cada aeropuerto es un vértice y cada destino o conexión es una arista
- **Posicion** - Se usa para gestionar las posiciones geográficas a base de Longitud y Latitud, con ell ase obtiene la distancia geográfica entre dos puntos o localizaciones geográficas.


### 5. Análisis de la complejidad en notación Big O de los algoritmos de búsqueda
------------


### 6. Conclusiones
------------


### 7. Bibliografía
------------
