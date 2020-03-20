'''
day 3
'''
from typing import List, Tuple
from dataclasses import dataclass


@dataclass
class Vector:
    tail: Tuple[int, int]
    head: Tuple[int, int]
    current_steps: int = 0
# END CLASS vector


@dataclass
class Tracker:
    wire_1: List[Vector]
    wire_2: List[Vector]
    intersection: Tuple[int, int]
# END CLASS Tracker


def main():
    wires: List[List[str]] = input_puller('example_input.txt')
    wire_1: List[Vector] = get_vectors(wires[0])
    wire_2: List[Vector] = get_vectors(wires[1])

    intersections: List[Tracker] = find_intersections(wire_1, wire_2)
    intersection_points: List[Tuple[int, int]] = [
        intersect.intersection for intersect in intersections
    ]

    distances: List[int] = get_manhattan_distance(intersection_points)

    steps: List[int] = get_steps(intersections)

    with open('log.txt', 'a+', encoding='utf-8') as file:
        for tracker in intersections:
            for vector in tracker.wire_1:
                file.write(str(vector))
                file.write('\n')
            # END INNER FOR

            file.write('\n\n')

            for vector in tracker.wire_2:
                file.write(str(vector))
                file.write('\n')
            # END INNER FOR

            file.write(str(tracker.intersection))
            file.write('\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n')
        # END FOR

    # END WITH
    print(sorted(distances))
    # print((sorted(distances))[0])
    # print((sorted(steps))[0])
    print(sorted(steps))
    # print(intersections)
# END main()


def input_puller(file_name: str) -> List[List[str]]:
    raw_input: List[str] = []
    wires: List[List[str]] = []

    with open(file_name, 'r', encoding='utf-8') as file:
        raw_input = file.read().splitlines()

        wires = [wire.split(',') for wire in raw_input]
        # END FOR
    # END WITH

    return wires
# END input_puller


def get_vectors(wire: List[str]) -> List[Vector]:
    vectors: List[Vector] = [Vector((0, 0), (0, 0))]
    direction: str
    prev_vector: Tuple[int, int]
    next_vector: Tuple[int, int]

    for direction in wire:
        prev_vector = (vectors[-1])
        next_vector = create_vector(prev_vector, direction)
        vectors.append(next_vector)
    # END FOR

    return vectors
# END create_directions()


def create_vector(prev_vector: Vector, direction: str) -> Vector:
    curr_direction = list(direction)
    next_vector: Vector
    next_direction: str = curr_direction.pop(0)

    steps: int = int(''.join(curr_direction))

    if next_direction == 'R':

        next_vector = Vector(
            (
                prev_vector.head[0],
                prev_vector.head[1]
            ),
            (
                prev_vector.head[0] + steps,
                prev_vector.head[1]
            ),
            prev_vector.current_steps + steps
        )
    elif next_direction == 'L':
        next_vector = Vector(
            (
                prev_vector.head[0],
                prev_vector.head[1]
            ),
            (
                prev_vector.head[0] - steps,
                prev_vector.head[1]
            ),
            prev_vector.current_steps + steps
        )
    elif next_direction == 'U':
        next_vector = Vector(
            (
                prev_vector.head[0],
                prev_vector.head[1]
            ),
            (
                prev_vector.head[0],
                prev_vector.head[1] + steps
            ),
            prev_vector.current_steps + steps
        )
    elif next_direction == 'D':
        next_vector = Vector(
            (
                prev_vector.head[0],
                prev_vector.head[1]
            ),
            (
                prev_vector.head[0],
                prev_vector.head[1] - steps
            ),
            prev_vector.current_steps + steps
        )
    else:
        print(f'ERROR: In create_vector, no direction {direction[0]}')
    # END IF

    return next_vector
# END create_vector()


def find_intersections(
    wire_1: List[Vector],
    wire_2: List[Vector]
) -> List[Tracker]:
    tracked_paths: List[Tracker] = []
    wire_1_path: List[Vector] = []
    wire_2_path: List[Vector] = []

    intersection: Tuple[int, int]

    horizontal: Vector
    vertical: Vector

    vector_index_1: int
    vector_index_2: int

    for vector_1 in wire_1:
        for vector_2 in wire_2:
            horizontal = find_horizontal(vector_1, vector_2)
            vertical = find_vertical(vector_1, vector_2)

            if check_intersect(horizontal, vertical) == True:
                intersection = get_intersection(horizontal, vertical)

                vector_index_1 = wire_1.index(vector_1) + 1
                vector_index_2 = wire_2.index(vector_2) + 1

                wire_1_path = wire_1[:vector_index_1]
                wire_2_path = wire_2[:vector_index_2]

                tracker = Tracker(
                    wire_1_path,
                    wire_2_path,
                    intersection
                )

                tracked_paths.append(tracker)
            # END INNER IF
        # END INNER FOR
    # END FOR

    return tracked_paths
