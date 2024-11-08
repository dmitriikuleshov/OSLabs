import matplotlib.pyplot as plt

threads_time = {}

with open('/home/home/OSLabs/lab2/research/results.txt', 'r') as file:
	for line in file:
		parts = line.split()
		thread_count = int(parts[0])
		time = float(parts[1])
		if thread_count not in threads_time:
			threads_time[thread_count] = [time]
		else:
			threads_time[thread_count].append(time)


threads_time = {key : sum(threads_time[key]) / len(threads_time[key]) for key , value in threads_time.items()}

plt.figure(figsize=(10, 6))
plt.plot(threads_time.keys(), threads_time.values(), marker='o', linestyle='-', color='b')
plt.xlabel('Number of threads')
plt.ylabel('Execution time (seconds)')
plt.title('The dependence of the execution time on the number of threads')
plt.grid(True)
plt.savefig('graph.png', format='png', dpi=300)
