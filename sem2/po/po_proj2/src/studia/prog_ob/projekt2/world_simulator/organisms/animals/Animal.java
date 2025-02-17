package studia.prog_ob.projekt2.world_simulator.organisms.animals;

import studia.prog_ob.projekt2.world_simulator.RandomGenerator;
import studia.prog_ob.projekt2.world_simulator.SimLogger;
import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;

public abstract class Animal extends Organism {

    public static final int BASE_ANIMAL_STRENGTH = 0;
    public static final int BASE_ANIMAL_INITIATIVE = 10;
    public static final int BASE_ANIMAL_SPEED = 1;


    private int speed;


    public Animal(int new_strength, int new_initiative, MapLocation new_map_location, char new_symbol, World new_world, int speed) {
        super(new_strength, new_initiative, new_map_location, new_symbol, new_world);
        this.speed = speed;
    }

    protected int decide_where_to_move() {
        return RandomGenerator.rand_int(getMap().DIRECTIONS_N + 1);
    }

    private MapLocation choose_new_location() {
        int direction = decide_where_to_move();

        if (direction == getMap().DIR_NULL) {
            return getMap_location();
        } else {
            MapLocation new_location = getMap().get_location_in_direction(getMap_location(), direction, getSpeed());
            if (getMap().out_of_map(new_location))
                return getMap_location();
            else
                return new_location;
        }
    }

    public void move() {
        MapLocation this_new_location = choose_new_location();
        if (this_new_location == getMap_location()) {
            SimLogger.log(this + SimLogger.LAZY_MESSAGE);
            return;
        }

        Organism organism_at_new_location = getMap().get_object(this_new_location);
        if (organism_at_new_location != null && organism_at_new_location != this) {
            pre_collision(organism_at_new_location);
        } else {
            update_location(this_new_location);
        }
    }

    protected Animal mate() {
        MapLocation off_l = null;

        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                off_l = new MapLocation(getX() + i, getY() + j);
                if (!getMap().out_of_map(off_l) && getMap().get_object(off_l) == null) {
                    return (Animal) getWorld().add_organism(spawn_offspring(off_l));
                }
            }
        }

        return null;
    }

    protected boolean reflect_attack(Animal attacker) {
        return false;
    }

    protected void pre_collision(Organism organismAtNewLocation) {
        organismAtNewLocation.collision(this);
    }

    @Override
    public void action() {
        move();
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
                super.collision(invader);
            }
        }
    }

    @Override
    public String toString() {
        return "Animal " + getMap_location() + " ";
    }

    public int getSpeed() {
        return speed;
    }

    public Animal setSpeed(int speed) {
        this.speed = speed;
        return this;
    }


}
