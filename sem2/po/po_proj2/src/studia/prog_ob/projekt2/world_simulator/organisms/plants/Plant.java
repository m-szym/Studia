package studia.prog_ob.projekt2.world_simulator.organisms.plants;

import studia.prog_ob.projekt2.world_simulator.RandomGenerator;
import studia.prog_ob.projekt2.world_simulator.SimLogger;
import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;

public abstract class Plant extends Organism {
    public static final int SEEDING_CHANCE_BASE = 100;
    public static final int BASE_PLANT_SEEDING_THRESHOLD = 97;
    public static final int BASE_PLANT_STRENGTH = 0;
    public static final int BASE_PLANT_INITIATIVE = 0;


    private final int seeding_threshold;
    public Plant(int new_strength, int new_initiative, MapLocation new_map_location, char new_symbol, World new_world, int new_seeding_threshold) {
        super(new_strength, new_initiative, new_map_location, new_symbol, new_world);
        this.seeding_threshold = new_seeding_threshold;
    }


    @Override
    public void action() {
        seed();
    }

    @Override
    public void collision(Organism invader) {
        invader.update_location(getMap_location());
        kill_self();
    }

    protected Plant seed() {
        int r = RandomGenerator.rand_int(SEEDING_CHANCE_BASE);

        if (r >= seeding_threshold) {
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (i == 0 && j == 0)
                        continue;

                    MapLocation l = new MapLocation(getMap_location());
                    l.x += j;
                    l.y += i;
                    if(!getWorld().getMap().out_of_map(l) && getWorld().getMap().get_object(l) == null) {
                        SimLogger.log(this + SimLogger.SEEDING_MESSAGE);
                        return (Plant) getWorld().add_organism(spawn_offspring(l));
                    }
                }
            }
        } else {
            //SimLogger.log(this + SimLogger.PLANT_IDLE_MESSAGE);
        }

        return null;
    }

    @Override
    public String toString() {
        return "Plant " + getMap_location() + " ";
    }
}
