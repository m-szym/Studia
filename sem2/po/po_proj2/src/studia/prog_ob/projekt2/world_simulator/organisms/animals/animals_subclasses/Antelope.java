package studia.prog_ob.projekt2.world_simulator.organisms.animals.animals_subclasses;


import studia.prog_ob.projekt2.world_simulator.RandomGenerator;
import studia.prog_ob.projekt2.world_simulator.SimLogger;
import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;
import studia.prog_ob.projekt2.world_simulator.organisms.animals.Animal;

public class Antelope extends Animal {

    public static final int ANTELOPE_STRENGTH = 4;
    public static final int ANTELOPE_INITIATIVE = 4;
    public static final int ANTELOPE_SPEED = 2;
    public static final char ANTELOPE_SYMBOL = 'A';
    public static final int ANTELOPE_ESCAPE_CHANCE_BASE = 10;
    public static final int ANTELOPE_ESCEPE_THRESHOLD = 5;

    public Antelope(MapLocation new_map_location, World new_world) {
        super(ANTELOPE_STRENGTH, ANTELOPE_INITIATIVE, new_map_location, ANTELOPE_SYMBOL, new_world, ANTELOPE_SPEED);
    }

    @Override
    public Organism spawn_offspring(MapLocation location) {
        return getWorld().add_organism(new Antelope(location, getWorld()));
    }

    @Override
    public void collision(Organism invader) {
        if (invader instanceof Animal invading_animal) {
            if (same_type(invader)) {
                SimLogger.log(this + SimLogger.MATING_MESSAGE + " " + invader);
                mate();
                return;
            }

            if (!reflect_attack(invading_animal)) {
                MapLocation cl = new MapLocation(getMap_location());

                if (escape()) {
                    invading_animal.update_location(cl);
                } else {
                    fight(invading_animal);
                }
            }
        }
    }

    boolean escape() {
        int escape = RandomGenerator.rand_int(ANTELOPE_ESCAPE_CHANCE_BASE);

        if (escape >= ANTELOPE_ESCEPE_THRESHOLD) {
            for (int i = 1; i < getMap().DIRECTIONS_N + 1; i++) {
                MapLocation l = getMap().get_location_in_direction(getMap_location(), i, getSpeed());
                if (!getMap().out_of_map(l) && getMap().get_object(l) == null) {
                    SimLogger.log(this + SimLogger.FLEE_MESSAGE + " to " + l);
                    update_location(l);
                    return true;
                }
            }
        }
        return false;
    }

    @Override
    public String toString() {
        return "Antelope " + getMap_location() + " ";
    }
}
