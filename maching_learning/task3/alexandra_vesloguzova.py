__author__ = 'av'
import numpy


def read_fasta(path):
    records = list()
    current_long_string = ""
    current_id = ""
    with open(path, 'r') as f:
        for line in f:
            if is_id(line):
                records.append(tuple({current_id, current_long_string}))
                current_id = line
                current_long_string = ""
            else:
                current_long_string += line

    return records


def is_id(line):
    return line[0] == ">"


def get_substring(s, n):
    result = dict()
    for i in range(0, len(s) - n - 1):
        tmp = s[i:i + n]
        if result.get(tmp):
            result[tmp] += 1
        else:
            result[tmp] = 1
    return result


def intersection(multiset1, multiset2):
    result = dict()
    for s, count in multiset1:
        if multiset2.get(s):
            result[s] = min(multiset1[s], multiset2[s])
    return result


def union(multiset1, multiset2):
    result = dict(multiset1)
    for s, count in multiset2:
        if result.get(s):
            result[s] += count
        else:
            result[s] = count
    return result


def jaccard(s, t, n):
    substr_s = get_substring(s, n)
    substr_t = get_substring(t, n)
    return 1 - len(intersection(substr_s, substr_t)) / len(union(substr_s, substr_t))


def levenshtein(s, t):
    if len(s) < len(t):
        return levenshtein(t, s)
    if len(t) == 0:
        return len(s)
    s = numpy.array(tuple(s))
    t = numpy.array(tuple(t))
    previous_row = numpy.arange(t.size + 1)
    for symbol in s:
        current_row = previous_row + 1
        current_row[1:] = numpy.minimum(current_row[1:], numpy.add(previous_row[:-1], t != symbol))
        current_row[1:] = numpy.minimum(current_row[1:], current_row[0:-1] + 1)
        previous_row = current_row
    return previous_row[-1]


def find_min(distances, C):
    pass


def lance_williams(X, dist):
    n = len(X)
    Z = numpy.zeros(n - 1, 3)
    C = list(range(1, len(X)))
    distances = numpy.zeros(2 * n - 1, 2 * n - 1)
    for i in range(0, len(X)):
        for j in range(0, len(X)):
            if i != j:
                distances[i][j] = dist(X[i][1], X[j][1])
    for t in range(2,len(X)):
        i,j = find_min(distances,C)

    # ...
    return Z


def show_dendrogram(Z, **kwargs):
    from scipy.cluster.hierarchy import dendrogram, from_mlab_linkage
    from matplotlib import pyplot as plt

    dendrogram(from_mlab_linkage(Z), **kwargs)
    plt.show()