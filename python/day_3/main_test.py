import unittest
import main as test


class MainTest(unittest.TestCase):
    '''
    test_vector_r = test.Vector((0, 0), (123, 0))
    test_vector_l = test.Vector((0, 0), (-123, 0))
    test_vector_u = test.Vector((0, 0), (0, 123))
    test_vector_d = test.Vector((0, 0), (0, -123))

    test_wire = ['R123', 'U123', 'R123']

    test_list_vectors = [
        test.Vector((0, 0), (0, 0)),
        test.Vector((0, 0), (123, 0)),
        test.Vector((123, 0), (123, 123)),
        test.Vector((123, 123), (246, 123)),
    ]

    test_wire_1 = [
        test.Vector((0, 0), (123, 0)),
        test.Vector((123, 0), (123, 123)),
        test.Vector((123, 123), (246, 123)),
    ]

    test_wire_2 = [
        test.Vector((0, 0), (0, 123)),
        test.Vector((0, 123), (50, 123)),
        test.Vector((50, 123), (50, -123))
    ]

    test_list_intersections = [(50, 0)]

    def test_create_vector_r(self):
        self.assertEqual(test.create_vector(
            (0, 0), 'R123'), self.test_vector_r)
    # END test_create_vector_r()

    def test_create_vector_l(self):
        self.assertEqual(test.create_vector(
            (0, 0), 'L123'), self.test_vector_l)
    # END test_create_vector_l()

    def test_create_vector_u(self):
        self.assertEqual(test.create_vector(
            (0, 0), 'U123'), self.test_vector_u)
    # END test_create_vector_u()

    def test_create_vector_d(self):
        self.assertEqual(test.create_vector(
            (0, 0), 'D123'), self.test_vector_d)
    # END test_create_vector_d()

    def test_get_vectors(self):
        self.assertEqual(
            test.get_vectors(self.test_wire),
            self.test_list_vectors
        )
    # END test_get_vectors()

    def test_find_horizontal(self):
        self.assertEqual(
            test.find_horizontal(
                test.Vector((0, 0), (123, 0)),
                test.Vector((50, 123), (50, -123))
            ),
            test.Vector((0, 0), (123, 0))
        )
    # END test_find_horizontal()

    def test_find_vertical(self):
        self.assertEqual(
            test.find_vertical(
                test.Vector((0, 0), (123, 0)),
                test.Vector((50, 123), (50, -123))
            ),
            test.Vector((50, 123), (50, -123))
        )
    # END test_find_vertical()

    def test_check_intersect(self):
        self.assertEqual(
            test.check_intersect(
                test.Vector((0, 0), (123, 0)),
                test.Vector((50, 123), (50, -123))
            ),
            True
        )
    # END test_check_intersect()

    def test_check_intersect_h(self):
        self.assertEqual(
            test.check_intersect(
                test.Vector((123, 123), (236, 123)),
                test.Vector((123, 572), (236, 572))
            ),
            False
        )
    # END test_check_intersect()

    def test_check_intersect_same(self):
        self.assertEqual(
            test.check_intersect(
                test.Vector((0, 0), (123, 0)),
                test.Vector((0, 0), (0, 123))
            ),
            False
        )
    # END test_check_intersect_same()

    def test_get_intersection(self):
        self.assertEqual(
            test.get_intersection(
                test.Vector((0, 0), (123, 0)),
                test.Vector((50, 123), (50, -123))
            ),
            (50, 0)
        )
    # END test_get_intersection()

    def test_find_intersections(self):
        self.assertEqual(
            test.find_intersections(
                [
                    test.Vector((0, 0), (123, 0)),
                    test.Vector((123, 0), (123, 123)),
                    test.Vector((123, 123), (246, 123)),
                ],
                [

                    test.Vector((0, 0), (0, 123)),
                    test.Vector((0, 123), (50, 123)),
                    test.Vector((50, 123), (50, -123))
                ]
            ),
            self.test_list_intersections
        )
    # END test_find_intersections()

    def test_get_manhattan_distance(self):
        self.assertEqual(
            test.get_manhattan_distance(
                [(123, 123)]
            ),
            [246]
        )
    # END test_get_manhattan_distance
    '''

    def test_calculate_steps(self):
        self.assertEqual(
            test.calculate_steps(
                test.Tracker(
                    [
                        test.Vector((0, 0), (0, 0), 0),
                    ],
                    [
                        test.Vector((0, 0), (0, 0), 0),
                        test.Vector((0, 0), (0, 123), 123),
                        test.Vector((0, 123), (50, 123), 173),
                    ],
                    (50, 0)
                )
            ),
            (50 + (123 + 50 + 123))
        )
    # END test_calculate_steps()

# END CLASS MainTest


if __name__ == "__main__":
    unittest.main()
