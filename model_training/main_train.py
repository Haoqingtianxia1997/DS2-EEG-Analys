##################################################################
##########                   Import                  #############
##################################################################
import ds2_input
import ds2_output
import ds2_preprocessing
import ds2_get_features
import ds2_train
from typing import Any, List, Tuple
import numpy as np
import pandas as pd


##################################################################
##########             Global Operation              #############
##################################################################
train_dataset = 'train_from_lzz_1'
train_dataset_path = 'E:/TUH/{}'.format(train_dataset)
model_path = './model/model_{}.pickle'.format(train_dataset)
features_path = './features/features_{}.csv'.format(train_dataset)
labels_path = './labels/labels_{}.csv'.format(train_dataset)

# methode = 'standard'
methode = 'simple'


##################################################################
##########          User-defined function            #############
##################################################################
def prepare_2_train(path: str) -> Tuple[np.ndarray, np.ndarray]:
    labels_matrix: List[List[int]] = []
    features_matrix: List[List[float]] = []
    dataset = ds2_input.EEGDataSet_new(path)
    for item in dataset:
        pt_id, ch, raw_data, fs, rs, eeg_labels = item
        # get labels
        label, onset, offset = eeg_labels
        labels_list = [int(label)]
        # ===================新添加==================
        if ds2_preprocessing.data_checking(raw_data) != None:
            labels_matrix.append(labels_list)
            patient_raw_pure = ds2_preprocessing.data_preprocessing(raw_data)
            # get features
            features = ds2_get_features.feature_extraction(patient_raw_pure)
            features_list = features.flatten().tolist()
            features_matrix.append(features_list)
        else:
            continue
        # ==================结束 ====================
    labels_df = pd.DataFrame(data=labels_matrix, columns=None, index=None)
    ds2_output.save_df_as_csv(labels_df, labels_path)
    labels = labels_df.values
    features_df = pd.DataFrame(data=features_matrix, columns=None, index=None)
    ds2_output.save_df_as_csv(features_df, features_path)
    features = features_df.values
    return features, labels


##################################################################
##########                   Main                    #############
##################################################################
if methode == 'simple':
    features_arr = ds2_input.load_csv_as_ndarray(features_path)
    labels_arr = ds2_input.load_csv_as_ndarray(labels_path)
else:
    features_arr, labels_arr = prepare_2_train(train_dataset_path)
model = ds2_train.train(features_arr, labels_arr)
ds2_output.save_modell_as_pickle(model, model_path)


