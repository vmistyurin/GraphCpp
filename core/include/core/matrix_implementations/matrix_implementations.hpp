#pragma once

#include "core/matrix_implementations/symmetric_matrixes/symmetric_matrix_base.hpp"
#include "core/matrix_implementations/symmetric_matrixes/full_symmetric_matrix.hpp"
#include "core/matrix_implementations/symmetric_matrixes/half_symmetric_matrix.hpp"
#include "core/matrix_implementations/symmetric_matrixes/single_vector_symmetric_matrix.hpp"

#define MATRIX_IMPLEMENTATIONS_SEQ (graphcpp::FullSymmetricMatrix) (graphcpp::HalfSymmetricMatrix) (graphcpp::SingleVectorSymmetricMatrix)
