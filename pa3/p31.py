'''
# Sample code to perform I/O:

name = input()                  # Reading input from STDIN
print('Hi, %s.' % name)         # Writing output to STDOUT

# Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
'''

# Write your code here
class INode:
    def __init__(self, I, left_node = None, right_node = None):
        self.lo = I[0]
        self.hi = I[1]
        self.max_hi = I[1]
        self.left = left_node
        self.right = right_node
        self.parent = None
        self.left_hi = None
        self.right_hi = None
        self.parent_hi = None
        
class ITree:
    def __init__(self):
        self.T = None
        self.T_hi = None
    
    def insert(self, I):
        # I is the tuple denoting interval
        # lo based tree insert position
        y = None
        x = self.T
        while x is not None:
            if I[0] < x.lo:
                y = x
                x = x.left
            else:
                y = x
                x = x.right
        # high based tree insert position
        y_hi = None
        x_hi = self.T_hi
        while x_hi is not None:
            if I[1] < x_hi.hi:
                y_hi = x_hi
                x_hi = x_hi.left_hi
            else:
                y_hi = x_hi
                x_hi = x_hi.right_hi
        new_node = INode(I)     # new node to be inserted
        if y is None and y_hi is None:   # tree is empty
            self.T = new_node
            self.T_hi = new_node
        else:
            # insert in T
            if I[0] < y.lo:
                y.left = new_node
                y.left.parent = y
                # fix max_hi all the way to root
                p = y
                q = y.left
                while p is not None and p.max_hi < q.max_hi:
                    p.max_hi = q.max_hi
                    q = p
                    p = p.parent
            else:
                y.right = new_node
                y.right.parent = y
                # fix max_hi all the way to root
                p = y
                q = y.right
                while p is not None and p.max_hi < q.max_hi:
                    p.max_hi = q.max_hi
                    q = p
                    p = p.parent
            # insert in T_hi
            if I[1] < y_hi.hi:
                y_hi.left_hi = new_node
                y_hi.left_hi.parent_hi = y_hi
            else:
                y_hi.right_hi = new_node
                y_hi.right_hi.parent_hi = y_hi
    
    def min(self):
        x = self.T
        while x.left is not None:
            x = x.left
        return x

    def max(self):
        x = self.T
        max_node = None
        while x is not None and max_node is None:
            if x.max_hi == x.hi:
                max_node = x
                continue    # loop breaks after this step
            elif x.left is not None and x.max_hi == x.left.max_hi:
                x = x.left
            else:   # we can go to right without any checking
                x = x.right
        return max_node

    def lo_succ(self, I):
        # search interval
        x = self.T
        while x is not None and x.lo != I[0]:
            if x.lo < I[0]:
                x = x.right
            else:
                x = x.left
        if x is not None:
            if x.right is not None:
                # find min node in tree rooted at x.left
                y = x.right
                while y.left is not None:
                    y = y.left
                return y
            else:   # x.right is None
                z = x
                y = x.parent
                while y is not None and z == y.right:
                    z = y
                    y = z.parent
                return y

    def hi_succ(self, I):
        # search interval
        x_hi = self.T_hi
        while x_hi is not None and x_hi.hi != I[1]:
            if x_hi.hi < I[1]:
                x_hi = x_hi.right_hi
            else:
                x_hi = x_hi.left_hi
        if x_hi is not None:
            if x_hi.right_hi is not None:
                # find min node in tree rooted at x_hi.left_hi
                y_hi = x_hi.right_hi
                while y_hi.left_hi is not None:
                    y_hi = y_hi.left_hi
                return y_hi
            else:   # x_hi.right_hi is None
                z_hi = x_hi
                y_hi = x_hi.parent_hi
                while y_hi is not None and z_hi == y_hi.right_hi:
                    z_hi = y_hi
                    y_hi = z_hi.parent_hi
                return y_hi
        

    def is_overlap(self, I):
        x = self.T
        while x is not None and (x.hi <= I[0] or x.lo >= I[1]):
            if x.left is not None and x.left.max_hi >= I[0]:
                x = x.left
            else:
                x = x.right
        if x is None:
            return 0
        else:
            return 1
            
    def transplant(self, u, v):
        if u.parent is None:
            self.T = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v
        if v is not None:
            v.parent = u.parent
            
    def transplant_hi(self, u, v):
        if u.parent_hi is None:
            self.T_hi = v
        elif u == u.parent_hi.left_hi:
            u.parent_hi.left_hi = v
        else:
            u.parent_hi.right_hi = v
        if v is not None:
            v.parent_hi = u.parent_hi
    
    def delete(self, I):
        # search interval in T (same as T_hi due to uniqueness)
        x = self.T
        while x is not None and x.lo != I[0]:
            if x.lo < I[0]:
                x = x.right
            else:
                x = x.left
        if x is None:
            return
        # delete in T_hi
        if x.left_hi is None:
            self.transplant_hi(x, x.right_hi)
        elif x.right_hi is None:
            self.transplant_hi(x, x.left_hi)
        else:
            # find min in x.right_hi
            p_hi = x.right_hi
            while p_hi is not None:
                y_hi = p_hi
                p_hi = p_hi.left_hi
            # check if x is not y_hi parent
            if y_hi.parent_hi != x:
                self.transplant_hi(y_hi, y_hi.right_hi)
                y_hi.right_hi = x.right_hi
                y_hi.right_hi.parent_hi = y_hi
            self.transplant_hi(x, y_hi)
            y_hi.left_hi = x.left_hi
            y_hi.left_hi.parent_hi = y_hi
        # delete in T
        if x.left is None:
            z = x.parent
            self.transplant(x, x.right)
        elif x.right is None:
            z = x.parent
            self.transplant(x, x.left)
        else:
            # find min in x.right
            p = x.right
            while p is not None:
                y = p
                p = p.left
            # check if x is not parent of y
            z = y
            if y.parent != x:
                z = y.parent
                self.transplant(y, y.right)
                y.right = x.right
                y.right.parent = y
            self.transplant(x, y)
            y.left = x.left
            y.left.parent = y
        # fix max_hi from z till root
        while z is not None:
            c = z.hi
            l = 0 if z.left is None else z.left.max_hi
            r = 0 if z.right is None else z.right.max_hi
            z.max_hi = max(c, l, r)
            z = z.parent
    
T = int(input())
for t in range(0, T):
    tree = ITree()
    ops = int(input())
    for i in range(0, ops):
        raw = input().split()
        if raw[0] == "+":
            I = (int(raw[1]), int(raw[2]))
            tree.insert(I)
        elif raw[0] == "-":
            I = (int(raw[1]), int(raw[2]))
            tree.delete(I)
        elif raw[0] == "min":
            r = tree.min()
            print("[%d %d]" %(r.lo, r.hi))
        elif raw[0] == "max":
            r = tree.max()
            print("[%d %d]" %(r.lo, r.hi))
        elif raw[0] == "lsucc":
            I = (int(raw[1]), int(raw[2]))
            r = tree.lo_succ(I)
            if r is None:
                print("INVALID")
            else:
                print("[%d %d]" %(r.lo, r.hi))
        elif raw[0] == "hsucc":
            I = (int(raw[1]), int(raw[2]))
            r = tree.hi_succ(I)
            if r is None:
                print("INVALID")
            else:
                print("[%d %d]" %(r.lo, r.hi))
        elif raw[0] == "overlap":
            I = (int(raw[1]), int(raw[2]))
            r = tree.is_overlap(I)
            print(r)