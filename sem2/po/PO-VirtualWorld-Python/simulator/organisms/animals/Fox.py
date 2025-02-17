from simulator.organisms.animals.Animal import Animal, BASE_ANIMAL_SPEED
from simulator.organisms.Organism import ORGANISM_TYPES

FOX_STRENGTH = 3
FOX_INITIATIVE = 7
FOX_SPEED = BASE_ANIMAL_SPEED


class Fox(Animal):
    def __init__(self, new_world, new_location):
        super().__init__(new_world, new_location, FOX_STRENGTH, FOX_INITIATIVE, ORGANISM_TYPES["Fox"], FOX_SPEED)

    def spawn_offspring(self, new_location):
        return Fox(self.world, new_location)

    def __str__(self):
        return "Fox at " + str(self.location)

    def pre_collision(self, autochton):
        if autochton.get_strength() > self.get_strength():
            self.tlog(" sensed " + str(autochton) + " and ran away")
        else:
            super().pre_collision(autochton)
