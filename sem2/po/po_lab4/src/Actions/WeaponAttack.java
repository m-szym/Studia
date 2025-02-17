package Actions;

import 

public class WeaponAttack {
    private final int toHitChance;
    private final String toHitStat;
    private final int toHitModifier;

    public WeaponAttack(int toHitChance, String toHitStat, int toHitModifier) {
        this.toHitChance = toHitChance;
        this.toHitStat = toHitStat;
        this.toHitModifier = toHitModifier;
    }
}
