package studia.prog_ob.projekt2.world_simulator.gui;

import studia.prog_ob.projekt2.world_simulator.World;

import javax.swing.*;
import java.awt.*;

public class BoardPanel extends JPanel {

    public BoardSquareButton[][] buttons;
    public int board_size_x;
    public int board_size_y;
    World thisWorld;

    public BoardPanel(int size_x, int size_y, World world) {
        board_size_x = size_x;
        board_size_y = size_y;
        thisWorld = world;

        setLayout(new GridLayout(size_y, size_x, 1, 1));

        buttons = new BoardSquareButton[size_y][size_x];
        for (int i = 0; i < size_y; i++) {
            for (int j = 0; j < size_x; j++) {
                BoardSquareButton button = new BoardSquareButton(i, j, world);
                buttons[i][j] = button;
                add(button);
            }
        }
    }

    public void updateBoard() {
        for (BoardSquareButton[] row: buttons) {
            for (BoardSquareButton button: row) {
                button.update_icon();
            }
        }

        revalidate();
        repaint();
    }

}
