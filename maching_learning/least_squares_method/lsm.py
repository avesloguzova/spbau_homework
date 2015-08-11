__author__ = 'avesloguzova'
import math
import sys

import numpy as np


class Soluton:
    def __init__(self, polynom_coefficients):
        self.polinom = polynom_coefficients

    def degree(self):
        return len(self.polinom)

    def test(self, test_x, test_y):
        value_y = [self.value(x) for x in test_x]
        return sum([(test - value) ** 2 for (test, value) in zip(test_y, value_y)])

    def standard_deviation(self, test_x, test_y):
        error = self.test(test_x, test_y)
        return math.sqrt((1.0 / (len(test_y) - len(self.polinom))) * error)

    def __str__(self):
        return "degree =" + str(self.degree()) + "\n Polynom: \n" + str(self.polinom)

    def value(self, x):
        result = 0
        for i in range(len(self.polinom)):
            result += self.polinom[i] * (x ** i)
        return result


def read_data(filename):
    x = []
    y = []
    with open(filename) as file:
        for line in file:
            data = line.split()
            x.append(float(data[0]))
            y.append(float(data[1]))
    return x, y


def get_matrix(degree, learn_x):
    result = [get_coefficients(i, degree, learn_x) for i in range(degree)]
    return np.array(result)


def get_coefficients(equation_number, degree, learn_x):
    result = []
    for j in range(degree):
        result.append(2 * sum([x ** (equation_number + j) for x in learn_x]))
    return result


def get_dependent_value(degree, learn_x, learn_y):
    return np.array(
        [2 * sum([y * x for (x, y) in zip(learn_y, [px ** i for px in learn_x])]) for i in range(degree)])


def solve(matrix, value):
    return Soluton(np.linalg.solve(matrix, value))


def find_best_solution(learn_x, learn_y, test_x, test_y):
    current_degree = 0
    current_solve = None
    new_solve = None
    current_sd = 99999999999.0
    new_sd = current_sd - 1
    while current_sd > new_sd:
        current_degree += 1
        current_solve = new_solve
        current_sd = new_sd
        new_solve = solve(get_matrix(current_degree + 1, learn_x),
                          get_dependent_value(current_degree + 1, learn_x, learn_y))
        new_sd = new_solve.standard_deviation(test_x, test_y)
    return current_solve, current_sd


def main(learn_file, test_file):
    learn_x, learn_y = read_data(learn_file)
    test_x, test_y = read_data(test_file)
    best_solve, sd = find_best_solution(learn_x, learn_y, test_x, test_y)
    print(best_solve)
    print("standard deviation:")
    print(sd)
    print("error:")
    print(best_solve.test(test_x, test_y))


if __name__ == '__main__':
    if len(sys.argv) == 3:
        main(sys.argv[1], sys.argv[2])
    else:
        print("Usage: ./lcm.py <learn_file> <test_file>")
