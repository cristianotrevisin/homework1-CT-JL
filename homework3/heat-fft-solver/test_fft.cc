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

TEST(FFT, inverse_transform) {
// the most intuitive approach would be applying the fourier transform,
// and its inverse and check if the final result equals the initial one
// however, this test is only on the inverse fourier and should not fail
// because of the direct fourier, which is tested elsewhere. 

UInt N = 512;
Matrix<complex> m(N);
Real k = 2 * M_PI / N;
for (auto&& entry : index(m)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    if (i == 1 && j == 0)
      val = N * N / 2;
    else if (i == N - 1 && j == 0)
      val = N * N / 2;
    else
      val = 0;

    
  }

  Matrix<complex> res = FFT::itransform(m);

  for (auto&& entry : index(res)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val1 = std::get<2>(entry);
    
    ASSERT_NEAR(val1.real(), cos(k * i), 1e-5);
  }


}
/*****************************************************************/

TEST(FFT, computeFrequencies) {
  // We deem reasonable just testing one even and one odd case, as this
  // will help us highlight whether the procedure is working correctly
  // or not. Another approach would consist in using a python script to
  // generate frequencies through numpy.fft.fftfreqs, but has a similar
  // degree of complexity for the end user.

  // even N
  UInt N = 4; //we test it for not many frequencies
  
  // we create the vector with the wavenumbers 
  // generate through np.fft.fftfreqs, and multiplied by N
  std::vector<int> vf = { 0, 1, -2, -1 };

  // generating wavenumbers
  Matrix<std::complex<int>> res = FFT::computeFrequencies(N);

  // checking
  for (auto&& entry : index(res)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    
    EXPECT_EQ(val.real(), vf[i]);
    EXPECT_EQ(val.imag(), vf[j]);
  }

  // odd N

  UInt No = 5;
  
  // we create the vector with the wavenumbers 
  // generate through np.fft.fftfreqs, and multiplied by N
  std::vector<int> vfo = { 0, 1, 2, -2, -1 };

  Matrix<std::complex<int>> reso = FFT::computeFrequencies(No);

  for (auto&& entry : index(reso)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    
    EXPECT_EQ(val.real(), vfo[i]);
    EXPECT_EQ(val.imag(), vfo[j]);
  }
}
/*****************************************************************/