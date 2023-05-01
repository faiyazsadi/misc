from queue import PriorityQueue

def get_neighbours(u):
    return graph[u]

def heuristic_cost(u):
    return hcost[u]

def astar(start_node, goal_node):
    frontier = PriorityQueue()
    frontier.put((0, start_node))

    came_from = {}
    cost_so_far = {}
    came_from[start_node] = None
    cost_so_far[start_node] = 0


    while not frontier.empty():
        current_node = frontier.get()[1]
        print(current_node)
        if current_node == goal_node:
            break

        for next_node, distance in get_neighbours(current_node):
            new_cost = cost_so_far[current_node] + distance
            if next_node not in cost_so_far or new_cost < cost_so_far[next_node]:
                cost_so_far[next_node] = new_cost
                priority = new_cost + heuristic_cost(next_node)
                frontier.put((priority, next_node))
                came_from[next_node] = current_node
    
    path = []
    current_node = goal_node
    while current_node != start_node:
        path.append(current_node)
        current_node = came_from[current_node]
    
    path.append(current_node)
    path.reverse()

    return path


hcost = {
    'A': 11,
    'B': 6,
    'C': 99,
    'D': 1,
    'E': 7,
    'G': 0,
}


graph = {
    'A': [('B', 2), ('E', 3)],
    'B': [('C', 1),('G', 9)],
    'C': [('A', 10000)],
    'E': [('D', 6)],
    'D': [('G', 1)],
}

s = 'A'
t = 'G'

path = astar(s, t)

print(path)