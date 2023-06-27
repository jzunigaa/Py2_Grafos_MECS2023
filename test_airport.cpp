#include<iostream>
#include "airport.h"
int main()
{
	Posicion Juliaca(-15.467103,-70.158169), Tumbes(-3.552528,-80.381356), aux;
	
	std::cout<<"Entre los aeropuertos de Juliaca y Puno hay : "<<aux.distancia(Juliaca, Tumbes)<<" Km";
}
