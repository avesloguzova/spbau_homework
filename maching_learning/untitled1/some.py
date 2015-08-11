__author__ = 'avesloguzova'
from matplotlib.mlab import find
import matplotlib.pyplot as pl
import numpy as np
from numpy import linalg
from cvxopt import matrix, solvers
from sklearn.datasets import make_classification

eps = 1e-5


class LinearSVM:
    def __init__(self, C):
        self.C = C
        self._w = None
        self._w0 = None
        self._ksi = None
        self.support_ = None

    def fit(self, X, y):
        n_samples, n_features = X.shape

        P = np.zeros((n_features + n_samples + 1, n_features + n_samples + 1))
        P[:n_features, :n_features] = np.identity(n_features)
        P = matrix(P)

        q = np.zeros((n_features + n_samples + 1, 1))
        q[n_samples + 1:, :] = np.ones((n_features, 1)) * self.C
        q = matrix(q, q.shape, 'd')

        h = np.zeros((2 * n_samples, 1))
        h[n_samples:, :] = -np.ones((n_samples, 1))
        h = matrix(h, h.shape, 'd')

        I = matrix(np.identity(n_samples))
        empty1 = matrix(np.zeros((n_samples, n_features)))
        empty2 = matrix(np.zeros((n_samples, 1)))
        G = matrix([[empty1, -matrix(y.reshape(len(y), 1) * X)], [empty2, matrix(-y)], [-I, -I]])
        x = solvers.qp(P, q, G=G, h=h)['x']

        self._w = np.array(x[:n_features])
        self._w0 = float(x[n_features])
        self._ksi = np.array(x[n_features + 1:])
        mask = [y[i] * (np.dot(self._w.T, X[i]) + self._w0) - 1 + self._ksi[i] <= eps for i in range(n_samples)]
        self.support_ = [i for i in range(n_samples) if mask[i]]

    def decision_function(self, X):
        return np.sum(X.T * self._w, axis=0).T + self._w0

    def predict(self, X):
        return np.sign(self.decision_function(X))


def linear_kernel(x1, x2):
    return np.dot(x1, x2)


def polynomial_kernel(x1, x2, p):
    return (1 + np.dot(x1, x2)) ** p


def gaussian_kernel(x1, x2, gamma):
    return np.exp(gamma*linalg.norm(x1 - x2) ** 2)


class KernelSVM:

    LINEAR_KERNEL = 1L
    POLY_KERNEL = 2L
    RBF_KERNEL = 3L

    def __init__(self, C, kernel=None, sigma=1.0, degree=1):
        self.C = C
        self.kernel = kernel
        self.gamma = - 1.0/(2*sigma**2)
        self.degree = degree
        self.support_ = None
        self._alpha = None
        self._support_x = None
        self._support_y = None
        self._w0 = 0

    def fit(self, X, y):
        n_samples, n_features = X.shape

        kernel_values = self._compute_kernel(X)

        P = matrix(np.outer(y, y) * kernel_values)
        A = matrix(y, (1, n_samples), 'd')
        q = matrix(np.ones(n_samples) * -1)
        h = matrix([matrix(np.ones(n_samples) * self.C), matrix(np.zeros((n_samples, 1)))])
        b = matrix(0, (1, 1), 'd')
        I = matrix(np.identity(n_samples))
        G = matrix([I, -I])

        a = np.ravel(solvers.qp(P, q, G, h, A, b)['x'])
        sv_mask = a > 0
        self.support_ = [i for i in range(n_samples) if sv_mask[i]]
        self._alpha = a[sv_mask]
        self._support_x = X[sv_mask]
        self._support_y = y[sv_mask]
        self._w0 = 0
        for n in range(len(self._alpha)):
            self._w0 += self._support_y[n]
            self._w0 -= np.sum(self._alpha * self._support_y * kernel_values[self.support_[n], sv_mask])
        if len(self._alpha) != 0:
            self._w0 /= len(self._alpha)

    def decision_function(self, X):
        kernel_value = self._compute_kernel(X, self._support_x)
        y = np.sum(self._alpha * self._support_y * kernel_value, axis=1) + self._w0
        return y

    def predict(self, X):
        return np.sign(self.decision_function(X))

    def _compute_kernel(self, X, S=None):
        if S is None:
            S = X
        n = X.shape[0]
        m = S.shape[0]
        # S_duplicate = np.array([S, ] * n)
        kernel_value = np.zeros((n, m))
        for i in range(n):
            for j in range(m):
                    if self.kernel == KernelSVM.LINEAR_KERNEL:
                        kernel_value[i, j] = linear_kernel(X[i], S[j])
                    if self.kernel == KernelSVM.POLY_KERNEL:
                        kernel_value[i, j] = polynomial_kernel(X[i], S[j], self.degree)
                    if self.kernel == KernelSVM.RBF_KERNEL:
                        kernel_value[i, j] = gaussian_kernel(X[i], S[j], self.gamma)
        return kernel_value


