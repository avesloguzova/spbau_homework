__author__ = 'sasha'
from numpy import linalg
import numpy as np
import csv
from sklearn.cross_validation import train_test_split
from sklearn.preprocessing import normalize

from matplotlib import pyplot as plt


class NormalLR:
    def fit(self, X, y):
        Fplus = linalg.pinv(X)
        weights = np.dot(Fplus, y)
        self.weights = weights
        return self

    def predict(self, X):
        y = np.dot(X, self.weights)
        return y


class GradientLR(NormalLR):
    MAX_ITER = 500

    def __init__(self, alpha):
        if alpha <= 0:
            raise ValueError("alpha should be positive")
        self.alpha = alpha
        self.threshold = alpha / 100

    def fit(self, X, y):
        l, k = X.shape
        old_weights = np.zeros(k)
        weights = np.zeros(k)
        for i in range(GradientLR.MAX_ITER):
            subtrahend = X.dot(old_weights) - y
            weights = old_weights - self.alpha * subtrahend.T.dot(X) / l
            if linalg.norm(weights - old_weights) <= self.threshold:
                break
            old_weights = weights.copy()
        self.weights = weights
        return self



def sample(size, weights):
    X = np.ones((size, 2))
    X[:, 1] = np.random.gamma(4., 2., size)
    y = X.dot(np.asarray(weights))
    y += np.random.normal(0, 1, size)
    return X[:, 1:], y

def mse(y_true, y_pred):
    return np.mean((y_true - y_pred) ** 2)


def read_data(filename):
    with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        data = np.asarray([tuple(map(float, line)) for line in reader])
        return data[:, :-1], data[:, -1]
def test(X,y):
    X_train, X_test, y_train, y_test = train_test_split(X, y,train_size=0.3)
    print("MSE(Normal):")
    lr = NormalLR()
    lr.fit(X_train, y_train)
    lr_y_pred = lr.predict(X_test)
    print (mse(y_test, lr_y_pred))

    print("MSE(Gradient):")
    glr = GradientLR(alpha=1e-2)
    glr.fit(X_train, y_train)
    glr_y_pred = glr.predict(X_test)
    print(mse(y_test, glr_y_pred))

def test_and_show(X, y):
    X_train, X_test, y_train, y_test = train_test_split(X, y,train_size=0.3)
    print("MSE(Normal):")
    lr = NormalLR()
    lr.fit(X_train, y_train)
    lr_y_pred = lr.predict(X_test)
    print (mse(y_test, lr_y_pred))
    plt.scatter(X, y)
    plt.plot(X_test, lr_y_pred, color="red")
    plt.show()
    print("MSE(Gradient):")
    glr = GradientLR(alpha=1e-2)
    glr.fit(X_train, y_train)
    glr_y_pred = glr.predict(X_test)
    print(mse(y_test, glr_y_pred))
    plt.scatter(X, y)
    plt.plot(X_test, glr_y_pred, color="red")
    plt.show()

size_list = (128, 256, 512, 1024)
experiments_count = 1

for size in size_list:

    print("SIZE:")
    print(size)
    # print("TEST:")
    # for j in range(experiments_count):
    #     X, y_true = sample(size, weights=[10., 15.])
    #     test_and_show(X,y_true)
    print("REAL:")
    X, y_true = read_data("boston.csv")
    # print("NO NORMALIZE")
    # for j in range(experiments_count):
    #     test(X,y_true)

    print("NOMALIZE")
    X_norm = normalize(X)
    for j in range(experiments_count):
        test(X_norm,y_true)