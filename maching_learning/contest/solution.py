__author__ = 'sasha'
import argparse
import datetime
import numpy
import random
import nltk
import cPickle
import string
from sklearn.svm import LinearSVC
from sklearn.svm import NuSVC
import sklearn
from nltk.stem.porter import *

from textblob.classifiers import NaiveBayesClassifier
from pandas.io.parsers import read_csv
from sklearn.ensemble import RandomForestClassifier

stopwords = {'a', 'the', 'it', 'they', 'of', 'in', 'to', 'is', 'have', 'are', 'were', 'and', 'very', '.', ','}
smiles = {":)", ":-)", ":(", ":-(", ";)", ";-)", ":D", ":P", "!!", "?!", "??"}


def magic_fix(text):
    return eval('u""" ' + text[1:-1] + ' """').strip()


def load_data(filename):
    train = read_csv(filename)
    data = []
    for i in xrange(len(train)):
        cell = train.iloc[i,]
        row = [magic_fix(cell[-1])] + list(cell[1:-1])
        data.append(tuple(row))
    return data
def load_test_data(filename):
    train = read_csv(filename)
    data = []
    for i in xrange(len(train)):
        cell = train.iloc[i,]
        row = [magic_fix(cell[-1])] + list(cell[1:-1])
        data.append(tuple(row))
    return data


def save_result(filename, data):
    with open(filename, 'w') as f:
        print >> f, 'Id,Insult'
        for i, a in enumerate(data):
            print >> f, "%d,%d" % (i, a)


def check_for_smile(post):
    features = {}
    for smile in smiles:
        if smile in post:
            features['contains(%s)' % smile] = True
    return features

stemmer = nltk.SnowballStemmer("english")

def dialogue_act_features(post):
    tmp_post = ''.join(c for c in post if c not in string.punctuation)
    features = {}
    features.update(check_for_smile(post))
    for word in nltk.word_tokenize(tmp_post):
        features['contains(%s)' % stemmer.stem(word.lower())] = True
        if word.isupper():
            features[u'uppercase'] = True
    return features


def main2(args):
    print("Load train data ...")
    train = load_data(args.train)
    train = random.sample(train, len(train))
    featuresets = [(dialogue_act_features(text), label)
                   for text, label in train]

    size = int(len(featuresets) * 0.7)
    train_set, test_set = featuresets[size:], featuresets[:size]
    print("Fit classifier")

    classifier = nltk.classify.SklearnClassifier(NuSVC(degree=1))
    classifier.train(train_set)
    # classifier = nltk.NaiveBayesClassifier.train(train_set)
    print(nltk.classify.accuracy(classifier, test_set))
    print("Load test data ...")
    test = load_data(args.test)
    featuresets_test = [dialogue_act_features(text) for (text,) in test]
    print("Classify test data")
    data = [classifier.classify(test_str) for test_str in featuresets_test]
    print("Save result")
    save_result(args.output, data)


def features(post):
    count_vector = sklearn.feature_extraction.text.CountVectorizer()
    word_counts = count_vector.fit_transform(post)
    tf_transformer = sklearn.feature_extraction.text.TfidfTransformer(use_idf=True).fit(word_counts)
    return tf_transformer.transform(word_counts)


def main(args):
    print("Load train data ...")
    train = load_data(args.train)
    featuresets = [(features(text), label)
                   for text, label in train]
    size = int(len(featuresets) * 0.4)
    train_set, test_set = featuresets[size:], featuresets[:size]
    classifier = nltk.classify.SklearnClassifier(LinearSVC())
    classifier.train(train_set)

    print("Load test data ...")
    test = load_data(args.test)
    featuresets_test = [dialogue_act_features(text) for (text,) in test]
    print("Classify test data")
    data = [classifier.classify(test_str) for test_str in featuresets_test]
    print("Save result")
    save_result(args.output, data)


if __name__ == "__main__":
    start = datetime.datetime.now()

    argparser = argparse.ArgumentParser(description="Comments learner")
    argparser.add_argument("--train", default="data/train_au.csv")
    argparser.add_argument("--test", default="data/test_au.csv")
    argparser.add_argument("--train-pre", default="data/train_pre.cpickle")
    argparser.add_argument("--test-pre", default="data/test_pre.cpickle")
    argparser.add_argument("--output", default="data/result.csv")
    args = argparser.parse_args()

    main2(args)
    # pre_save(args)

    finish = datetime.datetime.now()
    print "Time to run:", finish - start



