package pl.edu.pg.eti.ksg.po.lab1;
import java.awt.*;

public class Main {
    public static void main(String[] args)
    {
        /*
         * Konstrukcja językowa try {} catch (...){} służy do
         * obsługi wyjątków. Kod w bloku try jest monitorowany
         * pod kątem wystąpienia wyjątku bądź wyjątków
         * wspomnianych na początku bloku/bloków catch.
         * Jeżeli gdzieś w bloku try wystąpi wyjątek, to sterowanie
         * zostanie natychmiast przeniesione do bloku catch.
         * Tam powinien znajdować się kod obsługujący wyjątek.
         * Może to być np. wypisanie stosu wywołań na wyjście błędów
         * lub zapisanie wyjątku w logach, lub wyrzucenie (zgłoszenie)
         * innego wyjątku lepiej opisującego sytuacje (można załączyć
         * wyjątek który zainicjował to zdarzenie patrz. Konstruktor
         * klasy java.lang.Exception)
         */

        /*
        try {
            Punkt p1 = Punkt.E_X;
            System.out.println(p1);
            Transformacja tr = new Translacja(5, 6);
            System.out.println(tr);
            Punkt p2 = tr.transformuj(p1);
            System.out.println(p2);
            Transformacja trr = tr.getTransformacjaOdwrotna();
            System.out.println(trr);
            Punkt p3 = trr.transformuj(p2);
            System.out.println(p3);
        } catch (BrakTransformacjiOdwrotnejException ex)
        {
            ex.printStackTrace();
        }
        System.out.println();
        try
        {
            Punkt p1 = new Punkt(2, 2);
            System.out.println(p1);
            Transformacja tr2 = new Skalowanie(5, 4);
            System.out.println(tr2);
            Punkt p2 = tr2.transformuj(p1);
            System.out.println(p2);
            Transformacja trr2 = tr2.getTransformacjaOdwrotna();
            System.out.println(trr2);
            Punkt p3 = trr2.transformuj(p2);
            System.out.println(p3);
        }
        catch(BrakTransformacjiOdwrotnejException ex)
        {
            ex.printStackTrace();
        }
        System.out.println();
        try
        {
            Punkt p5 = new Punkt(3, 3);
            Transformacja obr = new Obrot(1);
            System.out.println(obr);
            System.out.println(p5);
            Punkt p6 = obr.transformuj(p5);
            System.out.println(p6);
            Transformacja obr2 = obr.getTransformacjaOdwrotna();
            System.out.println(obr2);
            Punkt p7 = obr2.transformuj(p6);
            System.out.println(p7);
        }
        catch(BrakTransformacjiOdwrotnejException ex)
        {
            ex.printStackTrace();
        }
        System.out.println();
        try
        {
            Punkt p1 = new Punkt(2, 2);
            Transformacja tr2 = new Skalowanie(5, 0);
            System.out.println(tr2);
            System.out.println(p1);
            Punkt p2 = tr2.transformuj(p1);
            System.out.println(p2);
            Transformacja trr2 = tr2.getTransformacjaOdwrotna();
            System.out.println(trr2);
            Punkt p3 = trr2.transformuj(p2);
            System.out.println(p3);
        }
        catch(BrakTransformacjiOdwrotnejException ex)
        {
            ex.printStackTrace();
        }

         */




        System.out.println("\n\nZłożenie transformacji");
        try
        {
            Punkt p10 = new Punkt(2, 2);
            ZlozenieTransformacji z = new ZlozenieTransformacji(2);
            System.out.println(p10);
            Punkt p20 = z.transformuj(p10);
            System.out.println("Po transformacji");
            System.out.println(p20);
            Transformacja zo = z.getTransformacjaOdwrotna();
            System.out.println("Po transformacji odwrotnej");
            Punkt p30 = zo.transformuj(p20);
            System.out.println(p30);
        }
        catch(BrakTransformacjiOdwrotnejException ex)
        {
            ex.printStackTrace();
        }


        System.out.println("\n\nSymetria osiowa");
        try
        {
            Punkt p1 = new Punkt(2, 2);
            SymetriaOsiowa so = new SymetriaOsiowa('y');
            System.out.println(p1);
            Punkt p2 = so.transformuj(p1);
            System.out.println("Po transformacji");
            System.out.println(p2);
            Transformacja zo = so.getTransformacjaOdwrotna();
            System.out.println("Po transformacji odwrotnej");
            Punkt p3 = zo.transformuj(p2);
            System.out.println(p3);
        }
        catch(BrakTransformacjiOdwrotnejException ex)
        {
            ex.printStackTrace();
        }
        System.out.println("\n\nSymetria punktowa");
        try
        {
            Punkt p5 = new Punkt(2, 2);
            SymetriaPunktowa sp = new SymetriaPunktowa(2,-2);
            System.out.println(p5);
            Punkt p6 = sp.transformuj(p5);
            System.out.println("Po transformacji");
            System.out.println(p6);
            Transformacja zo = sp.getTransformacjaOdwrotna();
            System.out.println("Po transformacji odwrotnej");
            Punkt p7 = zo.transformuj(p6);
            System.out.println(p7);
        }
        catch(BrakTransformacjiOdwrotnejException ex)
        {
            ex.printStackTrace();
        }
        System.out.println("End\n");
    }
}
