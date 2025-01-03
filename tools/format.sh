#!/bin/bash

# Path folder saat ini
BASE_DIR=$(pwd)

# Daftar folder yang ingin diformat
INCLUDE_DIRS=(
    "ncpp" 
    "ngrammar" 
    "nlexer" 
    "nparser"
)  # Ganti dengan nama folder yang ingin diformat

# Temukan dan format file dengan ekstensi yang relevan di folder yang ditentukan
for DIR in "${INCLUDE_DIRS[@]}"; do
    # Pastikan folder ada
    if [ -d "$BASE_DIR/$DIR" ]; then
        find "$BASE_DIR/$DIR" -type f \( -name "*.h" -o -name "*.hpp" -o -name "*.c" -o -name "*.cc" -o -name "*.cpp" \) -print0 | while IFS= read -r -d '' FILE; do
            # Format file menggunakan clang-format
            clang-format -i "$FILE"
            echo "Formatted: $FILE"
        done
    else
        echo "Directory $BASE_DIR/$DIR does not exist, skipping..."
    fi
done

echo "Formatting complete."