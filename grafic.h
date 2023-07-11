#ifndef GRAFIC_H_INCLUDED
#define GRAFIC_H_INCLUDED

#include "UndirectedGraphAirport.h"

class grafic{
    int width_w;
    int heigth_w;
    double lat_min;
    double lat_max;
    double lon_min;
    double lon_max;
    double mid_x;
    double mid_y;
    double width_g;
    double heigth_g;
    double factor_x;
    double factor_y;
    Graph grafo;

public:
    grafic(int _width_w,int _heigth_w,Graph _grafo){
        width_w = _width_w;
        heigth_w = _heigth_w;
        lat_min =  _grafo.lat_min;
        lat_max = _grafo.lat_max;
        lon_min = _grafo.lon_min;
        lon_max = _grafo.lon_max;
        grafo = _grafo;
        mid_x = width_w/2;
        mid_y = heigth_w/2;
        width_g = lon_max - lon_min;
        heigth_g = lat_max - lat_min;
        factor_x = width_w/width_g;
        factor_y = heigth_w/heigth_g;
    }

    /**
	  Graficar las aeropuertos
	**/
    void graficAirports(){
        double longitud;
        double latitud;
        /*
        double mid_x = width_w/2;
        double mid_y = heigth_w/2;
        double width_g = lon_max - lon_min;
        double heigth_g = lat_max - lat_min;
        double factor_x = width_w/width_g;
        double factor_y = heigth_w/heigth_g;
        */

        //definir el color de la grafica
        setcolor(YELLOW);
        // Recorrer el hash table de vértices
        for (const auto& vertex : grafo.getVertexes()) {

            //longitud = mid_x + vertex.second->data.Longitude*factor_x;
            //latitud = mid_y - vertex.second->data.Latitude*factor_y;
            longitud = 50 + (vertex.second->data.Longitude - lon_min)*factor_x*0.75;
            latitud = 50 + (vertex.second->data.Latitude - lat_min)*factor_y*0.75;
            if (latitud > mid_y){
                latitud = latitud - 2*(latitud-mid_y);
            }else {
                latitud = latitud + 2*(mid_y-latitud);
            };
            char arr[vertex.second->data.City.length() + 1];
            strcpy(arr,vertex.second->data.City.c_str());
            circle(longitud, latitud,2);
            /*settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
            settextjustify(LEFT_TEXT, CENTER_TEXT);
            outtextxy(longitud + 3, latitud, arr);
            */
            mensajeGrafico(longitud + 3,latitud,arr);
        };

        // Wait for the user to press a key.
        //getch();

        // Close the graphics window.
        //closegraph();
    }

    /**

    **/
    void mensajeGrafico(int x, int y, char *mensaje,int color = YELLOW, int bk_color = BLACK, int fontStyle = SANS_SERIF_FONT, int sizeFont = 1){
        setbkcolor(bk_color);
        setcolor(color);
        settextstyle(fontStyle, HORIZ_DIR, sizeFont);
        settextjustify(LEFT_TEXT, CENTER_TEXT);
        outtextxy(x, y, mensaje);
    }

    /**

    **/
    void mensajeHeader(char *mensaje,int x, int y,int colorText = BLUE, int bgText = WHITE,int sizeFont = 1){
        mensajeGrafico(x, y, mensaje, colorText, bgText,BOLD_FONT,sizeFont);
    }

    /**
	  Graficar las aristas
	**/

	void graficEdges(){
        double longitud_ini;
        double latitud_ini;
        double longitud_fin;
        double latitud_fin;
        /*
        double mid_x = width_w/2;
        double mid_y = heigth_w/2;
        double width_g = lon_max - lon_min;
        double heigth_g = lat_max - lat_min;
        double factor_x = width_w/width_g;
        double factor_y = heigth_w/heigth_g;
        */

        setcolor(WHITE);
        for (const auto& vertex : grafo.getVertexes()) {
            //coordenadas partida
            //longitud_ini = mid_x + vertex.second->data.Longitude*factor_x;
            //latitud_ini = mid_y - vertex.second->data.Latitude*factor_y;

            longitud_ini = 50 + (vertex.second->data.Longitude - lon_min)*factor_x*0.75;
            latitud_ini = 50 + (vertex.second->data.Latitude - lat_min)*factor_y*0.75;
            if (latitud_ini > mid_y){
                latitud_ini = latitud_ini - 2*(latitud_ini-mid_y);
            }else {
                latitud_ini = latitud_ini + 2*(mid_y-latitud_ini);
            };

            for (auto& edge : vertex.second->edges) {
            //coordenadas llegada
            //longitud_fin = mid_x + edge->vertexes[1]->data.Longitude*factor_x;
            //latitud_fin = mid_y - edge->vertexes[1]->data.Latitude*factor_y;
            longitud_fin = 50 + (edge->vertexes[1]->data.Longitude - lon_min)*factor_x*0.75;
            latitud_fin = 50 + (edge->vertexes[1]->data.Latitude - lat_min)*factor_y*0.75;
            if (latitud_fin > mid_y){
                latitud_fin = latitud_fin - 2*(latitud_fin-mid_y);
            }else {
                latitud_fin = latitud_fin + 2*(mid_y-latitud_fin);
            };

            line(longitud_ini, latitud_ini, longitud_fin, latitud_fin);
            }
        };

        // Wait for the user to press a key.
        //getch();

        // Close the graphics window.
        //closegraph();
    }

    /**
      obetener solo la grafica de los nombres de las ciudades
    **/

    void get_graficAirports(){

        graficAirports();

        // Wait for the user to press a key.
        getch();

        // Close the graphics window.
        closegraph();
    }

    /**
      obetener solo la grafica de los vertices
    **/

    void get_graficEdges(){

        graficEdges();

        // Wait for the user to press a key.
        getch();

        // Close the graphics window.
        closegraph();
    }

    /**
      obetener la grafica completa de los aeropuertos y las rutas
    **/

    void get_graficGraph(){
        //borde
        setlinestyle(DASHED_LINE,0 , 3);
        rectangle(10,10,width_w - 10,heigth_w - 10);

        setlinestyle(SOLID_LINE,0 , 1);
        //graficar cabecera
        //mensajeHeader(msj);

        //graficar aeropuertos
        graficAirports();

        //graficar rutas
        graficEdges();

        // Wait for the user to press a key.
        //getch();

        // Close the gr3aphics window.
        //closegraph();
    }
};

#endif // GRAFIC_H_INCLUDED
