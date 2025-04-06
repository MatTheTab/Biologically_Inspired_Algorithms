import re
import os

import numpy as np
import pandas as pd

import seaborn as sns
import matplotlib.pyplot as plt

# Names of instances ordered by instance size
instance_names_ordered = ["wil100", "lipa80a", "tai60a", "kra30a", "bur26a", "bur26b", "chr22a", "chr20c", "had14"][::-1]

RANDOMRUNTIMES = {'bur26a': 3123592.0,
                'bur26b': 2541337.0,
                'chr20c': 647929.9,
                'chr22a': 667595.9,
                'had14': 206135.0,
                'kra30a': 2795186.0,
                'lipa80a': 86358480.0,
                'tai60a': 29373680.0,
                'wil100': 1075083000.0}

algorithm_colors = {
    "greedyLS": "#e41a1c",
    "steepestLS": "#377eb8",
    "heuristic": "#4daf4a",
    "antiheuristic": "#a65628",
    "random": "#ff7f00",
    "randomwalk": "#fdb462",
    "randomsearch": "#984ea3",
    "iterativeImprovement": "#999999"
}

def plot_algorithms(save_name, summary, title="Measure", log_scale=False):
    plt.figure(figsize=(10, 6))
    sns.set_theme(style="whitegrid")

    algorithms = summary["Algorithm"].unique()

    for i, algorithm in enumerate(algorithms):
        subset = summary[summary["Algorithm"] == algorithm]
        plt.plot(subset["Instance"], subset["mean"], label=f"{algorithm} (Mean)", color=algorithm_colors[algorithm], marker="o", linestyle="-")
        plt.fill_between(subset["Instance"], subset["mean"] - subset["std"], subset["mean"] + subset["std"], alpha=0.2, color=algorithm_colors[algorithm])

    plt.xlabel("Instance")
    plt.ylabel(title)
    if log_scale:
        plt.yscale("log")
    
    full_title = f"Algorithm {title} per Instance with Standard Deviation"
    
    if log_scale:
        full_title += " (Log scale)"

    plt.title(full_title)
    plt.legend()
    plt.xticks(rotation=45)
    plt.savefig("./plots/" + save_name, format="pdf", bbox_inches="tight")
    plt.show()


def plot_std_line(save_name, summary, title="Standard Deviation", overlap=False, log_scale=False):
    plt.figure(figsize=(12, 6))
    sns.set_theme(style="whitegrid")
    
    algorithms = summary["Algorithm"].unique()
    instances = summary["Instance"].unique()
    
    for i, algorithm in enumerate(algorithms):
        subset = summary[summary["Algorithm"] == algorithm]
        plt.plot(subset["Instance"], subset["std"], label=f"{algorithm} (std)", color=algorithm_colors[algorithm], marker="o", linestyle="-")

    plt.xlabel("Instance")
    plt.ylabel(title)
    if log_scale:
        plt.yscale("log")
    
    full_title = f"Algorithm {title} per Instance"
    
    if log_scale:
        full_title += " (Log scale)"

    plt.title(full_title)
    if log_scale:
        plt.yscale("log")
    plt.xticks(np.arange(len(instances)), instances, rotation=45)
    plt.legend()
    plt.savefig("./plots/" + save_name, format="pdf", bbox_inches="tight")
    plt.show()

def plot_std_bar(save_name, summary, title="Standard Deviation", overlap=False, log_scale=False):
    plt.figure(figsize=(12, 6))
    sns.set_theme(style="whitegrid")
    
    algorithms = summary["Algorithm"].unique()
    instances = summary["Instance"].unique()
    
    bar_width = 0.8 / len(algorithms) if not overlap else 0.8
    
    for i, algorithm in enumerate(algorithms):
        subset = summary[summary["Algorithm"] == algorithm]
        x_positions = np.arange(len(instances))
        
        if not overlap:
            x_positions = x_positions + i * bar_width - (len(algorithms) - 1) * bar_width / 2
        
        plt.bar(x_positions, subset["std"], width=bar_width, label=algorithm, color=algorithm_colors[algorithm], alpha=0.7 if overlap else 1)
    
    plt.xlabel("Instance")
    plt.ylabel(title)
    if log_scale:
        plt.yscale("log") 
    
    full_title = f"Algorithm {title} per Instance"
    
    if log_scale:
        full_title += " (Log scale)"

    plt.title(full_title)
    if log_scale:
        plt.yscale("log")
    plt.xticks(np.arange(len(instances)), instances, rotation=45)
    plt.legend()
    plt.savefig("./plots/" + save_name, format="pdf", bbox_inches="tight")
    plt.show()


