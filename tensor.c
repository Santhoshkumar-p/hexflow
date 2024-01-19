#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>


// Types
typedef enum DType
{
    BOOL,
    FLOAT16,
    FLOAT32,
    FLOAT64,
    INT8,
    INT16,
    INT32,
    INT64,
    UINT8,
    UINT16,
    UINT32,
    UINT64 // BFLOAT
};

struct Shape
{
    size_t dims[];
};

typedef struct Tensor
{
    Shape shape;
    Buffer buffer;
    // void *data;
    DType dtype;
};

typedef struct Buffer
{
    size_t size; // Size of the buffer in bytes
    void *data;  // Pointer to the buffer data
    DType dtype; // Data type of the buffer
    // from_cpu, to_cpu
};

struct Allocator
{
    // Alloc
    // Free
    // Copy in
    // Copy out
};

typedef struct CType
{
    const *char type;
    size_t size;
}

// Initialization

Tensor
init_tensor(const Tensor *tensor)
{
    size_t total_elems = get_no_of_elems(tensor.shape);
    size_t elem_size = get_elem_size(tensor.dtype);
    size_t bytes = total_elems * elem_size;
    tensor->buffer = load_buffer(bytes);
    return tensor;
}

Buffer tensor_to_buffer(const Tensor *tensor)
{
    if (tensor->buffer->size > 0)
    {
        return tensor->buffer;
    }
    else
    {
        return NULL;
    }
}

// Tensor buffer_to_tensor(cosnt Buffer* buffer) {
// Tensor* tensor;
// tensor -> size = buffer -> size;
// tensor -> dtype = buffer -> dtype;
// tensor -> buffer = buffer;

// }

Buffer load_buffer(size_t size)
{
    Buffer *buffer;
    buffer->size = size;
    buffer->data = malloc(size);
    if (!buffer->data)
    {
        fprint("Buffer allocation failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        return NULL;
    }

    return buffer;
}

int free_buffer(Buffer *buffer)
{
    if (buffer)
    {
        free(buffer->data);
        return 0;
    }
    else
    {
        return 1;
    }
}

int free_tensor(Tensor *tensor)
{
    if (buffer)
    {
        free(tensor->buffer->data);
        return 0;
    }
    else
    {
        return 1;
    }
}

// Function to resize an existing buffer
int resize_buffer(Buffer *buffer, size_t new_size)
{
    buffer->data = realloc(buffer->data, new_size);
    if (!buffer->data)
    {
        fprint("Buffer reallocation failed");
        exit(EXIT_FAILURE);
        return 1;
    }
    buffer->size = new_size;
    return 0;
}

// Helper Functions
size_t get_elem_size(Dtype dtype)
{
    size_t elem_size = 0;
    switch (dtype)
    {
    case BOOL:
        elem_size = sizeof(_Bool);
        break;
    case FLOAT16:
        elem_size = sizeof(float) / 2;
        break;
    case FLOAT32:
        elem_size = sizeof(float);
        break;
    case FLOAT64:
        elem_size = sizeof(double);
        break;
    case INT8:
        elem_size = sizeof(int8_t);
        break;
    case INT16:
        elem_size = sizeof(int16_t);
        break;
    case INT32:
        elem_size = sizeof(int32_t);
        break;
    case INT64:
        elem_size = sizeof(int64_t);
        break;
    case UINT8:
        elem_size = sizeof(uint8_t);
        break;
    case UINT16:
        elem_size = sizeof(uint16_t);
        break;
    case UINT32:
        elem_size = sizeof(uint32_t);
        break;
    case UINT64:
        elem_size = sizeof(uint64_t);
        break;
    default:
        fprintf("Unsupported data type");
        break;
    }
    return elem_size;
}

size_t get_no_of_elems(Shape shape)
{
    size_t = 1;
    for (int i = 0; i < sizeof(shape.dims) / sizeof(size_t); i++)
    {
        size_t *= shape.dims[i];
    }
    return size_t;
}

void print_tensor(const Tensor *tensor)
{
    size_t total_size = 1;
    for (size_t i = 0; i < tensor->shape.dims; ++i)
    {
        total_size *= tensor->shape.dims[i];
    }

    size_t stride = 1;
    for (size_t i = tensor->shape.dims - 1; i > 0; --i)
    {
        stride *= tensor->shape.dims[i];
        for (size_t j = 0; j < total_size / stride; ++j)
        {
            for (size_t k = 0; k < stride; ++k)
            {
                printf("%u ", tensor->buffer->data[j * stride + k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    for (size_t i = 0; i < total_size / stride; ++i)
    {
        printf("%u ", tensor->buffer->data[i]);
    }
    printf("\n\n");
}
