__author__ = 'avesloguzova'
import cv2
import numpy as np

plot_size = 1000
orig_img_x = 0
orig_img_y = 0

def read_image(path):
    orig_img = cv2.imread(path)
    orig_img = cv2.cvtColor(orig_img, cv2.COLOR_BGR2RGB)
    orig_img_x = orig_img.shape[0]
    orig_img_y = orig_img.shape[1]
    image = np.reshape(orig_img,(orig_img_x * orig_img_y, 3))
    return image


def dist(x1, x2):
    return np.sqrt(np.sum((x1 - x2) ** 2, axis=1))

def k_means(X, n_clusters, distance_metric):
    centres = np.random.randint(0, 256, (n_clusters, 3))
    old_clusters = np.zeros(len(X))
    while True:
        distances = np.asarray([distance_metric(X, np.tile(center, (len(X), 1))) for center in centres])
        clusters = np.argmin(distances, axis=0)
        cluster_size = np.zeros(len(X))
        for i, point in enumerate(X):
            centres[clusters[i]] += point
            cluster_size[clusters[i]] += 1
        for i in range(n_clusters):
            if cluster_size[i] != 0:
                centres[i] = centres[i] / cluster_size[i]
            else:
                centres[i] = np.asarray([np.inf, np.inf, np.inf])
        if np.alltrue(clusters == old_clusters):
            break
        old_clusters = np.copy(clusters)
    return old_clusters, centres

def centroid_histogram(labels):
    histogram = np.zeros(max(labels)+1)
    for label in labels:
        histogram[label] += 1
    histogram /= np.sum(histogram)
    return histogram

def plot_colors(hist, centroids):
    bar = np.zeros((50, plot_size, 3), np.uint8)
    start_x = 0
    params = zip(hist, centroids)
    params.sort(key=lambda x: x[0])
    for (part, color) in params:
        end_x = part * plot_size + start_x
        cv2.rectangle(bar, (int(start_x), 0), (int(end_x), 50),
                      color.astype("uint8").tolist(), -1)
        start_x = end_x
    bar = cv2.cvtColor(bar, cv2.COLOR_RGB2BGR)
    return bar
def recolor(image, kmeans, n_colors):
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
    clusters, centers = k_means(image, n_colors, dist)
    hist = centroid_histogram(clusters)
    bar_image = plot_colors(hist, centers)
    recolored = recolor(cv2.imread(pic_name), (clusters, centers), n_colors)
    cv2.imshow('plot colors', bar_image)
    cv2.imwrite('result_' + pic_name, recolored)
    cv2.waitKey()
    cv2.destroyAllWindows()