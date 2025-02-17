package studia.prog_ob.projekt2.world_simulator.organisms.animals.animals_subclasses;


import studia.prog_ob.projekt2.world_simulator.SimLogger;
import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;
import studia.prog_ob.projekt2.world_simulator.organisms.animals.Animal;

public class Fox extends Animal {

    public static final int FOX_STRENGTH = 3;
    public static final int FOX_INITIATIVE = 7;
    public static final int FOX_SPEED = BASE_ANIMAL_SPEED;
    public static final char FOX_SYMBOL = 'F';

    public Fox(MapLocation new_map_location, World new_world) {
        super(FOX_STRENGTH, FOX_INITIATIVE, new_map_location, FOX_SYMBOL, new_world, FOX_SPEED);
    }

    @Override
    public Organism spawn_offspring(MapLocation location) {
        return getWorld().add_organism(new Fox(location, getWorld()));
    }

    @Override
    protected void pre_collision(Organism organismAtNewLocation) {
        if (organismAtNewLocation.getStrength() > this.getStrength()) {
            SimLogger.log(this + SimLogger.DANGERSENSE_MESSAGE);
            return;
        }

        super.pre_collision(organismAtNewLocation);
    }

    @Override
    public String toString() {
        return "Fox " + getMap_location() + " ";
    }
}
