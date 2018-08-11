#include "stdafx.h"

#include "sparse_binary_vector.hpp"
#include "sparse_binary_matrix.hpp"


void sparse_binary_vector__test()
{
    using namespace murph::simple;

    {
        // create a vector with 12 bits where three are turned on.
        sparse_binary_vector a(12, { 1,3,6 });
    }

    {
        // create a vector with 12 bits where three are turned on.
        sparse_binary_vector a(12, { 1,3,6,12 });
        //a.print();
    }
}

void sparse_binary_matrix__test()
{
    using namespace murph::simple;

    {
        // empty matrix
        sparse_binary_matrix a{};
        assert(a.rows() == 0);
        assert(a.columns() == 0);

        // add one ON bit at 0,0
        a = sparse_binary_matrix(10, 10);
        a.insert(0, 0);
        assert(a.num_non_zero() == 1);
        assert(a.contains(0, 0));
        assert(a.contains(0, 1) == false);

        // add one ON bit at index 88
        int index = 89;
        a.insert(index);
        auto i = index % a.rows();
        auto j = index / a.rows();
        
        assert(a.contains(i, j));

        // get access to indices
        const auto& indices = a.get_indices();
        assert(indices.size() == 2);

        assert(indices.find(0) != indices.end());
        assert(indices.find(index) != indices.end());
        assert(indices.find(99) == indices.end());

        // clear matrix
        a.clear();
        assert(a.num_non_zero() == 0);
    }

    {
        // create a matrix with 12x13 bits.
        sparse_binary_matrix a(12, 23);
        a.print();
    }

    {
        // create a vector with 12 bits where three are turned on.
        sparse_binary_matrix a{ { 0,1,1 },{ 1,0 } };
        assert(a.num_non_zero() == 3);
        assert(a.contains(0, 1));

        a.insert(0, 0);
        a.print();
    }
}


void unit_tests()
{
    sparse_binary_vector__test();
    sparse_binary_matrix__test();
}