import pandas as pd
import matplotlib.pyplot as plt

# read the data file and load it into a pandas dataframe
data = pd.read_csv('bmk_measures.txt', sep ='\t')
data.columns = ['#nodes', 'std::map', 'std::unordered_map', 'RedBlackTree']

# plot the three data series
fig = plt.figure(figsize=(15, 10))
plt.title('Benchmarking comparison')
plt.xlabel('# nodes')
plt.ylabel('time (μs)')
ax = plt.subplot(111)
ax.legend()
ax.plot(data['#nodes'], data['std::map'], label = 'map')
ax.plot(data['#nodes'], data['std::unordered_map'], label = 'unordered_map')
ax.plot(data['#nodes'], data['RedBlackTree'], label = 'RBTree')

if __name__ == '__main__':
    plt.show()