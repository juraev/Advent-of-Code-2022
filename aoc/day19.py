
# from gekko import GEKKO
from gurobipy import Model
from gurobipy import *
import numpy as np

res = 1

with open('inputs/day19.txt') as f:
    lines = f.readlines()
    for (i, line) in enumerate(lines):
        if i == 3:
            break
        line = line.split()
        # m = GEKKO(remote=False)
        m = Model()

        # print('--------- Follow local path to view files --------------')
        # print(m.path)               # show source file path
        # m.open_folder()
        # print('-'*56)


        if line[0] == "Blueprint":
            blueprint = int(line[1][:-1])
            ore_or = int(line[6])
            clay_or = int(line[12])
            obsedian_or = int(line[18])
            obsedian_clay = int(line[21])
            geode_or = int(line[27])
            geode_obs = int(line[30])
        else :
            break

        minutes = 32
        
        num_ore = [m.addVar(vtype=GRB.INTEGER, name="num_ore_{}".format(i), lb=0) for i in range(minutes + 1)]
        num_clay = [m.addVar(vtype=GRB.INTEGER, name="num_clay_{}".format(i), lb=0) for i in range(minutes + 1)]
        num_obsedian = [m.addVar(vtype=GRB.INTEGER, name="num_obsedian_{}".format(i), lb=0) for i in range(minutes + 1)]
        num_geode = [m.addVar(vtype=GRB.INTEGER, name="num_geode_{}".format(i), lb=0) for i in range(minutes + 1)]
        
        num_ore_bot = [m.addVar(vtype=GRB.INTEGER, name="num_ore_bot{}".format(i), lb=0) for i in range(minutes + 1)]
        num_clay_bot = [m.addVar(vtype=GRB.INTEGER, name="num_clay_bot{}".format(i), lb=0) for i in range(minutes + 1)]
        num_obsedian_bot = [m.addVar(vtype=GRB.INTEGER, name="num_obsedian_bot{}".format(i), lb=0) for i in range(minutes + 1)]
        num_geode_bot = [m.addVar(vtype=GRB.INTEGER, name="num_geode_bot{}".format(i), lb=0) for i in range(minutes + 1)]
    

        m.addConstr(num_ore_bot[0] == 1)
        m.addConstr(num_clay_bot[0] == 0)
        m.addConstr(num_obsedian_bot[0] == 0)
        m.addConstr(num_geode_bot[0] == 0)

        m.addConstr(num_ore[0] == 0)
        m.addConstr(num_clay[0] == 0)
        m.addConstr(num_obsedian[0] == 0)
        m.addConstr(num_geode[0] == 0)


        print(ore_or, clay_or, obsedian_or, obsedian_clay, geode_or, geode_obs)


        m.addConstrs(num_ore_bot[i]  * ore_or      <= num_ore_bot[i-1]  * ore_or         + num_ore[i-1] for i in range(1, minutes + 1))
        m.addConstrs(num_clay_bot[i] * clay_or       <= num_clay_bot[i-1]     * clay_or       + num_ore[i-1] for i in range(1, minutes + 1))
        m.addConstrs(num_obsedian_bot[i] * obsedian_or   <= num_obsedian_bot[i-1] * obsedian_or   + num_ore[i-1] for i in range(1, minutes + 1))
        m.addConstrs(num_obsedian_bot[i] * obsedian_clay <= num_obsedian_bot[i-1] * obsedian_clay + num_clay[i-1] for i in range(1, minutes + 1))
        m.addConstrs(num_geode_bot[i] * geode_or      <= num_geode_bot[i-1]    * geode_or      + num_ore[i-1] for i in range(1, minutes + 1))
        m.addConstrs(num_geode_bot[i] * geode_obs     <= num_geode_bot[i-1]    * geode_obs     + num_obsedian[i-1] for i in range(1, minutes + 1))

        m.addConstrs(num_ore_bot[i] >= num_ore_bot[i-1] for i in range(1, minutes + 1))
        m.addConstrs(num_clay_bot[i] >= num_clay_bot[i-1] for i in range(1, minutes + 1))
        m.addConstrs(num_obsedian_bot[i] >= num_obsedian_bot[i-1] for i in range(1, minutes + 1))
        m.addConstrs(num_geode_bot[i] >= num_geode_bot[i-1] for i in range(1, minutes + 1))

        m.addConstrs(num_ore[i]      >= num_ore_bot[i-1] for i in range(1, minutes + 1))
        m.addConstrs(num_clay[i]     >= num_clay_bot[i-1] for i in range(1, minutes + 1))
        m.addConstrs(num_obsedian[i] >= num_obsedian_bot[i-1] for i in range(1, minutes + 1))
        m.addConstrs(num_geode[i]    >= num_geode_bot[i-1] for i in range(1, minutes + 1))

        m.addConstrs(num_ore[i] == num_ore_bot[i-1] + num_ore[i-1] - (num_ore_bot[i]-num_ore_bot[i-1]) * ore_or - (num_clay_bot[i]-num_clay_bot[i-1]) * clay_or - (num_obsedian_bot[i]-num_obsedian_bot[i-1]) * obsedian_or - (num_geode_bot[i]-num_geode_bot[i-1]) * geode_or for i in range(1, minutes + 1))
        m.addConstrs(num_clay[i] == num_clay_bot[i-1] + num_clay[i-1] - (num_obsedian_bot[i]-num_obsedian_bot[i-1]) * obsedian_clay for i in range(1, minutes + 1))
        m.addConstrs(num_obsedian[i] == num_obsedian_bot[i-1] + num_obsedian[i-1] - (num_geode_bot[i]-num_geode_bot[i-1]) * geode_obs for i in range(1, minutes + 1))
        m.addConstrs(num_geode[i] == num_geode_bot[i-1] + num_geode[i-1] for i in range(1, minutes + 1))

        m.addConstrs((num_ore_bot[i]-num_ore_bot[i-1] + num_clay_bot[i]-num_clay_bot[i-1] + num_obsedian_bot[i]-num_obsedian_bot[i-1] + num_geode_bot[i]-num_geode_bot[i-1]) <= 1 for i in range(1, minutes + 1))

        print('Solving...')

        m.setObjective(num_geode[minutes], GRB.MAXIMIZE)
        m.update()
        m.optimize()

        print('Objective: ', m.objVal)
        # print('num_ore: ', num_ore)
        # print('num_clay: ', num_clay)
        # print('num_obsedian: ', num_obsedian)
        # print('num_ore', [v.X for v in num_ore])
        # print('num_clay: ', [v.X for v in num_clay])
        # print('num_obsedian: ', [v.X for v in num_obsedian])
        # print('num_geode: ', [v.X for v in num_geode])

        # res += (i + 1) * m.objVal
        res *= m.objVal

print(res)
        

        





