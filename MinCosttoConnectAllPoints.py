from typing import List

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n
    
    def find(self, i):
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])
        return self.parent[i]
    
    def union(self, i, j):
        root_i, root_j = self.find(i), self.find(j)
        if root_i == root_j:
            return False
        if self.size[root_i] < self.size[root_j]:
            root_i, root_j = root_j, root_i
        self.parent[root_j] = root_i
        self.size[root_i] += self.size[root_j]
        return True

class Solution:
    def minCostConnectPoints(self, pontos: List[List[int]]) -> int:
        n = len(pontos)
        edges = []
        for i in range(n):
            for j in range(i+1, n):
                dist = abs(pontos[i][0] - pontos[j][0]) + abs(pontos[i][1] - pontos[j][1])
                edges.append((dist, i, j))
        edges.sort()
        uf = UnionFind(n)
        cost = 0
        for dist, i, j in edges:
            if uf.union(i, j):
                cost += dist
        return cost
