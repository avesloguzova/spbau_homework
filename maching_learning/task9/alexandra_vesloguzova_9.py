__author__ = 'avesloguzova'
import random

from sklearn import datasets
from sklearn.cross_validation import train_test_split
import numpy as np


def sigmoid(z):
    return 1.0 / (1.0 + np.exp(-z))


sigmoid_vec = np.vectorize(sigmoid)


def sigmoid_prime(z):
    return sigmoid(z) * (1 - sigmoid(z))


sigmoid_prime_vec = np.vectorize(sigmoid_prime)


def cost_derivative(output_activations, y):
    return output_activations - y


class NeuralNetwork:
    def __init__(self, sizes):
        self.num_layers = len(sizes)
        self.sizes = sizes
        self.biases = [np.random.randn(y, 1) for y in sizes[1:]]
        self.weights = [np.random.randn(y, x)
                        for x, y in zip(sizes[:-1], sizes[1:])]

    def train(self, X, y, n_iter=100, learning_rate=1):
        for j in xrange(n_iter):
            random_weights_idx = list(random.sample(range(X.shape[0]), 1))
            mini_batch_x = X[random_weights_idx]
            mini_batch_y = y[random_weights_idx]
            self.update(mini_batch_x, mini_batch_y, learning_rate)
            print "Iteration {0} complete".format(j)

    def update(self, x, y, eta):
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]

        delta_nabla_b, delta_nabla_w = self.backpropagation(x, y)
        nabla_b = [nb + dnb for nb, dnb in zip(nabla_b, delta_nabla_b)]
        nabla_w = [nw + dnw for nw, dnw in zip(nabla_w, delta_nabla_w)]
        self.weights = [w - eta * nw
                        for w, nw in zip(self.weights, nabla_w)]
        self.biases = [b - eta * nb
                       for b, nb in zip(self.biases, nabla_b)]

    def feedforward(self, X):
        for b, w in zip(self.biases, self.weights):
            X = sigmoid_vec(np.dot(w, X) + b)
        return X

    def backpropagation(self, X, y):
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        activation = np.transpose(X)
        activations = [np.transpose(X)]
        zs = []
        for b, w in zip(self.biases, self.weights):
            z = np.dot(w, activation) + b
            zs.append(z)
            activation = sigmoid_vec(z)
            activations.append(activation)
        delta = cost_derivative(activations[-1], y) * \
                sigmoid_prime_vec(zs[-1])
        nabla_b[-1] = delta
        nabla_w[-1] = np.dot(delta, activations[-2].transpose())
        for l in xrange(2, self.num_layers):
            z = zs[-l]
            spv = sigmoid_prime_vec(z)
            delta = np.dot(self.weights[-l + 1].transpose(), delta) * spv
            nabla_b[-l] = delta
            nabla_w[-l] = np.dot(delta, activations[-l - 1].transpose())
        return (nabla_b, nabla_w)

    def predict(self, X):
        test_results = [np.argmax(self.feedforward(x)) for x in X]
        return test_results


if __name__ == "__main__":
    print("Load data...")
    dataset = datasets.fetch_mldata("MNIST Original")
    trainX, testX, trainY, testY = train_test_split(
        dataset.data / 255.0, dataset.target.astype("int0"), test_size=0.3)
    print("Start training...")
    nn = NeuralNetwork([trainX.shape[1], 100, 10])
    nn.train(trainX, trainY, n_iter=10000)
    print("Check result...")
    resultY = nn.predict(testX)
    print (resultY)
    print(testY)
    result = sum(int(x == y) for (x, y) in zip(resultY, testY)) / float(len(testY))
    print(result)