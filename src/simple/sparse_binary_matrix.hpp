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
            typedef std::set<index_t> container_t;

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

            /////////////////
            // Access
            
            // \brief Get access to the indices.
            const container_t& get_indices() const { return indices; }


            /////////////////
            // Non Modifying members

            size_t rows() const { return m_; }
            size_t columns() const { return n_; }

            bool empty() const { return indices.empty(); }

            size_t num_non_zero() const { return indices.size(); }

            // \brief Is a bit set for a given position
            bool contains(const index_t i, const index_t j) const 
            {
                return indices.find(convert_coord(i, j)) != indices.end();
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

            /////////////////
            // Modifying members

            // \brief Insert a on bit by coordinate.
            void insert(const size_t i, const size_t j)
            {
                if (i < m_ && j < n_)
                {
                    indices.insert(convert_coord(i, j));
                }
                else
                {
                    std::cout << "Out of bound." << std::endl;
                }
            }

            // \brief Insert a on bit by index.
            void insert(const size_t i)
            {
                indices.insert(i);
            }

            // \brief Clear matrix.
            void clear()
            {
                m_ = 0;
                n_ = 0;

                indices.clear();
            }

        protected:
            
            coord_t convert_index(index_t index) const 
            {
                return coord_t(index % m_, index / m_);
            }

            index_t convert_coord(const size_t i, const size_t j) const
            {
                return j * m_ + i;
            }

            index_t convert_coord(const coord_t& c) const
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
    }
}

