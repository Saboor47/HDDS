import numpy as np
import pandas as pd
from pykalman import KalmanFilter
from tqdm import tqdm

# Path from where to read raw data
raw_file_path = './raw_data'
# Name of txt file that contain raw data file names
file_name = r'raw_data_name.txt'
# Path from where to store filter data
filter_file_path = "./filter_data"

f = open('{}\{}'.format(raw_file_path,file_name), "r", encoding="utf-8")
file_names = map(lambda x: x[:-1], f.readlines())
f.close()

csv_names = list(file_names)
# print(csv_names)

variables = ['acc_x','acc_y','acc_z','gyro_x','gyro_y','gyro_z','mag_x','mag_y','mag_z']

for name in csv_names:
    df = pd.read_csv(f"{raw_file_path}\{name}")
    for var in tqdm(variables, desc=name):
        # Check for missing values
        df.dropna(inplace=True)
        data = df[var]
        kf = KalmanFilter(initial_state_mean = data.iloc[0], n_dim_obs=1)
        filter_data = kf.em(data).filter(data)[0].T[0]
        filter_data_s = pd.Series(np.array(filter_data), name=var)
        df[var] = filter_data_s
        
        # Normalized magnetometer data with min-max normalization
            
        if  var == "mag_x" or var =="mag_y" or var =="mag_z":
            normalized_data = (data-data.min())/(data.max()-data.min())
            df[var] = normalized_data
    # Save filtered data
    df.to_csv(f"{filter_file_path}\{name}", index=False)
