import os
import argparse

def generate_batch_script(instance_dir, runtime_results_file, performance_results_file, output_batch, mode):
    runtime_commands = [
        "bio_alg time heuristic 0 0 {dir} {instance} {result}",
        "bio_alg time random 0 0 {dir} {instance} {result}",
        "bio_alg time antiheuristic 0 0 {dir} {instance} {result}",
        "bio_alg time random 0 0 {dir} {instance} {result} greedyLS",
        "bio_alg time random 0 0 {dir} {instance} {result} steepestLS"
    ]

    performance_commands = [
        "bio_alg performance heuristic 100 0 {dir} {instance} {result}",
        "bio_alg performance antiheuristic 100 0 {dir} {instance} {result}",
        "bio_alg performance randomwalk 100 2871222 {dir} {instance} {result}", # HARDCODED AVG GREEDYLS RUNTIME
        "bio_alg performance randomsearch 100 2871222 {dir} {instance} {result}", # HARDCODED AVG GREEDYLS RUNTIME
        "bio_alg performance random 100 0 {dir} {instance} {result} greedyLS",
        "bio_alg performance random 100 0 {dir} {instance} {result} steepestLS"
    ]

    instance_names = [f[:-4] for f in os.listdir(instance_dir) if f.endswith(".dat") and f.startswith("bur26")
                       and os.path.exists(os.path.join(instance_dir, f[:-4] + ".sln"))]

    with open(output_batch, "w") as batch_file:
        batch_file.write("@echo off\n")
        for instance in instance_names:
            if mode in ("runtime", "both"):
                for cmd in runtime_commands:
                    # Make 10 tests for standard deviation
                    for _ in range(10):
                        batch_file.write(cmd.format(dir=instance_dir, instance=instance, result=runtime_results_file) + "\n")
            if mode in ("performance", "both"):
                for cmd in performance_commands:
                    batch_file.write(cmd.format(dir=instance_dir, instance=instance, result=performance_results_file) + "\n")

    print(f"Batch script '{output_batch}' created successfully.")

# python .\create_batch.py data/qap/ results/runtime_results.txt results/performance_results.txt runbatch.bat --mode both   

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate a batch file for running bio_alg commands.")
    parser.add_argument("instance_dir", help="Directory containing instance files")
    parser.add_argument("runtime_results_file", help="File to store runtime results")
    parser.add_argument("performance_results_file", help="File to store performance results")
    parser.add_argument("output_batch", help="Output batch file name")
    parser.add_argument("--mode", choices=["runtime", "performance", "both"], default="both",
                        help="Choose whether to generate runtime, performance, or both")
    
    args = parser.parse_args()
    generate_batch_script(args.instance_dir, args.runtime_results_file, args.performance_results_file, args.output_batch, args.mode)