def plot_efficiency(save_name, summary, legend=True, show_instances=True, 
                    title="Algorithm Performance: Runtime vs. Solution Quality",
                    log_scale_x=True, log_scale_y=True):
    
    plt.figure(figsize=(15, 6))
    sns.set_theme(style="whitegrid")

    algorithms = summary["Algorithm"].unique()
    instances = summary["Instance"].unique()
    markers = ["o", "s", "D", "v", "^"]  
    
    algorithm_legend = {}

    for i, algorithm in enumerate(algorithms):
        for j, instance in enumerate(instances):
            subset = summary[(summary["Algorithm"] == algorithm) & (summary["Instance"] == instance)]
            if not subset.empty:
                if show_instances:
                    label = label=f"{algorithm} - {instance}"
                else:
                    label = algorithm if algorithm not in algorithm_legend else "_nolegend_"
                plt.errorbar(
                    subset["mean_quality"], subset["mean_runtime"],
                    xerr=subset["std_quality"], yerr=subset["std_runtime"],
                    fmt=markers[j % len(markers)], color=algorithm_colors[algorithm], label=label,
                    capsize=3, linestyle="none"
                )
                algorithm_legend[algorithm] = True

    plt.ylabel("Runtime [ns] (Mean ± Std)")
    plt.xlabel("Solution Quality (Mean ± Std)")
    
    if log_scale_x:
        plt.xscale("log")
    
    if log_scale_y:
        plt.yscale("log")
    
    full_title = f"{title}"
    
    if log_scale_x and log_scale_y:
        full_title += " (Log scale x y)"
    elif log_scale_x:
        full_title += " (Log scale x)"
    elif log_scale_y:
        full_title += " (Log scale y)"

    plt.title(full_title)
    if legend:
        plt.legend(loc="upper right", fontsize=9, ncol=5)
    plt.savefig("./plots/" + save_name, format="pdf", bbox_inches="tight")
    plt.show()

def plot_ls_algorithms_comparison(save_name, df, algorithm=""):
    plt.figure(figsize=(10, 6))
    sns.set_theme(style="whitegrid")

    sns.scatterplot(
        data=df,
        x="Initial_Score",
        y="Score",
        hue="Instance",
        palette="tab10",
        alpha=0.6
    )

    plt.yscale("log") 
    plt.xscale("log") 

    plt.title(f"Comparison of LS Algorithms: Initial vs. Final Solution Score {algorithm}")
    plt.legend(title="Instance", loc="upper left", bbox_to_anchor=(1, 1))
    plt.savefig("./plots/" + save_name, format="pdf", bbox_inches="tight")
    plt.show()

def plot_ls_algorithms_comparison_all(save_name, df, algorithm=""):
    sns.set_theme(style="whitegrid")
    
    g = sns.FacetGrid(
        df, col="Instance", hue="Instance", palette="tab10", col_wrap=3, sharex=False, sharey=False
    )

    g.map_dataframe(
        sns.scatterplot, x="Initial_Score", y="Score",
        s=10,
        alpha=0.5,
        edgecolor='none'
    )

    def set_titles(**kwargs):
        ax = plt.gca()
        instance = kwargs.get('label', '')
        subset = df[df['Instance'] == instance]
        correlation = subset["Initial_Score"].corr(subset["Score"]) if not subset.empty else np.nan
        ax.set_title(f"{instance} Cor = {correlation:.2f}")
    
    g.map_dataframe(set_titles)
    
    g.figure.suptitle(f"Comparison of LS Algorithms: Initial vs. Final Solution Score {algorithm}", fontsize=16)
    g.figure.subplots_adjust(top=0.9)
    plt.savefig("./plots/" + save_name, format="pdf", bbox_inches="tight")
    plt.show()

