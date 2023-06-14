# `afnidespike`

Python/NumPy wrapper around AFNIs [despike utility functions](https://github.com/afni/afni/blob/7add343c2f9ae74320bc371371b6a7ac0e2e91ce/src/despike_inc.c) for educational purposes.

## Example
```Python
import numpy as np
import afnidespike
import matplotlib.pyplot as plt

a = (np.random.rand(100) + np.sin(np.arange(100) * 0.1)).astype(np.float32)
a[50] = 1e1
a[80] = 1e2
b = a.copy()

x = afnidespike.despike(a, 0)

print('Removed spikes:', x)

plt.plot(b)
plt.show()

plt.plot(a)
plt.show()
```