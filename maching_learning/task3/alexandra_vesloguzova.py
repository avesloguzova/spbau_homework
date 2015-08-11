__author__ = 'av'
import numpy


def read_fasta(path):
    records = list()
    labels = list()
    current_long_string = ""
    current_id = ""
    with open(path, 'r') as f:
        for line in f:
            if is_id(line):
                if current_long_string != "":
                    records.append(current_long_string)
                    labels.append(current_id)
                current_id = line
                current_long_string = ""
            else:
                current_long_string += line.replace("\n", "")

    return (records, labels)


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
    for s, count in multiset1.iteritems():
        if multiset2.get(s):
            result[s] = min(multiset1[s], multiset2[s])
    return result


def union(multiset1, multiset2):
    result = dict(multiset1)
    for s, count in multiset2.iteritems():
        if result.get(s):
            result[s] += count
        else:
            result[s] = count
    return result


def jaccard(s, t, n):
    substr_s = get_substring(s, n)
    substr_t = get_substring(t, n)
    return 1.0 - float(sum(intersection(substr_s, substr_t).values())) / float(sum(union(substr_s, substr_t).values()))


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
    min_dist = numpy.inf
    min_ind = (-1, -1)
    for i in C:
        for j in C:
            if distances[i][j] < min_dist:
                min_dist = distances[i][j]
                min_ind = (i, j)
    return min_ind


def lance_williams(X, dist):
    n = len(X)
    Z = numpy.zeros((n - 1, 3))
    clusters = list(range(0, n))
    distances = numpy.zeros((2 * n - 1, 2 * n - 1))
    cluster_sizes = numpy.zeros((2 * n - 1, 1))
    for i in range(0, len(X)):
        cluster_sizes[i] = 1
        for j in range(0, len(X)):
            if i != j:
                distances[i, j] = dist(X[i], X[j])
            else:
                distances[i, j] = numpy.inf
    for t in range(0, len(X) - 1):
        i, j = find_min(distances, clusters)
        Z[t, 0] = i + 1
        Z[t, 1] = j + 1
        Z[t, 2] = distances[i, j]
        clusters.remove(i)
        clusters.remove(j)
        cluster = n + t
        clusters.append(cluster)
        cluster_sizes[n + t] = cluster_sizes[i] + cluster_sizes[j]
        for ind in clusters:
            if ind != cluster:
                distances[cluster, ind] = distances[i, ind] * (cluster_sizes[i] / (cluster_sizes[cluster])) + \
                                          distances[j, ind] * (cluster_sizes[j] / (cluster_sizes[cluster]))
                distances[ind, cluster] = distances[cluster, ind]
            else:
                distances[ind, ind] = numpy.inf
    return Z


def show_dendrogram(Z, **kwargs):
    from scipy.cluster.hierarchy import dendrogram, from_mlab_linkage
    from matplotlib import pyplot as plt

    dendrogram(from_mlab_linkage(Z), **kwargs)
    plt.show()


if __name__ == "__main__":
    params = {16, 8, 1}
    X, labels = read_fasta("ribosome.fasta")
    show_dendrogram(lance_williams(X, levenshtein), labels=labels)
    for n in params:
        jac = lambda s, t: jaccard(s, t, n)
        show_dendrogram(lance_williams(X, jac), labels=labels)