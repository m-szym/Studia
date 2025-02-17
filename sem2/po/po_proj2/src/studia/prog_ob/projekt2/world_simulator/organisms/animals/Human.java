package studia.prog_ob.projekt2.world_simulator.organisms.animals;

import studia.prog_ob.projekt2.world_simulator.SimLogger;
import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.organisms.DirectControl;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;

public class Human extends Animal implements DirectControl {
    private static final int HUMAN_STRENGTH = 5;
    private static final int HUMAN_INITIATIVE = 4;
    private static final int HUMAN_SPEED = BASE_ANIMAL_SPEED;
    private static final char HUMAN_SYMBOL = 'H';
    private static final int HUMAN_SKILL_COOLDOWN = 5;
    private static final int HUMAN_SKILL_DURATION = 5;

    private int direction;
    private int skill_cooldown;
    private int skill_duration_left;
    private boolean skill_active;

    public Human(MapLocation new_map_location, World new_world) {
        super(HUMAN_STRENGTH, HUMAN_INITIATIVE, new_map_location, HUMAN_SYMBOL, new_world, HUMAN_SPEED);

        direction = getMap().DIR_NULL;
        skill_active = false;
        skill_cooldown = HUMAN_SKILL_COOLDOWN;
        skill_duration_left = 0;
    }

    @Override
    protected int decide_where_to_move() {
        return direction;
    }

    private void skill() {
        if (!skill_active && skill_cooldown > 0) {
            skill_cooldown--;
        }

        if (skill_active && skill_duration_left > 1) {
            skill_duration_left--;
        } else if (skill_active && skill_duration_left == 1) {
            skill_duration_left = 0;
            skill_active = false;
            skill_cooldown = HUMAN_SKILL_COOLDOWN;
        }

        if (skill_active) {
            balefire();
            SimLogger.log(this + SimLogger.BALEFIRE_MESSAGE);
        }
    }

    private int balefire() {
        int kills = 0;
        Organism target = null;

        for (int i = 1; i < getMap().DIRECTIONS_N + 1; i++) {
            target = getMap().get_neighbour(this, i);
            if (target != null) {
                //SimLogger.log("kill at " + i);
                target.kill_self();
                kills++;
            }
        }
        return kills;
    }

    private void activate_skill() {
        skill_active = true;
        skill_duration_left = HUMAN_SKILL_DURATION;
    }

    @Override
    public void action() {
        skill();

        super.action();

        direction = getMap().DIR_NULL;
    }

    @Override
    public Organism spawn_offspring(MapLocation location) {
        return null;
    }

    @Override
    public boolean give_command(int command) {
        if (command >= 100 && command < 200) {
            direction = command - 100;
            return true;
        } else if (command == USE_SKILL){
            if (skill_cooldown == 0 && !skill_active)
                activate_skill();
            return true;
        }

        return false;
    }

    @Override
    public String toString() {
        return "Human " + getMap_location() + " ";
    }

    public int getSkill_duration_left() {
        return skill_duration_left;
    }

    public Human setSkill_duration_left(int skill_duration_left) {
        this.skill_duration_left = skill_duration_left;
        return this;
    }

    public int getSkill_cooldown() {
        return skill_cooldown;
    }

    public Human setSkill_cooldown(int skill_cooldown) {
        this.skill_cooldown = skill_cooldown;
        return this;
    }

    public int getDirection() {
        return direction;
    }

    public Human setDirection(int direction) {
        this.direction = direction;
        return this;
    }

    public boolean isSkill_active() {
        return skill_active;
    }

    public Human setSkill_active(boolean skill_active) {
        this.skill_active = skill_active;
        return this;
    }
}
