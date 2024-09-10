# Generating two random 4x4 matrices
import numpy as np

matrix_A = np.random.randint(0, 10, size=(1024,1024))

matrix_B = np.random.randint(0, 10, size=(1024,1024))



# Saving matrices to .txt files

np.savetxt('matrix_A.txt', matrix_A, fmt='%d')

np.savetxt('matrix_B.txt', matrix_B, fmt='%d')



matrix_A, matrix_B