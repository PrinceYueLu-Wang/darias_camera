import numpy as np


N = 100
M = 10

x_obs = np.random.randn(N,3)

x_rob = np.random.randn(M,3)




subts = x_obs[:,None,:] - x_rob


d = ((x_rob[None,...] - x_obs[None,...])**2).sum(-1)
print(d.shape)