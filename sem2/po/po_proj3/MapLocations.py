class MapLocation:
    def __init__(self, new_coords):
        self._coords = new_coords

    @classmethod
    def copyc(cls, other_location):
        location = cls(other_location.get_coords())
        # location.coords = other_location.coords
        return location

    def __eq__(self, other):
        if not isinstance(other, MapLocation):
            return False
        return self._coords == other.get_coords()

    def __hash__(self):
        return hash(self._coords)

    def __str__(self):
        string_form = "("
        # for coord in self.coords:
        #     string_form += str(coord)
        #     if coord != self.coords[-1]:
        #         string_form += ", "
        string_form += str(self._coords[0])
        string_form += ", "
        string_form += str(self._coords[1])
        if len(self._coords) > 2:
            string_form += ", "
            string_form += str(self._coords[2])
        string_form += ")"
        return string_form

    def get_coords(self):
        return self._coords


#    N
#   W E
#    S


# SQUARE_DIRS = {
#     "E": (1, 0),
#     "S": (0, 1),
#     "W": (-1, 0),
#     "N": (0, -1)
# }


class SquareLocation(MapLocation):
    # def __init__(self, x, y):
    #     self.coords = (x, y)
    #     # self.coords_num = 2

    def __init__(self, new_coords):
        super().__init__(new_coords)

    def get_x(self):
        return self._coords[0]

    def get_y(self):
        return self._coords[1]

    def __add__(self, other_location):
        return SquareLocation((self.get_x() + other_location.get_x(),
                               self.get_y() + other_location.get_y()))

    def __mul__(self, scale):
        return SquareLocation((self.get_x() * scale,
                               self.get_y() * scale))

    def get_neighbour_location(self, direction, distance=1):
        return self + SQUARE_DIRS[direction] * distance

    def get_location_in_direction(self, direction, distance=1):
        return self + (direction * distance)

    def get_far_neighbour_location(self, direction, distance):
        return self + (SQUARE_DIRS[direction] * distance)


SQUARE_DIRS = [
    SquareLocation((1, 0)),
    SquareLocation((0, 1)),
    SquareLocation((-1, 0)),
    SquareLocation((0, -1))
]


#    NW NE
#   W     E
#    SW SE


# HEX_DIRS = {
#     "E": (1, 0, -1),
#     "SE": (0, 1, -1),
#     "SW": (-1, 1, 0),
#     "W": (-1, 0, 1),
#     "NW": (0, -1, 1),
#     "NE": (1, -1, 0)
# }
# HEX_DIRS = [
#     HexLocation((1, 0, -1)),
#     HexLocation((0, 1, -1)),
#     HexLocation((-1, 1, 0)),
#     HexLocation((-1, 0, 1)),
#     HexLocation((0, -1, 1)),
#     HexLocation((1, -1, 0))
# ]

class HexLocation(MapLocation):
    def __init__(self, coords):
        super().__init__(coords)

    # def __init__(self, q, r):
    #     self.coords = (q, r, -q-r)
    #     self.coords_num = 3

    def get_q(self):
        return self._coords[0]

    def get_r(self):
        return self._coords[1]

    def get_s(self):
        return self._coords[2]

    def __add__(self, other):
        return HexLocation((self.get_q() + other.get_q(),
                            self.get_r() + other.get_r(),
                            self.get_s() + other.get_s()))

    def __mul__(self, scale):
        return HexLocation((self.get_q() * scale,
                            self.get_r() * scale,
                            self.get_s() * scale))

    def get_neighbour_location(self, direction, distance=1):
        return self + HEX_DIRS[direction] * distance


HEX_DIRS = [
    HexLocation((1, 0, -1)),
    HexLocation((0, 1, -1)),
    HexLocation((-1, 1, 0)),
    HexLocation((-1, 0, 1)),
    HexLocation((0, -1, 1)),
    HexLocation((1, -1, 0))
]
