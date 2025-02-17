package studia.prog_ob.projekt2.world_simulator.maps;


import studia.prog_ob.projekt2.world_simulator.organisms.Organism;

import java.io.Serializable;

public interface WorldMap extends Serializable
{
    int DIRECTIONS_N=4;

    int DIR_NULL=0;

    boolean out_of_map(MapLocation location);

    boolean would_leave_map(Organism organism, int direction);

    MapLocation
    get_location_in_direction(MapLocation origin, int direction, int step);

    Organism place_object(MapLocation location, Organism object);
    Organism get_object(MapLocation location);
    Organism lift_object(MapLocation location);
    Organism move_object(MapLocation new_location, Organism object);

    Organism get_neighbour(Organism originator, int direction);

    void draw_map();

    int[] get_size();


}
