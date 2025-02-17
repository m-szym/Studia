import pickle
import random

import MapLocations
from Human import Human
from Maps import SquareMap, HexMap
from Organism import Organism, DEAD_STATE, ALIVE_STATE
from Sheep import Sheep
from Wolf import Wolf
from Fox import Fox
from Antelope import Antelope
from Turtle import Turtle
from CyberSheep import CyberSheep
from Grass import Grass
from Dandelion import Dandelion
from Guarana import Guarana
from Nightshade import Nightshade
from Hogweed import Hogweed
from Organism import ORGANISM_TYPES


SAVE_DIR = "saves/"


class World:
    def __init__(self):
        self.__organisms = []
        self.__turn = 0
        self.__human = None
        self.map = None

        self.turn_log = ""

    @classmethod
    def square_map(cls, width, height):
        world = cls()
        world.map = SquareMap(width, height)
        return world

    @classmethod
    def hex_map(cls, size):
        world = cls()
        world.map = HexMap(size)
        return world

    def populate(self):
        if isinstance(self.map, SquareMap):
            h = self.add_organism(Human(self, MapLocations.SquareLocation((0, 0))))
            self.__human = h
            orgs = (self.map.width * self.map.height) * 0.25
            for y in range(0, self.map.height, 2):
                if orgs < 1: break
                for x in range(0, self.map.width):
                    if orgs < 1: break
                    r = random.randint(0, 1)
                    if r == 0:
                        if self.map[MapLocations.SquareLocation((x, y))] is None:
                            self.add_random_organism(MapLocations.SquareLocation((x, y)))
                            orgs -= 1
        elif isinstance(self.map, HexMap):
            h = self.add_organism(Human(self, MapLocations.HexLocation((0, 0, 0))))
            self.__human = h
            orgs = (self.map.size * self.map.size)
            for q in range(-self.map.size, self.map.size + 1):
                if orgs < 1: break
                r1 = max(-self.map.size, -q - self.map.size)
                r2 = min(self.map.size, -q + self.map.size)
                for r in range(r1, r2 + 1):
                    if orgs < 1: break
                    r = random.randint(0, 2)
                    if r > 0:
                        try:
                            if self.map[MapLocations.HexLocation((q, r, -q - r))] is None:
                                self.add_random_organism(MapLocations.HexLocation((q, r, -q - r)))
                                orgs -= 1
                                print(orgs)
                        except KeyError:
                            print(f"Organism {str(MapLocations.HexLocation((q, r, -q - r)))} out of map")

    def add_random_organism(self, location):
        org_num = random.randint(0, 10)
        if org_num == 0:
            self.add_organism(Sheep(self, location))
        elif org_num == 1:
            self.add_organism(Wolf(self, location))
        elif org_num == 2:
            self.add_organism(Fox(self, location))
        elif org_num == 3:
            self.add_organism(Antelope(self, location))
        elif org_num == 4:
            self.add_organism(Turtle(self, location))
        elif org_num == 5:
            self.add_organism(CyberSheep(self, location))
        elif org_num == 6:
            self.add_organism(Grass(self, location))
        elif org_num == 7:
            self.add_organism(Dandelion(self, location))
        elif org_num == 8:
            self.add_organism(Guarana(self, location))
        elif org_num == 9:
            self.add_organism(Nightshade(self, location))
        elif org_num == 10:
            self.add_organism(Hogweed(self, location))
        else:
            print("Error: random organism number out of range")

    def add_organism(self, organism) -> Organism:
        try:
            self.map[organism.get_location()] = organism
            self.__organisms.append(organism)
            return organism
        except KeyError:
            print(f"Organism {str(organism.get_location())} out of map")
            return None

    def clean_board(self):
        for organism in self.__organisms:
            if organism.get_state() == DEAD_STATE:
                if organism._type == ORGANISM_TYPES["Human"]:
                    self.__human = None
                self.map[organism.get_location()] = None
                self.__organisms.remove(organism)

    def make_turn(self):
        self.turn_log = ""
        self.sort_organisms()
        self.clean_board()
        self.__turn += 1
        for organism in self.__organisms:
            if organism.get_state() == ALIVE_STATE:
                organism.action()

    def save(self, file_name):
        with open(SAVE_DIR + file_name, 'wb') as file:
            pickle.dump(self, file, pickle.HIGHEST_PROTOCOL)
            print(f'World successfully saved to "{file_name}"')

    @classmethod
    def load(cls, file_name):
        with open(SAVE_DIR + file_name, 'rb') as inp:
            world = pickle.load(inp)
            print(f'World successfully loaded from "{file_name}"')
            return world

    def sort_organisms(self):
        self.__organisms.sort()

    def get_map(self):
        return self.map

    def get_turn(self):
        return self.__turn

    def get_organisms(self):
        return self.__organisms

    def get_human(self):
        return self.__human

    def set_human(self, human):
        self.__human = human

    def get_turn_log(self):
        return self.turn_log

    def add_to_turn_log(self, text):
        self.turn_log += text + "\n"
