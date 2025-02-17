package pl.edu.pg.eti.ksg.po.lab1;

public class SymetriaPunktowa implements Transformacja {
    private final Punkt punkt;
    public SymetriaPunktowa(Punkt punkt) {
        this.punkt = punkt;
    }

    public  SymetriaPunktowa(double x, double y)
    {
        this.punkt = new Punkt(x, y);
    }

    @Override
    public Punkt transformuj(Punkt p) {
        Translacja tr = new Translacja(punkt.getX() - p.getX(), punkt.getY() - p.getY());
        return tr.transformuj(punkt);
    }

    /*
    @Override
    public Punkt transformuj(Punkt p) {
        double dx = punkt.getX() - p.getX();
        double dy = punkt.getY() - p.getY();
        return new Punkt(punkt.getX() + dx, punkt.getY() + dy);
    }
    */

    @Override
    public Transformacja getTransformacjaOdwrotna() throws BrakTransformacjiOdwrotnejException {
        return new SymetriaPunktowa(punkt);
    }

    @Override
    public String toString() {
        return "Symetria względem punktu" + this.punkt.toString();
    }
}
