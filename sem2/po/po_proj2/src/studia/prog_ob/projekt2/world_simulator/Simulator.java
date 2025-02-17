package studia.prog_ob.projekt2.world_simulator;

import studia.prog_ob.projekt2.world_simulator.gui.GUI;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;

import javax.swing.*;

import java.util.Collections;

public class Simulator {
    public static Simulator self;
    public World world;
    //private int turn_number;
    private final SimLogger simLogger;
    GUI gui;



    protected Simulator()
    {
        gui = new GUI(this);
        simLogger = new SimLogger();
    }



    public static Simulator Simulate()
    {
        if (self == null) {
            self = new Simulator();
        }
        return self;
    }

    public Simulator setSimLoggerTextArea(JTextArea textArea) {
        simLogger.setTextArea(textArea);
        return this;
    }


    private void update_initiative() {
        Collections.sort(world.getOrganisms());
    }

    private void clear_bodies() {
        world.getOrganisms().removeIf(o -> o.getMarker() == Organism.DEAD_MARKER);
    }

    private void add_waiting() {
        while (!world.getSpawn_queue().isEmpty()) {
            Organism o = world.getSpawn_queue().pop();
            if (o != null && o.getMap_location() != null) {
                world.getOrganisms().add(o);
                world.getMap().place_object(o.getMap_location(), o);
            }
        }

    }

    public void make_turn() {
        world.turn++;
        simLogger.logNewTurn(world.turn);

        clear_bodies();
        add_waiting();
        update_initiative();
        take_actions();

        //world.getMap().draw_map();

        gui.boardPanel.updateBoard();
        SimLogger.print();
    }

    private void take_actions() {
        for (Organism org: world.getOrganisms()) {
            if (org.getMarker() != Organism.DEAD_MARKER) {
                org.action();
            }
        }
    }
}
