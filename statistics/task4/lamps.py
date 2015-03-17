__author__ = 'av'

import numpy as np
from scipy.stats import gamma
import matplotlib.pyplot


def modeling(experiments_count,points_count,k,theta):
    lambda_param = np.random.gamma(k, theta, 1)
    experiments = np.random.exponential(1/lambda_param, experiments_count)
    beta = 1/theta
    for experiment in experiments:
        k += 1
        beta += experiment
        x = np.linspace(gamma.ppf(0.00, k, scale=1 / beta), gamma.ppf(0.99, k, scale=1 / beta), points_count)
        matplotlib.pyplot.plot(x, gamma.pdf(x, k, scale=1 / beta))
    matplotlib.pyplot.axvline(x=lambda_param, linewidth=2, color='k')
    matplotlib.pyplot.show()

if __name__ == "__main__":
    exp_count = 5000
    point_count = 1000
    k, theta = 9, 1
    modeling(exp_count,point_count, k, theta)
