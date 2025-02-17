package studia.prog_ob.projekt2.world_simulator;

import javax.swing.*;
import java.util.LinkedHashSet;


public class SimLogger {
    public static final String SPAWN_MESSAGE = "appears on map";
    public static final String DEATH_MESSAGE = "dies";
    public static final String MOVEMENT_MESSAGE = "moves to";
    public static final String ATTACK_MESSAGE = "attacks ";
    public static final String ATTACK_SUCCES_MESSAGE = "attacked succesfully";
    public static final String ATTACK_FAILURE_MESSAGE = "defended itself";
    public static final String MATING_MESSAGE = "mates with";
    public static final String FLEE_MESSAGE = "flees from danger";
    public static final String DANGERSENSE_MESSAGE = "senses danger";
    public static final String LAZY_MESSAGE = "stays in place";
    public static final String ATTACK_REFLECT_MESSAGE = "reflects attack";
    public static final String PLANT_IDLE_MESSAGE = "grows";
    public static final String SEEDING_MESSAGE = "seeds new ";
    public static final String BALEFIRE_MESSAGE = "uses balefire";
    public static final String TURTLE_SLUMBER_MESSAGE = "slumbers";
    public static final String GUARANA_MESSAGE = "gains Strength from eating ";
    public static final String NIGHTSHADE_POISONING = "is poisoned by ";
    public static final String PINEBORSHT_POISONING = "is poisoned by ";

    private String logFile;

    public static String logs;

    private LinkedHashSet<String> old;

    public static JTextArea textArea;

    public SimLogger() {
        textArea = null;
        logFile = "";
        logs = "";
        old = new LinkedHashSet<String>();
    }

    public void setTextArea(JTextArea textArea) {
        SimLogger.textArea = textArea;
    }

    public void dump() {
        for (String s: old) {
            System.out.print(s);
        }
    }

    public void logNewTurn(int turnNumber) {
        log("\n\n");
        old.add(logs);
        logs = "";
        log("\tTurn #" + turnNumber);
    }

    public static void log(String message) {
        logs += message + "\n";
        System.out.println(message);
    }

    public static void print() {
        textArea.setText(logs);
    }
}
