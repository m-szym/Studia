from Plant import *
from Organism import ORGANISM_TYPES

DANDELION_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD
DANDELION_STRENGTH = BASE_PLANT_STRENGTH
DANDELION_INITIATIVE = BASE_PLANT_INITIATIVE
DANDELION_SEEDING_ATTEMPTS = 3


class Dandelion(Plant):
    def __init__(self, new_world, new_location):
        super().__init__(new_world, new_location, DANDELION_STRENGTH, DANDELION_INITIATIVE, ORGANISM_TYPES["Dandelion"], DANDELION_SEEDING_THRESHOLD)

    def spawn_offspring(self, new_location):
        return Dandelion(self._world, new_location)

    def __str__(self):
        return "Dandelion at " + str(self._location)

    def action(self):
        for i in range(DANDELION_SEEDING_ATTEMPTS):
            self.seed()