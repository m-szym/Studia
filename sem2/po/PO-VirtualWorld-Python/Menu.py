import pygame as pg
import pygame_gui as pgui

from simulator.organisms.animals.Antelope import Antelope
from simulator.organisms.animals.CyberSheep import CyberSheep
from simulator.organisms.animals.Fox import Fox
from simulator.organisms.animals.Sheep import Sheep
from simulator.organisms.animals.Turtle import Turtle
from simulator.organisms.animals.Wolf import Wolf
from simulator.organisms.plants.Dandelion import Dandelion
from simulator.organisms.plants.Guarana import Guarana
from simulator.organisms.plants.Grass import Grass
from simulator.organisms.plants.Hogweed import Hogweed
from simulator.organisms.plants.Nightshade import Nightshade


class AddOrganismSubMenu():
    def __init__(self,
                 manager,
                 world,
                 MENU_X_OFFSET,
                 MENU_Y_OFFSET,
                 MENU_BUTTON_SIZE):
        self.o_to_add = None
        self.manager = manager
        self.world = world
        self.buttons = []

        next_button_x = MENU_X_OFFSET

        self.add_cybersheep_button = pgui.elements.UIButton(relative_rect=pg.Rect((next_button_x - MENU_BUTTON_SIZE[0],
                                                                                   MENU_Y_OFFSET),
                                                                                  MENU_BUTTON_SIZE),
                                                            text="CYBERSHEEP",
                                                            manager=self.manager)
        self.buttons.append(self.add_cybersheep_button)

        self.add_wolf_button = pgui.elements.UIButton(relative_rect=pg.Rect((next_button_x, MENU_Y_OFFSET),
                                                                            MENU_BUTTON_SIZE),
                                                      text="WOLF",
                                                      manager=self.manager)
        self.buttons.append(self.add_wolf_button)

        self.add_grass_button = pgui.elements.UIButton(
            relative_rect=pg.Rect((next_button_x, MENU_Y_OFFSET + MENU_BUTTON_SIZE[1]),
                                  MENU_BUTTON_SIZE),
            text="GRASS",
            manager=self.manager)
        self.buttons.append(self.add_grass_button)

        next_button_x += MENU_BUTTON_SIZE[0]

        self.add_sheep_button = pgui.elements.UIButton(relative_rect=pg.Rect((next_button_x, MENU_Y_OFFSET),
                                                                             MENU_BUTTON_SIZE),
                                                       text="SHEEP",
                                                       manager=self.manager)
        self.buttons.append(self.add_sheep_button)

        self.add_dandelion_button = pgui.elements.UIButton(
            relative_rect=pg.Rect((next_button_x, MENU_Y_OFFSET + MENU_BUTTON_SIZE[1]),
                                  MENU_BUTTON_SIZE),
            text="DANDELION",
            manager=self.manager)
        self.buttons.append(self.add_dandelion_button)

        next_button_x += MENU_BUTTON_SIZE[0]

        self.add_fox_button = pgui.elements.UIButton(relative_rect=pg.Rect((next_button_x, MENU_Y_OFFSET),
                                                                           MENU_BUTTON_SIZE),
                                                     text="FOX",
                                                     manager=self.manager)
        self.buttons.append(self.add_fox_button)

        self.add_nightshade_button = pgui.elements.UIButton(
            relative_rect=pg.Rect((next_button_x, MENU_Y_OFFSET + MENU_BUTTON_SIZE[1]),
                                  MENU_BUTTON_SIZE),
            text="NIGHTSAHDE",
            manager=self.manager)
        self.buttons.append(self.add_nightshade_button)

        next_button_x += MENU_BUTTON_SIZE[0]

        self.add_turtle_button = pgui.elements.UIButton(relative_rect=pg.Rect((next_button_x, MENU_Y_OFFSET),
                                                                              MENU_BUTTON_SIZE),
                                                        text="TURTLE",
                                                        manager=self.manager)
        self.buttons.append(self.add_turtle_button)

        self.add_guarana_button = pgui.elements.UIButton(
            relative_rect=pg.Rect((next_button_x, MENU_Y_OFFSET + MENU_BUTTON_SIZE[1]),
                                  MENU_BUTTON_SIZE),
            text="GUARANA",
            manager=self.manager)
        self.buttons.append(self.add_guarana_button)

        next_button_x += MENU_BUTTON_SIZE[0]

        self.add_antelope_button = pgui.elements.UIButton(relative_rect=pg.Rect((next_button_x, MENU_Y_OFFSET),
                                                                                MENU_BUTTON_SIZE),
                                                          text="ANTELOPE",
                                                          manager=self.manager)
        self.buttons.append(self.add_antelope_button)

        self.add_hogweed_button = pgui.elements.UIButton(
            relative_rect=pg.Rect((next_button_x, MENU_Y_OFFSET + MENU_BUTTON_SIZE[1]),
                                  MENU_BUTTON_SIZE),
            text="HOGWEED",
            manager=self.manager)
        self.buttons.append(self.add_hogweed_button)

        next_button_x += MENU_BUTTON_SIZE[0]

    def __contains__(self, button):
        if button in self.buttons:
            return True
        else:
            return False

    def manage_events(self, event):
        if event.ui_element == self.add_wolf_button:
            self.o_to_add = "WOLF"
        elif event.ui_element == self.add_sheep_button:
            self.o_to_add = "SHEEP"
        elif event.ui_element == self.add_fox_button:
            self.o_to_add = "FOX"
        elif event.ui_element == self.add_turtle_button:
            self.o_to_add = "TURTLE"
        elif event.ui_element == self.add_antelope_button:
            self.o_to_add = "ANTELOPE"
        elif event.ui_element == self.add_cybersheep_button:
            self.o_to_add = "CYBERSHEEP"

        elif event.ui_element == self.add_grass_button:
            self.o_to_add = "GRASS"
        elif event.ui_element == self.add_dandelion_button:
            self.o_to_add = "DANDELION"
        elif event.ui_element == self.add_nightshade_button:
            self.o_to_add = "NIGHTSAHDE"
        elif event.ui_element == self.add_guarana_button:
            self.o_to_add = "GUARANA"
        elif event.ui_element == self.add_hogweed_button:
            self.o_to_add = "HOGWEED"

        else:
            self.o_to_add = None

    def add_org(self, location):
        if self.world.map[location] is not None:
            return False
        else:
            if self.o_to_add is None:
                return False
            else:
                world_change = True
                if self.o_to_add == "SHEEP":
                    self.world.add_organism(Sheep(self.world, location))
                elif self.o_to_add == "WOLF":
                    self.world.add_organism(Wolf(self.world, location))
                elif self.o_to_add == "FOX":
                    self.world.add_organism(Fox(self.world, location))
                elif self.o_to_add == "TURTLE":
                    self.world.add_organism(Turtle(self.world, location))
                elif self.o_to_add == "ANTELOPE":
                    self.world.add_organism(Antelope(self.world, location))
                elif self.o_to_add == "CYBERSHEEP":
                    self.world.add_organism(CyberSheep(self.world, location))

                elif self.o_to_add == "GRASS":
                    self.world.add_organism(Grass(self.world, location))
                elif self.o_to_add == "DANDELION":
                    self.world.add_organism(Dandelion(self.world, location))
                elif self.o_to_add == "NIGHTSAHDE":
                    self.world.add_organism(Nightshade(self.world, location))
                elif self.o_to_add == "GUARANA":
                    self.world.add_organism(Guarana(self.world, location))
                elif self.o_to_add == "HOGWEED":
                    self.world.add_organism(Hogweed(self.world, location))

                self.o_to_add = None
                return True
