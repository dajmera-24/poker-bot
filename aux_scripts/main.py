import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import csv

def chen_score(r1, r2, suited):
    if r1 < r2: r1,r2 = r2,r1

    v1=0

    if r1 == 14: v1=10
    elif r1 == 13: v1=8
    elif r1 == 12: v1=7
    elif r1 == 11: v1=6
    else: v1=r1/2

    if r1==r2: 
        v1 = max(2*v1, 5)
        return np.ceil(v1)

    if suited: v1 += 2

    if r1-r2 == 1: v1 = v1
    elif r1-r2 == 2: v1 -= 1
    elif r1-r2 == 3: v1 -= 2
    elif r1-r2 == 4: v1 -= 4
    elif r1-r2 >= 5: v1 -= 5

    if (r1 < 12 and r2 < 12 and r1-r2 <= 2): v1 += 1

    return np.ceil(v1)

matrix = np.zeros((13,13))

with open('start_hands_pflop_vals.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Hand', 'Score'])
    for i in range(13):
        for j in range(i):
            matrix[i,j] = chen_score(i+2,j+2,False)
            writer.writerow([f'{i+2};{j+2};o', f'{matrix[i,j]}'])
        for j in range(13-i):
            if i == i+j:
                matrix[i,i+j] = chen_score(i+2,i+2+j,False)
                writer.writerow([f'{i+2};{i+2+j};o', f'{matrix[i,i+j]}'])
            else: 
                matrix[i,i+j] = chen_score(i+2,i+2+j,True)
                writer.writerow([f'{i+2};{i+2+j};s', f'{matrix[i,i+j]}'])



data = pd.DataFrame(matrix, index=[f'{i+2}' for i in range(13)], columns=[f'{i+2}' for i in range(13)])
center = data.median().median()
sns.heatmap(data, annot=True, cmap='viridis', center=center, vmin=-1, vmax=20)
plt.title('Chen Score of all Starting Hands')
plt.show()
print(data)