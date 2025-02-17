from MapLocations import SQUARE_DIRS, SquareLocation, HEX_DIRS, HexLocation


class Map:
    def __init__(self):
        self.directions_num = 0
        self.internal_map = {}
        # self.directions = {}

        self.create_map()

    def create_map(self):
        pass

    def __contains__(self, location):
        return location in self.internal_map

    def __getitem__(self, location):
        if location not in self.internal_map:
            raise KeyError("Location not in map")
        return self.internal_map[location]

    def __setitem__(self, location, value):
        if location not in self.internal_map:
            raise KeyError("Location not in map")
        self.internal_map[location] = value

    def on_map(self, location):
        if location in self.internal_map:
            return True
        else:
            return False

    def move_org(self, org, new_location):
        self.internal_map[org.get_location()] = None
        self.internal_map[new_location] = org

        # org.set_location(new_location)

    def do_on_all_neighbours(self, location, func):
        for direction in self.directions:
            neighbour_location = location + direction
            if neighbour_location in self:
                func(self, neighbour_location)

    def get_first_free_neighbour(self, location):
        for direction in self.directions:
            neighbour_location = location + direction
            if neighbour_location in self and self[neighbour_location] is None:
                return neighbour_location
        return None

    def get_neighbours(self, location):
        neighbours = []
        for direction in self.directions:
            neighbour_location = location + direction
            if neighbour_location in self.internal_map:
                neighbours.append(neighbour_location)
        return neighbours

    def get_neighbours_with_organisms(self, location):
        neighbours = []
        for direction in self.directions:
            neighbour_location = location + direction
            if neighbour_location in self.internal_map and self[neighbour_location] is not None:
                neighbours.append(self[neighbour_location])
        return neighbours

    def print_all_locations(self):
        for location in self.internal_map:
            print(location, self.internal_map[location])

    def print_map(self):
        pass

    def bfs(self, start_location, targeter_func):
        target_location = None
        prev = {start_location: None}
        queue = [start_location]

        while queue:
            current = queue.pop(0)
            if targeter_func(self, current):
                target_location = current
                break
            for neighbour in self.get_neighbours(current):
                if neighbour not in prev:
                    prev[neighbour] = current
                    queue.append(neighbour)

        if target_location is None:
            return None

        path = []
        current = target_location
        while current != start_location:
            path.append(current)
            if prev[current] is None:
                break
            current = prev[current]
        path.reverse()
        return path


class SquareMap(Map):
    def __init__(self, width, height):
        self.directions = SQUARE_DIRS
        self.directions_num = len(SQUARE_DIRS)
        self.internal_map = {}

        self.width = width
        self.height = height
        # super().__init__()
        self.create_map()

    def create_map(self):
        for x in range(self.width):
            for y in range(self.height):
                self.internal_map[SquareLocation((x, y))] = None

    def print_map(self):
        for y in range(self.height):
            for x in range(self.width):
                if self.internal_map[SquareLocation((x, y))] is None:
                    print("_", end="")
                else:
                    print(f"{self.internal_map[SquareLocation((x, y))].get_type()[0]}", end="")
                print(" ", end="")
            print()


class HexMap(Map):
    def __init__(self, size):
        self.directions = HEX_DIRS
        self.directions_num = len(HEX_DIRS)
        self.internal_map = {}

        self.size = size
        # super().__init__()
        self.create_map()

    def create_map(self):
        for q in range(-self.size, self.size + 1):
            r1 = max(-self.size, -q - self.size)
            r2 = min(self.size, -q + self.size)
            for r in range(r1, r2 + 1):
                self.internal_map[HexLocation((q, r, -q - r))] = None

    def print_map(self):
        for q in range(-self.size, self.size + 1):
            r1 = max(-self.size, -q - self.size)
            r2 = min(self.size, -q + self.size)

            for i in range(-self.size, self.size - r2 + r1):
                print(" ", end="")

            for r in range(r1, r2 + 1):
                if self.internal_map[HexLocation((q, r, -q - r))] is None:
                    print("_", end="")
                else:
                    print(f"{self.internal_map[HexLocation((q, r, -q - r))].get_type()[0]}", end="")
                print(" ", end="")
            print()
