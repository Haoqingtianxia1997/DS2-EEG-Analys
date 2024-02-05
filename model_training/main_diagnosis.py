##################################################################
##########                   Import                  #############
##################################################################
import ds2_input
import ds2_output
import ds2_preprocessing
import ds2_get_features
import ds2_prediction
import joblib
from typing import Any, List, Tuple


##################################################################
##########             Global Operation              #############
##################################################################
patient_id = 'aaaaagbf_s005_t002'
patient_data = 'E:/TUH/uniform_data/{}.edf'.format(patient_id)
ds2_model = 'model.pkl'


##################################################################
##########          User-defined function            #############
##################################################################


##################################################################
##########                   Main                    #############
##################################################################
# load raw data
patient_raw = ds2_input.load_signal_edf(patient_data)

# preprocessing
patient_raw_pure = ds2_preprocessing.data_preprocessing(patient_raw)

# get features
features = ds2_get_features.feature_extraction(patient_raw_pure)

# train
model = joblib.load(ds2_model)

# diagnosis
label_list, conf_list = ds2_prediction.predict_labels(features, model)
print('label -> {}'.format(label_list))
print('confidence -> {}'.format(conf_list))
