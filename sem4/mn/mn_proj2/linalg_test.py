import unittest

from linalg import *


class TestFlatMatrix(unittest.TestCase):
    def test_init(self):
        m = zeros((2, 3))
        self.assertEqual(m.rows(), 2)
        self.assertEqual(m.cols(), 3)
        self.assertEqual(m.data[0], [0, 0, 0]) #TODO: test 

    def test_str(self):
        m = zeros((2, 3))
        self.assertEqual(str(m), '[0, 0, 0]\n[0, 0, 0]')

    def test_eq(self):
        m1 = FlatMatrix((2, 2), 1)
        m2 = FlatMatrix((2, 2), 1)
        self.assertEqual(m1, m2)

    def test_neq(self):
        m1 = FlatMatrix((2, 2), 1)
        m2 = FlatMatrix((2, 2), 2)
        self.assertNotEqual(m1, m2)

    def test_shallow_copy(self):
        m = FlatMatrix((2, 2), 1)
        m2 = m.copy()
        m2[0][0] = 2
        self.assertNotEqual(m, m2)

    def test_len(self):
        m = FlatMatrix((2, 2), 1)
        self.assertEqual(len(m), 4)

    def test_iter(self):
        m = FlatMatrix((2, 2), 1)
        self.assertEqual(list(m), [1, 1, 1, 1])

    def test_repr(self):
        m = FlatMatrix((2, 2), 1)
        self.assertEqual(repr(m), 'FlatMatrix((2, 2), [[1, 1], [1, 1]])')

    def test_add(self):
        m1 = FlatMatrix((2, 2), 1)
        m2 = FlatMatrix((2, 2), 2)
        m3 = m1 + m2
        self.assertEqual(m3, FlatMatrix((2, 2), 3))

    def test_sub(self):
        m1 = FlatMatrix((2, 2), 1)
        m2 = FlatMatrix((2, 2), 2)
        m3 = m1 - m2
        self.assertEqual(m3, FlatMatrix((2, 2), -1))

    def test_scalar_mul(self):
        m = FlatMatrix((2, 2), 1)
        m2 = m * 2
        self.assertEqual(m2, FlatMatrix((2, 2), 2))

    def test_scalar_div(self):
        m = FlatMatrix((2, 2), 2)
        m2 = m / 2
        self.assertEqual(m2, FlatMatrix((2, 2), 1))

    def test_matmul_as_mul(self):
        m1 = FlatMatrix((2, 2), 1)
        m2 = FlatMatrix((2, 2), 2)
        m3 = m1 * m2
        self.assertEqual(m3, FlatMatrix((2, 2), 4))

    def test_matmul(self):
        m1 = FlatMatrix((2, 2), 1)
        m2 = FlatMatrix((2, 2), 2)
        m3 = m1 @ m2
        self.assertEqual(m3, FlatMatrix((2, 2), 4))

    def test_negation(self):
        m = FlatMatrix((2, 2), 1)
        m2 = -m
        self.assertEqual(m2, FlatMatrix((2, 2), -1))

    def test_transpose(self):
        m = FlatMatrix((2, 3), 1)
        m2 = m.transpose()
        self.assertEqual(m2, FlatMatrix((3, 2), 1))

    def test_transpose_shortcut(self):
        m = FlatMatrix((2, 3), 1)
        m2 = m.t()
        self.assertEqual(m2, FlatMatrix((3, 2), 1))

    def test_mod(self):
        m = FlatMatrix((2, 2), 5)
        m2 = m % 2
        self.assertEqual(m2, FlatMatrix((2, 2), 1))

    def test_floordiv(self):
        m = FlatMatrix((2, 2), 3)
        m2 = m // 2
        self.assertEqual(m2, FlatMatrix((2, 2), 1))

    def test_truediv(self):
        m = FlatMatrix((2, 2), 3.0)
        m2 = m / 2
        self.assertEqual(m2, FlatMatrix((2, 2), 1.5))

    def test_euclidean_norm(self):
        m = FlatMatrix((2, 2), 2)
        self.assertEqual(m.euclidean_norm(), 4)

    def test_diagflat(self):
        m = FlatMatrix((2, 2), 2)
        self.assertEqual(m.diagflat(), [2, 2])

    def test_diag(self):
        m = FlatMatrix((2, 2), 2)
        m2 = m.diag()
        self.assertEqual(m2.shape, (2, 1))
        self.assertEqual(m2, FlatMatrix((2, 1), 2))

    def test_zeros(self):
        m = zeros((2, 2))
        self.assertEqual(m, FlatMatrix((2, 2), 0))

    def test_ones(self):
        m = ones((2, 2))
        self.assertEqual(m, FlatMatrix((2, 2), 1))

    def test_eye(self):
        m = eye(2)
        self.assertEqual(m, FlatMatrix((2, 2), [[1, 0], [0, 1]]))

    def test_column(self):
        m = column(2)
        self.assertEqual(m, FlatMatrix((2, 1), [[0], [0]]))

    def test_row(self):
        m = row(2)
        self.assertEqual(m, FlatMatrix((1, 2), [[0, 0]]))

    def test_square(self):
        m = square(2)
        self.assertEqual(m, FlatMatrix((2, 2), [[0, 0], [0, 0]]))

    def test_diagonal_from_list(self):
        m = diagonal([1, 2, 3])
        self.assertEqual(m, FlatMatrix((3, 3), [[1, 0, 0], [0, 2, 0], [0, 0, 3]]))

    def test_diagonal_from_FlatMatrix(self):
        m = FlatMatrix((3, 3), [[1, 4, 4], [4, 2, 4], [4, 4, 3]])
        m2 = diagonal(m)
        self.assertEqual(m2, FlatMatrix((3, 3), [[1, 0, 0], [0, 2, 0], [0, 0, 3]]))

    def test_triu_basic(self):
        m = FlatMatrix((3, 3), [[1, 2, 3], [4, 5, 6], [7, 8, 9]])
        m2 = m.triu()
        self.assertEqual(m2, FlatMatrix((3,3), [[1, 2, 3], [0, 5, 6], [0, 0, 9]]))

    def test_triu_offset(self):
        m = FlatMatrix((3, 3), [[1, 2, 3], [4, 5, 6], [7, 8, 9]])
        m2 = m.triu(1)
        self.assertEqual(m2, FlatMatrix((3,3), [[0, 2, 3], [0, 0, 6], [0, 0, 0]]))

    def test_tril_basic(self):
        m = FlatMatrix((3, 3), [[1, 2, 3], [4, 5, 6], [7, 8, 9]])
        m2 = m.tril()
        self.assertEqual(m2, FlatMatrix((3,3), [[1, 0, 0], [4, 5, 0], [7, 8, 9]]))

    def test_tril_offset(self):
        m = FlatMatrix((3, 3), [[1, 2, 3], [4, 5, 6], [7, 8, 9]])
        m2 = m.tril(1)
        self.assertEqual(m2, FlatMatrix((3,3), [[0, 0, 0], [4, 0, 0], [7, 8, 0]]))

    def test_diag_invert(self):
        m = diagonal([1.0, 2.0, 3])
        self.assertEqual(m.diag_invert(), FlatMatrix((3, 3), [[1, 0, 0], [0, 0.5, 0], [0, 0, 1/3]]))

    def test_get_row(self):
        m = FlatMatrix((3, 3), [[1, 2, 3], [4, 5, 6], [7, 8, 9]])
        self.assertEqual(m.get_row(1), FlatMatrix((1, 3), [4, 5, 6]))

    def test_get_col(self):
        m = FlatMatrix((3, 3), [[1, 2, 3], [4, 5, 6], [7, 8, 9]])
        self.assertEqual(m.get_col(1), FlatMatrix((3, 1), [2, 5, 8]))

    def test_forward_substitution(self):
        L = FlatMatrix((4, 4), [[1, 0, 0, 0], [2, 1, 0, 0], [3, 1, 1, 0], [1, -1, -1, 1]])
        b = column(4, [7, 11, 31, 15])
        x = forward_substitution(L, b)
        self.assertEqual(x, column(4, [7.0, -3.0, 13.0, 18.0]))

    def test_backward_substitution(self):
        U = FlatMatrix((3, 3), [[1, -2, 1], [0, 1, 6], [0, 0, 1]])
        y = column(3, [4, -1, 2])
        x = backward_substitution(U, y)
        self.assertEqual(x, column(3, [-24.0, -13.0, 2.0]))

    def test_as_list(self):
        m = FlatMatrix((2, 2), [[1, 2], [3, 4]])
        self.assertEqual(m.flatten(), [1, 2, 3, 4])


