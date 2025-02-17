package pl.edu.pg.eti.ksg.po.lab1;

public class ZlozenieTransformacji
    implements Transformacja
{
    private Transformacja[] tab;

    ZlozenieTransformacji(int n)
    {
        tab = new Transformacja[n];
        int i = 0;
        double d1, d2;
        String input;
        java.util.Scanner scan = new java.util.Scanner(System.in);
        System.out.println("Podaj kody kolejnych transformacji");
        System.out.println("\tSkalowanie - 1\n\tTranslacja - 2\n\tObrot - 3\n\tSymeria osiowa - 4\n\tSymetria punktowa - 5");
        while (i < n)
        {
            System.out.println("Podaj kolejną transformację: ");
            //input = scan.nextLine();
            int j = scan.nextInt();
            //switch (input.charAt(0))
            //int j;
            //Integer jj;
            switch (j)
            {
                //case('s'):
                case(1):
                    System.out.println("Podaj skalę X: ");
                    d1 = scan.nextDouble();
                    System.out.println("Podaj skalę Y: ");
                    d2 = scan.nextDouble();
                    tab[i] = new Skalowanie(d1, d2);
                    i++;
                    break;
                //case('t'):
                case(2):
                    System.out.println("Podaj dX: ");
                    d1 = scan.nextDouble();
                    System.out.println("Podaj dY: ");
                    d2 = scan.nextDouble();
                    tab[i] = new Translacja(d1, d2);
                    i++;
                    break;
                //case('o'):
                case(3):
                    System.out.println("Podaj kąt (w radianach): ");
                    d1 = scan.nextDouble();
                    tab[i] = new Obrot(d1);
                    i++;
                    break;
                case(4):
                    System.out.println("Podaj oś (X-1 / Y-2): ");
                    d1 = scan.nextDouble();
                    if (d1 == 1) {
                        tab[i] = new SymetriaOsiowa('X');
                        i++;
                    }
                    else if (d1 == 2) {
                        tab[i] = new SymetriaOsiowa('Y');
                        i++;
                    } else System.out.println("Błąd");
                    break;
                case(5):
                    System.out.println("Podaj współrzędną X środka symetrii: ");
                    d1 = scan.nextDouble();
                    System.out.println("Podaj współrzędną Y środka symetrii: ");
                    d2 = scan.nextDouble();
                    tab[i] = new SymetriaPunktowa(d1, d2);
                    i++;
                    break;
                default:
                    System.out.println("Nieprawdiłowa komenda.");
            }
        }
    }

    ZlozenieTransformacji(Transformacja[] tabl)
    {
        this.tab = new Transformacja[tabl.length];
        for (int i = 0; i < tabl.length; i++) {
            tab[i] = tabl[i];
        }
    }

    @Override
    public Punkt transformuj(Punkt p) {
        Punkt pi = p;
        for (Transformacja tr : this.tab) {
            pi = tr.transformuj(pi);
        }
        return pi;
    }

    /*@Override
    public pl.edu.pg.eti.ksg.po.lab1.Transformacja getTransformacjaOdwrotna()
            throws pl.edu.pg.eti.ksg.po.lab1.BrakTransformacjiOdwrotnejException {
        pl.edu.pg.eti.ksg.po.lab1.Transformacja[] tmp = new pl.edu.pg.eti.ksg.po.lab1.Transformacja[tab.length];
        for (int i = 0 ; i < tab.length ; i++) {
            tmp[i] = tab[tab.length - i - 1];
        }
        return new pl.edu.pg.eti.ksg.po.lab1.ZlozenieTransformacji(tab);
    }*/

    @Override
    public Transformacja getTransformacjaOdwrotna()
            throws BrakTransformacjiOdwrotnejException {
        Transformacja[] tmp = new Transformacja[tab.length];
        double d1, d2;
        for (int i = 0 ; i < tab.length ; i++) {
            try
            {
                tmp[i] = tab[tab.length - i - 1].getTransformacjaOdwrotna();
            }
            catch(BrakTransformacjiOdwrotnejException ex)
            {
                ex.printStackTrace();
            }
        }
        return new ZlozenieTransformacji(tmp);
    }

    @Override
    public String toString() {
        String s = "Złożenie " + tab.length +  " transformacji:\n";
        for (Transformacja tr : this.tab) {
            s += "\t" + tr.toString() + "\n";
        }
        s += "Koniec złożenia";

        return s;
    }
}
