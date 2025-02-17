package studia.prog_ob.projekt2.world_simulator;

import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.maps.SquareMap;
import studia.prog_ob.projekt2.world_simulator.maps.WorldMap;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;
import studia.prog_ob.projekt2.world_simulator.organisms.animals.Human;
import studia.prog_ob.projekt2.world_simulator.organisms.animals.animals_subclasses.*;
import studia.prog_ob.projekt2.world_simulator.organisms.plants.plants_subclasses.*;

import java.io.Serializable;
import java.util.LinkedList;


public class World implements Serializable
{
    public int turn;
    private Human human;
    private final LinkedList<Organism> organisms;

    private final LinkedList<Organism> spawn_queue;

    private final WorldMap map;




    public World(int new_size_x, int new_size_y)
    {
        turn = 0;
        human = null;
        map = new SquareMap(new_size_x, new_size_y);
        organisms = new LinkedList<>();
        spawn_queue = new LinkedList<>();

        populate();
    }

    private void populate() {
        int x = this.getMap().get_size()[1];
        int y = this.getMap().get_size()[2];
        int o_density = (int) ((x * y) * 0.1);

        if (o_density < 0) return;

        int xi = RandomGenerator.rand_int(Integer.MAX_VALUE) % x;
        int yi = RandomGenerator.rand_int(Integer.MAX_VALUE) % y;
        int type = -1;

        MapLocation spawnlocation = null;
        setHuman((Human) add_organism(new Human(new MapLocation(x / 2,y / 2), this)));
        for (int i = 0; i < o_density; i++)
        {
            xi = RandomGenerator.rand_int(Integer.MAX_VALUE) % x;
            yi = RandomGenerator.rand_int(Integer.MAX_VALUE) % y;
            type = RandomGenerator.rand_int(Integer.MAX_VALUE) % Organism.ORGANISM_TYPES;

            spawnlocation = new MapLocation(xi, yi);
            if (getMap().get_object(spawnlocation) == null)
            {
                spawn_organism(spawnlocation, type);
            }
            else
                --i;
        }


    }   //TODO

    /*public Organism add_organism(Organism new_organism)
    {
        organisms.addFirst(new_organism);
        map.place_object(new_organism.getMap_location(), new_organism);

        return new_organism;
    }*/

    public LinkedList<Organism> getSpawn_queue() {
        return spawn_queue;
    }

    public Organism add_organism(Organism new_organism) //new_organism is NOT on the map
    {
        spawn_queue.addFirst(new_organism);
        //map.place_object(new_organism.getMap_location(), new_organism);

        return new_organism;
        //return null;
    }

    public Organism spawn_organism(MapLocation spawnlocation, int type) //new_organism is NOT on the map
    {
        switch (type) {
            case (0) -> {
                return add_organism(new Sheep(spawnlocation, this));
            } case (1) -> {
                return add_organism(new Wolf(spawnlocation, this));
            } case (2) -> {
               return  add_organism(new Fox(spawnlocation, this));
            } case (3) -> {
                return add_organism(new Turtle(spawnlocation, this));
            } case (4) -> {
                return add_organism(new Antelope(spawnlocation, this));
            } case (5) -> {
                return add_organism(new Grass(spawnlocation, this));
            } case (6) -> {
                return add_organism(new Dandellion(spawnlocation, this));
            } case (7) -> {
                return add_organism(new Guarana(spawnlocation, this));
            } case (8) -> {
                return add_organism(new Nightshade(spawnlocation, this));
            } case (9) -> {
                return add_organism(new PineBorscht(spawnlocation, this));
            } default -> {
                return null;
            }
        }
    }



    public void remove_organism(MapLocation location)
    {
        map.lift_object(location);
        organisms.removeIf(o -> o.getMap_location().equals(location));
    }




    public WorldMap getMap() {
        return map;
    }

    public Human getHuman() {
        return human;
    }

    public World setHuman(Human human) {
        this.human = human;
        return this;
    }

    public LinkedList<Organism> getOrganisms() {
        return organisms;
    }
}
