import matplotlib.pyplot as plt
import numpy as np

plt.rcParams["font.size"] = 12
plt.rcParams["axes.labelsize"] = 12
plt.rcParams["axes.titlesize"] = 14
plt.rcParams["legend.fontsize"] = 10

t_medio_30 = 0.701
s_30 = 1.0
a_30 = 2 * s_30 / (t_medio_30**2)

t_medio_60 = 0.410
s_60 = 0.58
a_60 = 2 * s_60 / (t_medio_60**2)

t_30 = np.linspace(0, t_medio_30, 100)
t_60 = np.linspace(0, t_medio_60, 100)

v_30 = a_30 * t_30
v_60 = a_60 * t_60

fig, ax = plt.subplots(figsize=(10, 6))

ax.plot(t_30, v_30, "b-", linewidth=2, label=f"30° (a = {a_30:.2f} m/s²)")
ax.plot(t_60, v_60, "r-", linewidth=2, label=f"60° (a = {a_60:.2f} m/s²)")

ax.plot(
    t_medio_30,
    a_30 * t_medio_30,
    "bo",
    markersize=8,
    label=f"Ponto final 30° (t={t_medio_30}s)",
)
ax.plot(
    t_medio_60,
    a_60 * t_medio_60,
    "ro",
    markersize=8,
    label=f"Ponto final 60° (t={t_medio_60}s)",
)

ax.set_xlabel("Tempo (s)")
ax.set_ylabel("Velocidade (m/s)")
ax.set_title("Velocidade em Função do Tempo - Plano Inclinado de Galileu")
ax.grid(True, alpha=0.3)
ax.legend()

textstr = f"Dados Experimentais:\n30°: v_final = {a_30 * t_medio_30:.2f} m/s\n60°: v_final = {a_60 * t_medio_60:.2f} m/s"
props = dict(boxstyle="round", facecolor="wheat", alpha=0.8)
ax.text(
    0.02,
    0.98,
    textstr,
    transform=ax.transAxes,
    fontsize=10,
    verticalalignment="top",
    bbox=props,
)

plt.tight_layout()
plt.savefig("./pictures/velocidade_tempo_obtido.png", dpi=300, bbox_inches="tight")
plt.savefig("./pictures/velocidade_tempo_obtido.pdf", bbox_inches="tight")
plt.show()

print(
    "Gráfico salvo como 'velocidade_tempo_obtido.png' e 'velocidade_tempo_obtido.pdf'"
)
print(f"Aceleração 30°: {a_30:.2f} m/s²")
print(f"Aceleração 60°: {a_60:.2f} m/s²")
print(f"Velocidade final 30°: {a_30 * t_medio_30:.2f} m/s")
print(f"Velocidade final 60°: {a_60 * t_medio_60:.2f} m/s")
