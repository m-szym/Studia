from simulator.organisms.animals.Animal import Animal, BASE_ANIMAL_SPEED
from simulator.organisms.Organism import ORGANISM_TYPES

HUMAN_STRENGTH = 5
HUMAN_INITIATIVE = 4
HUMAN_SPEED = BASE_ANIMAL_SPEED
HUMAN_SKILL_COOLDOWN = 5
HUMAN_SKILL_DURATION = 5


class Human(Animal):
    def __init__(self, new_world, new_location):
        super().__init__(new_world, new_location, HUMAN_STRENGTH, HUMAN_INITIATIVE, ORGANISM_TYPES["Human"], HUMAN_SPEED)
        self.skill_cooldown = 0
        self.skill_duration_left = 0
        self.skill_active = False
        self.direction = self.get_map().directions_num

    def spawn_offspring(self, new_location):
        pass

    def decide_where_to_move(self):
        return self.direction

    def skill(self):
        if not self.skill_active and self.skill_cooldown > 0:
            self.skill_cooldown -= 1

        if self.skill_active and self.skill_duration_left > 1:
            self.skill_duration_left -= 1
        elif self.skill_active and self.skill_duration_left == 1:
            self.skill_duration_left = 0
            self.skill_active = False
            self.skill_cooldown = HUMAN_SKILL_COOLDOWN

        if self.skill_active:
            self.tlog(" used skill")
            self.balefire()

    def balefire(self):
        self.get_map().do_on_all_neighbours(self.location, kill_target)

    def action(self):
        self.skill()
        super().action()
        self.direction = self.get_map().directions_num

    def activate_skill(self):
        self.skill_active = True
        self.skill_cooldown = HUMAN_SKILL_COOLDOWN
        self.skill_duration_left = HUMAN_SKILL_DURATION

    def give_command(self, command):
        if command <= self.get_map().directions_num + 100:
            self.direction = command - 100
            return True
        elif command == 200:
            if self.skill_cooldown == 0 and not self.skill_active:
                self.activate_skill()
                self.tlog("ACTIVE SKILL")
                return True
        else:
            return False

    def __str__(self):
        return "Human at " + str(self.location)


def kill_target(imap, loc):
    if imap[loc] is not None:
        imap[loc].tlog(" was erased from the pattern")
        imap[loc].kill_self()


