package studia.prog_ob.projekt2.world_simulator.organisms.plants.plants_subclasses;

import studia.prog_ob.projekt2.world_simulator.SimLogger;
import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;
import studia.prog_ob.projekt2.world_simulator.organisms.plants.Plant;

public class PineBorscht extends Plant {
    public static final int PINEBORSCHT_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD;
    public static final int PINEBORSCHT_STRENGTH = 0;
    public static final int PINEBORSCHT_INITIATIVE = BASE_PLANT_INITIATIVE;
    public static final char PINEBORSCHT_SYMBOL = 'b';


    public PineBorscht(MapLocation new_map_location, World new_world) {
        super(PINEBORSCHT_STRENGTH, PINEBORSCHT_INITIATIVE, new_map_location, PINEBORSCHT_SYMBOL, new_world, PINEBORSCHT_SEEDING_THRESHOLD);
    }

    @Override
    public Organism spawn_offspring(MapLocation location) {
        return new PineBorscht(location, getWorld());
    }

    @Override
    public void collision(Organism invader) {
        SimLogger.log(invader + SimLogger.PINEBORSHT_POISONING + this);
        invader.kill_self();
        super.collision(invader);
    }

    @Override
    public void action() {
        kill_neighbours();
        super.action();
    }

    private int kill_neighbours() {
        Organism target = null;
        int kills = 0;
        for (int i = 1; i < 5; i++) {
            target = getWorld().getMap().get_neighbour(this, i);
            if (target != null && !target.is_plant()) {
                SimLogger.log(target + SimLogger.PINEBORSHT_POISONING + this);
                target.kill_self();
                kills++;
            }
        }
        return kills;
    }

    @Override
    public String toString() {
        return "Pine Borsht " + getMap_location() + " ";
    }
}
