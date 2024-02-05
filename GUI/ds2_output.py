from typing import List, Tuple, Dict, Any
import pickle
import os
import numpy as np
import mne
from mne.io import Raw
import csv
import pandas as pd
import matplotlib.pyplot as plt


def save_modell_as_pickle(model: Any, save_dir: str) -> None:
    with open(save_dir, 'wb') as f:
        pickle.dump(model, f)
    return None


def save_df_as_csv(df: pd.DataFrame, save_dir: str) -> None:
    df.to_csv(save_dir, index=False, header=False)
    return None


def pictures_save_and_show(raw: any, path: str = './cache') -> None:
    """
    raw ： A specific format, in which the EEG signal of one patient is saved after re-referencing
        and channel elimination.
    path ： the file path where the image is saved
    """
    eeg_data = raw.get_data()
    fs = raw.info['sfreq']
    channels = raw.ch_names
    time = raw.times
    time_arr = np.array(time).reshape(1, -1)
    time_max = int(time[-1])
    len_data = eeg_data.shape[1]
    x_index = range(len_data)
    save_dir = path
    # calculate PSD
    spectrum = raw.compute_psd()
    # show psd in the frequency domain
    fig1 = spectrum.plot(average=True, picks="data", show=False)
    fig1.savefig(os.path.join(save_dir, f'psd_fm.png'))
    plt.close(fig1)  # 关闭图像以释放内存
    # show psd-topomap
    fig2 = spectrum.plot_topomap(show=False)
    fig2.savefig(os.path.join(save_dir, f'psd_gm.png'))
    plt.close(fig2)  # 关闭图像以释放内存
    # if not os.path.exists(save_dir):
    #     os.makedirs(save_dir)
    # 遍历每个通道并绘制图像
#    print('check')
    for i in range(len(channels)):  #11个通道
        # 计算时间轴
#        t = np.arange(eeg_data.shape[1]) / fs
        # 创建图像，这里设置了一个固定的单位长度，比如每个单位长度代表1秒
        # 您可以根据需求调整这个长度
#        unit_per_second = 1  # 这个值可以根据您的具体需求来设置
        fig_width = time_max  # 图片宽度随时间长度变化
        fig_height = 2  # 图片高度固定
        if fig_width < 200:
            plt.figure(figsize=(fig_width, fig_height))
            plt.plot(time, eeg_data[i, :])  # 使用时间作为横轴
        else:
            plt.figure(figsize=(200, fig_height))
            plt.plot(time_arr[0, :int(200*fs)], eeg_data[i, :int(200*fs)])  # 使用时间作为横轴
            time_max = 200
        plt.title('EEG_Channel_{}'.format(i+1))
        plt.xlabel('Time(s)')
        plt.ylabel('Amplitude(V)')
        # 设置横坐标以十秒为单位的刻度
#        max_time = t[-1]
        plt.xticks(np.arange(0, time_max, 1))
        # 添加网格
        plt.grid(True)
        # 在每个横向网格线上显示对应的纵坐标读数
        plt.tick_params(axis='y', which='both', labelleft=True, labelright=True)
        # 设置x轴的限制以消除0时刻之前的空白
        plt.xlim(left=0)
        # 设置x轴的限制以消除最后时刻之后的空白
        plt.xlim(right=time_max)
        # 使用 tight_layout 减少留白
        plt.tight_layout(pad=0.5)
        # 保存图像，这里使用了一个固定的纵向分辨率，而横向分辨率会随时间长度变化
        dpi = 100  # 每英寸点数，这个也可以根据需要调整
        plt.savefig(os.path.join(save_dir, f'channel_{i+1}.png'), dpi=dpi)
        plt.close()  # 关闭图像，以免占用太多内存
    return None

