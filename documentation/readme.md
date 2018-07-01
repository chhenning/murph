# Day 10

Found the Simple Temporal Pooler project

https://www.youtube.com/watch?v=BHjiffn_i64
https://github.com/LongBoolean/simple-temporal-memory


This might be interesting:
https://github.com/cpp-taskflow/cpp-taskflow

# Day 9

Creating tutorials.

0 - Setting Up Code
1 - Sparse Binary Matrix
2 - SDR
3 - Random Spatial Pooler

# Day 8

Create first cpp version of random spatial pooler. It now selects the active cells when running one sdr through the pooler.

Toy around with python's jupyter notebook. Pretty cool tool to code, annotate, display/plot data.

# Day 7

Read through the code for spatial pooler and figure out how to replicate the code. The goal is to have a SP running like
Episode 6 from HTM School.

Let's pool the resources into one document.

# Day 6

Starting with Spatial Pooling Algorithm. As a refresher I'll go throught HTM school video Episode 6. See HTM_School.md

Let's also start with Chapter 3 in "2011 - Hierarchical Temporal Memory...". See 2011-HTM_paper.md

Let's also start a tutorial with simplest approximation of a spatial pooler function.

# Day 5

Adding more operations to sparse binary matrix.

* overlap
* match

# Day 4

Working on simple sparse binary vector and matrix class.

Some design choices:

* a std::set to store indices
* the matrix only stores 1D indices

# Day 3

Adding the notes from HTM School videos.

# Day 2

Starting with code analysis of Numenta's Nupic.Core (see nupic_analysis.md)

# Day 1

We need a matrix lib to represent SDRs. There are many libs out there and I have settled on blaze (see blaze.md).
