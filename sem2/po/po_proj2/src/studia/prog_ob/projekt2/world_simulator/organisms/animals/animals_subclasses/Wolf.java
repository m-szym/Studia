package studia.prog_ob.projekt2.world_simulator.organisms.animals.animals_subclasses;


import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;
import studia.prog_ob.projekt2.world_simulator.organisms.animals.Animal;

public class Wolf extends Animal {

    public static final int WOLF_STRENGTH = 9;
    public static final int WOLF_INITIATIVE = 5;
    public static final int WOLF_SPEED = BASE_ANIMAL_SPEED;
    public static final char WOLF_SYMBOL = 'W';

    public Wolf(MapLocation new_map_location, World new_world) {
        super(WOLF_STRENGTH, WOLF_INITIATIVE, new_map_location, WOLF_SYMBOL, new_world, WOLF_SPEED);
    }

    @Override
    public Organism spawn_offspring(MapLocation location) {
        return getWorld().add_organism(new Wolf(location, getWorld()));
    }

    @Override
    public String toString() {
        return "Wolf " + getMap_location() + " ";
    }
}
