#pragma once

#pragma once

#include <cassert>

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

namespace murph
{
    namespace simple
    {
        /*
        * \brief A sparse matrix storing indices representing ON bits.
        *
        * \remarks A std::set is used to keep the indices in order and unique. The 2D grid is stored using 1D indices which can be 
        *          converted to and from 2D coordinates.
        *
        */
        class sparse_binary_matrix
        {

        public:

            typedef size_t index_t;
            typedef std::pair<size_t, size_t> coord_t;

        public:
            sparse_binary_matrix(size_t m, size_t n)
                : m_(m)
                , n_(n)
                , indices()
            {}
            
            sparse_binary_matrix(const std::initializer_list<std::initializer_list<size_t>>& matrix)
                : indices()
            {
                m_ = matrix.size();
                n_ = max_column_size(matrix);

                size_t i = 0;
                for (const auto& row : matrix)
                {
                    for (size_t j = 0; j < row.size(); ++j)
                    {
                        auto value = *(row.begin() + j);

                        if (value > 0)
                        {
                            indices.insert(convert_coord(i, j));
                        }
                    }

                    ++i;
                }
            }

            bool empty() { return indices.empty(); }

            size_t num_non_zero() { return indices.size(); }

            bool contains(const index_t i, const index_t j)
            {
                return indices.find(convert_coord(i, j)) != indices.end();
            }

            void insert(const index_t i, const index_t j)
            {
                indices.insert(convert_coord(i, j));
            }


            void print()
            {
                for (auto it = indices.begin(), end = indices.end(); it != end; ++it)
                {
                    auto coord = convert_index(*it);

                    std::cout << coord.first << " " << coord.second << std::endl;
                }

                std::cout << std::endl;
            }

            /*
            * \brief Print to console in SDR style (0s and 1s).
            *
            * 00010001
            * 11010001
            * 00010111
            */
            void print_sdr()
            {
                for (size_t i = 0; i < m_; ++i)
                {
                    for (size_t j = 0; j < n_; ++j)
                    {
                        std::cout << contains(i, j);
                    }
                    
                    std::cout << std::endl;
                }
            }

        private:
            
            coord_t convert_index(index_t index)
            {
                return coord_t(index / m_, index % m_);
            }

            index_t convert_coord(const index_t i, const index_t j)
            {
                return j * m_ + i;
            }

            index_t convert_coord(const coord_t& c)
            {
                return convert_coord(c.first, c.second);
            }


            /*
            * \brief Get the max column width from initializer list.
            */
            size_t max_column_size(std::initializer_list<std::initializer_list<size_t>> matrix)
            {
                size_t width = 0;

                for (const auto& r : matrix)
                {
                    width = std::max(width, r.size());
                }

                return width;
            }


        private:
            
            size_t m_; //!< The number of rows.
            size_t n_; //!< The number of columns.
            
            // 1D indices
            std::set<index_t> indices;
        };


        inline void sparse_binary_matrix__test()
        {
            {
                // create a vector with 12 bits where three are turned on.
                sparse_binary_matrix a(12, 23);
                a.print();
            }

            {
                // empty matrix
                sparse_binary_matrix a {};
            }

            {
                // create a vector with 12 bits where three are turned on.
                sparse_binary_matrix a { {0,1,1}, {1,0} };
                a.print_sdr();
                assert(a.num_non_zero() == 3);
                assert(a.contains(0, 1));

                a.insert(0, 0);
                a.print_sdr();
            }
        }
    }
}

