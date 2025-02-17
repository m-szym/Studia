# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Prog_Ob")



add_executable(Prog_Ob_P1
        ProgOb_P1.cpp
        world_organism_map.cpp world_organism_map.h 

        constants.h
        config.h
        misc.h misc.cpp
        List2d.h
        drawing.h drawing.cpp

        Animals/Animal.h Animals/Animal.cpp
        Animals/Animals_subclasses/Wolf.cpp Animals/Animals_subclasses/Wolf.h
        Animals/Animals_subclasses/Sheep.cpp Animals/Animals_subclasses/Sheep.h
        Animals/Animals_subclasses/Fox.cpp Animals/Animals_subclasses/Fox.h 
        Animals/Human.cpp Animals/Human.h

        Plants/Plant.cpp Plants/Plant.h
        Plants/Plants_subclasses/Grass.cpp Plants/Plants_subclasses/Grass.h 
        Plants/Plants_subclasses/Dandellion.cpp Plants/Plants_subclasses/Dandellion.h 
        Plants/Plants_subclasses/Guarana.cpp Plants/Plants_subclasses/Guarana.h 
        Plants/Plants_subclasses/Nightshade.cpp Plants/Plants_subclasses/Nightshade.h 
        Plants/Plants_subclasses/Pine_Borscht.cpp Plants/Plants_subclasses/Pine_Borscht.h 
        

         Animals/Animals_subclasses/Antelope.h Animals/Animals_subclasses/Antelope.cpp
Animals/Animals_subclasses/Turtle.h Animals/Animals_subclasses/Turtle.cpp 
Simulator.h Simulator.cpp
)
