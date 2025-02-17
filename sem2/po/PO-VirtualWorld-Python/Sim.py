import pygame as pg
import pygame_gui as pgui

from simulator.MapLocations import MapLocations
from simulator.Maps import Maps
from simulator.World import World
from simulator.organisms.animals.Human import Human
from Menu import AddOrganismSubMenu

BASE_WINDOW_WIDTH = 1000
BASE_WINDOW_HEIGHT = 800

MAP_BUTTON_SIZE = 50

LOG_TEXT_FIELD_WIDTH = 200
LOG_TEXT_FIELD_HEIGHT = BASE_WINDOW_HEIGHT
LOG_TEXT_FIELD_X_OFFSET = BASE_WINDOW_WIDTH - LOG_TEXT_FIELD_WIDTH

MENU_SPACE_WIDTH = BASE_WINDOW_WIDTH - LOG_TEXT_FIELD_WIDTH
MENU_SPACE_HEIGHT = 200
MENU_Y_OFFSET = BASE_WINDOW_HEIGHT - MENU_SPACE_HEIGHT
MENU_BUTTON_SIZE = (75, 75)

square_human_controls = [
    pg.K_UP,
    pg.K_DOWN,
    pg.K_LEFT,
    pg.K_RIGHT,
    pg.K_SPACE,
]

hex_human_controls = [
    pg.K_w,
    pg.K_e,
    pg.K_d,
    pg.K_x,
    pg.K_z,
    pg.K_a,
    pg.K_SPACE,
]


