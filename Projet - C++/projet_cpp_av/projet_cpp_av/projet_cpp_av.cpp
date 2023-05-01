#include <iostream>
#include "Read_data.h"
#include "../../data_project/Generic_station_parser.hpp"
#include "../../data_project/Generic_mapper.hpp"
#include "../../data_project/Generic_connection_parser.hpp"
//#include "../../data_project/Grade.hpp"
#define STATIONS_PATH "../../data_project/data/s.csv"
#define CONNECTIONS_PATH "../../data_project/data/c.csv"
typedef std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t> > map_t;

using namespace travel;
using namespace std;



int main() {
    Read_data data;
    data.overrided_read_stations(STATIONS_PATH);
    data.overrided_read_connections(CONNECTIONS_PATH);
    data.display_stations_list(data);

    string start_name, end_name;
    cout << "Entrez le nom de la station de départ : ";
    getline(cin, start_name);
    cout << "Entrez le nom de la station d'arrivée : ";
    getline(cin, end_name);

    try {
        auto ids = data.name_to_id(start_name, end_name);
        data.compute_and_display_travel(ids.first, ids.second);
    }
    catch (const string& s) {
        cout << "La station " << s << " n'existe pas." << endl;
    }

    return 0;
}


// Pour la méthode classique de calcul d'itinéraire, nous introduisons les stations avec leurs identifiants dans la fonction main.

//int main()
//{
//
//
//
//    uint64_t start_station_id = 2035; // ChÃ¢teau de Vincennes
//    uint64_t end_station_id = 1944; // Fort d'Aubervilliers
//
//    Read_data data;
//    vector_t path;
//
//    data.overrided_read_stations(STATIONS_PATH);
//    // data.display_stations_(data);
//
//    data.overrided_read_connections(CONNECTIONS_PATH);
//    // data.display_connections_(data);
//
//    data.compute_travel(start_station_id, end_station_id);
//    data.compute_and_display_travel(start_station_id, end_station_id);
//    
//    return 0;
//}