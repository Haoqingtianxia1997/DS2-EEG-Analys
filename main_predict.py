##################################################################
##########                   Import                  #############
##################################################################
import numpy as np
import pandas as pd
import ds2_input
import ds2_output
import ds2_preprocessing
import ds2_get_features
import ds2_prediction
import pickle
import sklearn
from typing import Any, List, Tuple


##################################################################
##########             Global Operation              #############
##################################################################
train_dataset = 'train_from_lzz_1'
predict_dataset = 'uniform_data'
predict_dataset_path = 'E:/TUH/{}'.format(predict_dataset)
model_path = './model/model_{}.pickle'.format(train_dataset)
features_path = './features/features_{}.csv'.format(predict_dataset)
labels_path = './labels/labels_{}.csv'.format(predict_dataset)

methode = 'standard'
# methode = 'simple'


##################################################################
##########          User-defined function            #############
##################################################################
def prepare_2_predict(path: str) -> Tuple[np.ndarray, np.ndarray]:
    labels_matrix: List[List[int]] = []
    features_matrix: List[List[float]] = []
    dataset = ds2_input.EEGDataSet_new(path)
    for item in dataset:
        pt_id, ch, raw_data, fs, rs, eeg_labels = item
        # get labels
        label, onset, offset = eeg_labels
        labels_list = [int(label)]
        # ===================changed==================
        if ds2_preprocessing.data_checking(raw_data) != None:
            labels_matrix.append(labels_list)
            # preprocessing
            patient_raw_pure = ds2_preprocessing.data_preprocessing(raw_data)
            # get features
            features = ds2_get_features.feature_extraction(patient_raw_pure)
            features_list = features.flatten().tolist()
            features_matrix.append(features_list)
        else:
            continue
        # ==================finisch change ====================
    labels_df = pd.DataFrame(data=labels_matrix, columns=None, index=None)
    labels = labels_df.values
    features_df = pd.DataFrame(data=features_matrix, columns=None, index=None)
    features = features_df.values
    return features, labels


##################################################################
##########                   Main                    #############
##################################################################
if methode == 'simple':
    features_arr = ds2_input.load_csv_as_ndarray(features_path)
    labels_arr = ds2_input.load_csv_as_ndarray(labels_path)
else:
    features_arr, labels_arr = prepare_2_predict(predict_dataset_path)
model = ds2_input.load_model_pickle(model_path)
# model = ds2_input.load_model_joblib(model_path)
pre = model.predict(features_arr)
ds2_prediction.show_performance(labels_arr, pre)
