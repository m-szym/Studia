# GraphNavigator
### Algorithms and Data Structures project
## Author: Marek Szymański


## Project description
The project is a simple program that finds the shortest path between two cities on a map. The map is represented as a directed graph, where each vertice represents a city and each edge represents a road or a flight connection between two cities. The edges are weighted with the time of travel between the two cities. The program uses Dijkstra's algorithm to find the shortest path between two given cities.


### Map format
This is an example of a map in format used by the program:
```
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
```
> Legend:
> - `.` - empty space
> - `#` - road
> - `*` - city
> - `GDANSK` - name of the closest city (`*` symbol)


### Goals
Main goals of the project were:
- implementing Dijkstra's algorithm to find the shortest path between two vertices in a graph
- personally implementing all the neccessary data structures (list, map, queue etc.) - no STL and no `string`


### How does it work?
The program first reads the map (see Map format for details) from standard input, parses it using BFS and creates a graph. 
Then it reads additional information about flight connections between cities, which are not marked on the map, which are then also added to the graph.

> MapData object is used to store the map (as 2D array of chars) and additional information
> Building the Graph object from it and the input (flights) is done in the dataReadingAndManip functions


On the graph each vertice represents a city and directed edges represent either roads between cities or flight connections, the edges are weighted with the time of travel.

> Graph class is used to store the graph and perform Dijkstra's algorithm on it, the algorithm is implemented in the dijkstra function
> Graph is implemented using an adjacency list of Node objects, each one holding a list of it's weighted edges (Link objects) to other nodes
> Adjacency list was preferred over adjacency matrix because the map is a multi-graph and the number of nodes is unknown during it's construction
> Dijkstra's algorithm is implemented using a priority queue as a method of the Graph

Afterwards the program reads queries from standard input, each query consisting of two city names and, using Dijkstra's algorithm, finds the shortest path between the two given cities.


---


#### Implementation details
- the implementation of Dijsktra's algorithm is based on the priority queue, which is implemented as a binary heap (in MinHeapQueue class)
- the program uses a custom implementation of a map (HashTable and CStringHastTable class) and 2 directional list (LinkedList class) to store the graph and access the graph
- as the use of `string` was prohibited, the program uses c-style arrays of chars instead


As the program was checked by an automated testing system, the input and output format was strictly defined and had to be followed.
