from sklearn.ensemble import VotingClassifier
from sklearn.naive_bayes import BernoulliNB
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier

class EnsembleModel:
    def __init__(self):
        KNN_classifier = KNeighborsClassifier(n_neighbors=3)
        BernoulliNB1 = BernoulliNB()
        SVM_classifier1 = SVC(kernel='poly', degree=2, C=3000, probability=True)
        RF_classifier1 = RandomForestClassifier(n_estimators=1000, random_state=30)
        # weights = np.array([2.5, 2, 2, 2.5])
        weights = np.array([1, 1, 1, 1])
        ensemble_model = VotingClassifier(estimators=[('knn1', KNN_classifier),
                                                    ('svm1', SVM_classifier1),
                                                    ('rf1', RF_classifier1),
                                                    ('nb',BernoulliNB1)
                                                    ],
                                                    voting='soft',
                                                    weights=weights)

    def fit(self, X_train, y_train):
        # 在这里使用集成模型的fit方法来训练模型
        self.ensemble_model.fit(X_train, y_train)

    def predict(self, X_test):
        # 在这里执行预测操作
        return self.ensemble_model.predict(X_test)