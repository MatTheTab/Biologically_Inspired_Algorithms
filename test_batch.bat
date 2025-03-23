@echo off
bio_alg heuristic data/qap/ bur26a new_results.txt
bio_alg random data/qap/ bur26a new_results.txt
bio_alg antiheuristic data/qap/ bur26a new_results.txt
bio_alg heuristic data/qap/ bur26a new_results.txt greedy_LS
bio_alg heuristic data/qap/ bur26a new_results.txt steepest_LS
bio_alg random data/qap/ bur26a new_results.txt greedy_LS
bio_alg antiheuristic data/qap/ bur26a new_results.txt greedy_LS
bio_alg heuristic data/qap/ bur26b new_results.txt
bio_alg random data/qap/ bur26b new_results.txt
bio_alg antiheuristic data/qap/ bur26b new_results.txt