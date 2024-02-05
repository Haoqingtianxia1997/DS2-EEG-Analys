import numpy as np
from mne.io import Raw
import mne
import scipy
import joblib


def feature_extraction(raw: Raw) -> np.ndarray:
    # 输入: Raw格式的数据
    # 输出: 一个维度为8的特征向量
    stride = 5
    # ----------------------------------feature extraction--------------------------------------#
    _fs = raw.info['sfreq']
    eeg_whole_signal = raw.get_data()
    _eeg_signals = np.mean(eeg_whole_signal, axis=0)  # 信号所有通道合并

    _, t, Zxx = scipy.signal.stft(x=_eeg_signals,
                                  fs=_fs,
                                  nperseg=1.0 * _fs,
                                  noverlap=0.5 * _fs)
    if len(t) > 10:
        energy_lst = []
        for n in range(0, len(t), stride):  # n是窗口的开端, 中点位置是(n_st+n_end)/2
            if n + stride < Zxx.shape[1]:  # 注意, 这里舍弃了最后一个不完整的窗口
                subband_window_delta = Zxx[0:4, n:n + stride]  # 窗口的位置:(0,5),(5,10),..
                subband_window_theta = Zxx[4:8, n:n + stride]  # 窗口的位置:(0,5),(5,10),..
                subband_window_alpha = Zxx[8:12, n:n + stride]  # 窗口的位置:(0,5),(5,10),..
                subband_window_betaa = Zxx[12:30, n:n + stride]  # 窗口的位置:(0,5),(5,10),..

                subband_energy_delta = np.sum(np.abs(subband_window_delta) ** 2)  # delta
                subband_std_delta = np.std(np.abs(subband_window_delta))
                subband_energy_theta = np.sum(np.abs(subband_window_theta) ** 2)  # theta
                subband_std_theta = np.std(np.abs(subband_window_theta))
                subband_energy_alpha = np.sum(np.abs(subband_window_alpha) ** 2)  # alpha
                subband_std_alpha = np.std(np.abs(subband_window_alpha))
                subband_energy_betaa = np.sum(np.abs(subband_window_betaa) ** 2)  # beta
                subband_std_betaa = np.std(np.abs(subband_window_betaa))

                energy_lst.append(np.array([subband_energy_delta,
                                            subband_std_delta,
                                            subband_energy_theta,
                                            subband_std_theta,
                                            subband_energy_alpha,
                                            subband_std_alpha,
                                            subband_energy_betaa,
                                            subband_std_betaa  # ,
                                            ]))  # 每个窗口的特征组合,在同一个维度上,12维

        energy_stack = np.vstack(energy_lst)  # 一个通道上的特征
        feat_smooth = []

        for i in range(energy_stack.shape[1]):
            feat_smooth.append(median_abs_dev_filter(energy_stack[:, i], threshold=3.5, axis=0))
        feats_smooth = np.vstack(feat_smooth)
        features = np.max(feats_smooth, axis=1)
        return features.reshape(1, -1)
    else:
        return np.array([0, 0, 0, 0, 0, 0, 0, 0]).reshape(1, -1)

#----------------------------------functions--------------------------------------#
def median_abs_dev_filter(data, threshold=3.5,axis=0): # median_absolute_deviation_filter
    median = np.median(data,axis=axis)
    dev_mad_rate = np.abs(data - median) / np.median(np.abs(data - median))
    for i, rate in enumerate(dev_mad_rate):
        if rate > threshold:
            data[i] = median
    return data
