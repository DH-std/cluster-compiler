import random
import sys
import subprocess
from fitness import evaluate

GEN_NUM = 100
POP_SIZE = 300

function_name = "img_boundary"

passes = []
with open('../pass.txt') as f:
    for line in f:
        passes.append(line.strip())


def tournament_selection(parents):
    tour_size = 3
    selected_parents = []
    parents_copy = [p for p in parents]

    while parents_copy:
        winner = None
        for _ in range(tour_size):
            tmp_parent = parents_copy.pop(random.randint(0, len(parents_copy)-1))
            if winner:
                if tmp_parent[1] < winner[1]:
                    winner = tmp_parent
            else:
                winner = tmp_parent
        selected_parents.append(winner)
    return selected_parents

def get_children(func, parents):
    i = 0
    tmp_children = []
    children = []
    selected_parents = tournament_selection(parents)
    while i < len(selected_parents):
        # 60% chance of crossover
        chance = random.randint(1,10)
        if chance >= 1 and chance <= 6:
            parent1 = selected_parents[i][0]
            parent2 = selected_parents[i+1][0]
            cross_pt = random.randint(0, min(len(parent1), len(parent2)))
            child = parent1[:cross_pt] + parent2[cross_pt:]
            # remove duplicates without changing orders
            child = nodup(child)
            tmp_children.append(child)
        i += 2
    passes_set = set(passes)
    for c in tmp_children:
        # 40% chance of mutation
        chance = random.randint(1,10)
        if chance >= 1 and chance <= 4:
           chance = random.randint(1,3)
           if chance == 1:
             # add a new pass
             new_passes = passes_set.difference(c)
             new_passes = list(new_passes)
             new_pass = new_passes[random.randint(0, len(new_passes) - 1)]
             if len(c) >= 16:
                 c[15] = new_pass
             else:
                 c.append(new_pass)
           elif chance == 2:
               # remove a pass:
               if c:
                   c.pop(random.randint(0, len(c) - 1))
           else:
               # swap order
               if len(c) >= 2:
                   indexes = random.sample(range(len(c)), 2)
                   i1 = indexes[0]
                   i2 = indexes[1]
                   tmp_pass = c[i1]
                   c[i1] = c[i2]
                   c[i2] = tmp_pass

        fit_score = fitness(func, c)
        if fit_score == 0:
            print "VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV"
            fit_score = fitness(func, c) 
        children.append((c, fit_score))
    # print children
    children = sorted(children, key=lambda x: x[1])
    return children

def fitness(func, passlist):
    return evaluate(func, passlist)

def select_new_parents(parents, children):
    new_parents = []
    i = 0
    j = 0
    while len(new_parents) < POP_SIZE:
        if parents[i][1] <= children[j][1]:
            new_parents.append(parents[i])
            i += 1
        else:
            new_parents.append(children[j])
            j += 1
        if (i >= len(parents)) or (j >= len(children)):
            break
    while len(new_parents) < POP_SIZE:
        if (i >= len(parents)):
            new_parents.append(children[j])
            j += 1
        else:
            new_parents.append(parents[i])
            i += 1
    return new_parents

def nodup(seq):
    seen = set()
    seen_add = seen.add
    return [x for x in seq if not (x in seen or seen_add(x))]

def ga(func):
    gen = 1

    #init
    parents = []
    for _ in range(POP_SIZE):
        tmp = []
        size = random.randint(1,16)
        indexes = random.sample(range(len(passes)), size)
        for i in indexes:
            tmp.append(passes[i])
        fit_score = fitness(func, tmp)
        if fit_score == 0:
            print "VVVVVVVVVVVVVVVVVVVVVVVVV"
            fit_score = fitness(func, tmp)
        parents.append((tmp, fit_score))

    while gen <= GEN_NUM:
        parents = sorted(parents, key=lambda x: x[1])
        children = get_children(func, parents)
        parents = select_new_parents(parents, children)
        gen += 1
        print "finish gen " + str(gen)
    return parents[0]

if __name__ == "__main__":
    func = "img_boundary"
    print ga(func)
