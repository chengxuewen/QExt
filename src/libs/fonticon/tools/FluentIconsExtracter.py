import os
import re
import sys
import shutil
import argparse

import xml.etree.ElementTree as XML

version = "0.1.2"

def main():
    print("Fluent Icons SVG Extracter")
    parser = argparse.ArgumentParser(prog='FluentIconsExtracter.py', description='Corresponding variables')
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
    src_subdirs = os.listdir(src_directory)
    src_subdirs.sort()
    for dir in src_subdirs:
        if not " Temp " in dir:
            dir_path = src_directory + "/" + dir + "/SVG"
            all_files = get_all_files_in_directory(dir_path)
            for file in all_files:
                file_extension = os.path.splitext(file)[1]
                if ".svg" == file_extension:
                    file_name = os.path.basename(file)
                    file_name = os.path.splitext(file_name)[0]
                    if "_20_" in file_name:
                        new_file_name = file_name.replace("ic_fluent_", "")
                        new_file_name = new_file_name.replace("_20_", "_")
                        # new_file_name = format_file_name(new_file_name)
                        new_file_path = "{0}/{1}.svg".format(dst_directory, new_file_name)
                        try:
                            shutil.copy2(file, new_file_path, follow_symlinks=True)
                            enums_content += "\nIcon_" + new_file_name + ","
                            print("Copy {0} to {1} success!".format(file_name, new_file_path))
                            if not os.path.exists(new_file_path):
                                sys.exit("Copy {0} to {1} failed!".format(file, new_file_path))
                        except Exception as e:
                            sys.exit("Copy {0} to {1} failed, for {2}!".format(file, new_file_path, str(e)))
    enums_content += "\n};"
    print(enums_content)
    
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