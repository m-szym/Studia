package Components;

import java.util.Map;

public class StatContainer {
    private Map<String, Stat> stats;

    public StatContainer() {}

    public StatContainer(Map<String, Stat> stats) {
        this.stats = stats;
    }

    public void addStat(String name, Stat stat) {
        stats.put(name, stat);
    }

    public void removeStat(String name) throws Exception{
        try {
            stats.remove(name);
        } catch (Exception e) {
            throw new Exception("No stat with name " + name + " exists.");
        }
    }

    public int getStatValue(String name) throws Exception {
        try {
            return stats.get(name).getValue();
        } catch (Exception e) {
            throw new Exception("No stat with name " + name + " exists.");
        }
    }

    public void setStatValue(String name, int value) throws Exception {
        try {
            stats.get(name).setValue(value);
        } catch (Exception e) {
            throw new Exception("No stat with name " + name + " exists.");
        }
    }

    public void increaseStatValue(String name, int value) throws Exception {
        try {
            stats.get(name).increaseValue(value);
        } catch (Exception e) {
            throw new Exception("No stat with name " + name + " exists.");
        }
    }

    public void decreaseStatValue(String name, int value) throws Exception {
        try {
            stats.get(name).decreaseValue(value);
        } catch (Exception e) {
            throw new Exception("No stat with name " + name + " exists.");
        }
    }

    public void resetStat(String name) throws Exception {
        try {
            Stat r = stats.get(name);
            try {
                Resource res = (Resource) r;
                res.resetValue();
            } catch (Exception e) {
                throw new Exception("Stat: " + name + " is not a resource.");
            }
        } catch (Exception e) {
            throw new Exception("No stat with name " + name + " exists.");
        }
    }
}
