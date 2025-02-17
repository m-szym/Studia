package Components;

public class Resource extends Stat {
    private int maxValue;

    public Resource(String name) {
        super(name);
    }

    public Resource(String name, int value) {
        super(name, value);
        this.maxValue = value;
    }

    public Resource(String name, int value, int maxValue) {
        super(name, value);
        this.maxValue = maxValue;
    }

    public int getMaxValue() {
        return maxValue;
    }

    public void setMaxValue(int maxValue) {
        this.maxValue = maxValue;
        this.shrinkValue();
    }

    public void increaseMaxValue(int value) {
        this.maxValue += value;
    }

    public void decreaseMaxValue(int value) {
        this.maxValue -= value;
        this.shrinkValue();
    }

    private void shrinkValue()
    {
        if (this.value > maxValue) {
                this.value = maxValue;
            }
    }

    public void resetValue()
    {
        this.value = maxValue;
    }

}
