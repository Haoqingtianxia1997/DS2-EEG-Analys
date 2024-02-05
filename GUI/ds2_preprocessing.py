import csv
import matplotlib.pyplot as plt
import numpy as np
import os
import mne
from typing import Any,List,Tuple
from mne.io import Raw

# ==================================== rereference =========================================
def data_rereference(raw_data: Raw, montage: str = 'LE') -> Any:
    """
    This function is to reference SINGLE raw EEG signals with Linked-Ear-reference system.
    T7 and T8 are set to be the Ear-channels.
    Input:
    raw_data: raw 22 EEG signal readed from files
    montage: not needed
    Output:
    Referenced EEG signal of type Raw
    """
    # raw_data = rename_channels(raw_data)
    if montage == 'LE':
        raw_data.set_montage("easycap-M1")
        raw_data.rename_channels({"T7": "M1","T8":"M2"})
        # this splits electrodes into  groups; left,midline, and right
        ch_names = mne.channels.make_1020_channel_selections(raw_data.info, return_ch_names=True)
        # remove the ref channels from the lists of to-be-rereferenced channels
        ch_names["Left"].remove("M1")
        ch_names["Right"].remove("M2")
        # midline referencing to mean of mastoids:
        mastoids = ["M1","M2"]
        rereferenced_midline_chs = (
            raw_data.copy().pick(mastoids + ch_names["Midline"])
            .set_eeg_reference(mastoids)
            .drop_channels(mastoids)
        )
        # contralateral referencing (alters channels in raw' in-place):
        for ref, hemi in dict(M2=ch_names["Left"],M1=ch_names["Right"]).items():
            mne.set_bipolar_reference(raw_data,anode=hemi, cathode=[ref] * len(hemi),copy=False)
        # strip off I-M1' and '-M2' suffixes added to each bipolar-referenced channel
        raw_data.rename_channels(lambda ch_name: ch_name.split("-")[0])
        # replace unreferenced midline with rereferenced midline
        raw_data.drop_channels(ch_names["Midline"]).add_channels([rereferenced_midline_chs])
        return raw_data
    else:
        print('No matching method!')
        return 0
    
# 调用这个
def data_rereference_judge(raw: Any , montage: str = 'LE') -> Any:
    """
    This function is to reference the SINGLE eeg signal or a eeg signal list
    T7 and T8 are set to be the Ear-channels.
    Input:
    data_wait_for_filter: Raw_data
    montage: not needed
    Output:
    a eeg signal of type raw / multiple eeg signals of type list
    """
    if isinstance(raw, list):
        new_raw_data_list = []
        for i,raw_data in enumerate(raw):
            raw_data = data_rereference(raw_data, montage)
            new_raw_data_list.append(raw_data)
        return new_raw_data_list
    elif isinstance(raw, mne.io.edf.edf.RawEDF):
        raw_data = data_rereference(raw, montage)
        return raw_data
    else:
        print ('No match Type! Must be a List or a Raw data')
        return
# ==================================== filtering ===========================================
def data_filtering(data_wait_for_filter: Raw, band_pass_frequency:Tuple[float,float] = (1.0,35.0)) -> Raw:
    """
    This function will use the bandpss filter on the SINGLE eeg signal
    Input:
    data_wait_for_filter: Raw_data
    band_pass_frequency: limit of frequency of band pass filter
    """
    low_frequency = band_pass_frequency[0]
    high_frequency = band_pass_frequency[1]
    data_wait_for_filter.filter(l_freq=low_frequency, h_freq=high_frequency)
    return data_wait_for_filter

# 调用这个
def data_filtering_judge(data_wait_for_filter:Any,band_pass_frequency:Tuple[float,float] = (1.0,35.0)) -> Any:
    """
   This function will use the bandpss filter on the SINGLE eeg signal or a eeg signal list
    Input:
    raw_data: single Raw_data / eeg signal list
    band_pass_frequency: limit of frequency of band pass filter
    Output:
    a eeg signal of type raw / multiple eeg signals of type list
    """
    if isinstance(data_wait_for_filter, list):
        new_raw_data_list = []
        for i,raw_data in enumerate(data_wait_for_filter):
            raw_data = data_filtering(raw_data, band_pass_frequency)
            new_raw_data_list.append(raw_data)
        return new_raw_data_list
    elif isinstance(data_wait_for_filter, mne.io.edf.edf.RawEDF):
        data_wait_for_filter = data_filtering(data_wait_for_filter, band_pass_frequency)
        return data_wait_for_filter
    else:
        print ('No match Type! Must be a List or a Raw data')
        return

