from simulator.organisms.plants.Plant import *
from simulator.organisms.Organism import ORGANISM_TYPES

HOGWEED_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD
HOGWEED_STRENGTH = 0
HOGWEED_INITIATIVE = BASE_PLANT_INITIATIVE



class Hogweed(Plant):
    def __init__(self, new_world, new_location):
        super().__init__(new_world, new_location, HOGWEED_STRENGTH, HOGWEED_INITIATIVE, ORGANISM_TYPES["Hogweed"],
                         HOGWEED_SEEDING_THRESHOLD)

    def spawn_offspring(self, new_location):
        return Hogweed(self.world, new_location)

    def __str__(self):
        return "Hogweed at " + str(self.location)

    def collision(self, invader):
        if invader.get_type() == ORGANISM_TYPES["CyberSheep"]:
            invader.update_location(self.location)
            self.kill_self()
        else:
            invader.kill_self()

    def action(self):
        self.get_map().do_on_all_neighbours(self.location, hogweed_poison)
        super().action()


def hogweed_poison(imap, loc):
    t = imap[loc]
    if t is not None:
        if t.get_type() == ORGANISM_TYPES["CyberSheep"] or t.get_type() == ORGANISM_TYPES["Hogweed"]:
            pass
        else:
            imap[loc].kill_self()
