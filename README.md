# Birkhoff–von Neumann Decomposition

## Pre-requisites

```bash
sudo apt-get install libboost-graph-dev
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