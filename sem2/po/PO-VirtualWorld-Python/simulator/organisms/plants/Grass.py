from simulator.organisms.plants.Plant import *
from simulator.organisms.Organism import ORGANISM_TYPES

GRASS_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD
GRASS_STRENGTH = BASE_PLANT_STRENGTH
GRASS_INITIATIVE = BASE_PLANT_INITIATIVE



class Grass(Plant):
    def __init__(self, new_world, new_location):
        super().__init__(new_world, new_location, GRASS_STRENGTH, GRASS_INITIATIVE, ORGANISM_TYPES["Grass"], GRASS_SEEDING_THRESHOLD)

    def spawn_offspring(self, new_location):
        return Grass(self.world, new_location)

    def __str__(self):
        return "Grass at " + str(self.location)
