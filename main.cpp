#include <iostream>
#include <chrono>

#include "ComplexNumber.h"
#include "FastFourierTransform.h"

int main()
{
    unsigned int input_count = std::pow(2, 20);

    ComplexNumber* input = new ComplexNumber[input_count];

    for(int i=0;i<input_count;i++)
    {
        input[i] = ComplexNumber(std::sin(double(i) / double(0.125*input_count) * M_PI) + std::sin(double(i) / double(0.0033*input_count) * M_PI));
    }

    //-------------------Iterative FFT---------------------

    auto start_iterative_fft = std::chrono::high_resolution_clock::now();
    
    //Generate factors
    ComplexNumber* factors_iterative_fft = new ComplexNumber[input_count/2];
    generate_factor_lookup(factors_iterative_fft, input_count, input_count/2);
    
    auto end_factors_iterative_fft = std::chrono::high_resolution_clock::now();
    unsigned int elapsed_factors_iterative_fft = std::chrono::duration_cast<std::chrono::milliseconds>(end_factors_iterative_fft - start_iterative_fft).count();
    std::cout << "factors iterative FFT: \t" << elapsed_factors_iterative_fft << "ms" << std::endl;

    //Do iterative fft
    ComplexNumber* output_iterative_fft = new ComplexNumber[input_count];
    iterative_fast_fourier_transform(input, output_iterative_fft, factors_iterative_fft, input_count);
    auto end_iterative_fft = std::chrono::high_resolution_clock::now();

    //CleanUp
    delete[] factors_iterative_fft;

    unsigned int elapsed_iterative_fft = std::chrono::duration_cast<std::chrono::milliseconds>(end_iterative_fft - end_factors_iterative_fft).count();
    std::cout << "iterative FFT: \t" << elapsed_iterative_fft << "ms" << std::endl;


    //-------------------Recursive FFT------------------------

    auto start_recursive_fft = std::chrono::high_resolution_clock::now();
    
    //Generate factors
    ComplexNumber* factors_recursive_fft = new ComplexNumber[input_count/2];
    generate_factor_lookup(factors_recursive_fft, input_count, input_count/2);
    
    auto end_factors_recursive_fft = std::chrono::high_resolution_clock::now();
    unsigned int elapsed_factors_recursive_fft = std::chrono::duration_cast<std::chrono::milliseconds>(end_factors_recursive_fft - start_recursive_fft).count();
    std::cout << "factors recursive FFT: \t" << elapsed_factors_recursive_fft << "ms" << std::endl;

    //Do recursive fft
    ComplexNumber* output_recursive_fft = new ComplexNumber[input_count];
    recursive_fast_fourier_transform(input, output_recursive_fft, factors_recursive_fft, input_count);
    auto end_recursive_fft = std::chrono::high_resolution_clock::now();

    //CleanUp
    delete[] factors_recursive_fft;

    unsigned int elapsed_recursive_fft = std::chrono::duration_cast<std::chrono::milliseconds>(end_recursive_fft - end_factors_recursive_fft).count();
    std::cout << "recursive FFT: \t" << elapsed_recursive_fft << "ms" << std::endl;
    
    //------------------------DFT------------------------

    auto start_dft = std::chrono::high_resolution_clock::now();
        
    //Generate factors
    //ComplexNumber* factors_dft = new ComplexNumber[input_count * input_count];
    //generate_factor_lookup(factors_dft, input_count, input_count * input_count);

    auto end_factors_dft = std::chrono::high_resolution_clock::now();
    unsigned int elapsed_factors_dft = std::chrono::duration_cast<std::chrono::milliseconds>(end_factors_dft - start_dft).count();
    std::cout << "factors DFT: \t" << elapsed_factors_dft << "ms" << std::endl;
    
    //Do recursive dft
    ComplexNumber* output_dft = new ComplexNumber[input_count];
    //discrete_fourier_transform(input, output_dft, factors_dft, input_count);
    
    auto end_dft = std::chrono::high_resolution_clock::now();
    
    //CleanUp
    //delete[] factors_dft;

    unsigned int elapsed_dft = std::chrono::duration_cast<std::chrono::milliseconds>(end_dft - end_factors_dft).count();
    std::cout << "DFT: \t\t" << elapsed_dft << "ms" << std::endl;
    
    std::cout << "\tDFT:" << ",\t\trFFT" << ",\t\tiFFT" << std::endl;

    for(int i=0;i<input_count;i++)
    {
        if(output_recursive_fft[i].magnitude() / double(input_count) > 0.1)
            std::cout << i << ":\t" << output_dft[i].magnitude() / double(input_count) << ",\t" << output_recursive_fft[i].magnitude() / double(input_count) << ",\t" << output_iterative_fft[i].magnitude() / double(input_count) << std::endl;
    }

    delete[] input;
    delete[] output_dft;
    delete[] output_recursive_fft;
    delete[] output_iterative_fft;

    return 0;
}