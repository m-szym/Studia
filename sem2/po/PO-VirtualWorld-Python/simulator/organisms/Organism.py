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
    organism_count = 0

    def __init__(self, new_world, new_location, new_strength=0, new_initiative=0, new_type=ORGANISM_TYPES["Organism"]):
        self.world = new_world
        self.type = new_type

        self.age = Organism.organism_count
        self.state = ALIVE_STATE
        Organism.organism_count += 1

        self.location = new_location
        self.strength = new_strength
        self.initiative = new_initiative

    def __str__(self):
        return "Organism at " + str(self.location)

    def __lt__(self, other):
        if self.initiative == other.get_initiative():
            return self.age < other.get_age()
        else:
            return self.initiative < other.get_initiative()

    def __eq__(self, other):
        if not isinstance(other, Organism):
            return False
        return (self.initiative == other.initiative) and (self.age == other.age)

    def collision(self, invader):
        self.fight(invader)

    def action(self):
        pass

    def fight(self, attacker):
        if attacker.get_strength() <= self.strength:
            self.tlog(" defends from " + str(attacker))
            attacker.kill_self()
        else:
            attacker.tlog(" kills " + str(self))
            attacker.update_location(self.location)
            self.kill_self()

    def update_location(self, new_location):
        self.tlog(" moved to " + str(new_location))
        self.world.map.move_org(self, new_location)
        self.location = new_location

    def kill_self(self):
        self.state = DEAD_STATE
        self.tlog(" dies")

        if self.world.map[self.location] == self:
            self.world.map[self.location] = None

    def is_plant(self):
        return self.initiative == 0

    def same_type(self, other):
        return self.type == other.get_type()

    def spawn_offspring(self, location):
        pass

    def tlog(self, message):
        self.world.add_to_turn_log(str(self) + message)

    def get_strength(self):
        return self.strength

    def set_strength(self, new_strength):
        self.strength = new_strength

    def get_location(self):
        return self.location

    def set_location(self, new_location):
        self.location = new_location

    def get_initiative(self):
        return self.initiative

    def get_type(self):
        return self.type

    def get_age(self):
        return self.age

    def get_state(self):
        return self.state

    def get_world(self):
        return self.world

    def get_map(self):
        return self.world.get_map()
