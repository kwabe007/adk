"""class Graph:
    self.nodeList = nodeList

class Node:

    def __init__(self):
        self.visited = False
        self.strength = strength
        self.adjList = adjList
        self.ditchList = ditchList"""
        
        
def makeObjsFromFile():
    matrixfile = open("matrixfile", "r")
    matrix = []
    ditchList = []
    for i in range(5):
        readLine = matrixfile.readline().rstrip()
        if readLine == "#MATRIX":
            while True:
                readLine = matrixfile.readline().rstrip()
                if not readLine == "#LIST":
                    lineList = readLine.split(" ")
                    lineList = [int(x) for x in lineList]
                    matrix.append(lineList)
                else:
                    while True:
                        readLine = matrixfile.readline().rstrip()
                        if not readLine == "#END":
                            lineList = readLine.split("-")
                            lhSide = lineList[0].split(",")
                            rhSide = lineList[1].split(",")
                            tempTuple = ((lhSide[0],lhSide[1]),(rhSide[0],rhSide[1]))
                            ditchList.append(tempTuple)
                        else:
                            break
                    break
        elif readLine == "#DEADEND":
            return matrix,ditchList

def main():
    print("Loading matrix and list from file...")
    matrix, ditchList= makeObjsFromFile()
    print("Load complete!\n")
    print("Here's the matrix")
    print(matrix)
    print("Here's the ditch list")
    print(ditchList)
    



main()
