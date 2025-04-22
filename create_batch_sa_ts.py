import os
import argparse

instance_names = ["wil100", "lipa80a", "tai60a", "kra30a", "bur26a", "bur26b", "chr22a", "chr20c", "had14"]
instance_sizes = [100, 80, 60, 30, 26, 26, 22, 20, 14]

# Parameters to vary
# sa_temp_decrease_rates = [0.9, 0.92, 0.95]
# sa_markov_dividers = [5, 10]

# taboo_stopping_thresholds = [10, 15, 20]

sa_temp_decrease_rates = [0.92]
sa_markov_dividers = [5]

taboo_stopping_thresholds = [15]

def generate_batch_script(instance_dir, runtime_results_file, performance_results_file, output_batch, mode, num_performance_tests, windows=True):
    if windows:
        run_command = "bio_alg"
    else:
        run_command = "./bio_alg"

    with open(output_batch, "w") as batch_file:
        if windows:
            batch_file.write("@echo off\n")

        for i, instance in enumerate(instance_names):
            for tdr in sa_temp_decrease_rates:
                for mmd in sa_markov_dividers:
                    sa_perf_cmd = f"{run_command} performance random {num_performance_tests} 0 {instance_dir} {instance} {performance_results_file} simulatedAnnealing {tdr} {mmd}"
                    sa_runtime_cmd = f"{run_command} time random 0 0 {instance_dir} {instance} {runtime_results_file} simulatedAnnealing {tdr} {mmd}"
                    
                    if mode == "both":
                        for _ in range(10):
                            batch_file.write(sa_runtime_cmd + "\n")

                        batch_file.write(sa_perf_cmd + "\n")

                    if mode == "runtime":
                        for _ in range(10):
                            batch_file.write(sa_runtime_cmd + "\n")
                    
                    if mode == "performance":
                        batch_file.write(sa_perf_cmd + "\n")

            tenure = instance_sizes[i] // 4
            for threshold in taboo_stopping_thresholds:
                taboo_perf_cmd = f"{run_command} performance random {num_performance_tests} 0 {instance_dir} {instance} {performance_results_file} tabooSearch {tenure} {threshold}"
                taboo_runtime_cmd = f"{run_command} time random 0 0 {instance_dir} {instance} {runtime_results_file} tabooSearch {tenure} {threshold}"
                
                if mode == "both":
                    for _ in range(10):
                        batch_file.write(taboo_runtime_cmd + "\n")

                    batch_file.write(taboo_perf_cmd + "\n")

                if mode == "runtime":
                    for _ in range(10):
                        batch_file.write(taboo_runtime_cmd + "\n")
                
                if mode == "performance":
                    batch_file.write(taboo_perf_cmd + "\n")
                        

    print(f"Batch script '{output_batch}' created successfully.")

# python create_batch_sa_ts.py data/qap results/sa_ts_runtime_results.txt results/sa_ts_performance_results.txt batch_files/run_sa_tabu.bat 

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate batch script for Simulated Annealing and Taboo Search.")
    parser.add_argument("instance_dir", help="Directory containing instance files")
    parser.add_argument("runtime_results_file", help="File to store runtime results")
    parser.add_argument("performance_results_file", help="File to store performance results")
    parser.add_argument("output_batch", help="Output batch file name")
    parser.add_argument("--mode", choices=["runtime", "performance", "both"], default="both",
                        help="Choose whether to generate runtime, performance, or both.")
    parser.add_argument("--num_performance_tests", default="100", help="Number of performance tests")
    parser.add_argument("--os", default="windows", help="Target operating system: Windows or Linux")

    args = parser.parse_args()
    windows = args.os.lower() == "windows"

    generate_batch_script(
        args.instance_dir,
        args.runtime_results_file,
        args.performance_results_file,
        args.output_batch,
        args.mode,
        int(args.num_performance_tests),
        windows
    )