# END find_intersections


def find_vertical(wire_1: Vector, wire_2: Vector) -> Vector:
    x11: int = wire_1.tail[0]
    x12: int = wire_1.head[0]
    x21: int = wire_2.tail[0]
    x22: int = wire_2.head[0]

    if x11 == x12:
        return wire_1
    else:
        return wire_2
# END find_horizontal()


def find_horizontal(wire_1: Vector, wire_2: Vector) -> Vector:
    y11: int = wire_1.tail[1]
    y12: int = wire_1.head[1]
    y21: int = wire_2.tail[1]
    y22: int = wire_2.head[1]

    if y11 == y12:
        return wire_1
    else:
        return wire_2
# END find_horizontal()


def check_intersect(horizontal: Vector, vertical: Vector) -> bool:
    x_range: List[int]
    y_range: List[int]

    hx1: int = horizontal.tail[0]
    hx2: int = horizontal.head[0]
    hy1: int = horizontal.tail[1]
    hy2: int = horizontal.head[1]

    vx1: int = vertical.tail[0]
    vx2: int = vertical.head[0]
    vy1: int = vertical.tail[1]
    vy2: int = vertical.head[1]

    smallest: int
    biggest: int

    if hx1 < hx2:
        smallest = hx1
        biggest = hx2
    else:
        smallest = hx2
        biggest = hx1
    # END IF

    x_range = [i for i in range(smallest + 1, biggest - 1)]

    if vy1 < vy2:
        smallest = vy1
        biggest = vy2
    else:
        smallest = vy2
        biggest = vy1
    # END IF

    y_range = [i for i in range(smallest + 1, biggest - 1)]

    if vx1 in x_range and hy1 in y_range:
        return True
    # END IF

    return False
# END get_intersection


def get_intersection(horizontal: Vector, vertical: Vector) -> Tuple[int, int]:
    intersection: Tuple[int, int]

    intersection = (
        vertical.head[0],
        horizontal.head[1]
    )

    return intersection
# END get_intersection()


def get_manhattan_distance(vectors: List[Tuple[int, int]]) -> List[int]:
    distances: List[int] = []
    temp_distance: int

    for vector in vectors:
        temp_distance = (abs(0 - vector[0]) + abs(0 - vector[1]))
        distances.append(temp_distance)
    # END FOR

    return distances
# END get_manhattan_distance()


def get_steps(intersections: List[Tracker]) -> List[int]:
    steps: List[int] = []
    total_steps: int

    for tracker in intersections:
        total_steps = calculate_steps(tracker)
        steps.append(total_steps)
    # END FOR

    return steps
# END get_steps()


def calculate_steps(tracker: Tracker) -> int:
    hx1: int = tracker.wire_1[-1].head[0]
    hx2: int = tracker.intersection[0]
    hy1: int = tracker.wire_1[-1].head[1]
    hy2: int = tracker.intersection[1]

    vx1: int = tracker.wire_2[-1].head[0]
    vx2: int = tracker.intersection[0]
    vy1: int = tracker.wire_2[-1].head[1]
    vy2: int = tracker.intersection[1]

    wire_1_steps: int
    wire_2_steps: int

    if hx1 == hx2:
        '''vertical distance'''
        if hy1 < 0 or hy2 < 0:
            wire_1_steps = abs(hy1) + abs(hy2)
        elif hy1 < 0 and hy2 < 0:
            wire_1_steps = abs(abs(hy1) + hy2)
        else:
            wire_1_steps = abs(hy1 - hy2)
        # END INNER IF
    else:
        '''horizontal distance'''
        if hx1 < 0 or hx2 < 0:
            wire_1_steps = abs(hx1) + abs(hx2)
        elif hy1 < 0 and hy2 < 0:
            wire_1_steps = abs(abs(hx1) + hx2)
        else:
            wire_1_steps = abs(hx1 - hx2)
        # END INNER IF
    # END IF

    wire_1_steps += tracker.wire_1[-1].current_steps

    if vx1 == vx2:
        '''vertical distance'''
        if vy1 < 0 or vy2 < 0:
            wire_2_steps = abs(vy1) + abs(vy2)
        elif vy1 < 0 and vy2 < 0:
            wire_2_steps = abs(abs(vy1) + vy2)
        else:
            wire_2_steps = abs(vy1 - vy2)
        # END INNER IF
    else:
        '''horizontal distance'''
        if vx1 < 0 or vx2 < 0:
            wire_2_steps = abs(vx1) + abs(vx2)
        elif vy1 < 0 and vy2 < 0:
            wire_2_steps = abs(abs(vx1) + vx2)
        else:
            wire_2_steps = abs(vx1 - vx2)
        # END INNER IF
    # END IF

    wire_2_steps += tracker.wire_2[-1].current_steps

    return wire_1_steps + wire_2_steps
# END calculate_steps()


if __name__ == '__main__':
    main()
# END IF
