import csv
import matplotlib.pyplot as plt
import numpy as np
import os
import mne
from typing import Any,List,Tuple
from mne.io import Raw

# =================================== remove extremly lout noise ===========================
def check_amp (raw_data: Raw, **kwargs) -> Raw:
    '''
    check if there is a signal channal with amplitude > 100mV
    ja: remove it to bad channels
    no: return raw data
    '''
    data = raw_data.get_data()
    bad_channels = []
    for i, channel_data in enumerate(data):
        # check wether there is some channels with extremly signal
        if max(abs(channel_data)) > 1e5:
            ch_name = raw_data.ch_names[i]
            bad_channels.append(ch_name)
    # move it to badchannels
    raw_data.info['bads'] += bad_channels
    return raw_data

# ==================================== clean data ==========================================
def data_checking(raw: Any, label_list: List[int] = [0], **kwargs) -> Any:
    """
    Check if there is some channels missing, if Input ist a list, then also give the label list, the recording with missing data will be exclude.
    if Input is a raw, do not need label list, if there is a missing signal ,return None, else return the raw data
    """
    expected_channels = ['EEG FP1-LE', 'EEG FP2-LE', 'EEG F3-LE', 'EEG F4-LE', 'EEG C3-LE', 
                    'EEG C4-LE', 'EEG P3-LE', 'EEG P4-LE', 'EEG O1-LE', 'EEG O2-LE', 
                    'EEG F7-LE', 'EEG F8-LE', 'EEG T3-LE', 'EEG T4-LE', 'EEG T5-LE', 
                    'EEG T6-LE', 'EEG FZ-LE', 'EEG CZ-LE', 'EEG PZ-LE']
    if isinstance(raw, list):
        data_without_bad_channels = []
        label_without_bad_channels = []
        for i,data in enumerate(raw):
            data = check_amp (data)
            label = label_list[i]
            missing_channels = [ch for ch in expected_channels if ch not in data.info['ch_names']]
            if len(missing_channels) != 0:
                continue
            else:
                data_without_bad_channels.append(data)
                label_without_bad_channels.append(label)    
        return data_without_bad_channels, label_without_bad_channels 
    
    elif isinstance(raw, mne.io.edf.edf.RawEDF):
        raw = check_amp (raw)
        missing_channels = [ch for ch in expected_channels if ch not in raw.info['ch_names']]
        if len(missing_channels) != 0:
            print (f'This data has missing chaneels,{missing_channels}')
            return None
        else:
            return raw
    else:
        print ('No match Type! Must be a List or a Raw data')
        return

# ==================================== rereference =========================================
# def rename_channels(raw_data: Raw) -> Raw:
#     """
#     This function ist to deal with the EEG signal that readed from files
#     It rename the channels and extract the channels that needed in the plotting
#     one call the function can deal with only one EEG signal in format Raw
#     Input => mne.io.read_raw_edf(dir)
#     Output => new raw data that can build easycap-M1 montage
#     """
#     mne.set_log_level('WARNING')
#     raw_data.load_data() # Load Data
#     new_name = [chan.replace("EEG ", "").replace("-LE", "").replace("-REF","") for chan in raw_data.info['ch_names']] # EEG T3-LE ->T3
#     raw_data.rename_channels({old_name: new_name for old_name, new_name in zip(raw_data.info['ch_names'], new_name)})
#     channels_to_extract = ['FP1', 'FP2', 'F3', 'F4', 'C3', 'C4', 'P3', 'P4', 'O1', 'O2', 'F7', 'F8', 'T3', 'T4', 'T5', 'T6', 'FZ', 'CZ', 'PZ']
#     raw_data = channels_extraction(raw_data,channels_to_extract)
#     raw_data.rename_channels({'T3':'T7', 'T4':'T8', 'T5':'P7', 'T6':'P8','FP1':'Fp1','FP2':'Fp2','FZ':'Fz','CZ':'Cz','PZ':'Pz'}) # 把旧的命名系统,改成新的
#     mne.set_log_level('INFO')
#     return raw_data


def data_rereference(raw_data: Raw, montage: str = 'LE', **kwargs) -> Any:
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
        mne.set_log_level('WARNING')
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
        mne.set_log_level('INFO')
        return raw_data
    else:
        print('No matching method!')
        return 0
    
def data_rereference_judge(raw: Any, montage: str = 'LE', **kwargs) -> Any:
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
def data_filtering(data_wait_for_filter: Raw, 
                   band_pass_frequency: Tuple[float,float] = (1.0,35.0), **kwargs) -> Raw:
    """
    This function will use the bandpss filter on the SINGLE eeg signal
    Input:
    data_wait_for_filter: Raw_data
    band_pass_frequency: limit of frequency of band pass filter
    """
    mne.set_log_level('WARNING')
    low_frequency = band_pass_frequency[0]
    high_frequency = band_pass_frequency[1]
    meg_picks = mne.pick_types(raw.info, meg=True)
    freqs = (50, 100)
    data_wait_for_filter.notch_filter(freqs=freqs, picks=meg_picks)
    data_wait_for_filter.filter(l_freq=low_frequency, h_freq=high_frequency)
    mne.set_log_level('INFO')
    return data_wait_for_filter
                       

def data_filtering_judge(data_wait_for_filter: Any, 
                         band_pass_frequency: Tuple[float,float] = (1.0,35.0), **kwargs) -> Any:
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
def data_downsamping(filtered_data: Raw, target_frequency: float, **kwargs)->Raw:
    """
    This function will down sampling the SINGLE eeg signal
    Input:
    filtered_data: Raw_data
    target_frequency: target sampling frequency, ex. target_frequency=1.0
    """
    mne.set_log_level('WARNING')
    if filtered_data.info['sfreq'] > target_frequency:
        filtered_data.resample(target_frequency)
    mne.set_log_level('INFO')
    return filtered_data


def data_downsamping_judge(filtered_data: Any, target_frequency: float, **kwargs) -> Any:
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
def channels_extraction(raw_data: Raw, channels_to_extract: List[str], **kwargs) -> Raw:
    """
    This function will extract needed channels from the SINGLE eeg signal
    Input:
    raw_data: Raw_data
    channels_to_extract: list of channel names that needed
    """
    mne.set_log_level('WARNING')
    raw_data = raw_data.pick_channels(channels_to_extract, ordered=False)
    mne.set_log_level('INFO')
    return raw_data

# loading this
def channels_extraction_judge(raw: Any, channels_to_extract: List[str], **kwargs) -> Any:
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

def data_preprocessing(raw_data: Any, montage: str = 'LE', band_pass_frequency: Tuple[float,float] = (1.0,35.0), 
                       target_frequency: float = 250, 
                       channels_to_extract: List[str] = ['Fp1', 'Fp2', 'F3', 'F4', 'C3', 'C4', 'P3', 'P4', 'Fz', 'Cz', 'Pz'], 
                       **kwargs) -> Any:
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
    raw_data = data_rereference_judge(raw_data, montage)
    raw_data = channels_extraction_judge(raw_data, channels_to_extract)
    data_downsamped = data_downsamping_judge(raw_data, target_frequency)
    data_filted = data_filtering_judge(data_downsamped, band_pass_frequency)
    return data_downsamped


    