# TODO: test set_row, set_col, set_item, get_item, get_row, get_col, get_submatrix, set_submatrix, get_diagonal, set_diagonal



if __name__ == '__main__':
    TestFlatMatrix().test_init()
    TestFlatMatrix().test_str()
    TestFlatMatrix().test_eq()
    TestFlatMatrix().test_neq()
    TestFlatMatrix().test_shallow_copy()
    TestFlatMatrix().test_len()
    TestFlatMatrix().test_iter()
    TestFlatMatrix().test_repr()
    TestFlatMatrix().test_add()
    TestFlatMatrix().test_sub()
    TestFlatMatrix().test_scalar_mul()
    TestFlatMatrix().test_scalar_div()
    TestFlatMatrix().test_matmul_as_mul()
    TestFlatMatrix().test_matmul()
    TestFlatMatrix().test_transpose()
    TestFlatMatrix().test_transpose_shortcut()
    TestFlatMatrix().test_mod()
    TestFlatMatrix().test_floordiv()
    TestFlatMatrix().test_euclidean_norm()
    TestFlatMatrix().test_diagflat()
    TestFlatMatrix().test_diag()
    TestFlatMatrix().test_zeros()
    TestFlatMatrix().test_ones()
    TestFlatMatrix().test_eye()
    TestFlatMatrix().test_column()
    TestFlatMatrix().test_row()
    TestFlatMatrix().test_square()
    TestFlatMatrix().test_diagonal_from_list()
    TestFlatMatrix().test_diagonal_from_FlatMatrix()
    TestFlatMatrix().test_triu_basic()
    TestFlatMatrix().test_triu_offset()
    TestFlatMatrix().test_tril_basic()
    TestFlatMatrix().test_tril_offset()
    TestFlatMatrix().test_forward_substitution()
    TestFlatMatrix().test_backward_substitution()
    TestFlatMatrix().test_as_list()
    print('All tests passed')

