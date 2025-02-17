package studia.prog_ob.projekt2.world_simulator.organisms.animals.animals_subclasses;


import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;
import studia.prog_ob.projekt2.world_simulator.organisms.animals.Animal;

public class Sheep extends Animal {

    public static final int SHEEP_STRENGTH = 4;
    public static final int SHEEP_INITIATIVE = 4;
    public static final int SHEEP_SPEED = BASE_ANIMAL_SPEED;
    public static final char SHEEP_SYMBOL = 'S';

    public Sheep(MapLocation new_map_location, World new_world) {
        super(SHEEP_STRENGTH, SHEEP_INITIATIVE, new_map_location, SHEEP_SYMBOL, new_world, SHEEP_SPEED);
    }

    @Override
    public Organism spawn_offspring(MapLocation location) {
        return getWorld().add_organism(new Sheep(location, getWorld()));
    }

    @Override
    public String toString() {
        return "Sheep " + getMap_location() + " ";
    }
}
