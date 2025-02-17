package studia.prog_ob.projekt2.world_simulator.organisms;

public interface DirectControl {
    int GO_DIR0 = 100;
    int GO_DIR1 = 101;
    int GO_DIR2= 102;
    int GO_DIR3= 103;
    int GO_DIR4 = 104;

    int USE_SKILL = 200;

    boolean give_command(int command);
}
