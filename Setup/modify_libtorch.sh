#!/bin/bash

# Define file paths
ENUM_FILE="Z:/Libtorch Versions/libtorch-2.2.1+cu121/libtorch/include/torch/csrc/api/include/torch/enum.h"
MODULE_FILE="Z:/Libtorch Versions/libtorch-2.2.1+cu121/libtorch/include/torch/csrc/api/include/torch/nn/module.h"

# Check if the enum.h file exists
if [[ -f "$ENUM_FILE" ]]; then
    # Use sed to remove "TORCH_API extern" from the specified line
    sed -i '/TORCH_API extern const enumtype::k##name k##name;/s/TORCH_API extern //' "$ENUM_FILE"
    echo "Updated $ENUM_FILE"
else
    echo "File $ENUM_FILE not found!"
fi

# Check if the module.h file exists
if [[ -f "$MODULE_FILE" ]]; then
    # Use sed to add the friend class line under the specified comment with 2-space indentation
    sed -i '/\/\/ Friend classes./a\  friend class IAtumLayer;' "$MODULE_FILE"
    echo "Updated $MODULE_FILE"
else
    echo "File $MODULE_FILE not found!"
fi
