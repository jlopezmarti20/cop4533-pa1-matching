import csv
import matplotlib.pyplot as plt
import os

def read_csv(path):
    ns = []
    times = []
    with open(path, newline="") as f:
        reader = csv.DictReader(f)
        for row in reader:
            ns.append(int(row["n"]))
            times.append(float(row["runtime_ms"]))
    return ns, times


m_n, m_t = read_csv("data/matcher_times.csv")
v_n, v_t = read_csv("data/verifier_times.csv")

plt.plot(m_n, m_t, marker="o", label="matcher")
plt.plot(v_n, v_t, marker="o", label="verifier")
plt.xlabel("n")
plt.ylabel("runtime (microseconds)")
plt.title("Matcher vs Verifier runtime")
plt.legend()
plt.xscale("log", base=2)
plt.grid(True)


os.makedirs("analysis/figures", exist_ok=True)
plt.tight_layout()
plt.savefig("analysis/figures/runtime_plot.png", dpi=300)

plt.show()

