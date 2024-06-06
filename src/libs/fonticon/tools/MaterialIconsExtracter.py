import os
import re
import sys
import shutil
import argparse

import xml.etree.ElementTree as XML

version = "0.1.2"

def main():
    print("Material Icons SVG Extracter")
    parser = argparse.ArgumentParser(prog='MaterialIconsExtracter.py', description='Corresponding variables')
    parser.add_argument('-v', '--version', action='version', version=f'%(prog)s {version}')
    parser.add_argument('-s', '--source', type=str, help='The source directory of the svg icons to be extract', metavar='\b', required=True)
    parser.add_argument('-d', '--destn', action='store', help="The destination directory of the svg icons to be save", metavar='\b', required=True)

    args = parser.parse_args()
    
    src_directory = os.path.abspath(args.source)
    dst_directory = os.path.abspath(args.destn)

    if not os.path.exists(src_directory):
        sys.exit("The source directory \"{0}\" does not exist!".format(src_directory))
        
    if not os.path.exists(dst_directory):
        user_input = input("Destination directory {0} does not exist, Are you want to create it?(yes/no): ".format(dst_directory))
        user_input_lower = user_input.lower()
        valid_input = {"yes", "y", "on", "ok", "o"}
        if user_input_lower in valid_input:
            try:
                os.mkdir(dst_directory)
            except Exception as e:
                sys.exit("Create destination directory \"{0}\" failed, for {1}".format(dst_directory, str(e)))
        else:
            sys.exit("The destination directory \"{0}\" does not exist!".format(dst_directory))

    enums_file_path = dst_directory + "/0Enums.txt"
    enums_content = "enum IconEnum {"
    src_subdirs = [d for d in os.listdir(src_directory) if os.path.isdir(os.path.join(src_directory, d))]
    all_dirs = []
    for dir in src_subdirs:
        dir_path = src_directory + "/" + dir
        subdirs = [d for d in os.listdir(dir_path) if os.path.isdir(os.path.join(dir_path, d))];
        for subdir in subdirs:
            all_dirs.append((subdir, dir_path))
    all_dirs.sort()
    # print(f"all_dirs={all_dirs}")
    valid_types = {"outlined", "round", "sharp"}
    for dir in all_dirs:
        dir_path = dir[1] + "/" + dir[0]
        subdirs = [d for d in os.listdir(dir_path) if os.path.isdir(os.path.join(dir_path, d))];
        # print(f"dir_path={dir_path}")
        for subdir in subdirs:
            type = subdir.replace("materialicons", "")
            # print(f"subdir={subdir}")
            # print(f"type={type}")
            if type in valid_types:
                subdir_path = dir_path + "/" + subdir
                all_files = get_all_files_in_directory(subdir_path)
                # print(f"all_files={all_files}")
                if len(all_files) > 0:
                    file = all_files[0]
                    # print(f"file={file}")
                    file_extension = os.path.splitext(file)[1]
                    if ".svg" == file_extension:
                        file_name = os.path.basename(dir_path) + "_" + type
                        new_file_name = file_name
                        # new_file_name = format_file_name(file_name)
                        new_file_path = "{0}/{1}.svg".format(dst_directory, new_file_name)
                        try:
                            shutil.copy(file, new_file_path)
                            enums_content += "\nIcon_" + new_file_name + ","
                            print("Copy {0} to {1} success!".format(file_name, new_file_path))
                        except Exception as e:
                            print("Copy {0} to {1} failed, for {2}!".format(file, new_file_path, str(e)))
    enums_content += "\n};"
    # print(enums_content)
    
    try:
        with open(enums_file_path, 'w') as file:
            file.write(enums_content)
    except Exception as e:
        print("Write enums_content to {0} failed, for {1}!".format(enums_file_path, str(e)))
    
def get_all_files_in_directory(directory):
    all_files = []
    for root, dirs, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            all_files.append(file_path)
    return all_files

def format_file_name(file_name):
    underline = True
    new_file_name = ""
    for char in file_name:
        if '_' == char:
            underline = True
        else:
            if underline:
                underline = False
                new_file_name += char.upper()
            else:
                new_file_name += char
    return new_file_name

if __name__ == "__main__":
    main()