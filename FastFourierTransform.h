#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "ComplexNumber.h"

void generate_factor_lookup(ComplexNumber* factors, unsigned int input_count, unsigned int factor_count)
{
    double input_count_factor = 1.0 / double(input_count);

    for(int i=0;i<factor_count;i++)
    {
        factors[i] = exp(ComplexNumber(0.0, -2.0 * M_PI * double(i) * input_count_factor));
    }
}

void discrete_fourier_transform(ComplexNumber* input, ComplexNumber* output, ComplexNumber* factors, unsigned int input_count)
{
    double input_count_factor = 1.0 / double(input_count);

    for(int i=0;i<input_count;i++)
    {
        for(int j=0;j<input_count;j++)
        {
            output[i] += input[j] * factors[i * j];
        }
    }
}

void recursive_fast_fourier_transform(ComplexNumber* input, ComplexNumber* output, ComplexNumber* factors, unsigned int input_count, unsigned int offset = 0, unsigned int step = 1)
{
    if(input_count == 1)
    {
        output[0] = input[offset];
    }
    else
    {
        unsigned int input_count_half = input_count >> 1;

        ComplexNumber* output_even = new ComplexNumber[input_count_half];
        ComplexNumber* output_odd  = new ComplexNumber[input_count_half];

        recursive_fast_fourier_transform(input, output_even, factors, input_count_half, offset,        2*step);
        recursive_fast_fourier_transform(input, output_odd , factors, input_count_half, offset + step, 2*step);

        for(int i=0;i<input_count_half;i++)
        {
            ComplexNumber odd_part = factors[i * step] * output_odd[i];

            output[i]                    = output_even[i] + odd_part;
            output[i + input_count_half] = output_even[i] - odd_part;
        }

        delete[] output_even;
        delete[] output_odd;
    }
}

unsigned int rev(unsigned int index, unsigned int bits)
{
    unsigned int new_index = 0;

    for(int i=0;i<bits+1;i++)
    {
        new_index += ((index >> i) & 1) << (bits - i);
    }

    return new_index;
}

void bit_reverse_copy(ComplexNumber* input, ComplexNumber* output, unsigned int input_count)
{
    unsigned int bits = std::log2(input_count) - 1;

    for(int i=0;i<input_count;i++)
    {
        output[rev(i, bits)] = input[i];
    }
}


void iterative_fast_fourier_transform(ComplexNumber* input, ComplexNumber* output, ComplexNumber* factors, unsigned int input_count)
{
    bit_reverse_copy(input, output, input_count);

    for(int i=1;i<std::log2(input_count)+1;i++)
    {
        unsigned int m = 1 << i;
        unsigned int factor_multiple = input_count / m;
        double inverse_m = 1.0 / double(m);
            
        unsigned int m_halves = m >> 1;

        for(int j=0;j<input_count;j+=m)
        {

            for(int k=0;k<m_halves;k++)
            {
                ComplexNumber odd_part = factors[k * factor_multiple] * output[j + k + m_halves];
                ComplexNumber even_part = output[j + k];

                output[j + k]            = even_part + odd_part;
                output[j + k + m_halves] = even_part - odd_part;
            }
        }
    }
}