import os
import argparse

instance_names = ["wil100", "lipa80a", "lipa80b", "tai60a", "kra30a", "bur26a", "bur26b", "chr22a", "had14"]
performance_restarts_instances = ["tai60a", "chr22a"]
instance_runtimes_greedy = [0, 0, 0, 0, 0, 0, 0, 0, 0] #TODO

avg_greedyLS = {instance: runtime for instance, runtime in zip(instance_names, instance_runtimes_greedy)}

number_msls_restarts = [20, 50, 100, 150, 200, 300, 500]

def generate_batch_script(instance_dir, runtime_results_file, performance_results_file, output_batch, mode, num_performance_tests):
    runtime_commands = [
        "bio_alg time heuristic 0 0 {dir} {instance} {result}",
        "bio_alg time random 0 0 {dir} {instance} {result}",
        "bio_alg time antiheuristic 0 0 {dir} {instance} {result}",
        "bio_alg time random 0 0 {dir} {instance} {result} greedyLS",
        "bio_alg time random 0 0 {dir} {instance} {result} steepestLS"
    ]

    performance_commands = [
        "bio_alg performance heuristic {perf_tests} 0 {dir} {instance} {result}",
        "bio_alg performance antiheuristic {perf_tests} 0 {dir} {instance} {result}",
        "bio_alg performance random {perf_tests} 0 {dir} {instance} {result} greedyLS",
        "bio_alg performance random {perf_tests} 0 {dir} {instance} {result} steepestLS"
    ]

    performance_random_commands = [
        "bio_alg performance randomwalk {perf_tests} {avg_greedyLS_runtime} {dir} {instance} {result}", # HARDCODE AVG GREEDYLS RUNTIME
        "bio_alg performance randomsearch {perf_tests} {avg_greedyLS_runtime} {dir} {instance} {result}", # HARDCODE AVG GREEDYLS RUNTIME
    ]

    performance_restarts_commands = [
        "bio_alg performance random {perf_tests} 0 {dir} {instance} {result} greedyLS",
        "bio_alg performance random {perf_tests} 0 {dir} {instance} {result} steepestLS"
    ]

    # instance_names = [f[:-4] for f in os.listdir(instance_dir) if f.endswith(".dat") and f.startswith("bur26")
    #                    and os.path.exists(os.path.join(instance_dir, f[:-4] + ".sln"))]


    # if os.path.exists(runtime_results_file):    
    #     os.remove(runtime_results_file)

    # if os.path.exists(performance_results_file):    
    #     os.remove(performance_results_file)

    with open(output_batch, "w") as batch_file:
        batch_file.write("@echo off\n")
        
        if mode == "performance_restarts":
            for instance in performance_restarts_instances:
                for num_tests in number_msls_restarts:
                    for cmd in performance_restarts_commands:
                        batch_file.write(cmd.format(dir=instance_dir, instance=instance, result=performance_results_file, perf_tests=num_tests) + "\n")
        
        else:
            for instance in instance_names:
                if mode in ("runtime", "both"):
                    for cmd in runtime_commands:
                        # Make 10 tests for standard deviation
                        for _ in range(10):
                            batch_file.write(cmd.format(dir=instance_dir, instance=instance, result=runtime_results_file) + "\n")
                if mode in ("performance", "both"):
                    for cmd in performance_commands:
                        batch_file.write(cmd.format(dir=instance_dir, instance=instance, result=performance_results_file, perf_tests=num_performance_tests) + "\n")

                    for cmd in performance_random_commands:
                        batch_file.write(cmd.format(dir=instance_dir, instance=instance, result=performance_results_file, perf_tests=num_performance_tests,
                                                    avg_greedyLS_runtime=avg_greedyLS[instance]) + "\n")


    print(f"Batch script '{output_batch}' created successfully.")

# python .\create_batch.py data/qap results/runtime_results.txt p.txt batch_files/run_runtime.bat --mode runtime

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
    
    args = parser.parse_args()
    generate_batch_script(args.instance_dir, args.runtime_results_file, args.performance_results_file, args.output_batch, args.mode, args.num_performance_tests)
