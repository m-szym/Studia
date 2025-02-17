package studia.prog_ob.projekt2.world_simulator.maps;

import java.io.Serializable;

public class MapLocation implements Serializable {
    public int x;
    public int y;

    public MapLocation(int new_x, int new_y) {
        x = new_x;
        y = new_y;
    }

    public MapLocation(MapLocation old_location) {
        x = old_location.x;
        y = old_location.y;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof MapLocation other) {
            return other.x == this.x && other.y == this.y;
        }
        return super.equals(obj);
    }

    public int getY() {
        return y;
    }

    public MapLocation setY(int y) {
        this.y = y;
        return this;
    }

    public int getX() {
        return x;
    }

    public MapLocation setX(int x) {
        this.x = x;
        return this;
    }

    @Override
    public String toString() {
        return "(" + x + ", " + y + ")";
    }
}
