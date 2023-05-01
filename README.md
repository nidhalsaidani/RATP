# RATP Shortest Path Program

This C++ program calculates the shortest path between two stations in a transportation network, considering travel time and metro lines. It uses Dijkstra's algorithm and reads station and connection data from CSV files.

## Usage

### Installation

To install the program, download the repository and open the project in Microsoft Visual Studio Community 2022 (64 bits) - Current Version 17.5.3 or later.

### Running the program

To run the program, simply compile and execute the main function. The program will prompt the user to enter the names of the starting and ending stations, and then display the shortest path between those stations, along with the estimated travel time and the metro lines the user should take.

### Dependencies

This program uses the following libraries and dependencies:

- `Generic_station_parser.hpp`
- `Generic_mapper.hpp`
- `Generic_connection_parser.hpp`

## Development

### Pre-Requisites

To develop this program, you will need the following:

- Microsoft Visual Studio Community 2022 (64 bits) - Current Version 17.5.3 or later.

### Development Environment

This program was developed in Microsoft Visual Studio Community 2022 (64 bits) - Current Version 17.5.3 on Windows 10.

### File Structure

The program is organized into the following files:

- `Read_data.h`: header file for the main program logic
- `Read_data.cpp`: source code file for the main program logic
- `Generic_station_parser.hpp`: header file for the station parser
- `Generic_mapper.hpp`: header file for the station mapper
- `Generic_connection_parser.hpp`: header file for the connection parser

### Build

To build the program, open the project in Microsoft Visual Studio Community 2022 (64 bits) - Current Version 17.5.3 or later and compile the code.

### Deployment

To deploy the program, simply distribute the compiled executable file along with the station and connection CSV files.

## Community

### Contribution

Contributions to the project are welcome. To contribute, fork the repository, make your changes, and submit a pull request.

### Branches

The `main` branch contains the most up-to-date and stable version of the code. Development work is done in separate feature branches, which are merged into the `main` branch once they have been tested and reviewed.

### Guidelines

When contributing to this project, please adhere to the following guidelines:

- Follow the coding style used in the existing code.
- Write clear and concise commit messages.
- Test your changes thoroughly before submitting a pull request.

## FAQ

- Q: How does the program handle stations or connections that are not in the data files?
- A: If the user enters the name of a station that is not in the data files, the program will display an error message indicating that the station does not exist.

## Resources

- [Dijkstra's algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
- [Microsoft Visual Studio Community 2022](https://visualstudio.microsoft.com/vs/)

## Gallery

![Shortest Path Program Screenshot](https://i.imgur.com/4g5k3xB.png)

## Credit/Acknowledgment

This program was developed as part of a project for a computer science course at Sorbonne University. Special thanks to Anis Sahbani and Janan Arslan for providing guidance and feedback throughout the development process.

## License

This project is licensed under the MIT License.
