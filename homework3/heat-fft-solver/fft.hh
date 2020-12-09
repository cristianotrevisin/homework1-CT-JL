#ifndef FFT_HH
#define FFT_HH
/* ------------------------------------------------------ */
#include "matrix.hh"
#include "my_types.hh"
#include <fftw3.h>
/* ------------------------------------------------------ */

struct FFT {

  static Matrix<complex> transform(Matrix<complex>& m);
  static Matrix<complex> itransform(Matrix<complex>& m);

  static Matrix<std::complex<int>> computeFrequencies(int size);
};

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::transform(Matrix<complex>& m_in) {

  //fftw_plan transform_plan fftw_plan_dft_2d(int n0, int n1, fftw_complex *in, fftw_complex *out, int sign, unsigned flags);
  Matrix<complex> m_out(m_in.size());

  fftw_plan transform_plan = fftw_plan_dft_2d(m_in.rows(), m_in.cols(), 
                                              reinterpret_cast<fftw_complex*>(m_in.data()), 
                                              reinterpret_cast<fftw_complex*>(m_out.data()), FFTW_FORWARD, FFTW_ESTIMATE);


  fftw_execute(transform_plan);

  fftw_destroy_plan(transform_plan);

  return m_out;

}

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::itransform(Matrix<complex>& m_in) {
  Matrix<complex> m_out(m_in.size());

  fftw_plan transform_plan = fftw_plan_dft_2d(m_in.rows(), m_in.cols(), 
                                              reinterpret_cast<fftw_complex*>(m_in.data()), 
                                              reinterpret_cast<fftw_complex*>(m_out.data()), FFTW_BACKWARD, FFTW_ESTIMATE);


  fftw_execute(transform_plan);

  /* FFTW ouput the unormalized transform */
  m_out /= (1.0*m_out.size()*m_out.size());



  fftw_destroy_plan(transform_plan);
  
  return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<std::complex<int>> FFT::computeFrequencies(int size) {

  std::vector<int> freq(size);

  if (size % 2 == 0){
    // if the size is even
    for (unsigned int i = 0; i < size/2; ++i){
      freq[i] = i;
    };
    for (unsigned int i = size/2; i < size; ++i){
      freq[i] = i - size;
    }
  } else {
    // if the size is odd
        for (unsigned int i = 0; i < (size-1)/2+1; ++i){
      freq[i] = i;
//      std::cout << freq[i]<< " ";
    };
    for (unsigned int i = (size-1)/2+1; i < size; ++i){
      freq[i] = i - size;
     // std::cout << freq[i]<< " ";
    }
    
  }
  //std::cout<<std::endl;

// writing on matrix

Matrix<std::complex<int>> freq_m(size);

  for (auto &&entry : index(freq_m)) {
        int indi = std::get<0>(entry);
        int indj = std::get<1>(entry);
        std::complex<int>& val1 = std::get<2>(entry);
        std::complex<int> val2;
        val2.imag(freq[indj]);
        val2.real(freq[indi]);

        val1 = val2;
    }

  return freq_m;
}

#endif  // FFT_HH
