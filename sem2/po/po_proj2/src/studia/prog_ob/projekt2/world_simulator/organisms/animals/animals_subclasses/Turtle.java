package studia.prog_ob.projekt2.world_simulator.organisms.animals.animals_subclasses;


import studia.prog_ob.projekt2.world_simulator.RandomGenerator;
import studia.prog_ob.projekt2.world_simulator.SimLogger;
import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;
import studia.prog_ob.projekt2.world_simulator.organisms.animals.Animal;

import java.util.Random;

public class Turtle extends Animal {

    public static final int TURTLE_STRENGTH = 2;
    public static final int TURTLE_INITIATIVE = 1;
    public static final int TURTLE_SPEED = BASE_ANIMAL_SPEED;
    public static final char TURTLE_SYMBOL = 'T';
    public static final int TURTLE_MOVEMENT_CHANCE_BASE = 4;
    public static final int TURTLE_MOVEMENT_THRESHOLD = 3;
    public static final int TURTLE_DEFENSE = 5;

    public Turtle(MapLocation new_map_location, World new_world) {
        super(TURTLE_STRENGTH, TURTLE_INITIATIVE, new_map_location, TURTLE_SYMBOL, new_world, TURTLE_SPEED);
    }

    @Override
    public Organism spawn_offspring(MapLocation location) {
        return getWorld().add_organism(new Turtle(location, getWorld()));
    }

    @Override
    protected boolean reflect_attack(Animal attacker) {
        if (attacker.getStrength() < TURTLE_DEFENSE) {
            SimLogger.log(this + SimLogger.ATTACK_REFLECT_MESSAGE);
            return true;
        } else {
            return false;
        }
    }

    @Override
    public void action()  {
        int move_chance = RandomGenerator.rand_int(TURTLE_MOVEMENT_CHANCE_BASE);
        if (move_chance >= TURTLE_MOVEMENT_THRESHOLD) {
            move();
        } else {
            SimLogger.log(this + SimLogger.TURTLE_SLUMBER_MESSAGE);
        }
    }

    @Override
    public String toString() {
        return "Turtle " + getMap_location() + " ";
    }

}
