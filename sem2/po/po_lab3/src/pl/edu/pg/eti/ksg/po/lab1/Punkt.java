package pl.edu.pg.eti.ksg.po.lab1;

public class Punkt {
    /*
     * Słowo kluczowe final oznacza, że po pierwszym przypisaniu
     * zawartość pól x oraz y nie może zostać zmieniona
     * w tym miejscu jest to odpowiednik słowa kluczowego const
     * z języka C++.
     */
    private final double x,y;
    public Punkt(double x, double y) {
        this.x = x;
        this.y = y;
    }
    public double getX() {
        return this.x;
    }
    public double getY() {
        return this.y;
    }
    @Override
    public boolean equals(Object obj) {
        if(obj instanceof Punkt)
        {
            Punkt other = (Punkt)obj;
            if (this.x == other.x && this.y == other.y) return true;
            else return false;
        }
        return false;
    }
    @Override
    public int hashCode() {
        /*
         * TODO */
        return 57 * Double.hashCode(x+y) + 9;
    }
    @Override
    public String toString() {
        return "Punkt(" + x + ", " + y + ")";
    }
    /**
     * Początek układu współrzędnych.
     * W tym miejscu słowo kluczowe final oznacza, że statyczne
     * pole klasy pl.edu.pg.eti.ksg.po.lab1.Punkt nie może zostać zmienione.
     * Dotyczy to jednak samej referencji, a nie obiektu, na który
     * wskazuje.
     */
    public static final Punkt O = new Punkt(0, 0);
    /**
     * pl.edu.pg.eti.ksg.po.lab1.Punkt (1,0) w układzie współrzędnych
     */
    public static final Punkt E_X = new Punkt(1, 0);
    /**
     * pl.edu.pg.eti.ksg.po.lab1.Punkt (0,1) w układzie współrzędnych
     */
    public static final Punkt E_Y = new Punkt(0, 1);
}
