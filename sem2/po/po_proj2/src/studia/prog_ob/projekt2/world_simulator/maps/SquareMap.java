package studia.prog_ob.projekt2.world_simulator.maps;

import studia.prog_ob.projekt2.world_simulator.organisms.animals.Animal;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;

import java.util.Map;

public class SquareMap implements WorldMap {

    public static int DIRECTIONS_N = 4;

    public static final int DIR_NULL = 0;
    public static final int DIR_UP = 1;
    public static final int DIR_RIGHT = 2;
    public static final int DIR_DOWN = 3;
    public static final int DIR_LEFT = 4;


    private final int size_x;
    private final int size_y;
    private final Organism[][] internal_map;


    public SquareMap(int new_size_x, int new_size_y) {
        size_x = new_size_x;
        size_y = new_size_y;
        this.internal_map = new Organism[size_y][size_x];

        for (int i = 0; i < size_y; i++) {
            for (int j = 0; j < size_x; j++) {
                internal_map[i][j] = null;
            }
        }
    }


    @Override
    public boolean out_of_map(MapLocation location) {
        if ((location.y >= 0 && location.y < size_y) &&
            (location.x >= 0 && location.x < size_x))
            return false;

        return true;
    }

    @Override
    public boolean would_leave_map(Organism organism, int direction) {
        if (organism instanceof Animal animal) {
            MapLocation new_location = get_location_in_direction(animal.getMap_location(), direction, animal.getSpeed());
            return out_of_map(new_location);
        } else
            return false;
    }

    @Override public MapLocation
    get_location_in_direction(MapLocation origin, int direction, int step) {
        if (direction == DIR_NULL)
            return origin;

        MapLocation new_location = new MapLocation(origin.x, origin.y);
        if (direction == DIR_UP) {
            new_location.y -= step;
        } else if (direction == DIR_RIGHT) {
            new_location.x += step;
        } else if (direction == DIR_DOWN) {
            new_location.y += step;
        } else if (direction == DIR_LEFT) {
            new_location.x -= step;
        }

        return new_location;
    }

    @Override
    public Organism place_object(MapLocation location, Organism object) {
        if (!out_of_map(location)) {
            internal_map[location.y][location.x] = object;
            return object;
        }
        else
            return null;
    }

    @Override
    public Organism get_object(MapLocation location) {
        if (!out_of_map(location))
            return internal_map[location.y][location.x];
        else
            return null;
    }

    @Override
    public Organism lift_object(MapLocation location) {
        if (!out_of_map(location)) {
            Organism object = internal_map[location.y][location.x];
            internal_map[location.y][location.x] = null;
            return object;
        }
        else
            return null;
    }

    @Override
    public Organism move_object(MapLocation new_location, Organism object) {
        lift_object(object.getMap_location());
        place_object(new_location, object);
        return object;
    }

    @Override
    public Organism get_neighbour(Organism originator, int direction) {
        int step = 1;
        if (originator instanceof Animal animal_originator) {
            step = animal_originator.getSpeed();
        }

        MapLocation neighbour_location = get_location_in_direction(originator.getMap_location(), direction, step);

        return get_object(neighbour_location);
    }


    public int getSize_y() {
        return size_y;
    }

    public int getSize_x() {
        return size_x;
    }


    @Override
    public void draw_map() {
        for (int i = 0; i < this.size_y; i++) {
            for (int j = 0; j < this.size_x; j++) {
                if (internal_map[i][j] != null) {
                    System.out.print(internal_map[i][j].getSymbol());
                } else {
                    System.out.print(".");
                }
                System.out.print(" ");
            }
            System.out.print("\n");
        }
    }

    @Override
    public int[] get_size() {
        int[] arr = new int[3];
        arr[0] = 2;
        arr[1] = size_x;
        arr[2] = size_y;

        return arr;
    }
    //first value is number of dimensions
}
