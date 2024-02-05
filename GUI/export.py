#!/usr/bin/env python
# -*- coding: utf-8 -*-
##################################################################
##########                  Import                   #############
##################################################################
import pandas as pd
import os
from typing import List, Tuple, Dict, Any


##################################################################
##########          User-defined function            #############
##################################################################
def save_result_csv(res: str, conf: float, path_d: str) -> None:
    data_name = os.path.basename(path_d)
    id_pt = data_name.split('.')[0]
    result_dic = {
        'patient_id': id_pt,
        'diagnostic_result': res,
        'confidence': conf
    }
    result_df = pd.DataFrame(result_dic, index=[0])
    result_df.to_csv('result_{}.csv'.format(id_pt), index=False)
