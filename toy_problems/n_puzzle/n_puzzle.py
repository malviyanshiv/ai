import queue as Q
import time
import sys
import math
import os
import argparse
import random
## Function for clearing screen

# Globals containing the goal state and its position
GOAL = []
COORD = []
MAX = 100000
S_G = False
D_G = False

## The Class that Represents the Puzzle

class PuzzleState(object):

    """docstring for PuzzleState"""

    def __init__(self, config, n, parent=None, action="Initial", cost=0):

        if n*n != len(config) or n < 2:
            raise Exception("the length of config is not correct!")

        self.n = n
        self.cost = cost
        self.parent = parent
        self.action = action
        self.dimension = n
        self.config = config
        self.children = []

        for i, item in enumerate(self.config):
            if item == 0:
                self.blank_row = i // self.n
                self.blank_col = i % self.n
                break
        self.goal = self.is_goal()
        self.f_val = self.cost + calculate_manhattan_dist(self.config, self.dimension)

    def display(self):
        maxi = len(str(self.n*self.n-1))
        l = "+"
        for _ in range(self.n):
            l+= "-"+ "-"*maxi+"-+"
        st = "|"
        word = " {} "
        for i in range(self.n):
            print(l)
            offset = i * self.n
            print(st, end="")
            for j in range(self.n):
                if self.config[offset+j] == 0:
                    print(" {:^{}} ".format("", maxi), end=st)
                else:
                    print(" {:^{}} ".format(self.config[offset + j], maxi), end=st)
            print()
        print(l)

    def move_left(self):
        if self.blank_col == 0:
            return None
        else:
            blank_index = self.blank_row * self.n + self.blank_col
            target = blank_index - 1
            new_config = list(self.config)
            new_config[blank_index], new_config[target] = new_config[target], new_config[blank_index]
            return PuzzleState(tuple(new_config), self.n, parent=self, action="Left", cost=self.cost + 1)

    def move_right(self):
        if self.blank_col == self.n - 1:
            return None
        else:
            blank_index = self.blank_row * self.n + self.blank_col
            target = blank_index + 1
            new_config = list(self.config)
            new_config[blank_index], new_config[target] = new_config[target], new_config[blank_index]
            return PuzzleState(tuple(new_config), self.n, parent=self, action="Right", cost=self.cost + 1)

    def move_up(self):
        if self.blank_row == 0:
            return None
        else:
            blank_index = self.blank_row * self.n + self.blank_col
            target = blank_index - self.n
            new_config = list(self.config)
            new_config[blank_index], new_config[target] = new_config[target], new_config[blank_index]
            return PuzzleState(tuple(new_config), self.n, parent=self, action="Up", cost=self.cost + 1)

    def move_down(self):
        if self.blank_row == self.n - 1:
            return None
        else:
            blank_index = self.blank_row * self.n + self.blank_col
            target = blank_index + self.n
            new_config = list(self.config)
            new_config[blank_index], new_config[target] = new_config[target], new_config[blank_index]
            return PuzzleState(tuple(new_config), self.n, parent=self, action="Down", cost=self.cost + 1)

    def expand(self):

        """expand the node"""
        # add child nodes in order of UDLR
        if len(self.children) == 0:
            up_child = self.move_up()
            if up_child is not None:
                self.children.append(up_child)
            down_child = self.move_down()
            if down_child is not None:
                self.children.append(down_child)
            left_child = self.move_left()
            if left_child is not None:
                self.children.append(left_child)
            right_child = self.move_right()
            if right_child is not None:
                self.children.append(right_child)
        return self.children

    def __eq__(self, another):
        for x, y in zip(self.config, another.config):
            if x != y:
                return False
        return True

    def __lt__(self, another):
        return self.f_val < another.f_val

    def __gt__(self, another):
        return self.f_val < another.f_val

    def __cmp__(self, another):
        return cmp( self.f_val, another.f_val)

    def __hash__(self):
        return hash( self.config )

    def is_goal(self):
        global GOAL
        for i in range(0,self.n**2):
            if self.config[i] != GOAL[i]:
                return False
        return True

## Defining various helper functions

# For clearing console screen
def cls():
    os.system('cls' if os.name=='nt' else 'clear')

# For calculating the heuristic value
def calculate_manhattan_dist(values, n):

    """calculatet the manhattan distance of a tile"""
    global COORD
    cost = 0
    for i in range(n):
        for j in range(n):
            ind = i*n+j
            if values[ind] == 0:
                continue
            cost = cost + abs(COORD[values[ind]][0] - i) + abs(COORD[values[ind]][1] - j)
    return cost

# Showing the execution of calculated plan
def show(start, path):
    cls()
    s = ['|', '/', '-', '\\']
    print(f"Executing Solution...{s[0]}")
    #start.display()
    start[0].display()
    time.sleep(1)
    for i in range(1, len(start)):
        cls()
        print(f"Executing Solution...{s[i%4]}")
        print("GOAL CONFIG: ")
        start[-1].display()
        print("Executing : " + path[i])
        start[i].display()
        time.sleep(1)

