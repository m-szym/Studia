package studia.prog_ob.projekt2.world_simulator.gui;

import studia.prog_ob.projekt2.world_simulator.Simulator;

import javax.swing.*;
import java.awt.event.ActionEvent;

public class EndTurnButton extends JButton {
    private final Simulator simulator;
    public EndTurnButton(Simulator simulator) {
        this.setSize(100, 60);
        this.setText("END TURN");
        this.setAction(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                simulator.make_turn();
            }
        });
        this.simulator = simulator;
    }
}