def plot_algorithm_performance(save_name, restart_data):
    sns.set_theme(style="whitegrid")

    avg_results = []
    best_results = []
    for num_restarts, df in restart_data:
        df = df.copy()
        df["Restarts"] = num_restarts
        avg_scores = df.groupby(["Instance", "Algorithm", "Restarts"], as_index=False)["Solution_Quality"].mean()
        best_scores = df.groupby(["Instance", "Algorithm", "Restarts"], as_index=False)["Solution_Quality"].min()
        avg_results.append(avg_scores)
        best_results.append(best_scores)

    avg_df = pd.concat(avg_results, ignore_index=True)
    best_df = pd.concat(best_results, ignore_index=True)

    avg_df = avg_df[avg_df["Instance"].isin(instance_names_ordered)]
    best_df = best_df[best_df["Instance"].isin(instance_names_ordered)]

    avg_df["Instance"] = pd.Categorical(avg_df["Instance"], categories=instance_names_ordered, ordered=True)
    best_df["Instance"] = pd.Categorical(best_df["Instance"], categories=instance_names_ordered, ordered=True)
    
    avg_df = avg_df.sort_values("Instance")
    best_df = best_df.sort_values("Instance")

    def plot_scores(name, df, title, score_type):
        plt.figure(figsize=(12, 6))
        sns.lineplot(
            data=df,
            x="Instance",
            y="Solution_Quality",
            hue="Restarts",
            palette="tab10",
            marker="o"
        )

        plt.xticks(rotation=45, ha="right")
        plt.title(title + " (log scale)")
        plt.xlabel("Instance")
        plt.ylabel(f"{score_type} Solution Quality")
        plt.yscale("log")
        plt.legend(title="Restarts")
        plt.grid(axis='y', linestyle="--", alpha=0.7)
        plt.savefig(name, format="pdf", bbox_inches="tight")
        plt.show()

    plot_scores("./plots/" + save_name + "greedy_average.pdf", avg_df[avg_df["Algorithm"] == "greedyLS"], "GreedyLS - Average Solution Quality", "Average")
    plot_scores("./plots/" + save_name + "greedy_best.pdf", best_df[best_df["Algorithm"] == "greedyLS"], "GreedyLS - Best Solution Quality", "Best")
    plot_scores("./plots/" + save_name + "steepest_average.pdf", avg_df[avg_df["Algorithm"] == "steepestLS"], "SteepestLS - Average Solution Quality", "Average")
    plot_scores("./plots/" + save_name + "steepest_best.pdf", best_df[best_df["Algorithm"] == "steepestLS"], "SteepestLS - Best Solution Quality", "Best")


def plot_optimality_heatmaps(restart_data, instance_order=None, cmap_colors=None):
    best_scores = []
    for num_restarts, df in restart_data:
        df = df.copy()
        df["Restarts"] = num_restarts
        best_per_instance = df.groupby(["Algorithm", "Instance", "Restarts"], as_index=False)[["Score", "Solution_Quality"]].min()
        best_scores.append(best_per_instance)

    best_df = pd.concat(best_scores, ignore_index=True)

    def status(row):
        diff = abs(row["Solution_Quality"])
        if diff < 1e-6:
            return "Optimal"
        elif diff <= 0.01:
            return "Close"
        else:
            return "No"

    best_df["Status"] = best_df.apply(status, axis=1)

    status_map = {"No": 0, "Close": 1, "Optimal": 2}
    best_df["Status_Num"] = best_df["Status"].map(status_map)
    status_label_map = {0: "", 1: "~", 2: "o"}

    if instance_order:
        best_df["Instance"] = pd.Categorical(best_df["Instance"], categories=instance_order, ordered=True)

    if cmap_colors is None:
        cmap_colors = ["#ffffff", "#ffe08a", "#b6f2b3"]

    algorithms = best_df["Algorithm"].unique()

    for algo in algorithms:
        pivot_numeric = best_df[best_df["Algorithm"] == algo].pivot(index="Instance", columns="Restarts", values="Status_Num")
        pivot_labels = pivot_numeric.copy().replace(status_label_map)

        plt.figure(figsize=(7, max(5, len(pivot_numeric) *0.4)))
        sns.heatmap(
            pivot_numeric,
            annot=pivot_labels,
            fmt="s",
            cmap=cmap_colors,
            linewidths=0.5,
            linecolor="gray",
            cbar=False
        )
        plt.title(f"Optimality Heatmap – {algo}", fontsize=14)
        plt.ylabel("Instance")
        plt.xlabel("Number of Restarts")
        plt.xticks(rotation=0)
        plt.yticks(rotation=0)
        plt.tight_layout()
        plt.savefig(f"./plots/Num Restarts Quality {algo}.pdf", format="pdf", bbox_inches="tight")
        plt.show()

