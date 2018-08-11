#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

namespace murph
{
    namespace simple
    {
        /*
        * \brief A sparse vector storing indices representing ON bits.
        *
        * \remarks A std::set is used to keep the indices in order and unique.
        *
        */
        class sparse_binary_vector
        {
        public:
            sparse_binary_vector(std::uint32_t size)
                : size(size)
                , indices()
            {
                truncate();
            }
            
            sparse_binary_vector(std::uint32_t size, std::initializer_list<std::uint32_t> indices)
                : size(size)
                , indices(indices)
            {
                truncate();
            }

            // \brief AND Operation. Make a intersection of two indices sets.
            void AND(const sparse_binary_vector& other)
            {
                std::vector<std::uint32_t> dest;
                std::set_intersection(indices.begin(), indices.end()
                    , other.indices.begin(), other.indices.end()
                    , std::back_inserter(dest));

                indices.clear();
                indices = std::set<std::uint32_t>(dest.begin(), dest.end());

                truncate();
            }

            // \brief OR Operation. Adding all new indices.
            void OR(const sparse_binary_vector& other)
            {
                indices.insert(other.indices.begin(), other.indices.end());

                truncate();
            }

            // \brief Remove all indices that are out of bounds.
            // 
            // \remarks This function will be called for each function which is changing the indices.
            void truncate()
            {
                if (indices.size() > 0)
                {
                    // the last element is the max index for an on bit
                    auto max_index = *indices.rbegin();

                    if (max_index >= size)
                    {
                        std::cout << "Removing elements" << std::endl;
                        auto it = indices.upper_bound(size);

                        indices.erase(it, indices.end());

                        // cannot use remove_if since it's reordering the elements
                        for (auto it = indices.begin(), end = indices.end(); it != end;)
                        {
                            if (*it >= size)
                            {
                                it = indices.erase(it);
                            }
                            else
                            {
                                ++it;
                            }
                        }
                    }
                }
            }

            void print()
            {
                for (auto it = indices.begin(), end = indices.end(); it != end; ++it)
                {
                    std::cout << *it << " ";
                }

                std::cout << std::endl;
            }


        private:
            
            std::uint32_t size;
            std::set<std::uint32_t> indices;
        };


        inline void sparse_binary_vector__test()
        {
            {
                // create a vector with 12 bits where three are turned on.
                sparse_binary_vector a(12, {1,3,6});
                a.print();
            }

            {
                // create a vector with 12 bits where three are turned on.
                sparse_binary_vector a(12, {1,3,6,12});
                a.print();
            }
        }
    }
}