class Simulator:
    def __init__(self, new_world):
        self.vis_running = None
        self.log_text_field = None
        self.clog = None
        self.buttons = None
        self.manager = None
        self.background = None
        self.window_surface = None
        self.h = None
        self.w = None
        self.world = new_world
        self.world_change = False

        self.init_visualizer()

        self.main_menu()

        self.run()

    def init_player_controls(self):
        if isinstance(self.world.map, Maps.SquareMap):
            self.human_commands = self.square_human_commands
            self.human_controls = square_human_controls
        elif isinstance(self.world.map, Maps.HexMap):
            self.human_commands = self.hex_human_commands
            self.human_controls = hex_human_controls
        else:
            raise Exception("Unknown map type")

    def init_visualizer(self,
                        window_width=BASE_WINDOW_WIDTH,
                        window_height=BASE_WINDOW_HEIGHT,
                        window_title="Marek Szymanski 193229 ProgOb Projekt 3",
                        background_color='#000000'):
        self.w = window_width
        self.h = window_height

        pg.init()

        pg.display.set_caption(window_title)
        self.window_surface = pg.display.set_mode((self.w, self.h))

        self.background = pg.Surface((self.w, self.h))
        self.background.fill(pg.Color(background_color))

        self.manager = pgui.UIManager((self.w, self.h))

        self.buttons = []

    def init_game_visualizer(self):
        try:
            self.init_map_visualizer(self.world.map)
            self.init_player_controls()
        except Exception as e:
            print(e)
            return

        self.init_menu()
        self.init_log_text_field()

    def init_map_visualizer(self, imap):
        if isinstance(imap, Maps.SquareMap):
            self.init_square_map_visualizer(imap)
        elif isinstance(imap, Maps.HexMap):
            self.init_hex_map_visualizer(imap)
        else:
            raise Exception("Unknown map type")

        self.icons = {
            "Sheep": pg.image.load("icons/icon_Sheep.jpg"),
            "Wolf": pg.image.load("icons/icon_Wolf.png"),
            "Turtle": pg.image.load("icons/icon_Turtle.jpg"),
            "Antelope": pg.image.load("icons/icon_Antelope.png"),
            "Fox": pg.image.load("icons/icon_Fox.jpg"),

            "grass": pg.image.load("icons/icon_grass.png"),
            "dandelion": pg.image.load("icons/icon_dandellion.png"),
            "uarana": pg.image.load("icons/icon_uarana.jpg"),
            "nightshade": pg.image.load("icons/icon_nightshade.jpg"),
            "hogweed": pg.image.load("icons/icon_hogweed.jpg"),
            "Human": pg.image.load("icons/icon_Human.jpg"),
            "CyberSheep": pg.image.load("icons/icon_CyberSheep.jpg"),

            "blank": pg.image.load("icons/icon_blank.jpg"),
        }

    def init_square_map_visualizer(self, imap):
        for y in range(imap.height):
            for x in range(imap.width):
                nb = pgui.elements.UIButton(relative_rect=pg.Rect((x * MAP_BUTTON_SIZE, y * MAP_BUTTON_SIZE),
                                                                  (MAP_BUTTON_SIZE, MAP_BUTTON_SIZE)),
                                            text='{i}'.format(i=len(self.buttons)),  # todo: remove text
                                            manager=self.manager)
                nb.map_location = MapLocations.SquareLocation((x, y))
                self.buttons.append(nb)

    def init_hex_map_visualizer(self, imap):
        size = imap.size
        x = 0
        y = 0

        for q in range(-size, size + 1):
            r1 = max(-size, -q - size)
            r2 = min(size, -q + size)

            for i in range(-size, size - r2 + r1):
                x += MAP_BUTTON_SIZE

            for r in range(0, abs(q)):
                x -= MAP_BUTTON_SIZE / 2

            for r in range(r1, r2 + 1):
                nb = pgui.elements.UIButton(relative_rect=pg.Rect((x, y), (MAP_BUTTON_SIZE, MAP_BUTTON_SIZE)),
                                            text='{i}'.format(i=len(self.buttons)),  # todo: remove text
                                            manager=self.manager)
                nb.map_location = MapLocations.HexLocation((q, r, -q - r))
                self.buttons.append(nb)

                x += MAP_BUTTON_SIZE

            y += MAP_BUTTON_SIZE
            x = 0

    def init_menu(self):
        self.save_button = pgui.elements.UIButton(relative_rect=pg.Rect((600, MENU_Y_OFFSET),
                                                                        MENU_BUTTON_SIZE),
                                                  text='Save',
                                                  manager=self.manager)

        self.ao_submenu = AddOrganismSubMenu(self.manager,
                                             self.world,
                                             MENU_BUTTON_SIZE[0] * 2,
                                             MENU_Y_OFFSET,
                                             MENU_BUTTON_SIZE)

    def init_log_text_field(self):
        self.clog = "<b>Lorem ipsum</b> dolor sit amet, consectetur adipiscing elit.\n\n"
        self.log_text_field = pgui.elements.UITextBox(relative_rect=pg.Rect((LOG_TEXT_FIELD_X_OFFSET, 0),
                                                                            (LOG_TEXT_FIELD_WIDTH,
                                                                             LOG_TEXT_FIELD_HEIGHT)),
                                                      html_text=self.clog,
                                                      manager=self.manager)

    def run(self):
        clock = pg.time.Clock()
        self.vis_running = True

        while self.vis_running:
            time_delta = clock.tick(60) / 1000.0

            self.manage_events()

            self.update(time_delta)

        pg.quit()

    def update(self, time_delta):
        if self.world_change:
            self.update_map_visualizer()
            self.log_text_field.set_text(self.world.get_turn_log())
            self.world_change = False

        self.manager.update(time_delta)

        self.window_surface.blit(self.background, (0, 0))
        self.manager.draw_ui(self.window_surface)

        pg.display.update()

    def update_map_visualizer(self):
        for button in self.buttons:
            if self.world.map[button.map_location] is None:
                button.drawable_shape.states['normal'].surface.blit(self.icons["blank"], (0, 0))
                button.drawable_shape.states['hovered'].surface.blit(self.icons["blank"], (0, 0))
                button.drawable_shape.states['active'].surface.blit(self.icons["blank"], (0, 0))
            else:
                type = self.world.map[button.map_location].get_type()
                if type in self.icons:
                    button.drawable_shape.states['normal'].surface.blit(self.icons[type], (0, 0))
                    button.drawable_shape.states['hovered'].surface.blit(self.icons[type], (0, 0))
                    button.drawable_shape.states['active'].surface.blit(self.icons[type], (0, 0))
            button.drawable_shape.active_state.has_fresh_surface = True



    def manage_events(self):
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.vis_running = False

            elif event.type == pg.KEYDOWN:
                if event.key == pg.K_ESCAPE:
                    self.vis_running = False

                if not self.main_menu_active:
                    if event.key in self.human_controls:
                        self.human_commands(event.key)

                    self.world_change = True
                    self.world.make_turn()

            elif event.type == pgui.UI_BUTTON_PRESSED:
                if not self.main_menu_active:
                    if event.ui_element == self.save_button:
                        self.clog += "<br>Save button pressed" 
                        self.world.save("savefile")

                    elif event.ui_element in self.ao_submenu:
                        self.ao_submenu.manage_events(event)

                    else:
                        if event.ui_element in self.buttons:
                            self.world_change = self.ao_submenu.add_org(event.ui_element.map_location)

                        self.clog += "<br>Button {i} pressed".format(i=event.ui_element.text)

                else:
                    if event.ui_element == self.square_world_button:
                        self.world = World.World.square_map(int(self.dimension_x_entry.get_text()),
                                                            int(self.dimension_y_entry.get_text()))
                        h = self.world.add_organism(Human(self.world, MapLocations.SquareLocation((0, 0))))
                        self.world.set_human(h)

                        self.delete_main_menu()
                        self.init_game_visualizer()

                    elif event.ui_element == self.hex_world_button:
                        self.world = World.World.hex_map(int(self.dimension_x_entry.get_text()))
                        h = self.world.add_organism(Human(self.world, MapLocations.HexLocation((0, 0, 0))))
                        self.world.set_human(h)

                        self.delete_main_menu()
                        self.init_game_visualizer()

                    elif event.ui_element == self.load_world_button:
                        self.world = World.World.load("savefile")

                        self.delete_main_menu()
                        self.init_game_visualizer()

            self.manager.process_events(event)

    def hex_human_commands(self, key_pressed):
        if key_pressed == pg.K_w:
            self.world.get_human().give_command(103)
        elif key_pressed == pg.K_e:
            self.world.get_human().give_command(102)
        elif key_pressed == pg.K_d:
            self.world.get_human().give_command(101)
        elif key_pressed == pg.K_x:
            self.world.get_human().give_command(100)
        elif key_pressed == pg.K_z:
            self.world.get_human().give_command(105)
        elif key_pressed == pg.K_a:
            self.world.get_human().give_command(104)
        elif key_pressed == pg.K_SPACE:
            self.world.get_human().give_command(200)

    def square_human_commands(self, key_pressed):
        if key_pressed == pg.K_UP:
            self.world.get_human().give_command(103)
        elif key_pressed == pg.K_RIGHT:
            self.world.get_human().give_command(100)
        elif key_pressed == pg.K_DOWN:
            self.world.get_human().give_command(101)
        elif key_pressed == pg.K_LEFT:
            self.world.get_human().give_command(102)
        elif key_pressed == pg.K_SPACE:
            self.world.get_human().give_command(200)

    def main_menu(self):
        self.square_world_button = pgui.elements.UIButton(relative_rect=pg.Rect((0, 0), (200, 30)),
                                                          text='Square world',
                                                          manager=self.manager)
        self.hex_world_button = pgui.elements.UIButton(relative_rect=pg.Rect((0, 40), (200, 30)),
                                                       text='Hex world',
                                                       manager=self.manager)
        self.main_menu_active = True

        self.dimension_x_entry = pgui.elements.UITextEntryLine(relative_rect=pg.Rect((0, 80), (200, 30)),
                                                               initial_text='width / radius',
                                                               manager=self.manager)
        self.dimension_y_entry = pgui.elements.UITextEntryLine(relative_rect=pg.Rect((0, 120), (200, 30)),
                                                               initial_text='height',
                                                               manager=self.manager)

        self.load_world_button = pgui.elements.UIButton(relative_rect=pg.Rect((0, 160), (200, 30)),
                                                        text='Load world',
                                                        manager=self.manager)

    def delete_main_menu(self):
        self.square_world_button.kill()
        self.hex_world_button.kill()
        self.dimension_x_entry.kill()
        self.dimension_y_entry.kill()
        self.load_world_button.kill()

        del self.square_world_button
        del self.hex_world_button
        del self.dimension_x_entry
        del self.dimension_y_entry
        del self.load_world_button

        self.main_menu_active = False
