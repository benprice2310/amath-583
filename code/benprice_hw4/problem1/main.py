import numpy as np
import matplotlib.pyplot as plt

# Matrix A
A = np.array([[1, 2], [0, 2]])


# Function to generate points on unit balls
def generate_unit_ball(norm_type, num_points=500):
    theta = np.linspace(0, 2 * np.pi, num_points)

    if norm_type == "2":
        # Unit circle
        x = np.cos(theta)
        y = np.sin(theta)
        return np.array([x, y])

    elif norm_type == "1":
        # 1-norm unit ball: diamond
        x, y = [], []
        for t in np.linspace(-1, 1, num_points // 4):
            x.append(t)
            y.append(1 - abs(t))
        for t in np.linspace(1, -1, num_points // 4):
            x.append(t)
            y.append(-1 + abs(t))
        for t in np.linspace(-1, 1, num_points // 4):
            x.append(1 - abs(t))
            y.append(t)
        for t in np.linspace(1, -1, num_points // 4):
            x.append(-1 + abs(t))
            y.append(t)
        return np.array([x, y])

    elif norm_type == "inf":
        # ∞-norm unit ball: square
        x, y = [], []
        for t in np.linspace(-1, 1, num_points // 4):
            x.append(t)
            y.append(1)
        for t in np.linspace(1, -1, num_points // 4):
            x.append(1)
            y.append(t)
        for t in np.linspace(1, -1, num_points // 4):
            x.append(t)
            y.append(-1)
        for t in np.linspace(-1, 1, num_points // 4):
            x.append(-1)
            y.append(t)
        return np.array([x, y])


# Generate unit balls
balls = {
    "1-Norm Unit Ball": generate_unit_ball("1"),
    "2-Norm Unit Ball": generate_unit_ball("2"),
    "∞-Norm Unit Ball": generate_unit_ball("inf"),
}

# Apply matrix A to each point
transformed = {name: A @ pts for name, pts in balls.items()}

# Plotting
fig, axes = plt.subplots(1, 2, figsize=(12, 6))

# Original unit balls
for name, pts in balls.items():
    axes[0].plot(pts[0], pts[1], label=name)
axes[0].set_title("Original Unit Balls in ℝ²")
axes[0].axis("equal")
axes[0].grid(True)
axes[0].legend()

# Transformed images
for name, pts in transformed.items():
    axes[1].plot(pts[0], pts[1], label=name)
axes[1].set_title("Images under A = [[1, 2], [0, 2]]")
axes[1].axis("equal")
axes[1].grid(True)
axes[1].legend()

plt.tight_layout()
plt.show()
