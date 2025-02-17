package studia.prog_ob.projekt2.world_simulator.organisms;

import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;

public interface LivingBeing {

    void action();

    void collision(Organism invader);

    Organism spawn_offspring(MapLocation location);

}
