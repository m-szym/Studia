package studia.prog_ob.projekt2.world_simulator.gui;
import studia.prog_ob.projekt2.world_simulator.Simulator;
import studia.prog_ob.projekt2.world_simulator.World;
import studia.prog_ob.projekt2.world_simulator.organisms.DirectControl;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.*;

public class GUI {
    public static final int FRAME_WIDTH = 500;
    public static final int FRAME_HEIGHT = 500;
    public static final String savesDir = "/Users/msz/IdeaProjects/ProgOb_P2/src/studia/prog_ob/projekt2/saves";

    private final JFrame mainFrame;
    public BoardPanel boardPanel;
    private final Simulator simulator;

    public GUI(Simulator simulator) {
        /*try{
            UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
        }catch(Exception e){
            e.printStackTrace();
        }*/

        this.simulator = simulator;
        mainFrame = mainFrame();

        StartMenu(simulator);

        //main_screen(simulator);

        mainFrame.setVisible(true);
    }

    private JFrame mainFrame() {
        JFrame mainFrame = new JFrame();

        mainFrame.setSize(FRAME_WIDTH, FRAME_HEIGHT);
        mainFrame.setTitle("Programowanie obiektowe - Projekt 2 - JAVA - Marek Szymański - 193229");
        mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        mainFrame.setLayout(new BorderLayout());

        return mainFrame;
    }


