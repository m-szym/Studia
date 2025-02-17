package studia.prog_ob.projekt2.world_simulator.organisms.plants.plants_subclasses;

import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;
import studia.prog_ob.projekt2.world_simulator.organisms.plants.Plant;

public class Dandellion extends Plant {
    public static final int DANDELLION_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD;
    public static final int DANDELLION_STRENGTH = BASE_PLANT_STRENGTH;
    public static final int DANDELLION_INITIATIVE = BASE_PLANT_INITIATIVE;
    public static final char DANDELLION_SYMBOL = 'd';
    public static final int DANDELLION_SEEDING_ATTEMPTS_PER_TURN = 3;


    public Dandellion(MapLocation new_map_location, World new_world) {
        super(DANDELLION_STRENGTH, DANDELLION_INITIATIVE, new_map_location, DANDELLION_SYMBOL, new_world, DANDELLION_SEEDING_THRESHOLD);
    }

    @Override
    public Organism spawn_offspring(MapLocation location) {
        return new Dandellion(location, getWorld());
    }

    @Override
    public void action() {
        for (int i = 0; i < DANDELLION_SEEDING_ATTEMPTS_PER_TURN; i++) {
            super.seed();
        }
    }

    @Override
    public String toString() {
        return "Dandellion " + getMap_location() + " ";
    }
}
