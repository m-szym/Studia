# Virtual World
### Object-oriented programming project
## Author: Marek Szymański

## Project description
The project is a simple, turn-based simulation of a virtual world, where different types of organisms can interact with each other. The world is represented as a 2D grid (either square or hexagonal), where each cell is occupied by a single organism. The organisms can move, fight, reproduce and die, each with different abilities and behaviours. A singular `Human` organism can be controlled by the user and there are controls for adding new organisms to the world.
The project was created to learn and practice object-oriented programming principles and design patterns, including inheritance, polymorphism, encapsulation, and the observer pattern.
It is implemented in Python3 and uses Pygame and Pygame-GUI libraries for visualizing the simulation and the graphical interface.

### Project details
Detailed requirements and description of the project can be found in the [project_requirements.pdf](project_requirements.pdf) file.

Currently, the project implements the following features:
- a 2D grid world with square or hexagonal cells
- different types of organisms with different abilities and behaviours
    - Animals: `Antelope`, `Fox`, `Sheep`, `Turtle`, `Wolf`, `CyberSheep` (a very special type of `Sheep`)
    - Plants: `Nightsahde`, `Grass`, `Guarana`, `Hogweed`, `Dandelion`
- a `Human` organism that can be controlled by the user and has the special activated ability to kill all organisms around it
- a simple graphical interface with the option to add new organisms to the world
- the ability to save and load the state of the world from a binary file
- side panel showcasing logs from the last turn of the simulation

### How to run
To run the project, you need to have Python3 installed on your machine. You also need to have the Pygame and Pygame-GUI libraries installed. You can install them using the following commands:
```
pip install -r requirements.txt
```
To run the project, use the following command:
```
python3 main.py
```
The project will open a window with the simulation. 

### In the future
Although the project and underlaying simulation are quite simple and primitve, I have always been interested in the topic of simulating real-world phenomena and systems. I would like to further develop this project by adding more complex behaviours and interactions between organisms, as well as additional layers of complexity - for example: environmental factors, weather or time-based events, like day-night cycle.

Perhaps more importantly the project needs a new graphical interface, as the current one is very basic and quite ugly. I would like to create a more visually appealing and user-friendly interface, that would allow for more interaction with the simulation and provide more information to the user.

I would also like to refactor the code and improve the overall design of the project, as it was created as a learning exercise and there are many places where the code could be improved and made more efficient.
