class Node:
    def __init__(self, row: int, col: int, val: int):
        self.row = row
        self.col = col
        self.val = val

def sparse_martix (mtx: list) -> None:
    nodes = []
    for i in range(len(mtx)):
        for j in range(len(mtx[0])):
            if mtx[i][j] != 0:
                nodes.append( Node(i, j, mtx[i][j]) )

    for i in range(len(mtx)):
        print(f"[{nodes[i].row}, {nodes[i].col}] : [{nodes[i].val}]")

if __name__ == '__main__':
    matrix = [
        [0, 0, 5, 2],
        [0, 0, 0, 6],
        [9, 0, 0, 0],
        [7, 0, 0, 0]
    ]
    sparse_martix(matrix)
