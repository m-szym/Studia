# TODO matrix and vector indexing - halted

class FlatMatrix:
    """
    Matrix class with basic matrix operations
    Currently only 2D matrices (and vectors as 2D matrices) are supported
    """
    def __init__(self, shape, init):
        self.shape = shape

        if isinstance(init, (int, float)):
            # Initialize 2D matrix with a scalar
            # self.data = [[init] * self.shape[1] for _ in range(self.shape[0])]
            self.data = [[init] * shape[1] for _ in range(shape[0])]

        elif isinstance(init, list):
            if isinstance(init[0], (int, float)):
                # Initialize 2D matrix with a list of scalars
                if len(init) != self.shape[0] and len(init) != self.shape[1]:
                    raise ValueError("Matrix dimensions must match")
                if not all(isinstance(x, (int, float)) for x in init):
                    raise ValueError("Matrix elements must be of type int or float")
                
                if shape[0] == 1:
                    self.data = [init.copy()]
                elif shape[1] == 1:
                    self.data = [[x] for x in init]

            elif isinstance(init[0], list):
                # Initialize 2D matrix with a list of lists
                if len(init) != self.shape[0] or len(init[0]) != self.shape[1]:
                    raise ValueError("Matrix dimensions must match")
                if not isinstance(init[0][0], (int, float)):
                    raise ValueError("Matrix elements must be of type int or float")
                
                self.data = [init[i].copy() for i in range(self.shape[0])]
            else:
                raise ValueError("Can't initialize matrix with this type")

        else:
            raise ValueError("Can't initialize matrix with this type")

    def rows(self):
        """Number of rows in a matrix"""
        return self.shape[0]

    def cols(self):
        """Number of columns in a matrix"""
        return self.shape[1]

    def copy(self):
        """Copy of a matrix"""
        # return FlatMatrix(self.shape, self.data)
        return FlatMatrix(self.shape, self.data.copy())

    def do_on_elements(self, func):
        """
        Apply a function to all elements of a matrix
        the function must take 1 int or float argument 
        and return an int or float into the matrix
        """
        for i in range(self.rows()):
            for j in range(self.cols()):
                self.data[i][j] = func(self.data[i][j])

    def __iter__(self):
        """Iterate over all elements of a matrix"""
        for i in range(self.rows()):
            for j in range(self.cols()):
                yield self.data[i][j]

    def __len__(self):
        """Number of elements in a matrix"""
        return self.shape[0] * self.shape[1]

    def __str__(self):
        return '\n'.join([' '.join([str(row)]) for row in self.data])

    def __repr__(self):
        return f'FlatMatrix({self.shape}, {self.data})'

    def __eq__(self, other):
        if not isinstance(other, FlatMatrix):
            return False
        if self.shape != other.shape:
            return False
        return self.data == other.data

    def __ne__(self, other):
        return not self == other

    def __getitem__(self, item):        # TODO: implement slicing and indexing
        return self.data[item]

    def __setitem__(self, key, value):  # TODO: implement slicing and indexing
        self.data[key] = value

    def __add__(self, other):
        """Elementwise addition by a scalar or matrix addition of two matrices"""
        if isinstance(other, FlatMatrix):
            if self.shape != other.shape:
                raise ValueError("Matrix dimensions must match")
            result = zeros(self.shape)
            for i in range(self.rows()):
                for j in range(self.cols()):
                    result[i][j] = self[i][j] + other[i][j]
            return result
        
        elif isinstance(other, (int, float)):
            result = self.copy()
            result.do_on_elements(lambda x: x + other)
            return result
        
        else:
            return NotImplemented

    def __sub__(self, other):
        """Elementwise subtraction by a scalar or matrix subtraction of two matrices"""
        if isinstance(other, FlatMatrix):
            if self.shape != other.shape:
                raise ValueError("Matrix dimensions must match")
            result = zeros(self.shape)
            for i in range(self.rows()):
                for j in range(self.cols()):
                    result[i][j] = self[i][j] - other[i][j]
            return result
        
        elif isinstance(other, (int, float)):
            result = self.copy()
            result.do_on_elements(lambda x: x - other)

            return result
        else:
            return NotImplemented

    def __mul__(self, other):
        """Matrix multiplication by a scalar or matrix multiplication of two matrices"""
        if isinstance(other, FlatMatrix):
            if self.cols() != other.rows():
                raise ValueError("Matrix dimensions must match")
            result = zeros(self.shape)
            for i in range(self.rows()):
                for j in range(other.cols()):
                    for k in range(self.cols()):
                        result[i][j] += self[i][k] * other[k][j]
            return result
        
        elif isinstance(other, (int, float)):
            result = self.copy()
            result.do_on_elements(lambda x: x * other)
            return result
        
        else:
            return NotImplemented

    def __neg__(self):
        """Negation of a matrix (ie. multiplication by -1)"""
        result = self.copy()
        result.do_on_elements(lambda x: -x)
        return result

    def __matmul__(self, other):
        """Explicit matrix multiplication of two matrices"""
        if isinstance(other, FlatMatrix):
            if self.cols() != other.rows():
                raise ValueError("Matrix dimensions must match")
            result = zeros((self.rows(), other.cols()))
            for i in range(self.rows()):
                for j in range(other.cols()):
                    for k in range(self.cols()):
                        result[i][j] += self[i][k] * other[k][j]
            return result

    def __truediv__(self, other):
        """Elementwise division of a matrix by a scalar"""
        if isinstance(other, (int, float)):
            result = self.copy()
            result.do_on_elements(lambda x: x / other)
            return result
        else:
            return NotImplemented

    def __floordiv__(self, other):
        """Elementwise floor-division of a matrix by a scalar"""
        if isinstance(other, (int, float)):
            result = self.copy()
            result.do_on_elements(lambda x: x // other)
            return result
        else:
            return NotImplemented

    def __mod__(self, other):
        """Elementwise modulo of a matrix by a scalar"""
        if isinstance(other, (int, float)):
            result = self.copy()
            result.do_on_elements(lambda x: x % other)
            return result
        else:
            return NotImplemented

    def transpose(self):
        """Transpose of a matrix"""
        result = zeros(self.shape[::-1])
        for i in range(self.rows()):
            for j in range(self.cols()):
                result[j][i] = self[i][j]
        return result

    def t(self):
        """Shortcut for transpose"""
        return self.transpose()

    def euclidean_norm(self):
        """Euclidean norm of a matrix"""
        return sum([sum([x ** 2 for x in row]) for row in self.data]) ** 0.5

    def inverse(self):
        """
        DO NOT INVERT MATRICES
        For diagonal matrices used .diag_invert()
        For other types Gauss-Jordan elimination is used
        """
        if self.rows() != self.cols():
            raise ValueError("Matrix must be square")

        n = self.rows()
        a = self.copy()
        b = eye(n)
        for i in range(n):
            for j in range(n):
                if i != j:
                    ratio = a[j][i] / a[i][i]
                    for k in range(n):
                        a[j][k] -= ratio * a[i][k]
                        b[j][k] -= ratio * b[i][k]
        for i in range(n):
            ratio = a[i][i]
            for j in range(n):
                a[i][j] /= ratio
                b[i][j] /= ratio
        return b

    def i(self):
        """Shortcut for inverse"""
        return self.inverse()

    def diagflat(self):
        """Diagonal of a matrix as list"""
        diagflat = []
        for i in range(self.rows()):
            diagflat.append(self[i][i])
        return diagflat

    def diag(self):
        """Diagonal of a matrix as a column vector"""
        diag = column(self.rows())
        for i in range(self.rows()):
            diag[i][0] = self[i][i]
        return diag

    def triu(self, offest=0):
        """
        Upper triangular part of a matrix offest is the offset 
        of the upper diagonal of triu from the main diagonal
        """
        if self.rows() != self.cols():
            raise ValueError("Matrix must be square")
        result = zeros(self.shape)
        for i in range(self.rows()):
            for j in range(i + offest, self.cols()):
                result[i][j] = self[i][j]
        return result

    def tril(self, offest=0):
        """
        Lower triangular part of a matrix offest is the offset
        of the lower diagonal of tril from the main diagonal
        """
        if self.rows() != self.cols():
            raise ValueError("Matrix must be square")
        result = zeros(self.shape)
        for i in range(self.rows()):
            for j in range(i - offest + 1):
                result[i][j] = self[i][j]
        return result

    def get_row(self, i):
        """Get i-th row of a matrix as a row vector"""
        return FlatMatrix((1, self.cols()), self[i])
    
    def get_row_as_list(self, i):
        """Get i-th row of a matrix as a list"""
        return self[i]

    def set_row(self, i, row):
        """Set i-th row of a matrix to given row vector or list"""
        if isinstance(row, FlatMatrix):
            self[i] = row[0]
        else:
            raise ValueError("Row must be a FlatMatrix")

    def get_col(self, j):
        """Get j-th column of a matrix as a column vector"""
        return FlatMatrix((self.rows(), 1), [self[i][j] for i in range(self.rows())])
    
    def get_col_as_list(self, j):
        """Get j-th column of a matrix as a list"""
        return [self[i][j] for i in range(self.rows())]

    def set_col(self, j, col):
        """Set j-th column of a matrix to given column vector or list"""
        if isinstance(col, FlatMatrix):
            for i, e in enumerate(col):
                self[i][j] = e
        else:
            for i in range(self.rows()):
                self[i][j] = col[i]

    def flatten(self):
        """Matrix as a list of elements in row-major order"""
        list_form = []
        for i in range(self.rows()):
            list_form.extend(self[i])
        return list_form
    
    def diag_invert(self):
        """
        Invert diagonal elements of a matrix
        ie. inverse of a diagonal matrix
        """
        return diagonal([1 / self.data[i][i] for i in range(self.rows())])


def square(n, init=0):
    """Square matrix of size n x n with all elements initialized to init"""
    return FlatMatrix((n, n), init)


def column(n, init=0):
    """Column matrix of size n x 1 with all elements initialized to init"""
    return FlatMatrix((n, 1), init)


def row(n, init=0):
    """Row vector of size 1 x n with all elements initialized to init"""
    return FlatMatrix((1, n), init)


def zeros(shape):
    """Matrix of size rows x cols with all elements initialized to 0"""
    return FlatMatrix(shape, 0)


def ones(shape):
    """Matrix of size rows x cols with all elements initialized to 1"""
    return FlatMatrix(shape, 1)


def eye(n):
    """Identity matrix of size n x n"""
    m = zeros((n, n))
    for i in range(n):
        m[i][i] = 1
    return m


def diagonal(v):
    """
    Diagonal matrix with vector v as diagonal
    v can be a list or a column vector
    """
    if isinstance(v, FlatMatrix):
        tmp = []
        tmp.extend(v.diagflat())
        v = tmp
        # v = list(map(lambda x: x[0], v.diagflat()))
        # v = v.flatten()

    n = len(v)
    m = zeros((n, n))
    for i in range(n):
        m[i][i] = v[i]
    return m


def dot(a, b):
    """Dot product of two matrices"""
    return a @ b


def forward_substitution(L, b):
    """
    Perform forward substitution on a lower triangular matrix L
    and a column vector b
    """
    n = L.rows()
    x = column(b.rows(), init=0)

    for i in range(n):
        a = L.get_row(i) @ x
        x[i][0] = (b[i][0] - a[0][0]) / L[i][i]

    return x


def backward_substitution(U, y):
    """
    Perform backward substitution on an upper triangular matrix U
    and a column vector y
    """
    n = U.rows()
    x = column(y.rows(), init=0)

    for i in range(n-1, -1, -1):
        a = U.get_row(i) @ x
        x[i][0] = (y[i][0] - a[0][0]) / U[i][i]

    return x
