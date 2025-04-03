import os
import argparse

instance_names = ["wil100", "lipa80a", "tai60a", "kra30a", "bur26a", "bur26b", "chr22a", "chr20c", "had14"]
performance_restarts_instances = ["tai60a", "kra30a", "bur26a", "bur26b", "chr22a", "chr20c", "had14"]

avg_greedyLS = {'bur26a': 3123592.0,
                'bur26b': 2541337.0,
                'chr20c': 647929.9,
                'chr22a': 667595.9,
                'had14': 206135.0,
                'kra30a': 2795186.0,
                'lipa80a': 86358480.0,
                'tai60a': 29373680.0,
                'wil100': 1075083000.0}

number_msls_restarts = [20, 50, 100, 150, 200, 300, 500]

def generate_batch_script(instance_dir, runtime_results_file, performance_results_file, output_batch, mode, num_performance_tests, windows=True):
    if windows:
        run_command = "bio_alg"
    else:
        run_command = "./bio_alg"

    runtime_commands = [
        "{run_command} time heuristic 0 0 {dir} {instance} {result}",
        "{run_command} time random 0 0 {dir} {instance} {result}",
        "{run_command} time antiheuristic 0 0 {dir} {instance} {result}",
        "{run_command} time random 0 0 {dir} {instance} {result} greedyLS",
        "{run_command} time random 0 0 {dir} {instance} {result} steepestLS",
        "{run_command} time random 0 0 {dir} {instance} {result} iterativeImprovement"
    ]

    performance_commands = [
        "{run_command} performance heuristic {perf_tests} 0 {dir} {instance} {result}",
        "{run_command} performance antiheuristic {perf_tests} 0 {dir} {instance} {result}",
        "{run_command} performance random {perf_tests} 0 {dir} {instance} {result} greedyLS",
        "{run_command} performance random {perf_tests} 0 {dir} {instance} {result} steepestLS",
        "{run_command} performance random {perf_tests} 0 {dir} {instance} {result} iterativeImprovement"
    ]

    performance_random_commands = [
        "{run_command} performance randomwalk {perf_tests} {avg_greedyLS_runtime} {dir} {instance} {result}", # HARDCODE AVG GREEDYLS RUNTIME
        "{run_command} performance randomsearch {perf_tests} {avg_greedyLS_runtime} {dir} {instance} {result}", # HARDCODE AVG GREEDYLS RUNTIME
    ]

    performance_restarts_commands = [
        "{run_command} performance random {perf_tests} 0 {dir} {instance} {result} greedyLS",
        "{run_command} performance random {perf_tests} 0 {dir} {instance} {result} steepestLS",
        "{run_command} performance random {perf_tests} 0 {dir} {instance} {result} iterativeImprovement"
    ]

    # instance_names = [f[:-4] for f in os.listdir(instance_dir) if f.endswith(".dat") and f.startswith("bur26")
    #                    and os.path.exists(os.path.join(instance_dir, f[:-4] + ".sln"))]


    # if os.path.exists(runtime_results_file):    
    #     os.remove(runtime_results_file)

    # if os.path.exists(performance_results_file):    
    #     os.remove(performance_results_file)

    with open(output_batch, "w") as batch_file:
        if windows:
            batch_file.write("@echo off\n")
        
        if mode == "performance_restarts":
            for instance in performance_restarts_instances:
                for num_tests in number_msls_restarts:
                    for cmd in performance_restarts_commands:
                        batch_file.write(cmd.format(run_command=run_command, dir=instance_dir, instance=instance, 
                                                    result=f"results\\MSLS_tests\\{num_tests}_msls_performance_results.txt", perf_tests=num_tests) + "\n")

        else:
            for instance in instance_names:
                if mode in ("runtime", "both"):
                    for cmd in runtime_commands:
                        # Make 10 tests for standard deviation
                        for _ in range(10):
                            batch_file.write(cmd.format(run_command=run_command, dir=instance_dir, instance=instance, result=runtime_results_file) + "\n")
                if mode in ("performance", "both"):
                    for cmd in performance_commands:
                        batch_file.write(cmd.format(run_command=run_command, dir=instance_dir, instance=instance, result=performance_results_file, perf_tests=num_performance_tests) + "\n")

                    for cmd in performance_random_commands:
                        batch_file.write(cmd.format(run_command=run_command, dir=instance_dir, instance=instance, result=performance_results_file, perf_tests=num_performance_tests,
                                                    avg_greedyLS_runtime=avg_greedyLS[instance]) + "\n")


    print(f"Batch script '{output_batch}' created successfully.")

# python .\create_batch.py data/qap results/runtime_results.txt p.txt batch_files/run_runtime.bat --mode runtime  --os windows  

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate a batch file for running bio_alg commands.")
    parser.add_argument("instance_dir", help="Directory containing instance files")
    parser.add_argument("runtime_results_file", help="File to store runtime results")
    parser.add_argument("performance_results_file", help="File to store performance results")
    parser.add_argument("output_batch", help="Output batch file name")
    parser.add_argument("--mode", choices=["runtime", "performance", "both", "performance_restarts"], default="both",
                        help="Choose whether to generate runtime, performance, or both.")
    parser.add_argument("--num_performance_tests", default="100",
                        help="Choose what should be the number of performance tests")
    parser.add_argument("--os", default="Windows",
                        help="Choose the operating system - Windows or Linux")
    
    args = parser.parse_args()

    if str(args.os).lower() == "windows":
        windows = True
    elif str(args.os).lower() == "linux":
        windows = False
    else:
        print("Invalid OS type")
        raise ValueError 
    generate_batch_script(args.instance_dir, args.runtime_results_file, args.performance_results_file, args.output_batch, args.mode, args.num_performance_tests, windows)
