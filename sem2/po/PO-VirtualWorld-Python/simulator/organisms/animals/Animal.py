import random

from simulator.organisms.Organism import Organism, ORGANISM_TYPES

BASE_ANIMAL_INITIATIVE = 0
BASE_ANIMAL_STRENGTH = 0
BASE_ANIMAL_SPEED = 1


class Animal(Organism):
    def __init__(self, new_world, new_location, new_strength, new_initiative, new_type, new_speed):
        super().__init__(new_world, new_location, new_strength, new_initiative, new_type)
        self.speed = new_speed

    def decide_where_to_move(self):
        return random.randint(0, self.get_map().directions_num)

    def choose_new_location(self):
        new_direction = self.decide_where_to_move()

        if new_direction == self.get_map().directions_num:
            return self.location
        else:
            new_location = self.location.get_neighbour_location(new_direction, self.get_speed())

            if self.get_map().on_map(new_location):
                return new_location
            else:
                return self.location

    def move(self):
        new_location = self.choose_new_location()

        if new_location != self.location:
            # print(str(self) + " might move to " + str(new_location))
            t = self.get_map()[new_location]
            if t is not None:
                self.pre_collision(t)
            else:

                self.update_location(new_location)
        # else:
        #     print(str(self) + " did not move")

    def mate(self):
        new_location = self.get_map().get_first_free_neighbour(self.location)

        if new_location is not None:
            self.tlog(" mates")
            return self.world.add_organism(self.spawn_offspring(new_location))
        else:
            return None

    def reflect_attack(self, attacker):
        return False

    def pre_collision(self, autochton):
        autochton.collision(self)

    def action(self):
        self.move()

    def collision(self, invader):
        if invader.get_type() == self.get_type():
            self.mate()
        elif not self.reflect_attack(invader):
            super().collision(invader)

    def __str__(self):
        return "Animal at " + str(self.location)

    def get_speed(self):
        return self.speed


