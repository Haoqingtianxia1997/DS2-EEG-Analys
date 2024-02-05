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
def load_single_data(path: str) -> Tuple[int, str, float, float, str]:
#    mne.set_log_level(False)
    channels_template: List[str] = ['EEG FP1', 'EEG FP2', 'EEG F3', 'EEG F4', 'EEG C3', 'EEG C4',
                                     'EEG P3', 'EEG P4', 'EEG O1', 'EEG O2', 'EEG F7', 'EEG F8',
                                     'EEG T3', 'EEG T4', 'EEG T5', 'EEG T6', 'EEG CZ']
    edf_data = mne.io.read_raw_edf(path, preload=True)
    channels_original = edf_data.ch_names
    channels_standard: Dict[str, str] = {}
    reference_system: str = ''
    for i, _ch in enumerate(channels_original):
        if i == 0:
            reference_system = ((_ch.split()[1]).split('-')[1]).upper()
        channels_standard[_ch] = _ch.split('-')[0]
    edf_data.rename_channels(channels_standard)
    edf_data.pick(channels_template)
    channels_picked = edf_data.ch_names
    # print(channels_picked)
    channels_norm: Dict[str, str] = {}
    for _ch in channels_picked:
        channels_norm[_ch] = (_ch.split()[1]).capitalize()
    edf_data.rename_channels(channels_norm)
    edf_data.rename_channels({"T3": "T7", "T4": "T8", "T5": "P7", "T6": "P8"})
    channels: List[str] = edf_data.ch_names
    ch_num: int = int(len(channels))
    data_len: int = edf_data.n_times
    data_size: str = str(ch_num) + 'x' + str(data_len)
    sampling_frequency: float = edf_data.info['sfreq']
    time_secs = edf_data.times
    data_len_secs = time_secs[-1]
    return ch_num, data_size, sampling_frequency, data_len_secs, reference_system

