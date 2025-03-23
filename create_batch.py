import os
import sys

"""
@file create_batch.py
@brief Script to generate a batch file for running bio_alg commands with different parameters.

This script takes in an instance directory, a result file, and an output batch file as command-line arguments.
It then generates a batch file with various bio_alg commands for each instance found in the instance directory.

@usage
    python create_batch.py <instance_directory> <result_file> <output_batch_file>
    Example:
    python create_batch.py data/qap/ bur26a batch.bat
"""

# Check if the correct number of arguments is passed.
if len(sys.argv) != 4:
    print("Usage: python create_batch.py <instance_directory> <result_file> <output_batch_file>")
    print("E.g.: python create_batch.py data/qap/ bur26a batch.bat")
    sys.exit(1)

# Assigning command line arguments to variables
instance_dir = sys.argv[1]
result_file = sys.argv[2]
output_batch = sys.argv[3]

# List of commands to be written into the batch file
commands = [
    "bio_alg heuristic {dir} {instance} {result}",
    "bio_alg random {dir} {instance} {result}",
    "bio_alg antiheuristic {dir} {instance} {result}",
    "bio_alg heuristic {dir} {instance} {result} greedy_LS",
    "bio_alg heuristic {dir} {instance} {result} steepest_LS",
    "bio_alg random {dir} {instance} {result} greedy_LS",
    "bio_alg antiheuristic {dir} {instance} {result} greedy_LS"
]

# Retrieve instance names (without extension) for instances that have a corresponding solution file
instance_names = [f[:-4] for f in os.listdir(instance_dir) if f.endswith(".dat") and os.path.exists(os.path.join(instance_dir, f[:-4] + ".sln"))]

# Open and write the batch file
with open(output_batch, "w") as batch_file:
    # Write the batch script header
    batch_file.write("@echo off\n")
    
    # Write each command for each instance
    for instance in instance_names:
        for cmd in commands:
            batch_file.write(cmd.format(dir=instance_dir, instance=instance, result=result_file) + "\n")

# Print success message
print(f"Batch script '{output_batch}' created successfully.")
