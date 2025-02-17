import random

from simulator.organisms.Organism import Organism

SEEDING_CHANCE_BASE = 100
BASE_PLANT_SEEDING_THRESHOLD = 97
BASE_PLANT_STRENGTH = 0
BASE_PLANT_INITIATIVE = 0


class Plant(Organism):
    def __init__(self, new_world, new_location, new_strength, new_initiative, new_type, new_seeding_threshold):
        super().__init__(new_world, new_location, new_strength, new_initiative, new_type)
        self.seeding_threshold = new_seeding_threshold

    def action(self):
        self.seed()

    def collision(self, invader):
        invader.update_location(self.location)
        self.kill_self()

    def seed(self):
        r = random.randint(0, SEEDING_CHANCE_BASE)

        if r > self.seeding_threshold:
            free_loc = self.world.map.get_first_free_neighbour(self.location)
            if free_loc is not None:
                self.tlog(" seeded at " + str(free_loc))
                self.world.add_organism(self.spawn_offspring(free_loc))

    def __str__(self):
        return "Plant " + str(self.location)