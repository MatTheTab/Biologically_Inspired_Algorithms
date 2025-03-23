import os
import sys

if len(sys.argv) != 4:
    print("Usage: python generate_batch.py <instance_directory> <result_file> <output_batch_file>")
    print("E.g.: python generate_batch.py data/qap/ bur26a batch.bat")
    sys.exit(1)

instance_dir = sys.argv[1]
result_file = sys.argv[2]
output_batch = sys.argv[3]

commands = [
    "bio_alg heuristic {dir} {instance} {result}",
    "bio_alg random {dir} {instance} {result}",
    "bio_alg antiheuristic {dir} {instance} {result}",
    "bio_alg heuristic {dir} {instance} {result} greedy_LS",
    "bio_alg heuristic {dir} {instance} {result} steepest_LS",
    "bio_alg random {dir} {instance} {result} greedy_LS",
    "bio_alg antiheuristic {dir} {instance} {result} greedy_LS"
]

instance_names = [f[:-4] for f in os.listdir(instance_dir) if f.endswith(".dat") and os.path.exists(os.path.join(instance_dir, f[:-4] + ".sln"))]

with open(output_batch, "w") as batch_file:
    batch_file.write("@echo off\n")
    for instance in instance_names:
        for cmd in commands:
            batch_file.write(cmd.format(dir=instance_dir, instance=instance, result=result_file) + "\n")

print(f"Batch script '{output_batch}' created successfully.")
