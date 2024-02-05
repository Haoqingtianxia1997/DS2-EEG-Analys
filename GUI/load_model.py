#!/usr/bin/env python
# -*- coding: utf-8 -*-
##################################################################
##########                  Import                   #############
##################################################################
from typing import List, Tuple, Dict, Any
import os
import csv
import math
import pickle
import mne
from mne.baseline import rescale
import numpy as np
import pandas as pd
from scipy import signal as sig
from scipy.signal import savgol_filter


##################################################################
##########          User-defined function            #############
##################################################################
def load_singel_model(path: str) -> Tuple[str, int, str, str, str, str, str, str]:
    model_name = os.path.basename(path)
    model_kern = 'ensemble->voting'
    feature_dim = 88
    label_dim = 'Binary'
    subk1 = 'KNN->k=3'
    subk2 = 'SVM->degree=2'
    subk3 = 'RF->trees=1000'
    subk4 = 'BNB->default'
    subk5 = 'None'
    return model_kern, feature_dim, label_dim, subk1, subk2, subk3, subk4, subk5,
