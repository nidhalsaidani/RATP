#include "Read_data.h"

std::string lower_str(const std::string& str)
{
    std::string result(str);
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
    return result;
}

void Read_data::read_stations(const string& _filename)
{
    string nom_fichier = _filename;
    ifstream file;
    file.open(nom_fichier);

    if (!file)
    {
        cerr << "Erreur : le fichier " << nom_fichier << " ne peut pas être ouvert." << endl;
    }
    else
    {
        string name_station = "string_name_station";
        string id = "uint32_s_id";
        string short_line = "string_short_line";
        string adress_station = "string_adress_station";
        string desc_line = "string_desc_line";

        size_t cpt(0);
        string line;

        while (getline(file, line))
        {
            if (cpt == 0) // Ignore la première ligne contenant les noms de colonnes.
            {
                ++cpt;
                continue;
            }

            istringstream ss(line);

            getline(ss, name_station, ',');
            getline(ss, id, ',');
            getline(ss, short_line, ',');
            getline(ss, adress_station, ',');
            getline(ss, desc_line);

            if (ss.fail() || ss.bad())
            {
                cerr << "Erreur : la ligne " << cpt << " ne peut pas être lue correctement." << endl;
            }
            else
            {
                Station new_station;

                new_station.name = name_station;
                new_station.line_id = id;
                new_station.address = adress_station;
                new_station.line_name = short_line;

                if (name_station.empty() || id.empty() || adress_station.empty() || short_line.empty() || desc_line.empty())
                {
                    cerr << "Erreur : la ligne " << cpt << " contient des champs vides." << endl;
                }
                else
                {
                    try
                    {
                        int int_id = stoi(id);
                        if (this->stations_hashmap.count(int_id) > 0)
                        {
                            cerr << "Erreur : la ligne " << cpt << " contient une clé en double (" << int_id << ")." << endl;
                        }
                        else
                        {
                            this->stations_hashmap[int_id] = new_station;
                        }
                    }
                    catch (const invalid_argument&)
                    {
                        cerr << "Erreur : la ligne " << cpt << " contient une clé invalide (" << id << ")." << endl;
                    }
                }
            }
            ++cpt;
        }

        if (file.bad())
        {
            cerr << "Erreur : une erreur est survenue lors de la lecture du fichier." << endl;
        }
        else if (cpt == 1)
        {
            cerr << "Erreur : le fichier est vide." << endl;
        }
        else
        {
            cout << "Les stations ont été chargées avec succès." << endl;
        }

        file.close();
    }
}

void Read_data::overrided_read_stations(const std::string& _filename) {
    this->read_stations(_filename);
}

// ------------------------------------------------------------

void Read_data::display_stations(const std::string& _filename)
{
    ifstream file(_filename);

    if (!file.is_open()) {
        cerr << "Error: failed to open file: " << _filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 5) {
            travel::Station s{ tokens[0], tokens[1], tokens[3], tokens[0] };
            for (auto const& s : tokens) {
                cout << s << " ";
            }
            cout << endl;
        }
        else {
            cerr << "Warning: invalid number of tokens in line, skipping line: " << line << endl;
        }
    }

    file.close();
    cout << "End-of-file reached." << endl;
}

void Read_data::overrided_display_stations(const std::string& _filename) {
    this->display_stations(_filename);
}

void Read_data::display_stations_(const travel::Generic_station_parser& data)
{
    const auto& stations = data.get_stations_hashmap();

    for (const auto& station : stations) {
        std::cout << "Name: " << station.second.name << ", Line ID: " << station.second.line_id << std::endl;
    }
}


void Read_data::display_stations_list(const travel::Generic_station_parser& data)
{
    const auto& stations = data.get_stations_hashmap();
    std::unordered_set<std::string> unique_stations;

    std::cout << "Liste des stations :" << std::endl;

    for (const auto& station : stations) {
        if (unique_stations.count(station.second.name) > 0) {
            continue;
        }
        unique_stations.insert(station.second.name);

        std::cout << "- " << station.second.name << std::endl;
    }
}




// ------------------------------------------------------------

void Read_data::read_connections(const string& filename)
{
    ifstream file(filename);

    if (!file)
    {
        cerr << "Erreur : impossible d'ouvrir le fichier" << endl;
        return;
    }

    string line;
    getline(file, line); // sauter la ligne d'en-tête

    while (getline(file, line))
    {
        stringstream ss(line);
        string from, to, time;
        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, time, '\n');

        try
        {
            uint32_t from_stop_id = stoul(from);
            uint32_t to_stop_id = stoul(to);
            uint32_t min_transfer_time = stoul(time);

            connections_hashmap[from_stop_id][to_stop_id] = min_transfer_time;
        }
        catch (invalid_argument&)
        {
            // sauter cette ligne si une des conversions stoul() échoue
            cerr << "Attention : une ligne dans le fichier des connexions ne contient pas des données valides, elle sera ignorée" << endl;
            continue;
        }
    }
}




void Read_data::overrided_read_connections(const string& _filename)
{
    this->read_connections(_filename);

}

