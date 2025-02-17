
public class A
{
    private int liczba;
    public A(int liczba)
    {
        this.liczba = liczba;
    }

    public void setLiczba(int liczba)
    {
        this.liczba = liczba;
    }
    public int getLiczba()
    {
        return this.liczba;
    }

    @Override
    public String toString()
    {
        return "Instancja klasy A zaiwerająca liczbę " + liczba;
    }

    @Override
    public boolean equals(Object obj) {
        if(obj instanceof A)
        {
            A other = (A)obj;
            return liczba == other.liczba;
        }
        return false;
    }

}
