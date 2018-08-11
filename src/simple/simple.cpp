// simple.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "sdr.hpp"
#include "spatial_pooler.hpp"

#include "unit_tests.hpp"

using namespace murph;

static bool run_unit_tests = true;


int main()
{
    if (run_unit_tests)
    {
        unit_tests();
    }


    //simple::sparse_binary_matrix__test();
    //simple::sdr__test();

    //simple::run_test();

    return 0;
}

