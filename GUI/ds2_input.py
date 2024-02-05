from typing import List, Tuple, Dict, Any
import pickle
import os
import numpy as np
import mne
from mne.io import Raw
import csv
import pandas as pd
import joblib


def load_signal_edf(folder: str) -> Raw:
    channels_template: List[str] = ['EEG FP1', 'EEG FP2', 'EEG F3', 'EEG F4', 'EEG C3', 'EEG C4',
                                    'EEG P3', 'EEG P4', 'EEG O1', 'EEG O2', 'EEG F7', 'EEG F8',
                                    'EEG T3', 'EEG T4', 'EEG T5', 'EEG T6', 'EEG CZ']
    edf_data = mne.io.read_raw_edf(folder, preload=True)
    channels_original = edf_data.ch_names
    channels_standard: Dict[str, str] = {}
    for i, _ch in enumerate(channels_original):
        channels_standard[_ch] = _ch.split('-')[0]
    edf_data.rename_channels(channels_standard)
    edf_data.pick(channels_template)
    channels_picked = edf_data.ch_names
    channels_norm: Dict[str, str] = {}
    for _ch in channels_picked:
        channels_norm[_ch] = (_ch.split()[1]).capitalize()
    edf_data.rename_channels(channels_norm)
    edf_data.rename_channels({"T3": "T7", "T4": "T8", "T5": "P7", "T6": "P8"})
    return edf_data



def load_dataset(folder: str = r'E:\EEG\aaaaaaac') -> Tuple[List[str], List[List[str]],
                                                          List[np.ndarray],  List[float],
                                                          List[str], List[Tuple[int,float,float]]]:
    ids: List[str] = []
    channels: List[List[str]] = []
    data: List[np.ndarray] = []
    sampling_frequencies: List[float] = []
    reference_systems: List[str] = []
    eeg_labels: List[Tuple[int, float, float]] = []

    dataset = EEGDataSet_new(folder)
    for item in dataset:
        ids.append(item[0])
        channels.append(item[1])
        data.append(item[2])
        sampling_frequencies.append(item[3])
        reference_systems.append(item[4])
        eeg_labels.append(item[5])

    print("{}\t data are loaded.".format(len(ids)))
    return ids, channels, data, sampling_frequencies, reference_systems, eeg_labels


class EEGDataSet_new:
    def __init__(self, folder: str) -> None:
        assert isinstance(folder, str), "Parameter folder muss ein string sein aber {} gegeben".format(type(folder))
        assert os.path.exists(folder), 'Parameter folder existiert nicht!'
        # Initialisiere Listen für ids und labels
        self._folder = folder
        self._ids: List[str] = []
        self._eeg_labels: List[Tuple[int, float, float]] = []
        self._channels_template: List[str] = ['EEG FP1', 'EEG FP2', 'EEG F3', 'EEG F4', 'EEG C3', 'EEG C4',
                                              'EEG P3', 'EEG P4', 'EEG O1', 'EEG O2', 'EEG F7', 'EEG F8',
                                              'EEG T3', 'EEG T4', 'EEG T5', 'EEG T6', 'EEG CZ']
        # Lade references Datei
        with open(os.path.join(folder, 'REFERENCE.csv')) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            # Iteriere über jede Zeile
            for row in csv_reader:
                self._ids.append(row[0])
                self._eeg_labels.append((int(row[1]), float(row[2]), float(row[3])))

    def __len__(self):
        return len(self._ids)

    def __getitem__(self, idx) -> Tuple[str, List[str],
                                    Any,  float,
                                    str, Tuple[int,float,float]]:
        #Lade Matlab-Datei
        reference_system: str = ''
        edf_data = mne.io.read_raw_edf(os.path.join(self._folder, self._ids[idx] + '.edf'), preload=True)
        channels_original = edf_data.ch_names
        channels_standard: Dict[str, str] = {}
        for i, _ch in enumerate(channels_original):
            if i == 0:
                reference_system = ((_ch.split()[1]).split('-')[1]).upper()
            channels_standard[_ch] = _ch.split('-')[0]
        edf_data.rename_channels(channels_standard)
        edf_data.pick(self._channels_template)
        channels_picked = edf_data.ch_names
        # print(channels_picked)
        channels_norm: Dict[str, str] = {}
        for _ch in channels_picked:
            channels_norm[_ch] = (_ch.split()[1]).capitalize()
        edf_data.rename_channels(channels_norm)
        edf_data.rename_channels({"T3": "T7", "T4": "T8", "T5": "P7", "T6": "P8"})
        # ch_names = eeg_data.get('channels')
        channels: List[str] = edf_data.ch_names
        # data = eeg_data.get('data')
        sampling_frequency: float = edf_data.info['sfreq']
        return (self._ids[idx], channels, edf_data, sampling_frequency, reference_system, self._eeg_labels[idx])

    def get_labels(self):
        return self._eeg_labels


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


def load_model_pickle(path: str) -> Any:
    with open(path, 'rb') as f:
        model = pickle.load(f)
    return model


def load_model_joblib(path: str) -> Any:
    model = joblib.load(path)
    return model
