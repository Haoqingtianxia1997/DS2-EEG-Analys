#!/usr/bin/env python
# -*- coding: utf-8 -*-
##################################################################
##########                  Import                   #############
##################################################################
import joblib
import pickle
import numpy as np
from typing import Any, List, Tuple


##################################################################
##########          User-defined function            #############
##################################################################
def predict_labels(features: np.ndarray, model: Any) -> Tuple[List[int], List[float]]:
    label_list: List[int] = []
    conf_list: List[float] = []
    len_0 = features.shape[0]
    pre = model.predict(features)
    prob = model.predict_proba(features)
    for i in range(len_0):
        if int(pre[i]):
            label_list.append(1)
            conf_list.append(prob[i][1])
        else:
            label_list.append(0)
            conf_list.append(prob[i][0])
    return label_list, conf_list


##################################################################
##########                   Main                    #############
##################################################################
model_path = 'D:/qt/usepy_test_4/model_from_lzz.pickle'
# model = joblib.load(model_path)
with open(model_path, 'rb') as f:
    model = pickle.load(f)

features_list = [5.93171627e-10, 4.22244940e-06, 1.09639583e-10, 1.41306915e-06, 6.12171621e-11, 1.06849407e-06, 4.12400236e-11, 3.51083836e-07]
features_arr = np.array(features_list)
features_arr_2d = features_arr.reshape(1, -1)

label_list, conf_list = predict_labels(features_arr_2d, model)

print(label_list[0], conf_list[0])
