#!/bin/bash

# This bash script is used to generate symbol files for Breakpad
# Run like:
# sudo ./dump_syms.sh  # Use default paths (VTApp + lib directory)
# sudo ./dump_syms.sh /path/to/search  # Use single custom search path
# sudo ./dump_syms.sh /path/to/search1 /path/to/search2  # Use multiple custom search paths
# minidump_stackwalk f5357c79-052e-44c3-ead548ba-625b37c4.dmp symbols/ > crash_f535.log


currentPath=$(pwd)

# Check if dump_syms tool exists
dumpSymsTool="$currentPath/dump_syms"
if [ ! -f "$dumpSymsTool" ]; then
    echo "Error: dump_syms not exist"
    exit 1
fi

# Set executable permission on dump_syms
chmod 777 "$dumpSymsTool"

# Create symbols directory if not exist
symbolsDir="$currentPath/symbols"
mkdir -p "$symbolsDir"

# Add target files to dump symbols
# Initialize target files array
dumpTargetFiles=()

# Default search paths that will always be included
defaultSearchPaths=("$currentPath/../lib" "$currentPath/../bin" "$currentPath/../android-build/libs")

# Add user-provided search paths if any
if [ $# -gt 0 ]; then
    echo "Using default search paths plus custom search paths: ${defaultSearchPaths[@]} $@"
    allSearchPaths=("${defaultSearchPaths[@]}" "$@")
else
    echo "Using default search paths: ${defaultSearchPaths[@]}"
    allSearchPaths=("${defaultSearchPaths[@]}")
fi

# Process all search paths
for searchPath in "${allSearchPaths[@]}"; do
    # Check if search path exists
    if [ ! -d "$searchPath" ]; then
        echo "Warning: Search path '$searchPath' does not exist (skipping)"
        continue
    fi
    
    # Add all files from current search path
    while IFS= read -r -d '' file; do
        dumpTargetFiles+=($file)
    done < <(find "$searchPath" -type f -print0)
done

# Verify we have files to process
if [ ${#dumpTargetFiles[@]} -eq 0 ]; then
    echo "Error: No files found to process"
    exit 1
fi

echo "Found ${#dumpTargetFiles[@]} files to process"

# Generate symbol files for all target files
for file in "${dumpTargetFiles[@]}"; do
    fileName=$(basename "$file")
    symFileName="$fileName.sym"
    fileSymsPath="$symbolsDir/$symFileName"
    
    dumpSymsCmd="$dumpSymsTool \"$file\" > \"$fileSymsPath\""
    echo "dumpSymsCmd=$dumpSymsCmd"
    eval "$dumpSymsCmd"
    
    # Check if symbol file was created successfully
    if [ ! -f "$fileSymsPath" ]; then
        echo "Warning: Failed to create symbol file for $file"
        continue
    fi
    
    fileSymsDir="$symbolsDir/$fileName"
    mkdir -p "$fileSymsDir"
    
    # Read first line of symbol file to get symCode
    firstLine=$(head -n 1 "$fileSymsPath")
    if [ -z "$firstLine" ]; then
        echo "Warning: $fileSymsPath first line is empty!"
        rm "$fileSymsPath"  # Clean up empty symbol file
        continue
    fi
    
    firstLineStrs=($firstLine)
    if [ ${#firstLineStrs[@]} -lt 4 ]; then
        echo "Warning: $fileSymsPath first line format error!"
        rm "$fileSymsPath"  # Clean up invalid symbol file
        continue
    fi
    
    symCode=${firstLineStrs[3]}
    fileSymsCodeDir="$fileSymsDir/$symCode"
    mkdir -p "$fileSymsCodeDir"
    
    # Move symbol file to the correct directory
    fileCodeSymsPath="$fileSymsCodeDir/$symFileName"
    if [ -f "$fileCodeSymsPath" ]; then
        rm "$fileCodeSymsPath"
    fi
    
    mv "$fileSymsPath" "$fileCodeSymsPath"
done

echo "Symbol generation completed!"
