# Harsh Driving Detection System (HDDS)

This is the research project for the design and development of the Harsh Driving Detection System that can accurately detect and classify harsh driving events when driving data is passed to the trained algorithm. The primary features/parameters that we are using for the classification of harsh driving events are sudden acceleration, sudden braking, aggressive left or right line changing, and sudden left or right turning. In this project, our main focus was on the design and development of an ML algorithm that can accurately classify driving style as safe or harsh and if the driving was harsh then which harsh driving events were performed during a complete driving trip. Initially, SVM, DT, and RF ML models were trained, then after model evaluation, the RF model was used for final field trials.

## Preview

1. Conceptual framework of the proposed system
<img src="https://drive.google.com/uc?export=view&id=1yOTOHY11HUqVYylhTtX8cKrullv0e-Gi" width=300>

2. Block diagram
<img src="https://drive.google.com/uc?export=view&id=1STfKkvCj59OH7MlaBc_MglEqSlNbhVnj" width=300>
   
3. Visualization of Raw sensor data and driving maneuver
<img src="https://drive.google.com/uc?export=view&id=1nl4hUeum7ww1N-y-7EG5fVj0CARKIT-z" width=300>

4. Final result of field trials
<p>
  <img src="https://drive.google.com/uc?export=view&id=1JTr7nf4Pta0gOaHZe1Kh_-6ZjdyGLz1n" width=300 height=250>
  <img src="https://drive.google.com/uc?export=view&id=1YJfkZQK5NuwCwzml1db5TyhHesFs8mh-" width=300 height=250>
</p>

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for testing purposes. For installation of required libraries please see the [Requirements](#requirements) section. 

* First _**fork**_ and then _**clone**_ the repository on your local machine.
* ["MPU9250_raw_data"](./MPU9250_raw_data_code.ino) file contains code for the configuration and raw data collection from the MPU9250 sensor. Run this file and upload the code on the microcontroller to get raw sensor data.
* [Arduino IDE](https://www.arduino.cc/en/software) - IDE for Arduino microcontroller, is used for the sensor configuration.
* Once you start getting raw data from the microcontroller run the ["CSV file creation"](https://github.com/Saboor47/HDDS/blob/main/code%20for%20csv%20file%20creation.py) files to store raw sensor data in CSV file.
* ["Built models"](https://github.com/Saboor47/HDDS/tree/main/built%20models) folder contains 6 trained ML models for the detection of each harsh driving event.
* Then run the ["ML model testing"](https://github.com/Saboor47/HDDS/blob/main/code%20for%20ML%20model%20testing.ipynb) file to detect harsh driving events if present in the stored raw data in CSV file.
* Run ["Raw data plotting"](https://github.com/Saboor47/HDDS/blob/main/code%20raw%20data%20ploting.py) file to visualize the raw data.
  
## Requirements

* All required libraries are specified in the [requirements.txt](./requirements.txt) file.
* To install all required libraries, open the Python terminal and run the following command:
  ```python
  pip install lib
  ```
  replace "lib" with the libraries presented in the [requirements.txt](./requirements.txt) file.

## Authors

* [Saboor Ahmed](https://www.linkedin.com/in/saboor-ahmed)
