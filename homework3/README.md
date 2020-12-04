

## Test dynamic linking
````
otool -L test_fft
test_fft:
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1292.0.0)
	/usr/local/opt/fftw/lib/libfftw3.3.dylib (compatibility version 9.0.0, current version 9.8.0)
	/usr/local/opt/fftw/lib/libfftw3f.3.dylib (compatibility version 9.0.0, current version 9.8.0)
	/usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 904.4.0)
```