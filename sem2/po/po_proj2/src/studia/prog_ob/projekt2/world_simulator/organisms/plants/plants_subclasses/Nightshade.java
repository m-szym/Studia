package studia.prog_ob.projekt2.world_simulator.organisms.plants.plants_subclasses;

import studia.prog_ob.projekt2.world_simulator.SimLogger;
import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;
import studia.prog_ob.projekt2.world_simulator.organisms.plants.Plant;

public class Nightshade extends Plant {
    public static final int NIGHTSHADE_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD;
    public static final int NIGHTSHADE_STRENGTH = 99;
    public static final int NIGHTSHADE_INITIATIVE = BASE_PLANT_INITIATIVE;
    public static final char NIGHTSHADE_SYMBOL = 'n';


    public Nightshade(MapLocation new_map_location, World new_world) {
        super(NIGHTSHADE_STRENGTH, NIGHTSHADE_INITIATIVE, new_map_location, NIGHTSHADE_SYMBOL, new_world, NIGHTSHADE_SEEDING_THRESHOLD);
    }

    @Override
    public Organism spawn_offspring(MapLocation location) {
        return new Nightshade(location, getWorld());
    }

    @Override
    public void collision(Organism invader) {
        SimLogger.log(invader + SimLogger.NIGHTSHADE_POISONING + this);
        invader.kill_self();
    }

    @Override
    public String toString() {
        return "Nightshade " + getMap_location() + " ";
    }
}
