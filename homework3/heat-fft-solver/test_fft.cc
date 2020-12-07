#include "fft.hh"
#include "my_types.hh"
#include <gtest/gtest.h>

/*****************************************************************/
TEST(FFT, transform) {
  UInt N = 512;
  Matrix<complex> m(N);

  Real k = 2 * M_PI / N;
  for (auto&& entry : index(m)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    val = cos(k * i);
  }

  Matrix<complex> res = FFT::transform(m);

  for (auto&& entry : index(res)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    if (std::abs(val) > 1e-10)
      std::cout << i << "," << j << " = " << val << std::endl;

    if (i == 1 && j == 0)
      ASSERT_NEAR(std::abs(val), N * N / 2, 1e-10);
    else if (i == N - 1 && j == 0)
      ASSERT_NEAR(std::abs(val), N * N / 2, 1e-10);
    else
      ASSERT_NEAR(std::abs(val), 0, 1e-10);
  }
}
/*****************************************************************/

TEST(FFT, inverse_transform) {}
/*****************************************************************/

TEST(FFT, computeFrequencies) {
  // even N
  UInt N = 4; //we test it for not many frequencies
  
  // we create the vector with the wavenumbers (results are from np.fft.fftfreqs, multiplied by N)
  std::vector<int> vf;
  vf.push_back(0);
  vf.push_back(1);
  vf.push_back(-2);
  vf.push_back(-1);

  Matrix<std::complex<int>> res = FFT::computeFrequencies(N);

  for (auto&& entry : index(res)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    
    ASSERT_NEAR(val.real(), vf[i], 1e-10);
    ASSERT_NEAR(val.imag(), vf[j], 1e-10);
  }

  // odd N

  UInt No = 5; //we test it for not many frequencies
  
  // we create the vector with the wavenumbers (results are from np.fft.fftfreqs, multiplied by N)
  std::vector<int> vfo;
  vfo.push_back(0);
  vfo.push_back(1);
  vfo.push_back(2);
  vfo.push_back(-2);
  vfo.push_back(-1);

  Matrix<std::complex<int>> reso = FFT::computeFrequencies(No);

  for (auto&& entry : index(reso)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    
    ASSERT_NEAR(val.real(), vfo[i], 1e-10);
    ASSERT_NEAR(val.imag(), vfo[j], 1e-10);
  }
}
/*****************************************************************/