void Read_data::display_connections(const std::string& _filename)
{
    ifstream file(_filename);

    if (!file.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier : " << _filename << endl;
        exit(1);
    }

    string line;
    getline(file, line); // sauter la ligne d'en-tête
    cout << line << endl; // afficher la ligne d'en-tête dans la console

    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 3) {
            uint64_t from_stop_id = stoi(tokens[0]);
            uint64_t to_stop_id = stoi(tokens[1]);
            uint64_t min_transfer_time = stoi(tokens[2]);

            cout << from_stop_id << "," << to_stop_id << "," << min_transfer_time << endl;
        }
        else {
            cerr << "Attention : le nombre de champs dans une ligne du fichier des connexions est invalide, cette ligne sera ignorée : " << line << endl;
        }
    }

    file.close();
    cout << "Fin du fichier atteinte." << endl;
}


void Read_data::overrided_display_connections(const std::string& _filename) {
    this->display_connections(_filename);
}


void Read_data::display_connections_(const travel::Generic_connection_parser& data)
{
    const auto& connections = data.get_connections_hashmap();

    for (const auto& from_station : connections) {
        std::cout << "From Station ID: " << from_station.first << std::endl;

        const auto& to_stations = from_station.second;
        for (const auto& to_station : to_stations) {
            std::cout << "    To Station ID: " << to_station.first << ", Min Transfer Time: " << to_station.second << std::endl;
        }
    }
}


// --------------------------------------------------------------


vector<pair<uint64_t, uint64_t>> Read_data::compute_travel(uint64_t _start, uint64_t _end) {
    unordered_map<uint64_t, Station> graph(stations_hashmap); // (node_Id,distance)
    unordered_map<uint64_t, uint64_t> pred;
    unordered_map<uint64_t, uint64_t> distance;

    priority_queue<pair<uint64_t, uint64_t>, vector<pair<uint64_t, uint64_t>>, greater<pair<uint64_t, uint64_t>>> pq;

    // Initialization of graph (node_Id, node_distance)
    for (auto station_iterator = stations_hashmap.begin(); station_iterator != stations_hashmap.end(); station_iterator++) {
        distance[station_iterator->first] = numeric_limits<uint64_t>::max();
    }
    distance[_start] = 0;
    pq.push(make_pair(0, _start));

    while (!pq.empty()) {
        uint64_t Id_node_min_distance = pq.top().second;
        pq.pop();

        if (Id_node_min_distance == _end) {
            break;
        }

        if (distance[Id_node_min_distance] == numeric_limits<uint64_t>::max()) {
            break;
        }

        // Update the distances of neighbors
        for (auto iterator = connections_hashmap[Id_node_min_distance].begin(); iterator != connections_hashmap[Id_node_min_distance].end(); iterator++) {
            uint64_t neighbor_node = iterator->first;
            uint64_t neighbor_dist = iterator->second;

            if (distance[Id_node_min_distance] + neighbor_dist < distance[neighbor_node]) {
                distance[neighbor_node] = distance[Id_node_min_distance] + neighbor_dist;
                pred[neighbor_node] = Id_node_min_distance;
                pq.push(make_pair(distance[neighbor_node], neighbor_node));
            }
        }
    }

    // Record the best path in a vector
    uint64_t node = _end;
    vector<pair<uint64_t, uint64_t>> path;
    while (node != _start) {
        path.push_back(make_pair(node, connections_hashmap[pred[node]][node]));
        node = pred[node];
    }
    reverse(path.begin(), path.end()); // Reverse the order of the path to get it from start to end
    return path;
}




void Read_data::compute_and_display_travel(uint64_t _start, uint64_t _end) {
    vector_t Path = compute_travel(_start, _end);

    uint64_t total_time = 0;
    cout << "Follow these instructions to reach your destination:" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "- Start at " << stations_hashmap[_start] << "." << endl;
    for (int i = 0; i < Path.size(); i++) {
        Station current_station = stations_hashmap[Path[i].first];
        uint64_t current_time = Path[i].second;
        total_time += current_time;

        cout << "- At " << current_station << " -  Metro: " << current_station.line_name << ", ";
        if (i == 0) {
            cout << "board the train." << endl;
        }
        else if (i == Path.size() - 1) {
            cout << "alight from the train." << endl;
        }
        else {
            cout << "continue on the train for " << current_time / 60 << " minutes and " << current_time % 60 << " seconds." << endl;
        }
    }

    cout << "-------------------------------------------------" << endl;
    cout << "Total travel time: " << total_time / 60 << " minutes and " << total_time % 60 << " seconds. / (" << total_time << " seconds.)" << std::endl;
}


std::pair<uint64_t, uint64_t> Read_data::name_to_id(const std::string& _start, const std::string& _end) {
    uint64_t start = 0;
    uint64_t end = 0;

    bool found_start = false;
    bool found_end = false;

    // On transforme d'abord les strings en minuscule puis on les compare aux stations tarnsformées aussi pour être insensible à la casse
    string lower_start = lower_str(_start);
    string lower_end = lower_str(_end);

    // Boucle qui parcourt la map, 
    for (auto i : this->stations_hashmap) {
        if (lower_str(i.second.name) == lower_start) {
            start = i.first;
            found_start = true;
        }
        // On met un if au lieu d'un else if ici pour autoriser la recherche du chemin dont la station d'arrivé est la station de départ.
        if (lower_str(i.second.name) == lower_end) {
            end = i.first;
            found_end = true;
        }

        // Si on a trouvé les deux stations, on quitte la boucle pour ne pas faire des calcus inutiles
        if (found_start && found_end)
            break;
    }

    // Si le nom de station donné n'existe pas on crée une exception
    if (!found_start)
        throw _start;

    if (!found_end)
        throw _end;

    return make_pair(start, end);
}



