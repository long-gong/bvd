# Birkhoff–von Neumann Decomposition

## Pre-requisites

```bash
sudo apt-get install libboost-graph-dev libeigen3-dev
```

## Padding a matrix to doubly stochastic 

```bash
make example
```

Sample output:
```bash
Before: mat = 
0 3 2 0 3 1 1 0
3 2 3 3 0 4 1 4
3 2 1 2 4 3 3 3
0 4 0 0 1 3 1 1
3 0 4 0 1 0 2 3
1 4 4 3 1 3 3 2
0 2 1 4 2 0 1 0
4 2 3 4 4 1 3 0

w = 21

After: mat = 
3 3 2 0 3 1 1 8
3 3 3 3 0 4 1 4
3 2 1 2 4 3 3 3
4 4 0 0 1 9 2 1
3 1 7 0 5 0 2 3
1 4 4 3 1 3 3 2
0 2 1 9 3 0 6 0
4 2 3 4 4 1 3 0
Is it a doubly stochastic matrix 1
```

## Demo

```bash
make demo
```

Sample output:
```bash
Generating random matches ...
        (0, 5) (1, 7) (2, 3) (3, 1) (4, 4) (5, 0) (6, 6) (7, 2) 
        (0, 0) (1, 7) (2, 3) (3, 2) (4, 5) (5, 6) (6, 4) (7, 1) 
        (0, 4) (1, 7) (2, 5) (3, 1) (4, 2) (5, 3) (6, 0) (7, 6) 
Done

Got 3 matchings:
        (0, 4) (1, 7) (2, 3) (3, 1) (4, 5) (5, 0) (6, 6) (7, 2) 
        (0, 5) (1, 7) (2, 3) (3, 2) (4, 4) (5, 6) (6, 0) (7, 1) 
        (0, 0) (1, 7) (2, 5) (3, 1) (4, 2) (5, 3) (6, 4) (7, 6) 
```