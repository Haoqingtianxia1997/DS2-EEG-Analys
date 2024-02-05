import csv
import matplotlib.pyplot as plt
import numpy as np
import os
import mne
from typing import Any,List
from mne.io import Raw
import sys


# ==================================== caculate PSD ========================================
def caculate_PSD(raw_data: Raw, **kwargs) -> Any:
    """
    Calculates the Power Spectral Density (PSD) of the raw data.

    Parameters:
    - raw_data (Raw): The raw data object.

    Returns:
    - spectrum (Any): The computed power spectral density.
    """
    
    mne.set_log_level('WARNING')
    spectrum = raw_data.compute_psd()
    mne.set_log_level('INFO')
    return spectrum


# ==================================== plot PSD in frequency domain ========================
def plot_psd(raw_data: Raw, save_dir: str = 'pictures', **kwargs) -> None:
    """
    plot and save psd result
    save_dir: the path you want to save pictures
    """
    mne.set_log_level('WARNING')
    psd_result = caculate_PSD(raw_data)
    if not os.path.exists(f'{save_dir}/psd_result'):
        os.makedirs(f'{save_dir}/psd_result')
    fig = psd_result.plot(average=True, picks="data")
    fig.savefig(f'{save_dir}/psd_result/psd_result.png')
    mne.set_log_level('INFO')
    return None


# ==================================== show psd topomap ====================================
def plot_psd_topomap(raw_data: Raw, save_dir: str = 'pictures', **kwargs) -> None:
    """
    plot and save psd topomap
    save_dir: the path you want to save pictures
    """
    mne.set_log_level('WARNING')
    psd_result = caculate_PSD(raw_data)
    if not os.path.exists(f'{save_dir}/psd_topomap'):
        os.makedirs(f'{save_dir}/psd_topomap')
    fig = psd_result.plot_topomap()
    fig.savefig(f'{save_dir}/psd_topomap/psd_topomap.png')
    mne.set_log_level('INFO')
    return None


# ==================================== plot eeg signals ====================================
def plot_eeg_signal(raw: Raw, channels_to_extract: List[str], save_dir: str = 'pictures', **kwargs) -> None:
    """
    plot and save all eeg signals
    save_dir: the path you want to save pictures
    """   
    mne.set_log_level('WARNING')
    eeg_data = raw.get_data()
    fs = raw.info['sfreq']
    if not os.path.exists(f'{save_dir}/eeg_signals'):
        os.makedirs(f'{save_dir}/eeg_signals')
    for i in range(len(eeg_data)):
        # count time axis
        t = np.arange(eeg_data.shape[1]) / fs
        
        # Here, a fixed unit length is set, for example, 
        # each unit length represents 1 second. You can adjust this length according to your needs.
        unit_per_second = 5 
        # picture width changing with the time axis
        fig_width = t[-1] / unit_per_second
        # heigt of picture is fixed
        fig_height = 4 
        plt.figure(figsize=(fig_width, fig_height))
        
        plt.plot(t, eeg_data[i, :])
        plt.title(f'EEG Channel {channels_to_extract[i]}')
        plt.xlabel('Time (s)')
        plt.ylabel('Amplitude')

        max_time = t[-1]
        plt.xticks(np.arange(0, max_time, 10))
        
        plt.grid(True)
        
        # Display the corresponding vertical coordinate readings on each horizontal grid line.
        plt.tick_params(axis='y', which='both', labelleft=True, labelright=True)

        plt.xlim(left=0)
        plt.xlim(right=t[-1])
        plt.tight_layout()
        
        # The image is saved with a fixed vertical resolution, 
        # while the horizontal resolution changes according to the duration of time.
        # Dots per inch, this can also be adjusted as needed.
        dpi = 100 
        plt.savefig(os.path.join(f'{save_dir}/eeg_signals', f'Channel_{i+1}.png'), dpi=dpi)
        plt.close()
    mne.set_log_level('INFO')
    print(t[-1], fs, len(eeg_data),5)
    return None
