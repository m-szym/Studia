package pl.edu.pg.eti.ksg.po.lab1;

import java.lang.Math;
public class Obrot
        implements Transformacja
{
    private final double kat_rad;

    public Obrot(double kat_rad)
    {
        this.kat_rad = kat_rad;
    }
    @Override
    public Punkt transformuj(Punkt p)
    {
        return new Punkt(
                p.getX() * Math.cos(kat_rad) - p.getY() * Math.sin(kat_rad),
                p.getX() * Math.sin(kat_rad) - p.getY() * Math.cos(kat_rad)
                        );
    }

    @Override
    public Transformacja getTransformacjaOdwrotna()
            throws BrakTransformacjiOdwrotnejException {
        return new Obrot(-kat_rad);
    }

    @Override
    public String toString() {
        return "Obrót o " + kat_rad + " radianów wokół punktu(0,0)";
    }
}
