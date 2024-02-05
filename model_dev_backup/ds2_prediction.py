import numpy as np
from typing import Any, List, Tuple
from mne.io import Raw
import mne
import scipy
import joblib
from sklearn.metrics import accuracy_score, recall_score, precision_score, f1_score


def predict_labels(features: np.ndarray, model: Any) -> Tuple[List[int], List[float]]:
    label_list: List[int] = []
    conf_list: List[float] = []
    len_0 = features.shape[0]
    pre = model.predict(features)
    prob = model.predict_proba(features)
    for i in range(len_0):
        if int(pre[i]):
            label_list.append(1)
            conf_list.append(prob[i][1])
        else:
            label_list.append(0)
            conf_list.append(prob[i][0])
    return label_list, conf_list


def show_performance(labels_true: np.ndarray, labels_pre: np.ndarray) -> None:
    auc = accuracy_score(labels_true, labels_pre)
    precision = precision_score(labels_true, labels_pre, average='macro')
    recall = recall_score(labels_true, labels_pre, average='macro')
    f1 = f1_score(labels_true, labels_pre, average='macro')
    print('***************** Zusammenfassung der Ergebnisse ********************')
    print('Accuracy: %.4f' % auc)
    print('Precision: %.4f' % precision)
    print('Recall: %.4f' % recall)
    print('F1_Score: %.4f' % f1)
    return None
