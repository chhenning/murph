URL: https://bitbucket.org/blaze-lib/blaze

Good video: [CppCon 2016: Klaus Iglberger “The Blaze High Performance Math Library"](https://www.youtube.com/watch?v=w-Y22KrMgFE), [Slides](
https://github.com/CppCon/CppCon2016/blob/master/Tutorials/The%20Blaze%20High%20Performance%20Math%20Library/The%20Blaze%20High%20Performance%20Math%20Library%20-%20Klaus%20Iglberger%20-%20CppCon%202016.pdf)

* opensource, header-only, fast
* sparse matrix implementation: CompressedVector, CompressedMatrix
* vcpkg supported

# Installation

`vcpkg install blaze:x64-windows`

In cmake the just insert:
```
find_package(blaze CONFIG REQUIRED)
target_link_libraries(main PRIVATE blaze::blaze)
```

# First steps

```
#include <blaze/Math.h>
#include <blaze/math/CompressedMatrix.h>
#include <blaze/math/CompressedVector.h>

///////////
// create a sparse binary matrix (SDR)
typedef blaze::CompressedMatrix<bool, blaze::rowMajor> sparse_binary_matrix_t;
sparse_binary_matrix_t sdr{ {0,1,0}, {0,0,0}, {0,1,0} };

assert(sdr.nonZeros(0) == 1); // row 1 has one non-zero values

auto sdr_ = sdr.transpose();
assert(sdr_.nonZeros(1) == 2); // in a transposed matrix the second has 2 non-zero values

///////////
// create an SDR from a dense matrix
blaze::DynamicMatrix<float, blaze::rowMajor> dense{ {0.f, 1.f, 2.f},{0.f, 0.f, 5.f},{8.f, 7.f, 0.f} };
sparse_binary_matrix_t sdr2(dense);

assert(s2.nonZeros(2) == 2);

```

# Links

[Matrix Operations](https://bitbucket.org/blaze-lib/blaze/wiki/Matrix%20Operations)
