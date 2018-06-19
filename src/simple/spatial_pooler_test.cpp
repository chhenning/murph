#include "stdafx.h"


#include <cmath>

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

namespace murph
{
    namespace simple
    {
        typedef size_t index_t;
        typedef std::vector<index_t> sdr_t;

        // 1D input space
        const size_t input_space_size = 300;
        
        const size_t num_columns = 300;
        
        const float input_bits_coverage = 0.5;


        // 1D column
        class column
        {
        public:

            /*
            // Select n random bits from the input space.
            */
            void init(size_t input_size)
            {
                size_t num_coverage = (size_t)(input_size * input_bits_coverage);
                size_t counter = 0;

                // look for n bits
                while (input_indices.size() < num_coverage)
                {
                    input_indices.insert(rand() % input_size);
                }
            }

           
            // A column is connected to a random set of input bits. The randomness is defined by some parameters. See initialize() member
            std::set<index_t> input_indices;
        };

        typedef std::vector<column> columns_t;

        void init_columns(columns_t& columns, size_t input_space_size)
        {
            for (auto& c : columns)
            {
                c.init(input_space_size);
            }
        }


        void run_test()
        {
            auto columns = columns_t(num_columns);
            init_columns(columns, input_space_size);
        }
    }
}