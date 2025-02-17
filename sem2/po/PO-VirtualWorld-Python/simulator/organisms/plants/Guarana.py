from simulator.organisms.plants.Plant import *
from simulator.organisms.Organism import ORGANISM_TYPES

GUARANA_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD
GUARANA_STRENGTH = BASE_PLANT_STRENGTH
GUARANA_INITIATIVE = BASE_PLANT_INITIATIVE
GUARANA_STRENGTH_BONUS = 3


class Guarana(Plant):
    def __init__(self, new_world, new_location):
        super().__init__(new_world, new_location, GUARANA_STRENGTH, GUARANA_INITIATIVE, ORGANISM_TYPES["Guarana"], GUARANA_SEEDING_THRESHOLD)

    def spawn_offspring(self, new_location):
        return Guarana(self.world, new_location)

    def __str__(self):
        return "Guarana at " + str(self.location)

    def collision(self, invader):
        invader.tlog(" ate " + str(self)  + " and gained +" + str(GUARANA_STRENGTH_BONUS) + " Strength")
        invader.set_strength(invader.get_strength() + GUARANA_STRENGTH_BONUS)
        invader.update_location(self.location)
        self.kill_self()