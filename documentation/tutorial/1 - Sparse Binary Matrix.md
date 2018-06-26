# Sparse Binary Matrix

Hierarchical Temporal Memory (HTM) need a sparse binary matrix to represent Sparse Distributed Representations (SDR) which I'll be introduce in the next tutorial.

## Disclaimer

The implementation in this tutorial wont be an efficient nor a complete implementation of a Sparse Binary Matrix. In fact, over the course of this series we will add more and more functionality.

See [Future](#Future) 

# Theory

Like the name already says:

1. We need a way to represent values in a Matrix (2D) or Vector (1D) fashion.
2. We only need to represent two (**binary**) values. Naturally that would **0** or **1**.
3. The vast majority of values will be 0s hence the word `Sparse` in the name of this tutorial. Typically the sparsity is set to 2%.

For more theory have a look at [1], [2], and [4].

# Implementation

## Typedefs 

```
typedef size_t index_t;
typedef std::pair<size_t, size_t> coord_t;
typedef std::set<index_t> container_t;
```

## Storing Values

There have been many implementations of matrices, esspecially in c++. This implementation is a little different to due the requirements outlined in [above](# Theroy). Effectively, we don't need to allocate memory for the whole matrix but rather just store the indices for the few **1** values.

For now I have choosen to keep the indices in a `std::set<index_t>` for the following reasons:

* Easy to add indices without creating duplicates
* Indices will be ordered automatically.
* Finding, inserting, and removal of an index is of logarithmic complexity.
* The STL has set algoritms for Union, Difference, Intersection, etc. operations.

In addition to the `std::set` design choice, a coordinate x, y will be converted into a 1D index, and vice versa.

```
coord_t convert_index(index_t index) const 
{
    return coord_t(index / m_, index % m_);
}

index_t convert_coord(const size_t i, const size_t j) const
{
    return j * m_ + i;
}

index_t convert_coord(const coord_t& c) const
{
    return convert_coord(c.first, c.second);
}
```



## Cons


# Dense and Sparse Non-Binary Matrices

I'll be using 


# Future 

In the future this code might be replaced by a 3rd party lib, like blaze, see [3].


# Reference

[1] [BIOLOGICAL AND MACHINE INTELLIGENCE](https://numenta.com/resources/biological-and-machine-intelligence/)

[2] [Building HTM Systems - An HTM School Masters Course](https://buildinghtm.systems/)

[3] [Blaze](https://bitbucket.org/blaze-lib/blaze/src/master/)

[4] [HTM School]()