#include "stdafx.h"


#include <cmath>

#include <algorithm>
#include <iostream>
#include <random>
#include <set>
#include <vector>

using namespace std;

namespace murph
{
    namespace simple
    {
        ////////////////
        // This is an example of a random spatial spooler which doesn't learn.


        typedef size_t index_t;
        typedef std::vector<index_t> sdr_t;

        // 1D input space
        const size_t input_space_size = 300;
        
        // number of columns
        const size_t num_columns = 300;
        
        // number of potential connections (percentage of input space bits)
        const float potential_percent = 0.5f;

        // if permanence is >= then there is a connection
        const float connection_threshold = 0.1f;

        // if overlap score is >= then a column becomes active
        const size_t overlap_threshold = 40;


        const size_t seed = 0;
        std::default_random_engine generator(seed);

        std::uniform_int_distribution<size_t> uniform_distribution(0, input_space_size - 1);

        // normal distribution around the connectin_threshold
        std::normal_distribution<float> normal_distribution(connection_threshold, 0.5);

        class overlap;

        // 1D column
        class column
        {
        public:

            column()
             : num_potential_connections((size_t)(input_space_size * potential_percent))
             , num_connected_synapses(0)
            {
                potential_pool.reserve(num_potential_connections);
                permanences.reserve(num_potential_connections);
            }

            //
            // Select potential pool and assign permanences.
            //
            void init()
            {
                size_t counter = 0;

                // use a set to ensure that n unique potential connections are generates. 
                std::set<index_t> input_indices;

                while (input_indices.size() < num_potential_connections)
                {
                    input_indices.insert(uniform_distribution(generator));
                }

                // 
                for (const auto& i : input_indices)
                {
                    potential_pool.push_back(i);
                    
                    // keep [0, 1]
                    auto permanence = normal_distribution(generator);
                    permanence = (permanence >= 0.f) ? permanence : 0;
                    permanence = (permanence < 1.f) ? permanence : 1;

                    permanences.push_back(permanence);

                    // keep track of num of connections
                    if (permanence >= connection_threshold)
                    {
                        num_connected_synapses++;
                    }
                }


            }

            //
            // Find overlap score for an sdr.
            //
            void compute(overlap& o) const;


            ///////////////////////
            // stats
            
            size_t num_potential_connections;
            
            // number of actual connections
            size_t num_connected_synapses;


            ///////////////
            
            // potential pool of connections
            std::vector<index_t> potential_pool;
            std::vector<float> permanences;
        };

        typedef std::vector<column> columns_t;

        class overlap
        {
        public:
            
            overlap(const sdr_t& sdr, const column& col)
                : overlap_score(0)
                , sdr(sdr)
                , column(col)
            {}
            
            size_t overlap_score;

            const sdr_t& sdr;
            const column& column;
        };

        ////////////////////

        void column::compute(overlap& o) const
        {
            // Find overlap
            for (size_t i = 0; i < num_potential_connections; ++i)
            {
                if (permanences[i] > connection_threshold)
                {
                    auto bit = potential_pool[i];
                    if (o.sdr[bit] > 0)
                    {
                        o.overlap_score++;
                    }
                }
            }
        }

        ////////////////////




        void do_stats(const columns_t& columns)
        {
            size_t sum_synapses = 0;
            for (const auto& col : columns)
            {
                sum_synapses += col.num_connected_synapses;
            }

            cout << (size_t)(sum_synapses / columns.size()) << endl;
        }

        void run_test()
        {
            auto columns = columns_t(num_columns);
            std::for_each(columns.begin(), columns.end(), [](column& col) {col.init(); });

            std::uniform_int_distribution<size_t> dist(0, 1);
            sdr_t a(input_space_size, 0);
            std::generate(a.begin(), a.end(), [&dist]() {return dist(generator); });

            std::vector<overlap> overlaps;
            std::vector<column> active_columns;

            std::for_each(columns.begin(), columns.end(), [&a, &overlaps, &active_columns](const column& col)
            { 
                overlap o(a, col);
                col.compute(o); 

                overlaps.push_back(o);

                if (o.overlap_score >= overlap_threshold)
                {
                    active_columns.push_back(col);
                }
            });

        }
    }
}