#ifndef __AIRPORT_H
#define __AIRPORT_H
#include<string>
#include<cmath>
#include<vector>

struct Posicion;

/**
  Estructura para los datos de un aeropuerto
**/
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
  
  Airport(std::string id, std::string country, std::string name, std::string city, double longit, double latit)
  {
  	Airport_ID = id;   
    Country    = country;      
    Name       = name;         
    City       = city;         
    Longitude  = longit;    
    Latitude   = latit;     
    DBTZ       = "";
    IATA_FAA   = "";
    ICAO       = "";
    Timezone   = 0;
    DST        = "";
  };
  
  Airport()
  {
  	Airport_ID = "";   
    Country    = "";      
    Name       = "";
    City       = "";
    Longitude  = 0.0;
    Latitude   = 0.0;
    DBTZ       = "";
    IATA_FAA   = "";
    ICAO       = "";
    Timezone   = 0;
    DST        = "";
  }
};

/**
  Estructura para gestionar las localizaciones geofráficas
  El método distancia() sirve para hallar la distancia geográfica 
  entre dos puntos geográficos
**/
struct Posicion {
	double longitud;
    double latitud;
	
	/**
	   Posición o localización geográfica
	   Argumentos en ° sexagesimales
	   longitud entre 0° y 180°
	   latitud  entre -90° y 90°
	**/
	Posicion(double lon = 0, double lat = 0)
	{
		longitud = lon*M_PI/180; // en rad
		latitud  = lat*M_PI/180; // en rad
	}
	
	/**
       Obtencion de la distancia geográfica usando la formula de Haversine:
       R = 6371 es media de la radio de la tierra en Km
       a = sin²(dif_lat/2) + cos(lat_origen) · cos(lat_destino) · sin²(dif_lon/2)
       c = 2 * atan2 (raiz(a), raiz(1-a))
       distancia = R * c
    **/
    double distancia(Posicion origen, Posicion destino)
    {
  	  double R = 6371; 
  	
      double dif_lat = destino.latitud - origen.latitud;
      double dif_lon = destino.longitud - origen.longitud;
      double a = pow(sin(dif_lat/2),2) + cos(origen.latitud)*cos(destino.latitud)* pow(sin(dif_lon/2),2);
      double c = 2*atan2(sqrt(a),sqrt(1 - a));                      

      return R * c;
    };
};




#endif 
