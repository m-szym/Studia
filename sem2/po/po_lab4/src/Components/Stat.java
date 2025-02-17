package Components;

public class Stat {
    private final String name;
    protected int value;

    public Stat(String name) {
        this.name = name;
        this.value = 0;
    }

    public Stat(String name, int value) {
        this.name = name;
        this.value = value;
    }

    public String getName() {
        return name;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public void increaseValue(int value) {
        this.value += value;
    }

    public void decreaseValue(int value) {
        this.value -= value;
    }


}
