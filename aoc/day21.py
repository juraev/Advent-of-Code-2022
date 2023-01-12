
import torch 
import torch.nn as nn

with open("inputs/day21.txt") as f:
    lines = f.read().splitlines()

class Monkey:

    def __init__(self, name, val, op, left, right):
        self.name = name
        self.val = val
        self.op = None
        self.left = left
        self.right = right

    def set_op(self, op):
        if op == "+":
            self.op = (lambda x, y: x + y)
        elif op == "*":
            self.op = (lambda x, y: x * y)
        elif op == "-":
            self.op = (lambda x, y: x - y)
        elif op == "/":
            self.op = (lambda x, y: x / y)

    def eval(self):
        if self.op is None:
            return self.val
        else:
            return self.op(self.left.eval(), self.right.eval()) 
    
vars = {}

def get(name):
    if name not in vars.keys():
        vars[name] = Monkey(name, 0, None, None, None)
    return vars[name]


for line in lines:
    line = line.split()

    M = get(line[0][:4])
    
    if line[1].isnumeric():
        # M.val = int(line[1])
        M.val = torch.autograd.Variable(torch.tensor(int(line[1]), dtype=torch.float64), requires_grad=False)
    else:
        M.left = get(line[1])
        M.set_op(line[2])
        M.right = get(line[3])


root = get("root")


# with torch.no_grad():
# print (root.eval())















humn = get("humn")
humn.val.requires_grad = True


root.set_op("-")

# print(root.eval().item())


criterion = nn.MSELoss()
optimiser = torch.optim.SGD([humn.val], lr=0.001)

# w <- w - lr * gradient(w)

for i in range(20000):

    rt = root.eval()
    loss = criterion(rt, torch.tensor(0, dtype=torch.float64))

    optimiser.zero_grad()
    loss.backward()
    optimiser.step()



with torch.no_grad():
    print (humn.eval().item())
    print (root.eval().item())