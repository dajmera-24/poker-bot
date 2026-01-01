import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

def f(x, n):
    return 1.5 ** ((x - 1) / (n - 1))

data = []

for n in [6, 9]:
    for x in range(1, n + 1):
        data.append({
            "x": x,
            "f(x)": f(x, n),
            "n": f"n = {n}"
        })

df = pd.DataFrame(data)

sns.set_theme(
    context="paper",
    style="white",
    font="sans-serif",
    font_scale=1.2
)

palette = {
    "n = 6": "#4C72B0",
    "n = 9": "#55A868"
}

plt.figure(figsize=(5.5, 4))

ax = sns.lineplot(
    data=df,
    x="x",
    y="f(x)",
    hue="n",
    style="n",
    markers=True,
    dashes=True,
    linewidth=2,
    markersize=7,
    palette=palette
)

ax.set_xlabel("x")
ax.set_ylabel(r"$f(x) = 1.5^{\frac{x-1}{n-1}}$")

ax.set_xticks(range(1, 10))

ax.legend(title=None, frameon=False)

sns.despine()

plt.tight_layout()
plt.savefig("fx_plot_seaborn.pdf")
plt.show()
