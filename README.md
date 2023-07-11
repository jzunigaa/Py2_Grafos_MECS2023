# RUTA AÉREA ÓPTIMA CON GRAFOS Y ALGORITMOS DE BÚSQUEDA

Proyecto 02 del curso Estructuras de Datos, Maestría en Computer Science - UTEC 2023.

#### Gestión de Rutas/Destinos y Aeropuertos

- Implementado en POO
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
