# Spatial Pooler

This document only deals with details of the spatial pooler function.

The Spatial Pooler is responsible for creating a SDR of the input. Given an input it computes a set of sparse active columns.

There are two main functions.

1. Initialize
2. compute

## Parameters

inputDimensions - An int vector representing the dimensions of the input. 

columDimensions - An int vector representing the dimensions of a column the the SP.

potentialRadius -   An float parameter which determines the extent of the input that each column can potentially be connected to.
                    It represents the input bits which a column can "see". A large value can result in global coverage, that is
                    a column can potentially connect to every input bit.
                    This parameter defines a square area: A column will have a max square potential ppol with sides of length 
                    (2 * potentialRadius + 1)

potentialPct -  A float parameter representing the percentage of the input, within a column's potential radius, that a column can be
                connected to. If 1.0 the column will connect to every input within its coverage.
                This parameter is used to give each column a unique potential pool when a large potentialRadius causes overlap between the columns.
                At initialization time we choose ((2*potentialRadius + 1)^(# inputDimensions) * potentialPct) input bits to comprise the column's potential pool.

                

## Initialization

## compute
