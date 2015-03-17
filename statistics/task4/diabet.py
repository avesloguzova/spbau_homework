__author__ = 'av'
import numpy as np


def modeling(m_d, sigma_d, m_h, sigma_h, total_patients, diabetes_prop):
    health_prop = 1 - diabetes_prop
    size_d = int(total_patients * diabetes_prop)
    size_h = int(total_patients * health_prop)
    distribution_d = np.random.normal(m_d, sigma_d, size_d)
    distribution_h = np.random.normal(m_h, sigma_h, size_h)
    diabetes_res = measurements(distribution_d, (diabetes_prop, health_prop), (m_d, m_h), (sigma_d, sigma_h), 1000000,
                                0, True)
    healthy_res = measurements(distribution_h, (diabetes_prop, health_prop), (m_d, m_h), (sigma_d, sigma_h),
                               diabetes_res[3], diabetes_res[2], False)
    decision_bound = healthy_res[2]
    fp = diabetes_res[0] + healthy_res[0]
    fn = diabetes_res[1] + healthy_res[1]
    error_rate = float(fp + fn) / total_patients
    return decision_bound, error_rate


def measurements(distribution, probabilities, m, sigmas, delta, bound, is_diabetes):
    diabetes_pr, healthy_pr = probabilities
    m_d, m_h = m
    sigma_d, sigma_h = sigmas
    fp = 0
    fn = 0
    for patient in distribution:
        posterior_d = np.exp(-(patient - m_d) ** 2 / (2 * sigma_d ** 2)) / (sigma_d * np.sqrt(2 * np.pi))
        posterior_h = np.exp(-(patient - m_h) ** 2 / (2 * sigma_h ** 2)) / (sigma_h * np.sqrt(2 * np.pi))

        bayes_factor = diabetes_pr * posterior_d / (healthy_pr * posterior_h)
        if is_diabetes and bayes_factor <= 1:
            fn += 1
        if not is_diabetes and bayes_factor > 1:
            fp += 1

        if abs(bayes_factor - 1) < delta:
            delta = abs(bayes_factor - 1)
            bound = patient
    return fp, fn, bound, delta

if __name__ == "__main__":
    bound = -1
    m_d, sigma_d = 3, 2
    m_h, sigma_h = 1, 0.35
    total_patients = 10000
    diabetes_prop = 0.01
    while bound < 0:
        bound, error = modeling(m_d, sigma_d, m_h, sigma_h, total_patients, diabetes_prop)
    print(error)
    print(bound)