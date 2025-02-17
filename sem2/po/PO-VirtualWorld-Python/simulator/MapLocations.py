class MapLocation:
    """
    An abstract class used to represent a singular, atomic location (or 'tile' or 'cell') on a map.
    It creates a common interface for locations in different types of maps (square grid, hexagonal grid etc.).
    As it is abstract, it should not be instantiated directly.
    """

    def __init__(self, new_coords):
        self.coords = new_coords

    @classmethod
    def copyc(cls, other_location):
        """
        Creates a new location object with the same coordinates as the given location.
        """

        location = cls(other_location.coords)

        return location

    def __eq__(self, other):
        if not isinstance(other, MapLocation):
            return False
        return self.coords == other.coords

    def __hash__(self):
        return hash(self.coords)

    def __str__(self):
        """
        Returns a string of coordinates in the form (x, y) or (x, y, z).
        These are the coordinates of the location, respectively on a square grid or a hexagonal grid.
        """

        string_form = "("
        string_form += str(self.coords[0])
        string_form += ", "
        string_form += str(self.coords[1])
        if len(self.coords) > 2:
            string_form += ", "
            string_form += str(self.coords[2])
        string_form += ")"
        return string_form

# The directions for a square grid are defined as follows:
#    N
#   W E
#    S
# The directions are indexed from 0 to 3 in a clockwise manner, starting from the north direction.

class SquareLocation(MapLocation):
    """
    A class used to represent a location on a square grid.
    It is a subclass of MapLocation.
    Uses the two-dimensional coordinates (x, y) of a square grid.

    Methods
    -------
    __add__(other_location):
    __mul__(scale):
        Arithmetic operations allow for easy manipulation of location objects oon the grid.
        eg. location1 + location2 = location3, where location3 is the sum of the coordinates of location1 and location2.
            location1 * 2 = location4, where location4 is the product of the coordinates of location1 and 2.

    get_neighbour_location(direction, distance=1):
        Returns the location of a neighbour of the location in the given direction.
        The distance parameter allows for getting the location of a neighbour at a distance greater than 1.
        eg. A = SquareLocation((0, 0))
            A.get_neighbour_location(0) returns a location equal to SquareLocation((1, 0)) 
            (i.e. the neighbour to the right of A).
    
    """

    def __init__(self, new_coords):
        super().__init__(new_coords)

    def get_x(self):
        return self.coords[0]

    def get_y(self):
        return self.coords[1]

    def __add__(self, other_location):
        return SquareLocation((self.get_x() + other_location.get_x(),
                               self.get_y() + other_location.get_y()))

    def __mul__(self, scale):
        return SquareLocation((self.get_x() * scale,
                               self.get_y() * scale))

    def get_neighbour_location(self, direction, distance=1):
        return self + SQUARE_DIRS[direction] * distance

# These objects are used to represent the directions on a square grid.
# Because of the MapLocation arithmetic getting N(orth) neighbour is the same as adding (0, 1) to the location.
# eg. A = SquareLocation((0, 0))
#     A + SQUARE_DIRS[0] = SquareLocation((0, 1))
SQUARE_DIRS = [
    SquareLocation((1, 0)),
    SquareLocation((0, 1)),
    SquareLocation((-1, 0)),
    SquareLocation((0, -1))
]

# The directions for a hexagon with flat sides on top and bottom are defined as follows:
#    NW NE
#   W     E
#    SW SE
# The directions are indexed from 0 to 5 in a clockwise manner, starting from the NW direction.

class HexLocation(MapLocation):
    """
    A class used to represent a location on a hexagonal grid.
    It is a subclass of MapLocation.
    Uses the three-dimensional coordinates (q, r, s) of a hexagonal grid.

    Methods
    -------
    __add__(other_location):
    __mul__(scale):
        Arithmetic operations allow for easy manipulation of location objects on the grid.
        eg. location1 + location2 = location3, where location3 is the sum of the coordinates of location1 and location2.
            location1 * 2 = location4, where location4 is the product of the coordinates of location1 and 2.

    get_neighbour_location(direction, distance=1):
        Returns the location of a neighbour of the location in the given direction.
        The distance parameter allows for getting the location of a neighbour at a distance greater than 1.
        eg. A = HexLocation((0, 0, 0))
            A.get_neighbour_location(0) returns a location equal to HexLocation((1, 0, -1)) 
            (i.e. the neighbour to the east (right) of A).

    
    """


    def __init__(self, coords):
        super().__init__(coords)

    def get_q(self):
        return self.coords[0]

    def get_r(self):
        return self.coords[1]

    def get_s(self):
        return self.coords[2]

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

# These objects are used to represent the directions on a hexagonal grid.
# Because of the MapLocation arithmetic getting NW(orthwest) neighbour is the same as adding (1, 0, -1) to the location.
# eg. A = HexLocation((0, 0, 0))
#     A + HEX_DIRS[0] = HexLocation((1, 0, -1))
HEX_DIRS = [
    HexLocation((1, 0, -1)),
    HexLocation((0, 1, -1)),
    HexLocation((-1, 1, 0)),
    HexLocation((-1, 0, 1)),
    HexLocation((0, -1, 1)),
    HexLocation((1, -1, 0))
]
