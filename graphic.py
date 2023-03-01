import matplotlib.pyplot as plt
from matplotlib.pyplot import clf

n_elements = [1, 2, 3, 4, 5, 6]

def parse (s):
    arr = s.split()
    t_VEB_Tree = float(arr[3])
    t_red_black_trees = float(arr[5])
    return t_VEB_Tree, t_red_black_trees

N_OPERATIONS = 5

times_VEB_Tree = [[] for _ in range(N_OPERATIONS)]
times_red_black_trees = [[] for _ in range(N_OPERATIONS)]

for n in n_elements:
    file_name = "./times/time-" + str(2**(2**n)) + ".md"
    with open(file_name) as file:
        header = file.readline()
        _ = file.readline()
        for op in range(N_OPERATIONS):
            a, b = parse(file.readline())
            times_VEB_Tree[op].append(a)
            times_red_black_trees[op].append(b)

# Insert
plt.plot(n_elements, times_VEB_Tree[0], color = 'red')
plt.plot(n_elements, times_red_black_trees[0], color = 'blue')
plt.xlabel('k: Number elements (2^(2^k))')
plt.ylabel('Time (s)')
plt.legend(['Insertion in  VEB Tree', 'Insertion in red_black_trees'])
plt.savefig('./graphics/insert.jpg')
plt.show()
clf()

# Lookup
plt.plot(n_elements, times_VEB_Tree[1], color = 'red')
plt.plot(n_elements, times_red_black_trees[1], color = 'blue')
plt.xlabel('k: Number elements (2^(2^k))')
plt.ylabel('Time (s)')
plt.legend(['IsMember in  VEB Tree', 'IsMember in red_black_trees'])
plt.savefig('./graphics/lookup.jpg')
plt.show()
clf()

# Predecessor
plt.plot(n_elements, times_VEB_Tree[2], color = 'red')
plt.plot(n_elements, times_red_black_trees[2], color = 'blue')
plt.xlabel('k: Number elements (2^(2^k))')
plt.ylabel('Time (s)')
plt.legend(['Predecessor in VEB Tree', 'Predecessor in red_black_trees'])
plt.savefig('./graphics/predecessor.jpg')
plt.show()
clf()

# Successor
plt.plot(n_elements, times_VEB_Tree[3], color = 'red')
plt.plot(n_elements, times_red_black_trees[3], color = 'blue')
plt.xlabel('k: Number elements (2^(2^k))')
plt.ylabel('Time (s)')
plt.legend(['Successor in VEB Tree', 'Successor in red_black_trees'])
plt.savefig('./graphics/successor.jpg')
plt.show()
clf()

# Erase
plt.plot(n_elements, times_VEB_Tree[4], color = 'red')
plt.plot(n_elements, times_red_black_trees[4], color = 'blue')
plt.xlabel('k: Number elements (2^(2^k)')
plt.ylabel('Time (s)')
plt.legend(['Deletion in  VEB Tree', 'Deletion in red_black_trees'])
plt.savefig('./graphics/erase.jpg')
plt.show()
clf()

