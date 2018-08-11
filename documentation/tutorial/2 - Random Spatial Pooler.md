# Random Spatial Pooler

In this tutorial, we'll implement a **very** simplistic algorithm of the spatial pooler (**SP**). It will hopefully provide us with a base to add more and more features.

This tutorial is mostly based on [1] and [2].

The term Random Spatial Pooler comes from the video @todo


Ideally such tutorial is a prime candidate for a jupyter notebook using python. But in this instance I'll stick with C++. Later I might add a such a notebook.

A few caveats before we start:

* Each SDR is 1D.
* The SP has no learning step.
* Each column is 1D. Meaning just one cell.
* The receptive field for each column is the whole input space.

These are pretty severe caveats and will need to be eliminated in subsequent tutorials.


## Terms

This tutorial is not an introduction of the HTM. For that please start with the links in the [reference section](#references).


* **Input Space**: The universe of all values and value combinations. For instance, all possible values of a sin curve. Or all values of a time series containing a datetime and power consumption.
* **SDR**: An instance of the input space. Basically a bit array.
* **Receptive Field**: A list bits in the input space that a column might make a connection with.
* **Permanence**: Represents the strength of a connection. The higher the better. Range is [0.0,1.0]

## Setting up the source code

Let's include some c++ standard headers.

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

// uniform distribution to generate some ON bits.
std::uniform_int_distribution<size_t> uniform_distribution(0, input_space_size - 1);

// normal distribution around the connectin_threshold
std::normal_distribution<float> normal_distribution(connection_threshold, 0.5);
```

## Generating some data

## The SP Algorithm

Two steps:

1. Initialize the SP based in the input space.
2. [Feed SDRs and compute](#Compute)


### Initializing the SP

One time procedure to define the SPs columns and how they map back into the input space. Each column has its own receptive field (collection of bits in input space) and permanence (strengh). If the permanence is strong enough a connection is established.

```
auto columns = columns_t(num_columns);
std::for_each(columns.begin(), columns.end(), [](column& col) { col.init(); });
```


### Compute

* Calculate overlap score 
* Select n active columns 


## References

[1] [HTM School Episode 6]()

[2] [Input Space chapter](https://buildinghtm.systems/input-space/)