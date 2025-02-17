//#include <iostream>
//#include <fstream>
//#include <list>
//
//#include "world_organism_map.h"
////#include "Organism.h"
////#include "World.h"
//
//
//#include "Animals/Human.h"
//#include "Animals/Animals_subclasses/Wolf.h"
//#include "Animals/Animals_subclasses/Sheep.h"
//#include "Animals/Animals_subclasses/Fox.h"
//#include "Animals/Animals_subclasses/Antelope.h"
//#include "Animals/Animals_subclasses/Turtle.h"
//
//#include "Plants/Plants_subclasses/Grass.h"
//#include "Plants/Plants_subclasses/Dandellion.h"
//#include "Plants/Plants_subclasses/Guarana.h"
//#include "Plants/Plants_subclasses/Nightshade.h"
//#include "Plants/Plants_subclasses/Pine_Borscht.h"

#include "Simulator.h"


//int save_world(World& w);
//World* load_world();

int main()
{
#ifndef __cplusplus
    Conio2_Init();
#endif

    srand(time(nullptr));

    //World w(10,10);

    //Organism* o2 = w.add_organism(new Antelope(5,5,w));
    //Organism* o = w.add_organism(new Wolf(5, 6, w));
    //w.add_organism(new Wolf(5, 4, w));
    //w.add_organism(new Wolf(6, 5, w));
    //////w.add_organism(new Sheep(5, 6, w));

    ////w.draw_world();
    ////w.make_turn();
    //w.draw_world();



    ////Organism* h = w.add_organism(new Human(5,5,w));
    ////w.set_human(h);    
    ////w.draw_world();
    //
    //char input = '0';
    //int i = 0;
    //while (input != 'q')
    //{
    //    i++;
    //    std::cout << "\nTura nr " << i << "\n";
    //    //w.take_input();
    //    w.make_turn();
    //    w.draw_world();

    //    std::cin >> input;
    //}
    

   //save_world(w);


    //World* w2 = load_world();
    //w2->draw_world();

    //std::cout << "\nw odczytanym\n";
    //if (w2 != nullptr) {
    //    std::cout << "w2\n";
    //    for (Organism* o : w2->get_organisms_list()) {
    //        std::cout << o->get_symbol() << " - " << o->get_x() << ", " << o->get_y() << std::endl;
    //    }
    //}
    //else {
    //    std::cout << "null";
    //}


    //std::cout << "dest\n";
    //delete w2;
    //std::cout << "dest2\n";

    Simulator* s = s->Instance();
    //s->add_organism_to_world(new Sheep(10, 10, s->getw()));
    s->simulate_world();
}



