package studia.prog_ob.projekt2.world_simulator.organisms;

import studia.prog_ob.projekt2.world_simulator.SimLogger;
import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.maps.WorldMap;

import java.io.Serializable;

public abstract class Organism implements LivingBeing, Comparable<Organism>, Serializable
{
    public static final int NULL_MARKER = 100;
    public static final int DEAD_MARKER = 400;

    public static final char HUMAN_SYMBOL = 'H';
    public static final char SHEEP_SYMBOL = 'S';
    public static final char WOLF_SYMBOL = 'W';
    public static final char FOX_SYMBOL = 'F';
    public static final char TURTLE_SYMBOL = 'T';
    public static final char ANTELOPE_SYMBOL = 'A';
    public static final char GRASS_SYMBOL = 'g';
    public static final char DANDELLION_SYMBOL = 'd';
    public static final char GUARANA_SYMBOL = 'r';
    public static final char NIGHTSHADE_SYMBOL = 'n';
    public static final char PINEBORSHT_SYMBOL = 'b';

    public static final int ORGANISM_TYPES = 10;


    private int strength;
    private int initiative;
    private MapLocation map_location;
    private char symbol;

    private int marker;
    private final int age;
    private static int organisms_counter;
    private World world;




    public Organism(int new_strength, int new_initiative, MapLocation new_map_location, char new_symbol, World new_world)
    {
        strength = new_strength;
        initiative = new_initiative;
        map_location = new_map_location;
        world = new_world;
        symbol = new_symbol;
        organisms_counter++;
        age = organisms_counter;
        marker = NULL_MARKER;
    }


    @Override
    public void collision(Organism invader) {
        fight(invader);
    }

    protected void fight(Organism attacker) {
        if (strength >= attacker.getStrength()) {
            SimLogger.log(this + SimLogger.ATTACK_FAILURE_MESSAGE + " from " + attacker);
            attacker.kill_self();
        } else {
            SimLogger.log(attacker + SimLogger.ATTACK_SUCCES_MESSAGE + " " + this);
            attacker.update_location(map_location);
            kill_self();
        }
    }

    public Organism update_location(MapLocation new_location) {
        SimLogger.log(this + SimLogger.MOVEMENT_MESSAGE + " " + new_location);

        world.getMap().move_object(new_location, this);
        setMap_location(new_location);

        return this;
    }
    public void kill_self() {
        marker = DEAD_MARKER;

        SimLogger.log(this + SimLogger.DEATH_MESSAGE);

        if (world.getMap().get_object(map_location) == this)
            world.getMap().lift_object(map_location);
    }


    public boolean is_plant() {
        return initiative == 0;
    }

    @Override
    public int compareTo(Organism other) {
        if (initiative > other.getInitiative())
            return -1;
        else if (initiative == other.getInitiative()) {
            if (age < other.getAge())
                return 1;
            else
                return -1;
        }
        else
            return 1;
    }

    public boolean same_type(Organism other) {
        return other.getSymbol() == this.getSymbol();
    }

    @Override
    public String toString() {
        return "Organism " + getMap_location() + " ";
    }

    public WorldMap getMap() {
        return world.getMap();
    }

    public World getWorld() {
        return world;
    }

    public int getMarker() {
        return marker;
    }

    public Organism setWorld(World world) {
        this.world = world;
        return this;
    }

    public static int getOrganisms_counter() {
        return organisms_counter;
    }

    public int getAge() {
        return age;
    }

    public char getSymbol() {
        return symbol;
    }

    public Organism setSymbol(char symbol) {
        this.symbol = symbol;
        return this;
    }

    public MapLocation getMap_location() {
        return map_location;
    }

    public Organism setMap_location(MapLocation map_location) {
        this.map_location = map_location;
        return this;
    }

    public int getInitiative() {
        return initiative;
    }

    public Organism setInitiative(int initiative) {
        this.initiative = initiative;
        return this;
    }

    public int getStrength() {
        return strength;
    }

    public Organism setStrength(int strength) {
        this.strength = strength;
        return this;
    }

    public int getX() {
        return this.map_location.x;
    }

    public int getY() {
        return this.map_location.y;
    }

}
