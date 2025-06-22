import matplotlib.pyplot as plt
import numpy as np

# Data for the curve
x_curve = np.linspace(0, 10, 200)
y_curve = 2 * np.sin(x_curve / 2) + 2.5 # A curve that's mostly positive

# Define the x-range for the filled area
x1 = 3.0
x2 = 7.0

plt.figure(figsize=(8, 5))

# Plot the full curve
plt.plot(x_curve, y_curve, color='blue', label='Main Curve')

# --- Filter data for the fill_between region ---
# Find the indices where x_curve is between x1 and x2
indices_to_fill = (x_curve >= x1) & (x_curve <= x2)

# Get the x and y values within that range
x_fill = x_curve[indices_to_fill]
y_fill = y_curve[indices_to_fill]

# --- Fill the area between x1 and x2, from y=0 to y_curve ---
plt.fill_between(x_fill, y_fill, 0,
                 color='lightblue', alpha=0.5, label=f'Area from {x1} to {x2}, 0 to Curve')

# Add vertical lines for x1 and x2 (optional)
# plt.axvline(x=x1, color='red', linestyle=':', linewidth=1)
# plt.axvline(x=x2, color='red', linestyle=':', linewidth=1)
# plt.axhline(y=0, color='black', linewidth=0.8) # Explicitly show y=0

plt.title("Fill Area Between x1 and x2, from 0 to a Curve")
plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)
plt.ylim(bottom=-0.5) # Ensure y=0 is visible
plt.show()