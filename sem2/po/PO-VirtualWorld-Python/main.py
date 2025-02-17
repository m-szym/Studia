import pygame as pg
import pygame_gui as pgui

import MapLocations
import Maps

import World as w
from simulator.organisms.animals.Human import Human
from Sheep import Sheep
from Wolf import Wolf
from Sim import Simulator


if __name__ == '__main__':
    h = w.World.hex_map(5)
    human = h.add_organism(Human(h, MapLocations.HexLocation((0, 0, 0))))
    h.add_organism(Sheep(h, MapLocations.HexLocation((0, 1, -1))))
    h.human = human
    v = Simulator(h)
    v.run()
