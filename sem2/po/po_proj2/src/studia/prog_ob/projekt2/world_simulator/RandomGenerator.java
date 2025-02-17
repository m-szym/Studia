package studia.prog_ob.projekt2.world_simulator;
import java.util.Random;
public class RandomGenerator {
    private static final Random generator = new Random();
    public static int rand_int(int roof) {
        return generator.nextInt(roof);
    }
    public static int rand_int(int floor, int roof) {
        return generator.nextInt(roof) + floor;
    }
}
