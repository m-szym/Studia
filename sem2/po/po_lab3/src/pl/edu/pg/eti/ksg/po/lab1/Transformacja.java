package pl.edu.pg.eti.ksg.po.lab1;

public interface Transformacja
{
    Punkt transformuj(Punkt p);

    Transformacja getTransformacjaOdwrotna()
            throws BrakTransformacjiOdwrotnejException;
}
