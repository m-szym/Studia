from simulator.organisms.animals.Animal import Animal, BASE_ANIMAL_SPEED
from simulator.organisms.Organism import ORGANISM_TYPES

WOLF_STRENGTH = 9
WOLF_INITIATIVE = 5
WOLF_SPEED = BASE_ANIMAL_SPEED


class Wolf(Animal):
    def __init__(self, new_world, new_location):
        super().__init__(new_world, new_location, WOLF_STRENGTH, WOLF_INITIATIVE, ORGANISM_TYPES["Wolf"], WOLF_SPEED)

    def spawn_offspring(self, new_location):
        return Wolf(self.world, new_location)

    def __str__(self):
        return "Wolf at " + str(self.location)
