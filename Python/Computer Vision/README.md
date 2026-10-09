# Computer Vision

Labs from the computer vision and deep learning course. The notebooks are the work, with saved cell outputs removed. Images and the CIFAR archives are not in the repo.

`lab1-numpy-images.ipynb` is the warmup: NumPy arrays, plotting, OpenCV and a first look at PyTorch tensors.

`lab2-softmax-classification.ipynb` is image classification from scratch. I wrote softmax (including temperature, so the distribution can be made sharper or flatter), then a linear classifier on CIFAR-10. `cifar10.py` loads a batch, reshapes the flat 3072-byte rows into 32x32 RGB images and returns the ten class names.

`lab3-convolution.ipynb` drops down to the operation itself. Convolution and pooling are implemented directly, then applied as classic filters: low-pass to keep smooth regions, and the usual edge-oriented kernels, so I could see what a layer actually does to a photo before using a framework version.

`cifar10-cnn.ipynb` trains a small network on CIFAR-10: two convolutions, max-pool, three linear layers, cross-entropy and SGD with momentum. For each epoch I store train and test loss and accuracy and plot them side by side, which is the check that the model is learning the training set and what happens on the test set.

Technologies: Python, NumPy, Matplotlib, OpenCV, PyTorch, torchvision, CIFAR-10.
