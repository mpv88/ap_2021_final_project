import pandas as pd
import matplotlib.pyplot as plt

# read the data file and load it into a pandas dataframe
data = pd.read_csv('bmk_measures_double.txt', sep ='\t')
data.columns = ['#elements', 'std::map', 'std::unordered_map', 'RedBlackTree']

# plot the three data series
fig = plt.figure(figsize=(15, 10))
plt.title('Benchmarking comparison (double)')
plt.xlabel('# elements to be found')
plt.ylabel('time (μs)')
ax = plt.subplot(111)
ax.plot(data['#elements'], data['std::map'], label = 'map')
ax.plot(data['#elements'], data['std::unordered_map'], label = 'unordered_map')
ax.plot(data['#elements'], data['RedBlackTree'], label = 'RBTree')
ax.legend()


if __name__ == '__main__':
    plt.show()