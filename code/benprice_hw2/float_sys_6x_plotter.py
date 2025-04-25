import matplotlib.pyplot as plt

# --- System Parameters ---
bias = 3  # Bias for exponent field (3-bit: k=3)
mantissas = [0.00, 0.25, 0.5, 0.75]
exponent_range = range(1, 7)  # Exponent bits 001 to 110 → e = 1 to 6

# --- Value Computation ---
normalized_values = []
denormalized_values = []

# Normalized values: x = ±(1 + f) * 2^(E), E = e - bias
for sign in [1, -1]:
    for e in exponent_range:
        E = e - bias
        for f in mantissas:
            x = sign * (1 + f) * 2**E
            normalized_values.append(x)

# Denormalized values: x = ±f * 2^(1 - bias) = ±f * 2^(-2)
for sign in [1, -1]:
    for f in [0.25, 0.5, 0.75]:  # exclude zero mantissa
        x = sign * f * 2 ** (-2)
        denormalized_values.append(x)

# --- Debug Printout (Optional) ---
print("Normalized Values:")
print(sorted(normalized_values))
print("\nDenormalized Values:")
print(sorted(denormalized_values))

# --- Plotting ---
fig, ax = plt.subplots(figsize=(12, 3))
ax.stem(
    normalized_values,
    [1] * len(normalized_values),
    linefmt="b-",
    markerfmt="bo",
    basefmt=" ",
    label="Normalized",
)
ax.stem(
    denormalized_values,
    [1] * len(denormalized_values),
    linefmt="r-",
    markerfmt="ro",
    basefmt=" ",
    label="Denormalized",
)

# Add center line and labels
ax.axvline(0, color="gray", linestyle="--", linewidth=1)
ax.set_title("Representable Numbers in Custom 6-bit Floating Point System", fontsize=14)
ax.set_xlabel("Value", fontsize=12)
ax.set_yticks([])
ax.grid(True, axis="x", linestyle=":", alpha=0.5)
ax.legend(loc="upper right")
plt.tight_layout()

# --- Save to File ---
output_base = "./code/hw2/float_sys_6x_plot"
fig.savefig(f"{output_base}.pdf", format="pdf")
fig.savefig(f"{output_base}.png", format="png", dpi=300)
fig.savefig(f"{output_base}.svg", format="svg")
# fig.savefig(f"{output_base}.pgf", format="pgf")


# --- Display ---
plt.show()
