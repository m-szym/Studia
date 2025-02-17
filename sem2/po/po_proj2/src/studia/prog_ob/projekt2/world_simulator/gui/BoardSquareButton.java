package studia.prog_ob.projekt2.world_simulator.gui;

import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.gui.images.icons.Icons;
import studia.prog_ob.projekt2.world_simulator.maps.MapLocation;
import studia.prog_ob.projekt2.world_simulator.organisms.Organism;
import studia.prog_ob.projekt2.world_simulator.organisms.animals.animals_subclasses.*;
import studia.prog_ob.projekt2.world_simulator.organisms.plants.plants_subclasses.*;

import javax.swing.*;
import java.awt.event.ActionEvent;

public class BoardSquareButton extends JButton {
    public MapLocation mapLocation;
    public World thisWorld;


    public BoardSquareButton(int i, int j, World world) {
        this.mapLocation = new MapLocation(j,i);
        this.thisWorld = world;


        setAction(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (thisWorld.getMap().get_object(mapLocation) == null)
                    showPopUpMenu();

            }
        });
    }

    public void showPopUpMenu() {
        JPopupMenu menu = new JPopupMenu();

        JMenuItem addSheep = new JMenuItem("Add sheep");
        JMenuItem addWolf = new JMenuItem("Add wolf");
        JMenuItem addFox = new JMenuItem("Add fox");
        JMenuItem addTurtle = new JMenuItem("Add turtle");
        JMenuItem addAntelope = new JMenuItem("Add antelope");
        JMenuItem addGrass = new JMenuItem("Add grass");
        JMenuItem addDandellion = new JMenuItem("Add dandellion");
        JMenuItem addGuarana = new JMenuItem("Add guarana");
        JMenuItem addNightshade = new JMenuItem("Add nightshade");
        JMenuItem addPineborsht = new JMenuItem("Add pineborsht");

        addSheep.addActionListener(new addAction(Organism.SHEEP_SYMBOL));
        addWolf.addActionListener(new addAction(Organism.WOLF_SYMBOL));
        addFox.addActionListener(new addAction(Organism.FOX_SYMBOL));
        addTurtle.addActionListener(new addAction(Organism.TURTLE_SYMBOL));
        addAntelope.addActionListener(new addAction(Organism.ANTELOPE_SYMBOL));
        addGrass.addActionListener(new addAction(Organism.GRASS_SYMBOL));
        addDandellion.addActionListener(new addAction(Organism.DANDELLION_SYMBOL));
        addGuarana.addActionListener(new addAction(Organism.GUARANA_SYMBOL));
        addNightshade.addActionListener(new addAction(Organism.NIGHTSHADE_SYMBOL));
        addPineborsht.addActionListener(new addAction(Organism.PINEBORSHT_SYMBOL));

        menu.add(addSheep);
        menu.add(addWolf);
        menu.add(addFox);
        menu.add(addTurtle);
        menu.add(addAntelope);
        menu.add(addGrass);
        menu.add(addDandellion);
        menu.add(addGuarana);
        menu.add(addNightshade);
        menu.add(addPineborsht);

        menu.show(this, 0, 0);
    }

    private class addAction extends AbstractAction {
        private final char type;
        public addAction(char organismType) {
            super("Add " + organismType);
            type = organismType;
        }
        @Override
        public void actionPerformed(ActionEvent e) {
            if (type == Organism.SHEEP_SYMBOL) {
                thisWorld.add_organism(new Sheep(mapLocation, thisWorld));
            } else if (type == Organism.WOLF_SYMBOL) {
                thisWorld.add_organism(new Wolf(mapLocation, thisWorld));
            } else if (type == Organism.FOX_SYMBOL) {
                thisWorld.add_organism(new Fox(mapLocation, thisWorld));
            } else if (type == Organism.TURTLE_SYMBOL) {
                thisWorld.add_organism(new Turtle(mapLocation, thisWorld));
            } else if (type == Organism.ANTELOPE_SYMBOL) {
                thisWorld.add_organism(new Antelope(mapLocation, thisWorld));
            } else if (type == Organism.GRASS_SYMBOL) {
                thisWorld.add_organism(new Grass(mapLocation, thisWorld));
            } else if (type == Organism.DANDELLION_SYMBOL) {
                thisWorld.add_organism(new Dandellion(mapLocation, thisWorld));
            } else if (type == Organism.GUARANA_SYMBOL) {
                thisWorld.add_organism(new Guarana(mapLocation, thisWorld));
            } else if (type == Organism.NIGHTSHADE_SYMBOL) {
                thisWorld.add_organism(new Nightshade(mapLocation, thisWorld));
            } else if (type == Organism.PINEBORSHT_SYMBOL) {
                thisWorld.add_organism(new PineBorscht(mapLocation, thisWorld));
            }
        }
    }

    public void update_icon() {
        Organism o = thisWorld.getMap().get_object(mapLocation);

        if (o == null) {
            setIcon(null);
        } else {
            char type = o.getSymbol();
            if (type == Organism.SHEEP_SYMBOL) {
                setIcon(Icons.SHEEP_ICON);
            } else if (type == Organism.WOLF_SYMBOL) {
                setIcon(Icons.WOLF_ICON);
            } else if (type == Organism.FOX_SYMBOL) {
                setIcon(Icons.FOX_ICON);
            } else if (type == Organism.TURTLE_SYMBOL) {
                setIcon(Icons.TURTLE_ICON);
            } else if (type == Organism.ANTELOPE_SYMBOL) {
                setIcon(Icons.ANTELOPE_ICON);
            } else if (type == Organism.GRASS_SYMBOL) {
                setIcon(Icons.GRASS_ICON);
            } else if (type == Organism.DANDELLION_SYMBOL) {
                setIcon(Icons.DANDELLION_ICON);
            } else if (type == Organism.GUARANA_SYMBOL) {
                setIcon(Icons.GUARANA_ICON);
            } else if (type == Organism.NIGHTSHADE_SYMBOL) {
                setIcon(Icons.NIGHTSHADE_ICON);
            } else if (type == Organism.PINEBORSHT_SYMBOL) {
                setIcon(Icons.PINEBORSHT_ICON);
            } else if (type == Organism.HUMAN_SYMBOL) {
                setIcon(Icons.HUMAN_ICON);
            }
        }
    }


}
