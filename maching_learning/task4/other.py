__author__ = 'Andrey'
import cv2
import numpy as np


infpoint = np.asarray([np.inf, np.inf, np.inf])


def read_image(path):
    original_image = cv2.imread(path)
    original_image = cv2.cvtColor(original_image, cv2.COLOR_BGR2RGB)
    result_image = np.zeros((original_image.shape[0] * original_image.shape[1], 3))
    for i in range(original_image.shape[0]):
        for j in range(original_image.shape[1]):
            result_image[i * original_image.shape[1] + j] = original_image[i][j]
    return result_image


# need to be vectorized
def euclidian(x1, x2):
    return np.sqrt(np.sum((x1 - x2) ** 2, axis=1))


def k_means(X, n_clusters, distance_metric):
    """

    :type X: feature vector of points in RBG color space
    """
    centroids = np.random.randint(0, 256, (n_clusters, 3))
    old_clusters = np.zeros(len(X))
    while True:
        distances = np.asarray([distance_metric(X, np.tile(center, (len(X), 1))) for center in centroids])
        new_clusters = np.argmin(distances, axis=0)
        cluster_size = np.zeros(len(X))
        for i, point in enumerate(X):
            centroids[new_clusters[i]] += point
            cluster_size[new_clusters[i]] += 1
        for i in range(n_clusters):
            centroids[i] = centroids[i] / cluster_size[i] if cluster_size[i] != 0 else infpoint
        if np.alltrue(new_clusters == old_clusters):
            break
        old_clusters = np.copy(new_clusters)
    return old_clusters, centroids


def plot_colors(hist, centroids):
    bar_len = 500
    centroids = np.asarray([centr[::-1] for centr in centroids])
    bar = np.zeros((50, bar_len, 3), np.uint8)
    start_x = 0
    params = zip(hist, centroids)
    params.sort(key=lambda a: a[0], reverse=True)
    for (percent, color) in params:
        end_x = start_x + percent * bar_len
        cv2.rectangle(bar, (int(start_x), 0), (int(end_x), 50),
                      color.astype("uint8").tolist(), -1)
        start_x = end_x
    return bar


def centroid_histogram(labels):
    histogram = np.zeros(max(labels) + 1)
    for label in labels:
        histogram[label] += 1
    histogram /= np.sum(histogram)
    return histogram


def recolor(image, kmeans, n_colors):
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    recolor_clusters, cluster_centers = kmeans[0], kmeans[1]
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            image[i][j] = cluster_centers[recolor_clusters[i * image.shape[1] + j]]
    image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
    return image


if __name__ == "__main__":
    pic_name = 'superman-batman.png'
    n_colors = 16
    image = read_image(pic_name)
    clusters, centers = k_means(image, n_colors, euclidian)
    hist = centroid_histogram(clusters)
    bar_image = plot_colors(hist, centers)
    recolored = recolor(cv2.imread(pic_name), (clusters, centers), n_colors)
    cv2.imshow('bar', bar_image)
    cv2.imshow('pic', recolored)
    cv2.imwrite('16colors_' + pic_name, recolored)
    cv2.waitKey()
    cv2.destroyAllWindows()