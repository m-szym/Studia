ORGANISM_TYPES = {
    "Organism": "0rganism",

    "Animal": "4nimal",
    "Sheep": "Sheep",
    "Wolf": "Wolf",
    "Fox": "Fox",
    "Turtle": "Turtle",
    "Antelope": "Antelope",
    "CyberSheep": "CyberSheep",
    "Human": "Human",

    "Plant": "9lant",
    "Grass": "grass",
    "Dandelion": "dandelion",
    "Guarana": "uarana",
    "Nightshade": "nightshade",
    "Hogweed": "hogweed",
}

ALIVE_STATE = "Alive"
DEAD_STATE = "Dead"


class Organism:
    __organism_count = 0

    def __init__(self, new_world, new_location, new_strength=0, new_initiative=0, new_type=ORGANISM_TYPES["Organism"]):
        self._world = new_world
        self._type = new_type

        self._age = Organism.__organism_count
        self._state = ALIVE_STATE
        Organism.__organism_count += 1

        self._location = new_location
        self._strength = new_strength
        self._initiative = new_initiative

    def __str__(self):
        return "Organism at " + str(self._location)

    def __lt__(self, other):
        if self._initiative == other.get_initiative():
            return self._age < other.get_age()
        else:
            return self._initiative < other.get_initiative()

    def __eq__(self, other):
        if not isinstance(other, Organism):
            return False
        return (self._initiative == other.get_initiative()) and (self._age == other.get_age())

    def collision(self, invader):
        self.fight(invader)

    def action(self):
        pass

    def fight(self, attacker):
        if attacker.get_strength() <= self.get_strength():
            self.tlog(" defends from " + str(attacker))
            attacker.kill_self()
        else:
            attacker.tlog(" kills " + str(self))
            attacker.update_location(self._location)
            self.kill_self()

    def update_location(self, new_location):
        self.tlog(" moved to " + str(new_location))
        self._world.map.move_org(self, new_location)
        self._location = new_location

    def kill_self(self):
        self._state = DEAD_STATE
        self.tlog(" dies")

        if self._world.map[self._location] == self:
            self._world.map[self._location] = None

    def is_plant(self):
        return self._initiative == 0

    def same_type(self, other):
        return self._type == other.get_type()

    def spawn_offspring(self, location):
        pass

    def tlog(self, message):
        self._world.add_to_turn_log(str(self) + message)

    def get_strength(self):
        return self._strength

    def set_strength(self, new_strength):
        self._strength = new_strength

    def get_location(self):
        return self._location

    def set_location(self, new_location):
        self._location = new_location

    def get_initiative(self):
        return self._initiative

    def get_type(self):
        return self._type

    def get_age(self):
        return self._age

    def get_state(self):
        return self._state

    def get_world(self):
        return self._world

    def get_map(self):
        return self._world.get_map()
