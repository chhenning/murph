# Notes from the 2011 paper

2011 - HIERARCHICAL TEMPORAL MEMORY including HTM Cortical Learning Algorithms.pdf

Terms:





# Chapter 3: Spatial Pooling Implementation and Pseudocode

First implementation of the spatial pooler **FUNCTION**.

The **INPUT** to this code is an array of bottom-up binary inputs from sensory data or the previous level

The code computes `activeColumns(t)` the list of columns that win.

The pseudocode is split into **three distinct phases** that occur in sequence:

1. Compute the Overlap with the current input for each column.
2. Compute the winning columns after inhibition.
3. Update Synapse permanence adn internal variables.

Skipping phase 3 is like turning off learning.

## Initialization

Each column select a random set of inputs (bits from input space). The randomness refer to a random natural center over the input region.

Each input is represented by a synapse and assigned a random permanence value.

Column Properties:
    
    * center in input region
    * array of input bits around the center (rectangle)
    * each bit in the array has permanence value biased towards the center (distance to center)

Random Permanence Value:
    
    * small range around `connectedPerm` parameter. It defines the minimum permanence value at which a synapse is considered "connected".


## Phase 1: Overlap

```
for( c in columns )
{
    // reset overlap for column c
    overlap(c) = 0;

    // number of connected synapses with active inputs, multiplied by its boost
    for(s in connected_synapses(c))
        overlap(c) += input(t, s.source_input);

    if(overlap(c) < minOverlap>)
    {
        overlap(c) = 0;
    }
    else
    {
        overlap(c) *= boost(c);
    }
}
```


## Phase 2: Inhibition

```
for( c in columns )
{
    min_local_activity = kth_score(neighbors(c), desired_local_activity);

    if(overlap(c) > 0 && overlap(c) >= min_local_activity)
    {
        active_columns(t).append(c);
    }
}
```