import torch
from torch_geometric.datasets import Planetoid
import torch_geometric.utils as pyg_utils

def load_data():
    dataset = Planetoid(root='data', name='Cora')
    data = dataset[0]
    return data

def calculate_graph_stats(data):
    print(data)
    mean_degree = torch.bincount(data['edge_index'][0]).to(torch.float).mean()  # get average number of edges
    max_degree = torch.bincount(data['edge_index'][0]).max()                    # get max number of edges
    matrix_H_size = data['x'].shape                                             # read shape of H matrix
    num_classes = len(data['y'].unique())                                       # count the unique class ids present in the target tensor
    
    return mean_degree, max_degree, matrix_H_size, num_classes

if __name__ == "__main__":
    data = load_data()
    stats = calculate_graph_stats(data)
    print(f"Mean Degree: {stats[0]:.2f}, Max Degree: {stats[1]}, H size: {stats[2]}, num_classes: {stats[3]}")