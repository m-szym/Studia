package studia.prog_ob.projekt2.world_simulator.organisms.plants.plants_subclasses;

import studia.prog_ob.projekt2.world_simulator.SimLogger;
import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;
import studia.prog_ob.projekt2.world_simulator.organisms.plants.Plant;

public class Guarana extends Plant {
    public static final int GUARANA_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD;
    public static final int GUARANA_STRENGTH = BASE_PLANT_STRENGTH;
    public static final int GUARANA_INITIATIVE = BASE_PLANT_INITIATIVE;
    public static final char GUARANA_SYMBOL = 'r';
    public static final int GUARANA_STRENGTH_BONUS = 3;


    public Guarana(MapLocation new_map_location, World new_world) {
        super(GUARANA_STRENGTH, GUARANA_INITIATIVE, new_map_location, GUARANA_SYMBOL, new_world, GUARANA_SEEDING_THRESHOLD);
    }

    @Override
    public Organism spawn_offspring(MapLocation location) {
        return new Guarana(location, getWorld());
    }

    @Override
    public void collision(Organism invader) {
        invader.setStrength(invader.getStrength() + GUARANA_STRENGTH_BONUS);
        SimLogger.log(invader + SimLogger.GUARANA_MESSAGE + this);
        super.collision(invader);
    }

    @Override
    public String toString() {
        return "Guarana " + getMap_location() + " ";
    }
}
