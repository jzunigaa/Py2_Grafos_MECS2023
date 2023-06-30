#include <iostream>
#include <fstream>
#include <json/json.h>
#include "airport.h"

int main() {
    // Abrir el archivo JSON
    std::ifstream file("airports.json");

    // Leer el contenido del archivo JSON
    Json::Value jsonData;
    file >> jsonData;
    std::vector<Airport> aeropuertos;
    // Iterar sobre los JSONs del array
    for (const auto& json : jsonData) {
        // Acceder a los datos del JSON
        std::string lon = json["Longitude"].asString();
        std::string lat = json["Latitude"].asString();

        double longi = std::stod(lon);
        double latit = std::stod(lat);

        Airport vuelo(json["Airport ID"].asString(), json["Country"].asString(), json["Name"].asString(), json["City"].asString(), longi,latit);
        //inicializar los datos del json
        std::vector<std::string> destinos;
        for (const auto& valor : json["destinations"]) {
            destinos.push_back(valor.asString());
        }
        // subir los datos de destino
        vuelo.destinations = destinos;
        aeropuertos.push_back(vuelo);
    }
    // Cerrar el archivo
    file.close();

    return 0;
}
