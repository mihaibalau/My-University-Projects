import pickle
import numpy as np
import os
import torch

LABELS = ['airplane', 'automobile', 'bird', 'cat', 'deer',
          'dog', 'frog', 'horse', 'ship', 'truck']

def load_batch(filepath):
    with open(filepath, 'rb') as f:
        batch = pickle.load(f, encoding='bytes')
    # Images are flat arrays of 3072 values: 1024 R + 1024 G + 1024 B
    X = batch[b'data']               # shape: (10000, 3072)
    y = np.array(batch[b'labels'])   # shape: (10000,)

    # Reshape to (N, 3, 32, 32) then transpose to (N, 32, 32, 3) for RGB
    X = X.reshape(-1, 3, 32, 32).transpose(0, 2, 3, 1)
    return X, y

def load_cifar10(root_dir):
    X_train, y_train = [], []

    # Load all 5 training batches
    for i in range(1, 6):
        filepath = os.path.join(root_dir, f'data_batch_{i}')
        X, y = load_batch(filepath)
        X_train.append(X)
        y_train.append(y)

    X_train = np.concatenate(X_train, axis=0)  # (50000, 32, 32, 3)
    y_train = np.concatenate(y_train, axis=0)  # (50000,)

    # Load test batch
    X_test, y_test = load_batch(os.path.join(root_dir, 'test_batch'))

    return X_train, y_train, X_test, y_test