from typing import List
from sklearn.model_selection import train_test_split
from sklearn.metrics import f1_score
import joblib
import pickle
import numpy as np
from sklearn.ensemble import VotingClassifier
from sklearn.naive_bayes import GaussianNB
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier
from typing import List, Tuple, Dict, Any


def train(features : np.ndarray, labels: np.ndarray) -> Any:
    # Input: features: feature matrix containing all features; Labels: list containing all labels; model path
    # Output: None
    # Save the model locally
    # X_train, X_test, y_train, y_test = train_test_split(features, labels, test_size=0.23,
    #                                                      random_state=15,
    #                                                      shuffle=True)
    #========================================================================================
    gaussian_NB1 = GaussianNB()
    knn_classifier1 = KNeighborsClassifier(n_neighbors=20,algorithm='auto')
    knn_classifier2 = KNeighborsClassifier(n_neighbors=10,algorithm='auto')
    svm_classifier1 = SVC(kernel='poly', degree=10, C=0.5, probability=True)
    rf_classifier1 = RandomForestClassifier(n_estimators=2500, random_state=42)

    ensemble_model = VotingClassifier(estimators=[('knn1', knn_classifier1),
                                                ('knn2', knn_classifier2),
                                                ('svm1', svm_classifier1),
                                                ('rf1', rf_classifier1),
                                                ('nb',gaussian_NB1)
                                                ],
                                                voting='soft')
    
    #========================================================================================
    ensemble_model.fit(features, labels.ravel())
    # y_pred = ensemble_model.predict(X_test)
    #
    # f1_ensem = f1_score(y_test, y_pred)
    # print("F1 score:", f1_ensem)
    # joblib.dump(ensemble_model, f'{save_dir}/model_f1{f1_ensem}.pkl')
    return ensemble_model

