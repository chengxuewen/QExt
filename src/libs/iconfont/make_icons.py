import os
import sys
import shutil
from pathlib import Path


src_dir = sys.path[0] + "/src"
target_dir = sys.path[0] + "/icons"
print("src_dir:", src_dir)
print("target_dir:", target_dir)

if os.path.exists(target_dir):
    shutil.rmtree(target_dir)
os.mkdir(target_dir)

for categoryDir in Path(src_dir).iterdir():
    categoryName = Path(categoryDir).name
    targetCategoryDir = target_dir + "/" + categoryName
    if os.path.exists(targetCategoryDir):
        shutil.rmtree(targetCategoryDir)
    os.mkdir(targetCategoryDir)
    # print("iconsCategoryPath:", iconsCategoryPath)
    # print("categoryName:", categoryName)
    for productionDir in Path(categoryDir).iterdir():
        productionName = Path(productionDir).name
        # print("productionName:", productionName)
        for iconDir in Path(productionDir).iterdir():
            iconName = Path(iconDir).name
            iconType = iconName[13:]
            # print("iconDir:", iconDir)
            # print("iconName:", iconName)
            # print("iconType:", iconType)
            iconPath = str(iconDir) + "/24px.svg"
            # print("iconPath:", iconPath)
            if os.path.exists(iconPath):
                if 0 == len(iconType):
                    targetIconPath = targetCategoryDir + "/" + productionName + "_24px.svg"
                else:
                    targetIconPath = targetCategoryDir + "/" + productionName + "_" + iconType + "_24px.svg"
                print("targetIconPath:", targetIconPath)
                shutil.copy(iconPath, targetIconPath)