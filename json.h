#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <vector>
#include <unordered_map>
#include "UndirectedGraphAirport.h"
#include "airport.h"
struct Registro
{
    std::unordered_map<std::string, std::string> data;
    std::vector<std::string> destinos;
};

class JSON {
    std::unordered_map<std::string, std::string> data;
    std::vector<std::string> dest;

public:
    double lat_min = 1000,lat_max = -1000,lon_min = 1000,lon_max = -1000;
    std::list<Registro> registros;
    void parse(const std::string& json) {

        std::istringstream iss(json);
        std::string line;
        std::string key, value;
        bool fin_registro = false;

        while (std::getline(iss, line)) {
            trim(line);
            if (line.empty() || line[0] == '[' || line[0] == '{' || line[0] == '}' || (line.size() - 2 == '}' && line.size() - 1 == ',')) {
                continue;
            }
            std::istringstream issLine(line);
            std::getline(issLine, key, ':');
            std::getline(issLine, value);
            trim(key);
            trim(value);

            // Remover comillas del valor si existe
            if (value[0] == '"' && value[value.size()-2] == '"') {
                value = value.substr(1, value.size() - 3);
            }

            // Remover comillas de la clave si existe
            if (key[0] == '"' && key[key.size() - 1] == '"') {
                key = key.substr(1, key.size() - 2);
            }

            if (value == "[") {
                while (std::getline(iss, line)) {
                    trim(line);
                    if (line == "]") {
                        registros.push_back(Registro{data,dest});
                        data.clear();
                        dest.clear();
                        fin_registro = true;
                        break;
                    }
                    value = line;
                    // Remover comillas del valor si existe
                    if (value[0] == '"' && (value[value.size() - 2] == '"' || value[value.size() - 1] == '"')) {
                        if (value[value.size() - 2] == '"')
                            value = value.substr(1, value.size() - 3);
                        else
                            value = value.substr(1, value.size() - 2);
                    }
                    dest.push_back(value);
                }
            }
            if (!fin_registro)
                data[key] = value;
            else
                fin_registro = false;
        }
    }

    std::string getValue(const std::string& key) {
        return data[key];
    }

    void setValue(const std::string& key, const std::string& value) {
        data[key] = value;
    }


	// Leer archivo JSON y guardarlo en Graph
    bool read_JSON(Graph &G, std::string namefile)
    {
    	std::ifstream inputFile(namefile);
        if (!inputFile.is_open()) {
            std::cerr << "No se puede abrir el archivo " << namefile << std::endl;
            return false;
        }
        std::stringstream buffer;
        buffer << inputFile.rdbuf();
        std::string json = buffer.str();

        // Parsear el JSON
        parse(json);

        // Guardar los aeropuertos en cada vértice del grafo
        std::list<Registro>::iterator it;
        for (it = registros.begin(); it != registros.end(); ++it)
        {
        	if(isNumber(it->data["Longitude"]) && isNumber(it->data["Latitude"])) {
				Airport apto(it->data["Airport ID"], it->data["Country"], it->data["Name"],it->data["City"],
				             std::stod(it->data["Longitude"]),std::stod(it->data["Latitude"]));
	        	G.insertVertex(apto);
	        	if(lat_min > std::stod(it->data["Latitude"])){
                    lat_min = std::stod(it->data["Latitude"]);
	        	};
	        	if(lat_max < std::stod(it->data["Latitude"])){
                    lat_max = std::stod(it->data["Latitude"]);
	        	};
	        	if(lon_min > std::stod(it->data["Longitude"])){
                    lon_min = std::stod(it->data["Longitude"]);
	        	};
	        	if(lon_max < std::stod(it->data["Longitude"])){
                    lon_max = std::stod(it->data["Longitude"]);
	        	};

	        	if(G.existVertex(it->data["Airport ID"]))
	        	{
	        		std::cout<<"Se ha guardado correctamente el aeropuerto "<<it->data["Airport ID"]<<" : "<<it->data["City"]<<endl;;
				}
				else
				{
					std::cout<<"No se ha guardado el aeropuerto "<<it->data["Airport ID"]<<" : "<<it->data["City"]<<endl;
				}
			}
			else {
				std::cout<<"No se ha guardado el aeropuerto "<<it->data["Airport ID"]<<" : "<<it->data["City"]<<", Longitud y/o Latitud con errores"<<endl;

			}
        }

        // Guardar los destinos de cada aeropuerto
        std::list<Registro>::iterator it2;
        for (it2 = registros.begin(); it2 != registros.end(); ++it2)
        {
        	// solo se considera registrar el aeropuerto con datos de lat y long correctos
        	if(isNumber(it2->data["Longitude"]) && isNumber(it2->data["Latitude"])) {
	            for (int i = 0; i < it2->destinos.size(); i++)
	            {
	            	if(G.existVertex(it2->destinos[i]))
	            	{
	            		G.createEdge(G.findById(it2->data["Airport ID"]), G.findById(it2->destinos[i]));
					}
					else {
						std::cout<<"No existe destino aeropuerto de codigo "<<it2->destinos[i]<<endl;
					}
	            }
	    	}
        }

    	return true;
	}

	// Validar si un texto es un número válido
	bool isNumber(const std::string& s)
	{
    	char* end = nullptr;
    	double val = strtod(s.c_str(), &end);
	    return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
	}

private:
	// Limpiar espacios extremos de la cadena
    void trim(std::string& str) {
        const std::string whitespace = " \t";
        size_t start = str.find_first_not_of(whitespace);
        size_t end = str.find_last_not_of(whitespace);
        if (start != std::string::npos && end != std::string::npos) {
            str = str.substr(start, end - start + 1);
        } else {
            str.clear();
        }
    }
};

