from typing import List, Tuple, Dict, Any
import pickle
import os
import numpy as np
import mne
from mne.io import Raw
import csv
import pandas as pd


def save_modell_as_pickle(model: Any, save_dir: str) -> None:
    with open(save_dir, 'wb') as f:
        pickle.dump(model, f)
    return None


def save_df_as_csv(df: pd.DataFrame, save_dir: str) -> None:
    df.to_csv(save_dir, index=False, header=False)
    return None