def compute_similarity(solution1, solution2):
    return sum(1 for a, b in zip(solution1, solution2) if a == b)/len(solution1)*100

def plot_solution_quality_vs_similarity(save_name, df, instances=["chr15a", "tai60c"]):
    sns.set_theme(style="whitegrid")
    
    for instance in instances:
        subset = df[df["Instance"] == instance]
        
        plot_data = []
        
        for _, row in subset.iterrows():
            similarity = compute_similarity(row["Optimal_Solution"], row["Solution"])
            plot_data.append({
                "Algorithm": row["Algorithm"],
                "Quality": (row["Score"] - row["Optimal_Score"]) / row["Optimal_Score"] * 100,
                "Similarity": similarity
            })
        
        plot_df = pd.DataFrame(plot_data)
        
        plt.figure(figsize=(10, 6))
        sns.scatterplot(data=plot_df, x="Quality", y="Similarity", hue="Algorithm", palette=algorithm_colors, alpha=0.7)
        plt.title(f"Solution Quality vs. Similarity to Optimal Solution for {instance}")
        plt.xlabel("Solution Quality")
        plt.ylabel("Similarity to Optimal Solution (%)")
        plt.legend(title="Algorithm")
        plt.savefig("./plots/" + save_name + instance + ".pdf", format="pdf", bbox_inches="tight")
        plt.show()


def plot_similarity_heatmaps(df, algorithm="steepestLS", num_labels=10):
    algo_df = df[df["Algorithm"] == algorithm].copy()

    # Compute solution quality
    algo_df["Solution_Quality"] = (algo_df["Score"] - algo_df["Optimal_Score"]) / algo_df["Optimal_Score"] * 100

    instances = algo_df["Instance"].unique()
    num_instances = len(instances)

    cols = 3
    rows = int(np.ceil(num_instances / cols))
    fig, axes = plt.subplots(rows, cols, figsize=(cols * 5, rows * 5))
    axes = axes.flatten()

    for i, instance in enumerate(instances):
        ax = axes[i]
        instance_df = algo_df[algo_df["Instance"] == instance].copy()
        instance_df = instance_df.sort_values("Solution_Quality").reset_index(drop=True)

        n = len(instance_df)
        similarity_matrix = np.zeros((n, n))

        for a in range(n):
            for b in range(n):
                similarity_matrix[a, b] = compute_similarity(instance_df["Solution"][a], instance_df["Solution"][b])

        label_indices = np.linspace(0, n - 1, num=num_labels, dtype=int)
        labels = [f"{instance_df['Solution_Quality'][j]:.1f}" if j in label_indices else "" for j in range(n)]

        sns.heatmap(similarity_matrix, ax=ax, cmap="viridis",
                    xticklabels=labels, yticklabels=labels, cbar=False,
                    linewidths=0)

        ax.set_title(f"{instance}", fontsize=15, y=-0.075)
        ax.set_xlabel("Solution Quality", fontsize=10)
        ax.set_ylabel("Solution Quality", fontsize=10)
        ax.xaxis.tick_top()
        ax.xaxis.set_label_position("top")
        ax.tick_params(axis='x', rotation=0, labelsize=8, which='both', length=0)
        ax.tick_params(axis='y',  rotation=0, labelsize=8, which='both', length=0)


    cbar_ax = fig.add_axes([0.35, 0.025, 0.02, 0.27])
    norm = plt.Normalize(vmin=similarity_matrix.min(), vmax=similarity_matrix.max())
    sm = plt.cm.ScalarMappable(cmap="viridis", norm=norm)
    sm.set_array([])
    cbar = fig.colorbar(sm, cax=cbar_ax)
    cbar.set_label('Solution similarity', fontsize=15, rotation=90)  # Add label to colorbar (legend)


    for j in range(i + 1, len(axes)):
        fig.delaxes(axes[j])

    fig.suptitle(f"Solution Similarity Heatmaps ({algorithm})", fontsize=16)
    plt.tight_layout(rect=[0, 0, 1, 0.97])
    plt.savefig("./plots/" + "solution_similarity_" + algorithm + ".pdf", format="pdf", bbox_inches="tight")
    plt.show()