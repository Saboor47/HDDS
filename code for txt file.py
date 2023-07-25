import os

def file_name(path):
    dir = os.listdir(path)
    i = 0
    # Checking if the list is empty or not
    if len(dir) == 0:
        print("Directory is empty")
    else:
        for path_file in os.scandir(path):
            
            if path_file.is_file():
                i += 1
                with open ('{}\{}'.format(file_path,name),'a') as file:
                    if path_file.name == name:
                        break
                    else:
                        file.write(path_file.name)
                        file.write('\n')
    print('Total number of files: ', i)
    print("File is created successfully")

# Path from where to read files name
file_path = './Raw data'
# Name of txt file
name = 'raw_data_name.txt'

file_name(file_path)