# ==================================== downsampling ========================================
def data_downsamping(filtered_data:Raw,target_frequency:float)->Raw:
    """
    This function will down sampling the SINGLE eeg signal
    Input:
    filtered_data: Raw_data
    target_frequency: target sampling frequency, ex. target_frequency=1.0
    """
    if filtered_data.info['sfreq'] > target_frequency:
        filtered_data.resample(target_frequency)
    return filtered_data

# 调用这个
def data_downsamping_judge(filtered_data:Any,target_frequency:float) -> Any:
    """
    This function will down sampling the SINGLE eeg signal or a eeg signal list
    Input:
    raw_data: single Raw_data / eeg signal list
    target_frequency: target sampling frequency, ex. target_frequency=1.0
    Output:
    a eeg signal of type raw / multiple eeg signals of type list
    """
    if isinstance(filtered_data, list):
        new_raw_data_list = []
        for i,raw_data in enumerate(filtered_data):
            raw_data = data_downsamping(raw_data, target_frequency)
            new_raw_data_list.append(raw_data)
        return new_raw_data_list
    elif isinstance(filtered_data, mne.io.edf.edf.RawEDF):
        raw_data = data_downsamping(filtered_data, target_frequency)
        return raw_data
    else:
        print ('No match Type! Must be a List or a Raw data')
        return

# ===================================== extract data ========================================
def channels_extraction(raw_data:Raw, channels_to_extract:List[str]) -> Raw:
    """
    This function will extract needed channels from the SINGLE eeg signal
    Input:
    raw_data: Raw_data
    channels_to_extract: list of channel names that needed
    """
    raw_data = raw_data.pick_channels(channels_to_extract,ordered=False)
    return raw_data

# 调用这个
def channels_extraction_judge(raw: Any, channels_to_extract:List[str]) -> Any:
    """
    This function will extract needed channels from the SINGLE eeg signal or a eeg signal list
    Input:
    raw_data: single Raw_data / eeg signal list
    channels_to_extract: list of channel names that needed
    Output:
    a eeg signal of type raw / multiple eeg signals of type list
    """
    if isinstance(raw, list):
        new_raw_data_list = []
        for i,raw_data in enumerate(raw):
            raw_data = channels_extraction(raw_data, channels_to_extract)
            new_raw_data_list.append(raw_data)
        return new_raw_data_list
    elif isinstance(raw, mne.io.edf.edf.RawEDF):
        raw_data = channels_extraction(raw, channels_to_extract)
        return raw_data
    else:
        print('No match Type! Must be a List or a Raw data')
        return



################################################################################
#                            data preprocessing                                #
################################################################################

def data_preprocessing(raw_data: Any, montage: str = 'LE', band_pass_frequency:Tuple[float,float] = (1.0,35.0),
                       target_frequency: float = 250) -> Any:
    """
    Input:
    raw_data: single Raw_data / eeg signal list
    montage: not needed to change
    band_pass_frequency: limit of frequency of band pass filter
    target_frequency: target sampling frequency, ex. target_frequency=1.0
    channels_to_extract: list of channel names that needed
    Output:
    a eeg signal of type raw / multiple eeg signals of type list      
    """
    channels_to_extract = ['Fp1', 'Fp2', 'F3', 'F4', 'C3', 'C4', 'P3', 'P4', 'Fz', 'Cz', 'Pz']
    raw_data = data_rereference_judge(raw_data,montage)
    raw_data = channels_extraction_judge(raw_data,channels_to_extract)
    data_filted = data_filtering_judge(raw_data,band_pass_frequency)
    data_downsamped = data_downsamping_judge(data_filted,target_frequency)
    return data_downsamped


    
