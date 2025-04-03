# Biologically_Inspired_Algorithms
Repository for biologically inspired algorithms classes.

## How to run the experiments:
1. Build the main program <br>
`g++ -o bio_alg main.cpp random.cpp Problem.cpp solution.cpp utils.cpp -std=c++17`

2. Create a batch script for running the runtime evaluations e.g.:<br>
`python .\create_batch.py data/qap/ results/runtime_results.txt p.txt batch_files/run_runtime.bat --mode runtime`

3. Run the runtime evaluation batch script e.g.:<br>
`.\batch_files/run_runtime.bat`

4. Copy the mean runtime of greedyLS algorithm for each instance into create_batch.py

5. Create a batch script for running the performance evaluations e.g.:<br>
`python .\create_batch.py data/qap/ r.txt results/performance_results.txt batch_files/run_performance.bat --mode performance`

6. Run the performance evaluation batch script e.g.:<br>
`.\batch_files/run_performance.bat`

7. Create batch script for running the MSLS number of restarts evaluations e.g.:<br>
`python .\create_batch.py data/qap/ r.txt results/MSLS_restarts_results.txt batch_files/run_msls_performance.bat --mode performance_restarts`

8. Run the MSLS number of restarts evaluations batch script e.g.:<br>
`.\batch_files/run_msls_performance.bat`

9. Visualize results with LS_Results.ipynb (remember to set appropriate paths to result files) 