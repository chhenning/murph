# Setting Up The Code

This series of tutorials attempts to build a Hierarchical Temporal Memory (HTM) system. It will be written in modern c++. Some algorithms might be 
developed and highlighted in jupyter notebooks for visualizing and tinkering but the final implementation should be in c++.

I'll try to stay away from 3rd party libs as much as possible but for some components like matrices I'll be using [blaze](#Reference). It also means that 
I'll use the latest c++ version available, like c++17 to make use of filesystem.

## Disclaimer

This code is for educational purposes only.

# Sparse Binary Matrices

tutorial [here](https://github.com/chhenning/murph/blob/master/documentation/tutorial/1%20-%20Sparse%20Binary%20Matrix.md)

# Dense and Sparse Non-Binary Matrices

See [blaze](#Reference).

```
// A sparse matrix with floats as element type
typedef blaze::CompressedMatrix<float, blaze::rowMajor> sparse_matrix_t;

// A dense matrix with std::uint32 as element type
typedef blaze::DynamicMatrix<std::uint32, blaze::rowMajor> dense_matrix_t;

// Converting from dense to sparse
blaze::DynamicMatrix<float, blaze::rowMajor> dense{ {0.f, 1.f, 2.f},{0.f, 0.f, 5.f},{8.f, 7.f, 0.f} };
blaze::CompressedMatrix<float, blaze::rowMajor> sparse(dense);
assert(sparse.nonZeros(2) == 2);

// Converting from sparse<int> to dense<float>
blaze::CompressedMatrix<std::uint32, blaze::rowMajor> sparse2{ {0,99,88}, {0,77,11} };
blaze::DynamicMatrix<float, blaze::rowMajor> dense2(sparse2);
```

# Reference

[1] [Blaze](https://bitbucket.org/blaze-lib/blaze/src/master/)