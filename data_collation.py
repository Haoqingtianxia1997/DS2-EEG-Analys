from typing import List, Tuple, Dict, Any
import os
import numpy as np
import shutil
import pandas as pd


def copyfile(srcfile, dstpath):  # Move Functions
    if not os.path.isfile(srcfile):
        print("%s not exist!" % (srcfile))
    else:
        fpath, fname = os.path.split(srcfile)
        if not os.path.exists(dstpath):
            os.makedirs(dstpath)
        shutil.copy(srcfile, dstpath + fname)
        print("copy %s -> %s" % (srcfile, dstpath + fname))


dev_folder = r'E:\TUH\dev'  # original dataset folder
uniform_data_folder = r'E:\TUH\uniform_data'  # new and balance dataset folder

seiz_counter = 0
nonseiz_counter = 0
ids: List[str] = []
labels: List[int] = []
onset: List[float] = []
offset: List[float] = []

for root, dirs, files in os.walk(dev_folder):
    if files:
        for _f in files:
            _id, _extension = os.path.splitext(_f)
            if _extension == '.csv_bi':
                csv_bi_data = np.genfromtxt(os.path.join(root, _f), delimiter=',', dtype=str)
                if csv_bi_data[1][3] == 'seiz':
                    if seiz_counter < 150:
                        copyfile(root + r'\\' + _id + '.edf', r'E:\TUH\uniform_data\\')
                        # copyfile(root + r'\\' + _f, r'E:\TUH\uniform_data\\')
                        ids.append(_id)
                        onset.append(float(csv_bi_data[1][1]))
                        offset.append(float(csv_bi_data[1][2]))
                        labels.append(1)
                        seiz_counter += 1
                else:
                    if nonseiz_counter < 150:
                        copyfile(root + r'\\' + _id + '.edf', r'E:\TUH\uniform_data\\')
                        # copyfile(root + r'\\' + _f, r'E:\TUH\uniform_data\\')
                        ids.append(_id)
                        labels.append(0)
                        onset.append(0.)
                        offset.append(0.)
                        nonseiz_counter += 1

df = pd.DataFrame({'id': ids, 'label': labels, 'onset': onset, 'offset': offset})
df.to_csv(r'E:\TUH\uniform_data\REFERENCE.csv', index=False, header=False)

