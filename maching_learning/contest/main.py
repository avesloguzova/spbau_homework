import string

__author__ = 'sasha'

import numpy as np
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.linear_model import SGDClassifier
from sklearn.pipeline import Pipeline
from sklearn import metrics
from pandas.io.parsers import read_csv
from sklearn.grid_search import GridSearchCV
from BeautifulSoup import BeautifulSoup
from nltk.stem.porter import *
import nltk

stemmer = nltk.SnowballStemmer("english")


def magic_fix(text):
    soup = BeautifulSoup(text)
    clean_text = soup.text
    # clean_text = eval('u""" ' + text[1:-1] + ' """').strip()
    clean_text = clean_text.decode('unicode_escape').encode('ascii', 'ignore')
    clean_text = ''.join([i if i.isalpha() else ' ' for i in text])
    # tmp_text = ''.join(c if c not in string.punctuation else ' ' for c in clean_text)
    return ' '.join(stemmer.stem(word.lower()) for word in clean_text.split())


def load_data(filename):
    train = read_csv(filename)
    X = []
    y = []
    for i in xrange(len(train)):
        cell = train.iloc[i,]
        row = magic_fix(cell.Comment)
        X.append(row)
        y.append(cell.Insult)
    return X, y


def load_test_data(filename):
    data = read_csv(filename)
    X = []
    for i in xrange(len(data)):
        cell = data.iloc[i,]
        row = magic_fix(cell.Text)
        X.append(row)
    return X


def save_result(filename, data):
    with open(filename, 'w') as f:
        print >> f, 'Id,Insult'
        for i, a in enumerate(data):
            print >> f, "%d,%d" % (i, a)


print("Load train data ...")

X_train, y_train = load_data("data/train_au.csv")

print("Load test data ...")
result_X = load_test_data("data/test_au.csv")
text_clf = Pipeline([
    ('vect', CountVectorizer()),
    ('tfidf', TfidfTransformer()),
    ('clf', SGDClassifier()),
])

parameters = {'vect__ngram_range': [(1, 2)],
              # 'vect__max_df': (0.5, 0.75, 1.0),
              # 'vect__max_features': (None, 5000, 10000),
              # 'tfidf__use_idf': [True],
              # 'tfidf__sublinear_tf': [True, False],
              # 'tfidf__norm': [('l1', 'l2')],
              # 'clf__penalty': ['l2'],
              'clf__alpha': (1e-3, ),
              'clf__n_iter': (50, 100, 200, 400)
}
gs_clf = GridSearchCV(text_clf, parameters, n_jobs=-1)
print("Start training")
gs_clf = gs_clf.fit(X_train, y_train)
best_parameters, score, _ = max(gs_clf.grid_scores_, key=lambda x: x[1])
for param_name in sorted(parameters.keys()):
    print("%s: %r" % (param_name, best_parameters[param_name]))

print("Score:%s" % score)
# predicted = gs_clf.predict(X_test)
# print(metrics.classification_report(y_test, predicted, ))

save_result("data/result.csv", gs_clf.predict(result_X))