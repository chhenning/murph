#pragma once

#include <iterator>

#include "sparse_binary_matrix.hpp"

namespace murph
{
    namespace simple
    {
        /*
        * \brief A SDR class to perform SDR operations.
        *
        * \remarks It's inheritating from sparse_binary_matrix and essentially extending the matrix with some SDR operations.
        *   For now it's just a 1D vector.
        *
        */
        class sdr : public sparse_binary_matrix
        {

        public:

            sdr(size_t n)
                : sparse_binary_matrix(1, n)
            {}

            // \brief Create from 1D vector.
            sdr(std::initializer_list<size_t> list)
                : sparse_binary_matrix(1, list.size())
            {
                create(list);
            }

            // \brief Create a random sdr with a given sparsity in percentage.
            sdr(size_t n, double sparsity, int seed = 0)
                : sparse_binary_matrix(1, n)
            {
                create(sparsity, seed);
            }


            /////////////////
            // Non Modifying members


            // \brief Determine the overlap score.
            size_t overlap(const sdr& other) const
            {
                auto indices = get_indices();
                auto other_indices = other.get_indices();

                container_t result;
                auto bla = std::set_intersection(indices.begin(), indices.end(), other_indices.begin(), other_indices.end()
                    , std::inserter(result, result.begin()));

                return result.size();
            }

            // \brief Determines a match by checking if two sdr's overlap sufficiently.
            bool match(const sdr& other, size_t theta)
            {
                return overlap(other) >= theta;
            }


            /*
            * \brief Print to console in SDR style (0s and 1s).
            *
            * 00010001
            */
            void print(std::ostream& out)
            {
                for (size_t j = 0; j < columns(); j++)
                {
                    out << (contains(0, j)) ? 1 : 0;
                }

                out << std::endl;
            }


            /////////////////
            // Modifying members

            // \brief Create from 1D vector.
            void create(std::initializer_list<size_t> list)
            {
                int i = 0;
                for (const auto& e : list)
                {
                    if (e > 0)
                    {
                        insert(0, i);
                    }

                    ++i;
                }
            }

            // \brief Create a random sdr with a given sparsity in percentage.
            void create(double sparsity, int seed = 0)
            {
                if (sparsity > 0)
                {
                    size_t num_on_bits = static_cast<size_t>(columns() * sparsity);

                    if (num_on_bits > 0)
                    {
                        std::srand(seed);

                        for (size_t v = 0; v < num_on_bits; ++v)
                        {
                            insert(0, std::rand() % columns());
                        }
                    }
                }
            }

        private:
        };


        inline void sdr__test()
        {
            {
                // 
                sdr a(128);
                a.print(std::cout);
            }
 
            {
                // 
                sdr a{ 0,1,1 };
                sdr b{ 0,1,0 };
                
                std::cout << "Overlap score: " << a.overlap(b) << std::endl;
            }

            {
                // create random sdr with 2% sparsity
                sdr a(128, 0.02);
                sdr b(128, 0.02);

                std::cout << "Overlap score: " << a.overlap(b) << std::endl;
            }
        }
    }
}