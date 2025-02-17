package studia.prog_ob.projekt2.world_simulator.organisms.plants.plants_subclasses;

import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;
import studia.prog_ob.projekt2.world_simulator.organisms.plants.Plant;

public class Grass extends Plant {
    public static final int GRASS_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD;
    public static final int GRASS_STRENGTH = BASE_PLANT_STRENGTH;
    public static final int GRASS_INITIATIVE = BASE_PLANT_INITIATIVE;
    public static final char GRASS_SYMBOL = 'g';


    public Grass(MapLocation new_map_location, World new_world) {
        super(GRASS_STRENGTH, GRASS_INITIATIVE, new_map_location, GRASS_SYMBOL, new_world, GRASS_SEEDING_THRESHOLD);
    }

    @Override
    public Organism spawn_offspring(MapLocation location) {
        return new Grass(location, getWorld());
    }

    @Override
    public String toString() {
        return "Grass " + getMap_location() + " ";
    }
}