    public void mainScreen(Simulator simulator) {
        //new Icons();
        int[] map_size = simulator.world.getMap().get_size();
        int worldSizeX = map_size[1];
        int worldSizeY = map_size[2];

        boardPanel = new BoardPanel(worldSizeX, worldSizeY, simulator.world);
        mainFrame.add(BorderLayout.CENTER, new JScrollPane(boardPanel));


        JPanel buttonPanel = new JPanel(new FlowLayout());
        EndTurnButton endTurnButton = new EndTurnButton(simulator);
        endTurnButton.setText("END TURN");
        buttonPanel.add(endTurnButton);

        JButton exitButton = new JButton("EXIT");
        exitButton.setAction(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                mainFrame.dispose();
            }
        });
        exitButton.setText("EXIT");
        buttonPanel.add(exitButton);

        //todo 2
        JButton saveButton = new JButton("SAVE");
        saveButton.setAction(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent event) throws RuntimeException {
                String s = JOptionPane.showInputDialog(mainFrame, "Enter savefile name", "Save world Dialog", JOptionPane.PLAIN_MESSAGE);

                if ((s != null) && (s.length() > 0)) {
                    try (ObjectOutputStream outputStream = new ObjectOutputStream(new FileOutputStream(savesDir + "/" + s + ".bin"))) {
                        outputStream.writeObject(simulator.world);
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        });
        buttonPanel.add(saveButton);
        saveButton.setText("SAVE WORLD");

        mainFrame.add(BorderLayout.SOUTH, buttonPanel);

        JPanel logPanel = new JPanel(new BorderLayout());
        JTextArea logTextArea = new JTextArea("LOREM IPSUM");

        //logTextArea.setLineWrap(true);
        logTextArea.setAutoscrolls(true);
        logPanel.add(BorderLayout.CENTER, logTextArea);
        simulator.setSimLoggerTextArea(logTextArea);
        ScrollPane scrollPane = new ScrollPane();
        scrollPane.add(logPanel);
        mainFrame.add(scrollPane, BorderLayout.EAST);
        scrollPane.setSize(new Dimension(200, 200));

        mainFrame.setFocusable(true);
        mainFrame.requestFocusInWindow();
        mainFrame.addKeyListener(new KeyControl());

        simulator.make_turn();

        mainFrame.revalidate();
        mainFrame.repaint();
    }

    private class KeyControl implements KeyListener {
        @Override
        public void keyPressed(KeyEvent e) {

            if(e.getKeyCode() == KeyEvent.VK_UP) {
                simulator.world.getHuman().give_command(DirectControl.GO_DIR1);
            }

            if(e.getKeyCode() == KeyEvent.VK_RIGHT) {
                simulator.world.getHuman().give_command(DirectControl.GO_DIR2);
            }

            if(e.getKeyCode() == KeyEvent.VK_DOWN) {
                simulator.world.getHuman().give_command(DirectControl.GO_DIR3);
            }

            if(e.getKeyCode() == KeyEvent.VK_LEFT) {
                simulator.world.getHuman().give_command(DirectControl.GO_DIR4);
            }

            if(e.getKeyCode() == KeyEvent.VK_SPACE) {
                simulator.world.getHuman().give_command(DirectControl.USE_SKILL);
            }

            simulator.make_turn();
        }

        @Override
        public void keyTyped(KeyEvent e) {

        }

        @Override
        public void keyReleased(KeyEvent e) {

        }
    }


    private void StartMenu(Simulator simulator) {

        JButton startButton = new JButton("START");
        JButton loadButton = new JButton("LOAD");

        JPanel p = new JPanel(new FlowLayout());
        p.add(startButton);
        p.add(loadButton);
        mainFrame.add(BorderLayout.CENTER, p);


        startButton.setSize(200,200);
        startButton.setAction(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                p.removeAll();
                mainFrame.remove(p);

                newWorldMenu(simulator);
            }
        });
        startButton.setText("NEW WORLD");

        loadButton.setSize(200,200);
        loadButton.setAction(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                p.removeAll();
                mainFrame.remove(p);

                loadWorldMenu(simulator);
            }
        });
        loadButton.setText("LOAD WORLD");
    }

    private void newWorldMenu(Simulator simulator) {
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));

        JSlider xSlider = new JSlider(5, 25, 10);
        xSlider.setMajorTickSpacing(5);
        xSlider.setMinorTickSpacing(1);
        xSlider.setPaintTicks(true);
        xSlider.setPaintLabels(true);

        JSlider ySlider = new JSlider(5, 25, 10);
        ySlider.setMajorTickSpacing(5);
        ySlider.setMinorTickSpacing(1);
        ySlider.setPaintTicks(true);
        ySlider.setPaintLabels(true);

        JButton confirmButton = new JButton("CONFIRM");
        confirmButton.setAction(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int x = xSlider.getValue();
                int y = ySlider.getValue();
                System.out.println("X: " + x + ", Y: " + y);
                panel.removeAll();
                mainFrame.remove(panel);

                simulator.world = new World(x, y);
                mainScreen(simulator);
            }
        });
        confirmButton.setAlignmentX(Component.CENTER_ALIGNMENT);


        JLabel l = new JLabel("Choose the size of your world");
        l.setAlignmentX(Component.CENTER_ALIGNMENT);
        panel.add(l);
        panel.add(xSlider);
        l = new JLabel("Size X");
        l.setAlignmentX(Component.CENTER_ALIGNMENT);
        panel.add(l);
        panel.add(ySlider);
        l = new JLabel("Size Y");
        l.setAlignmentX(Component.CENTER_ALIGNMENT);
        panel.add(l);
        panel.add(confirmButton);
        confirmButton.setText("CONFIRM");

        mainFrame.add(BorderLayout.CENTER, panel);

        mainFrame.revalidate();
        mainFrame.repaint();
    }

    private void loadWorldMenu(Simulator simulator) {
        JFileChooser f = new JFileChooser(savesDir);

        f.setAcceptAllFileFilterUsed(false);
        f.setDialogTitle("Select a .bin savefile");
        FileNameExtensionFilter restrict = new FileNameExtensionFilter("Only .bin files", "bin");
        f.addChoosableFileFilter(restrict);

        //todo 1
        if (f.showOpenDialog(mainFrame) == JFileChooser.APPROVE_OPTION) {
            File F = f.getSelectedFile();
            System.out.println(F.getAbsolutePath());
            try (ObjectInputStream inputStream = new ObjectInputStream(new FileInputStream(F.getAbsolutePath()))) {
                simulator.world = (World) inputStream.readObject();
                //nw.getMap().draw_map();
                mainScreen(simulator);
            } catch (IOException | ClassNotFoundException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