def visualize(clf, X, y):
    border = .5
    h = .02

    x_min, x_max = X[:, 0].min() - border, X[:, 0].max() + border
    y_min, y_max = X[:, 1].min() - border, X[:, 1].max() + border

    xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))
    mesh = np.c_[xx.ravel(), yy.ravel()]

    z_class = clf.predict(mesh).reshape(xx.shape)

    # Put the result into a color plot
    pl.figure(1, figsize=(8, 6))
    pl.pcolormesh(xx, yy, z_class, cmap=pl.cm.summer, alpha=0.3)

    # Plot hyperplane and margin
    z_dist = clf.decision_function(mesh).reshape(xx.shape)
    pl.contour(xx, yy, z_dist, [0.0], colors='black')
    pl.contour(xx, yy, z_dist, [-1.0, 1.0], colors='black', linestyles='dashed')

    # Plot also the training points
    y_pred = clf.predict(X)

    ind_support = clf.support_
    ind_correct = list(set(find(y == y_pred)) - set(ind_support))
    ind_incorrect = list(set(find(y != y_pred)) - set(ind_support))

    pl.scatter(X[ind_correct, 0], X[ind_correct, 1], c=y[ind_correct], cmap=pl.cm.summer, alpha=0.9)
    pl.scatter(X[ind_incorrect, 0], X[ind_incorrect, 1], c=y[ind_incorrect], cmap=pl.cm.summer, alpha=0.9, marker='*',
               s=50)
    pl.scatter(X[ind_support, 0], X[ind_support, 1], c=y[ind_support], cmap=pl.cm.summer, alpha=0.9, linewidths=1.8,
               s=40)

    pl.xlim(xx.min(), xx.max())
    pl.ylim(yy.min(), yy.max())


def train_test_split(X, y, ratio):
    mask = np.random.uniform(size=len(y)) < ratio
    return X[mask], y[mask], X[~mask], y[~mask]


def generate_sample():
    X, y = make_classification(n_samples=50, n_features=2, n_redundant=0, )
    np.place(y, y == 0, -1)
    return X, y

def test_linear_svm_linear_kernel():
    for C in (0.1, 1, 10):
        l_svm = LinearSVM(C=C)
        k_svm = KernelSVM(kernel=KernelSVM.LINEAR_KERNEL, C=C)
        X, y = generate_sample()
        l_svm.fit(X, y)
        k_svm.fit(X, y)
        visualize(l_svm, X, y)
        pl.show()
        visualize(k_svm, X, y)
        pl.show()


def test_rbf_kernel():
    for sigma in (0.1, 1, 10):
        for C in (1, 10):
            svm = KernelSVM(kernel=KernelSVM.RBF_KERNEL, C=C, sigma=sigma)
            X, y = generate_sample()
            svm.fit(X, y)
            visualize(svm, X, y)
            pl.show()


def test_poly_kernel():
    degree = 2
    for C in (0.1, 1, 10):
        svm = KernelSVM(kernel=KernelSVM.POLY_KERNEL, C=C, degree=degree)
        X, y = generate_sample()
        svm.fit(X, y)
        visualize(svm, X, y)
        pl.show()


if __name__ == "__main__":
    # test_linear_svm_linear_kernel()
    test_poly_kernel()
    # test_rbf_kernel()