# Writing output to standard out
def writeOutput( node, max_d, n_exp, timer):
    cls()
    path = []
    start = get_path(node, path)
    path.reverse()
    start.reverse()
    print("INITIAL CONFIG: ")
    start[0].display()
    print("FINAL CONFIG: ")
    start[-1].display()
    res = ["path_to_goal: ", "cost_of_path: ", "nodes_expanded: ", "search_depth: ", "max_search_depth: ", "running_time: ", "max_ram_usage: "]
    if sys.platform == "win32":
        import psutil
        rsc =  psutil.Process().memory_info().rss
    else:
        import resource
        rsc = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss

    print(res[0] + str(path))
    print(res[1] + str(node.cost))
    print(res[2] + str(n_exp))
    print(res[3] + str(node.cost))
    print(res[4] + str(max_d))
    print(res[5] + str(timer))
    print(res[6] + str(rsc))
    n = input("Show execution(y/n):")
    if n == 'y' or n == 'Y':
        show(start, path)

# Extracting path
def get_path( curr , l):
    s = []
    while curr.action != "Initial":
        l.append(curr.action)
        s.append(curr)
        curr = curr.parent
    return s

#Generating a random new state
def get_random_state(n):
    global GOAL
    start = PuzzleState(tuple(GOAL), n)
    i = 0
    while i < 100:
        start = random.choice(start.expand())
        i += 1
    return start.config

#Checking the validity of goal state
def check_goal(n):
    global GOAL
    for i in range(n*n):
        if i not in GOAL:
            return False
    if len(GOAL) != n*n:
        return False
    return True

#Counting total number of inversions
def get_inversions(state, n):
    cnt = 0
    for i in range(n*n-1):
        for j in range(i+1, n*n):
            if state[i] != 0 and state[j] != 0 and state[i] > state[j]:
                cnt += 1
    return cnt

def check_initial(ini, n):
    for i in range(n*n):
        if i not in ini:
            return False
    if len(ini) != n*n:
        return False
    return True

def set_coord(n):
    global COORD, GOAL
    COORD = [ 0 for _ in range(n*n)]
    for i in range(n):
        for j in range(n):
            ind = i*n+j
            COORD[GOAL[ind]] = (i, j)

def get_default_goal(n):
    a = [i for i in range(n*n)]
    return tuple(a)

def print_starter(n, initial):
    print(f"Starting with {n}-Puzzle Problem")
    print("INITIAL STATE:")
    a = PuzzleState(initial, n)
    a.display()
    print("FINAL STATE:")
    a = PuzzleState(tuple(GOAL), n)
    a.display()


def A_star_search(initial_state):

    """A * search"""
    start = time.time()
    frontier = Q.PriorityQueue()
    frontier.put(initial_state)
    explored = set()
    explored.add(initial_state)
    max_d = 0
    cnt = 0
    n = initial_state.n
    while not frontier.empty():
        curr = frontier.get()
        if curr.goal:
            writeOutput(curr, max_d, cnt, time.time()-start)
            return
        if cnt > MAX:
            print("Cannot find solution within the limited moves....")
            if S_G and D_G:
                print("Please recheck yours initial and final states")
            elif S_G:
                print("Please check if given initial state is compatible with goal")
            exit(0)
        cnt = cnt+1
        for i in curr.expand():
            if i not in explored:
                frontier.put(i)
                explored.add(i)
                max_d = max(max_d, i.cost)
                

if __name__ == '__main__':
    #global GOAL
    parser = argparse.ArgumentParser(
        description='''This is a automatic solver for n-Puzzle toy game using A* search and manhattan heuristic. ''')
    parser.add_argument('-n', type=int, default=3, help="Specify size of problem [A problem of size n contains n*n blocks]")
    parser.add_argument('-s', default="", help="This is the initial configuration of board")
    parser.add_argument('-g', default="", help="This is the goal configuration to reach")
    args = parser.parse_args()
    if len(args.g) == 0:
        GOAL = get_default_goal(args.n)
        set_coord(args.n)
    else:
        D_G = True
        try:
            GOAL = tuple(map(int, args.g.split(",")))
        except ValueError as e:
            print("Problem in parsing goal state !!!")
            print("A valid goal state for n=3 is like: 1,2,3,4,5,6,7,8,0")
            print("Try using -h option")
            exit(1)
        except Exception as e:
            print(str(e))
        if not check_goal(args.n):
            print("Goal state is not valid")
            print("A valid goal state for n=3 is like: 1,2,3,4,5,6,7,8,0")
            exit(1)
        set_coord(args.n)
    if len(args.s) == 0:
        initial = get_random_state(args.n)
    else:
        S_G = True
        try:
            initial = tuple(map(int, args.s.split(",")))
        except ValueError as e:
            print("Problem in parsing start state !!!")
            print("A valid start state for n=3 is like: 1,2,4,3,5,6,0,8,7")
            print("Try using -h option")
            exit(1)
        except Exception as e:
            print(str(e))
        if not check_initial(initial, args.n):
            print("Start state is not valid")
            print("A valid start state for n=3 is like: 1,2,4,3,5,6,0,8,7")
            exit(1)
    print_starter(args.n, initial)
    n = input("Wanna Continue(y/n): ")
    if n  == 'y' or n == 'Y':
        print("Searching for solution....")
        hard_state = PuzzleState(initial, args.n)
        A_star_search(hard_state)