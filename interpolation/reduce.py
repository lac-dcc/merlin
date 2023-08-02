import sys
from sympy import *

if __name__ == '__main__':
    x = symbols('x')
    y = symbols('y')
    
    if len(sys.argv) < 2:
        print("Input invalid")
        sys.exit(1)
    
    expr_str = sys.argv[1]
    expr = sympify(expr_str)
    simplified_expr = simplify(expr)
    print(simplified_expr)