#pragma once

#include "../../data_project/Generic_station_parser.hpp"
#include "../../data_project/Generic_connection_parser.hpp"

#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <limits>
#include <iomanip>
#include <istream>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <cmath>
#include <queue>
#include <set>

#define SEPARATOR ','

using namespace std;
using namespace travel;

typedef vector<pair<uint64_t, uint64_t>> vector_t;

class Read_data : public Generic_connection_parser
{
public:
    void overrided_read_stations(const string& _filename);
    void overrided_display_stations(const std::string& _filename);
    void overrided_read_connections(const string& _filename);
    void overrided_display_connections(const std::string& _filename);
    void display_stations_(const travel::Generic_station_parser& data);
    void display_connections_(const travel::Generic_connection_parser& data);
    void display_stations_list(const travel::Generic_station_parser& data);
    vector_t compute_travel(uint64_t _start, uint64_t _end);
    void compute_and_display_travel(uint64_t _start, uint64_t _end);
    std::pair<uint64_t, uint64_t> name_to_id(const std::string& _start, const std::string& _end);
protected:
    void read_stations(const std::string& _filename) override;
    void read_connections(const string& _filename) override;
    void display_stations(const std::string& _filename);
    void display_connections(const std::string& _filename); 
};

