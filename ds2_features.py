import numpy as np
from mne.io import Raw
import mne
import scipy
import joblib

def feature_extraction(raw : Raw) -> np.ndarray:
    # 输入: Raw格式的数据
    # 输出: 一个维度为88的特征向量
    mne.set_log_level('WARNING')
    #----------------------------------feature extraction--------------------------------------#
    target_fs = raw.info['sfreq'] # Target Signal 250Hz
    eeg_whole_signal = raw.get_data()
    features = []
    if eeg_whole_signal.shape[1] < 5*target_fs:
        return np.zeros(88)

    feature_channels = []
    for channel_signal in eeg_whole_signal:  # 遍历通道 / 或6Montage:
        channels_median = median_abs_dev_filter(channel_signal,threshold=100)
        _, t, Zxx = scipy.signal.stft(x=channels_median,
                                    fs=target_fs,
                                    nperseg=5*target_fs, # 5秒窗口
                                    noverlap=2.5*target_fs) # 2.5秒重叠
        
        feature_list = []
        for (i, j) in ((1*5, 4*5), (4*5, 8*5), (8*5, 12*5), (12*5, 20*5)):

            # 求特征 -- 一个一维数组:
            subband_mean = np.mean(np.abs(Zxx[i:j,:])) * np.ones(len(t))
            subband_energy = np.sum(np.square(np.abs(Zxx[i:j,:])-subband_mean), axis=0)
            subband_std = np.std(np.abs(Zxx[i:j,:]), axis=0)

            # 求最大值 / 或平均值 / 或最大斜率
            energy = np.mean(subband_energy)
            std = np.mean(subband_std)

            feature_list.append(np.array([energy, std]))

        feature_stack = np.hstack(feature_list)

        feature_channels.append(feature_stack)
    features= np.hstack(feature_channels)

    mne.set_log_level('INFO')
    return features

#----------------------------------functions--------------------------------------#
def median_abs_dev_filter(data, threshold=3.5,axis=0): # median_absolute_deviation_filter
    median = np.median(data,axis=axis)
    dev_mad_rate = np.abs(data - median) / np.median(np.abs(data - median))
    for i, rate in enumerate(dev_mad_rate):
        if rate > threshold:
            data[i] = median
    return data