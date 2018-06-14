

# Day 1

We need a matrix lib to represent SDRs. There are many libs out there and I have settled on blaze (see blaze.md).

# Day 2

Starting with code analysis of Numenta's Nupic.Core (see nupic_analysis.md)

# Day 3

Adding the notes from HTM School videos.

# Day 4

Working on simple sparse binary vector and matrix class.

Some design choices:

* a std::set to store indices
* the matrix only stores 1D indices
