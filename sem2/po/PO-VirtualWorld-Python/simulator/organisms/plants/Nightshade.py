from simulator.organisms.plants.Plant import *
from simulator.organisms.Organism import ORGANISM_TYPES

NIGHTSHADE_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD
NIGHTSHADE_STRENGTH = 99
NIGHTSHADE_INITIATIVE = BASE_PLANT_INITIATIVE


class Nightshade(Plant):
    def __init__(self, new_world, new_location):
        super().__init__(new_world, new_location, NIGHTSHADE_STRENGTH, NIGHTSHADE_INITIATIVE, ORGANISM_TYPES["Nightshade"], NIGHTSHADE_SEEDING_THRESHOLD)

    def spawn_offspring(self, new_location):
        return Nightshade(self.world, new_location)

    def __str__(self):
        return "Nightshade at " + str(self.location)

    def collision(self, invader):
        self.tlog(" poisoned " + str(invader))
        invader.kill_self()