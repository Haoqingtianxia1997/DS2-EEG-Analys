#!/usr/bin/env python
# -*- coding: utf-8 -*-
##################################################################
##########                  Import                   #############
##################################################################
import numpy as np
import pandas as pd
import mne
from mne.io import Raw
from typing import Any, List, Tuple, Dict
from sklearn.ensemble import VotingClassifier
from sklearn.naive_bayes import GaussianNB
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier
import ds2_preprocessing
import ds2_get_features
import ds2_input
import ds2_output
import matplotlib.pyplot as plt


##################################################################
##########             Global Operation              #############
##################################################################
features_path = 'D:/qt/usepy_test_4/features_train_from_lzz_1.csv'
labels_path = 'D:/qt/usepy_test_4/labels_train_from_lzz_1.csv'
model_path = 'D:/qt/usepy_test_4/model_train_from_lzz_1.pickle'
pt_1 = 'E:/TUH/show_data/aaaaaajy_s002_t002.edf'
pt_2 = 'E:/TUH/show_data/aaaaagbf_s005_t001.edf'

mne.set_log_level(False)


##################################################################
##########          User-defined function            #############
##################################################################
def predict_labels(features: np.ndarray, model: Any) -> Tuple[List[str], List[float], int]:
    label_list: List[str] = []
    conf_list: List[float] = []
    len_0 = features.shape[0]
    pre = model.predict(features)
    prob = model.predict_proba(features)
    flag = 0
    for i in range(len_0):
        if int(pre[i]):
            label_list.append('Seizures')
            conf_list.append(prob[i][1])
            flag = 1
        else:
            label_list.append('No Seizures')
            conf_list.append(prob[i][0])
    return label_list, conf_list, flag


def load_csv_as_df(path: str) -> Any:
    df = pd.read_csv(path, header=None)
    return df


def load_csv_as_ndarray(path: str) -> np.ndarray:
    df = load_csv_as_df(path)
    arr = df.values
    if arr.shape[0] == 0:
        arr_2d = arr.reshape(1, -1)
        return arr_2d
    else:
        return arr


def build(features: np.ndarray, labels: np.ndarray) -> Any:
    gaussian_NB1 = GaussianNB()
    knn_classifier1 = KNeighborsClassifier(n_neighbors=20,algorithm='auto')
    knn_classifier2 = KNeighborsClassifier(n_neighbors=10,algorithm='auto')
    svm_classifier1 = SVC(kernel='poly', degree=10, C=0.5, probability=True)
    rf_classifier1 = RandomForestClassifier(n_estimators=2500, random_state=42)
    ensemble_model = VotingClassifier(estimators=[('knn1', knn_classifier1),
                                                ('knn2', knn_classifier2),
                                                ('svm1', svm_classifier1),
                                                ('rf1', rf_classifier1),
                                                ('nb',gaussian_NB1)
                                                ],
                                                voting='soft')
    ensemble_model.fit(features, labels.ravel())
    return ensemble_model


def secret_operation(f_path: str, l_path: str) -> Any:
    features = load_csv_as_ndarray(f_path)
    labels = load_csv_as_ndarray(l_path)
    modell = build(features, labels)
    return modell


def epilepsy_detector(path_p: str) -> Tuple[str, float, int]:
    # load raw data
    patient_raw = ds2_input.load_signal_edf(path_p)
    # preprocessing
    patient_raw_pure = ds2_preprocessing.data_preprocessing(patient_raw)
    # export pictures
    ds2_output.pictures_save_and_show(patient_raw_pure, './cache')
    # get features
    features = ds2_get_features.feature_extraction(patient_raw_pure)
    model = secret_operation(features_path, labels_path)
    label_list, conf_list, flagg = predict_labels(features, model)
    return label_list[0], conf_list[0], flagg




