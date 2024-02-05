import csv
import matplotlib.pyplot as plt
import numpy as np
import os
import mne
from typing import Any,List
from mne.io import Raw
import sys


# ==================================== caculate PSD ========================================
def caculate_PSD(raw_data: Raw) -> Any:
    mne.set_log_level('WARNING')
    spectrum =raw_data.compute_psd()
    mne.set_log_level('INFO')
    return spectrum


# ==================================== plot PSD in frequency domain ========================
def plot_psd(raw_data: Raw,save_dir:str = 'pictures') -> None:
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
def plot_psd_topomap(raw_data: Raw,save_dir:str = 'pictures') -> None:
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
def plot_eeg_signal(raw: Raw, channels_to_extract:List[str],save_dir:str = 'pictures') -> None:
    """
    plot and save all eeg signals
    save_dir: the path you want to save pictures
    """   
    mne.set_log_level('WARNING')
    eeg_data = raw.get_data()
    fs = raw.info['sfreq']
    if not os.path.exists(f'{save_dir}/eeg_signals'):
        os.makedirs(f'{save_dir}/eeg_signals')
    # 遍历每个通道并绘制图像
    for i in range(len(eeg_data)):
        # 计算时间轴
        t = np.arange(eeg_data.shape[1]) / fs
        
        # 创建图像，这里设置了一个固定的单位长度，比如每个单位长度代表1秒
        # 您可以根据需求调整这个长度
        unit_per_second = 5  # 这个值可以根据您的具体需求来设置
        fig_width = t[-1] / unit_per_second  # 图片宽度随时间长度变化
        fig_height = 4 # 图片高度固定
        plt.figure(figsize=(fig_width, fig_height))
        
        plt.plot(t, eeg_data[i, :])  # 使用时间作为横轴
        plt.title(f'EEG Channel {channels_to_extract[i]}')
        plt.xlabel('Time (s)')
        plt.ylabel('Amplitude')

        # 设置横坐标以十秒为单位的刻度
        max_time = t[-1]
        plt.xticks(np.arange(0, max_time, 10))
        
        # 添加网格
        plt.grid(True)
        
        # 在每个横向网格线上显示对应的纵坐标读数
        plt.tick_params(axis='y', which='both', labelleft=True, labelright=True)

        # 设置x轴的限制以消除0时刻之前的空白
        plt.xlim(left=0)
        # 设置x轴的限制以消除最后时刻之后的空白
        plt.xlim(right=t[-1])
        
        # 使用 tight_layout 减少留白
        plt.tight_layout()
        # 保存图像，这里使用了一个固定的纵向分辨率，而横向分辨率会随时间长度变化
        dpi = 100  # 每英寸点数，这个也可以根据需要调整
        plt.savefig(os.path.join(f'{save_dir}/eeg_signals', f'Channel_{i+1}.png'), dpi=dpi)
        plt.close()  # 关闭图像，以免占用太多内存
    mne.set_log_level('INFO')
    print(t[-1],fs,len(eeg_data),5)
    return None
