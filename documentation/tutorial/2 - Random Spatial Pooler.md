# Random Spatial Pooler

In this tutorial, we'll implement a **very** simplistic algorithm of the spatial pooler (**SP**). It will hopefully provide us with a base to add more and more features.

This tutorial is mostly based on [1] and [2].

The term Random Spatial Pooler comes from the video @todo


Ideally such tutorial is a prime candidate for a jupyter notebook using python. But in this instance I'll stick with C++. Later I might add a such a notebook.

A few caveats before we start:

* Each SDR is 1D.
* The SP has no learning step.
* Each column is 1D.
* The receptive field for each column is the whole input space.

These are pretty severe caveats and will need to be eliminated in subsequent tutorials.


## Terms

This tutorial is not an introduction of the HTM. For that please start with the links in the [reference section](#references).


* **Input Space**: 
* **SDR**: An instance of the input space. Basically a bit array.
* **Receptive Field**: A list bits in the input space
* **Permanence**: 

## Setting up the source code

```
#include <cmath>
#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include <vector>
```





## Parameters

* **Input Space Size**: The length of the 1D input space.
* **Number of Columns**: The number of 1D columns of the SP.
* **Potential Percentage**: The percentage of input bits a column can connected to. (aka receptive field).
* **Connection Threshold**: Describes the minimum permanence 

```
// 1D input space
const size_t input_space_size = 300;

// number of columns
const size_t num_columns = 300;

// number of potential connections (percentage of input space bits)
const float potential_percent = 0.5f;

// if permanence is >= than there is a connection
const float connection_threshold = 0.1f;

// if overlap score is >= then a column becomes active
const size_t overlap_threshold = 40;
```

To generate random data we'll use 

```
const size_t seed = 0;
std::default_random_engine generator(seed);

std::uniform_int_distribution<size_t> uniform_distribution(0, input_space_size - 1);

// normal distribution around the connectin_threshold
std::normal_distribution<float> normal_distribution(connection_threshold, 0.5);

```


## Generating some data

## The SP Algorithm

Two steps:

1. Initialize the SP based in the input space.
2. 

### Initializing the SP

### Compute


## References

[1] [HTM School Episode 6]()

[2] [Input Space chapter](https://buildinghtm.systems/input-space/)