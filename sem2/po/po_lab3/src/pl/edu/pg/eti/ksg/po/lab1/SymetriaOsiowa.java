package pl.edu.pg.eti.ksg.po.lab1;

public class SymetriaOsiowa implements  Transformacja{
    private final char axis;

    SymetriaOsiowa(char axis)
    {
        this.axis = axis;
    }

    @Override
    public Punkt transformuj(Punkt p) {
        if (axis == 'X' || axis == 'x')
            return new Punkt(p.getX(), -1 * p.getY());
        else if (axis == 'Y' || axis == 'y')
            return new Punkt(-1 * p.getX(), p.getY());
        else
            return null;
    }

    @Override
    public Transformacja getTransformacjaOdwrotna() throws BrakTransformacjiOdwrotnejException {
        if (axis == 'X' || axis == 'x' || axis == 'Y' || axis == 'y')
            return new SymetriaOsiowa(this.axis);
        else
            throw new BrakTransformacjiOdwrotnejException("Nie podano poprawnej osi. - Poprawne osie to OX i OY.");
    }

    @Override
    public String toString() {
        return "Symetria osiowa względem osi " + this.axis;
    }
}
