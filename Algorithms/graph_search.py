# Breath-first search vs Depth-first search
# For simplicity use python instead of C to illustrate algorithms
from collections import deque


'''
     1
   // \\
   2 == 3
 // \\   \\
4    5    6
'''

# Graph represented as a python dict
G = {
    1 : [2, 3],
    2 : [1, 3, 4, 5],
    3 : [1, 2, 6],
    4 : [2],
    5 : [2],
    6 : [3]
}

# Breath-first search with a starting node
def bfs(G, start):
    queue = deque([start])
    visited = set()
    traversal = []

    while queue:
        vertex = queue.popleft() # Deque a vertex until the layer is cleared
        if vertex not in visited:
            visited.add(vertex)
            traversal.append(vertex)
            for nbor in G[vertex]:
                # Add each nbor to the queue, search layer by layer
                if nbor not in visited:
                    queue.append(nbor)

    print(traversal)


bfs(G, 1) # [1, 2, 3, 4, 5, 6]


# Depth-first search with a starting node
def dfs(G, start):
    stack = [start]
    visited = set()
    traversal = []

    while stack:
        vertex = stack.pop() # Pop the most recently added, go deep!
        if vertex not in visited:
            visited.add(vertex)
            traversal.append(vertex)
            for nbor in G[vertex]:
                if nbor not in visited:
                    stack.append(nbor)
    
    print(traversal)


dfs(G, 1) 
