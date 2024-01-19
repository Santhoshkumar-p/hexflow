#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <hexagon_protos.h>
#include <hexagon_types.h>
#include "tensor.c"

// Example Hexagon DSP vector intrinsic operations
#define HEXAGON_VT_addu2(x, y) Q6_P_vaddu_VV(x, y)
#define HEXAGON_VT_subu2(x, y) Q6_P_vsubu_VV(x, y)
#define HEXAGON_VT_max2(x, y) Q6_P_vmax_VV(x, y)
#define HEXAGON_VT_cmplt2(x, y) Q6_P_vcmpgtu_VV(y, x)


//vector size based on Hexagon DSP architecture
#define VEC_LEN 128

int main() {
    size_t dimensions_A[] = {4, 4, 4, 4};
    size_t dimensions_B[] = {4, 4, 4, 4};
    Tensor A, B, result;

    init_tensor(&A, sizeof(dimensions_A) / sizeof(dimensions_A[0]), dimensions_A);
    init_tensor(&B, sizeof(dimensions_B) / sizeof(dimensions_B[0]), dimensions_B);

    // Initialize result tensor
    result.shape.num_dimensions = 4;
    result.shape.dimensions = dimensions_B;
    result.data = (uint8_t*)aligned_alloc(128, dimensions_B[0] * dimensions_B[1] * dimensions_B[2] * dimensions_B[3]);

    // Perform tensor multiplication using HVX
    tensor_multiply_hvx(&A, &B, &result);

    // Print tensors (for debugging)
    printf("Tensor A:\n");
    print_tensor(&A);

    printf("Tensor B:\n");
    print_tensor(&B);

    printf("Result:\n");
    print_tensor(&result);

    // Free tensor data
    free_buffer(&A -> data);
    free_buffer(&B -> data);
    free_buffer(&result -> data);

    return 0;
}

void tensor_multiply_hvx(const Tensor* A, const Tensor* B, Tensor* result) {
    // Assuming A, B, and result have dimensions (4, 4, 4, 4)
    // Modify the loop structure based on dynamic shapes

    for (size_t i = 0; i < A->shape.dimensions[0]; ++i) {
        for (size_t j = 0; j < B->shape.dimensions[1]; ++j) {
            for (size_t k = 0; k < A->shape.dimensions[1]; ++k) {
                // Load 128 bytes from A and B into HVX registers
                HVX_VectorPred allTrue = Q6_V_vsplat_R(0xFFFFFFFF);
                HVX_Vector* aPtr = (HVX_Vector*)(A->data + i * A->shape.dimensions[1] * 128 + k * 128);
                HVX_Vector* bPtr = (HVX_Vector*)(B->data + k * B->shape.dimensions[1] * 128 + j * 128);

                HVX_Vector* resultPtr = (HVX_Vector*)(result->data + i * B->shape.dimensions[1] * 128 + j * 128);

                // Perform HVX vector multiplication
                for (size_t l = 0; l < 4; ++l) {
                    HVX_Vector av = Q6_V_vldu_A(aPtr + l);
                    HVX_Vector bv = Q6_V_vldu_A(bPtr + l);
                    HVX_VectorProd resultVector = Q6_Wuw_vmpy_VuwVuwR_sat(av, bv, allTrue);
                    Q6_V_vstu_A(resultVector, resultPtr + l);
                }
            }
        }
    }
}


// Buffer operation: CONST
void constant_op(int val, void* output, int size) {
    int* out = (int*)output;
    for (int i = 0; i < size; ++i) {
        out[i] = val;
    }
}

// Binary operation: ADD
void add_op(const int* x, const int* y, int* output, int size) {
    for (int i = 0; i < size; ++i) {
        output[i] = HEXAGON_VT_addu2(x[i], y[i]);
    }
}

// Binary operation: SUB
void subtract_op(const int* x, const int* y, int* output, int size) {
    for (int i = 0; i < size; ++i) {
        output[i] = HEXAGON_VT_subu2(x[i], y[i]);
    }
}

// Binary operation: MAX
void max_op(const int* x, const int* y, int* output, int size) {
    for (int i = 0; i < size; ++i) {
        output[i] = HEXAGON_VT_max2(x[i], y[i]);
    }
}

// Binary operation: CMPLT
void cmplt_op(const int* x, const int* y, int* output, int size) {
    for (int i = 0; i < size; ++i) {
        output[i] = HEXAGON_VT_cmplt2(x[i], y[i]);
    }
}

// Function to perform element-wise EXP2 operation
void exp2_op(float* input, float* output, int size) {
    for (int i = 0; i < size; i += VEC_SIZE) {
        HVX_Vector vin = *(HVX_Vector*)(&input[i]);
        HVX_Vector vout = Q6_Vb_vsplat_R(Q6_R_vsplatb_R(vin), 0);
        *(HVX_Vector*)(&output[i]) = vout;
    }
}

// // Example usage
// int main() {
//     const int size = 8;
//     int x[size] = {1, 2, 3, 4, 5, 6, 7, 8};
//     int y[size] = {8, 7, 6, 5, 4, 3, 2, 1};
//     int output[size];

//     // Binary operation: ADD
//     add_op(x, y, output, size);

//     // Binary operation: SUB
//     subtract_op(x, y, output, size);

//     // Binary operation: MAX
//     max_op(x, y, output, size);

//     // Binary operation: CMPLT
//     cmplt_op(x, y, output, size);

//     return 0;
// }

