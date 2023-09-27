#!/bin/bash

# Define the source directory
source_dir="./"

# Define the destination
destination="aba215@csil-cpu8.csil.sfu.ca:/home/aba215/373/parser"

# Define the SSH key
ssh_key="/Users/alexbruma/.ssh/id_rsa"

# Create an array of excluded files/directories
excludes=("sync_files.sh" ".vscode")

# Build the exclude options for rsync
exclude_opts=""
for exclude in "${excludes[@]}"; do
  exclude_opts+=" --exclude='$exclude'"
done

# Run the rsync command with SSH key authentication and multiple exclusions
rsync -avz --delete -e "ssh -i $ssh_key" $exclude_opts "$source_dir" "$destination"

