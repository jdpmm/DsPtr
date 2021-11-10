# :]
import math
from time import time

class SparseTable:
    def __init__(self, values: list):
        self.__sparseTable = []
        self.__valuesInit = values
        self.__create()

    def __create (self):
        rows = math.floor(math.log2(len(self.__valuesInit))) + 1

        for row in range(rows):
            potencia2 = 2 ** row
            min_in_this_set = []

            for col in range(len(self.__valuesInit)):
                auxSet = self.__valuesInit[col : col+potencia2]
                if len(auxSet) == potencia2:
                    min_in_this_set.append( min(auxSet) )

            self.__sparseTable.append( min_in_this_set )
            print(self.__sparseTable[row], ":" , "2^{}".format(row))

    def query (self, a: int, b: int) -> int:
        p = math.floor(math.log2( b - a + 1 ))
        k = 2**p
        min_ = min(
            self.__sparseTable[p][a],
            self.__sparseTable[p][b - k + 1]
        )
        return min_



if __name__ == '__main__':
    values = [4, 2, 3, 7, 1, 5, 3, 3, 9, 6, 7, -1, 4]
    sp = SparseTable(values)
    print(sp.query(3, 5))
