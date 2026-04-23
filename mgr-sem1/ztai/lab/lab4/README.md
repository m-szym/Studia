# Introduction to Graph Neural Networks

Author: Marek Szymański 193229

## Task 0

Mean Degree: 3.90
Max Degree: 168
H matrix shape: 2708 x 1433
Number of classes: 7

## Task 1

Multi-layer perceptrion: 200967 parameters
Graph-convolutional network: 200967 parameters
Graph-attentional network: 201493 parameters

## Task 2

All models trained and tested for **30** epochs using full-graph.

|     | Training time [s] | Accuracy |
|-----|-------------------|----------|
| MLP | 0.2877            | 0.4110   |
| GCN | 0.2811            | 0.7620   |
| GAT | 0.3352            | 0.7350   |

The dedicated graph architectures achieve clearly superior results.

## Task 3

All models trained using neighbourhood sampling.

|     | Training time [s] | Iterations | Accuracy |
|-----|-------------------|------------|----------|
| MLP | 0.2888            | 132        | 0.4560   |
| GCN | 0.2842            | 92         | 0.7490   |
| GAT | 0.3352            | 78         | 0.7530   |

---

Comparison between full and sampled graph. 

|     | Accuracy on full graph | Accuracy on sampled graph | Full - sampled | Change [%] |
|-----|------------------------|---------------------------|----------------|------------|
| MLP | 0.4110                 | 0.4560                    | -0.0450        | -10.95     |
| GCN | 0.7620                 | 0.7490                    |  0.0130        |   1.70     |
| GAT | 0.7350                 | 0.7530                    | -0.0180        | -02.45     |

The MLP model noted most drastic change in accuracy losing almost 11% compared to full-graph training.

GCN and GAT noted only slight differences in accuracy - gaining 1.7% and losing 2.45% respectively.

All models perfmormed significantly more iterations in the same clock time - 4 times more for MLP, 3 for GCN and 2.6 in case of GAT.