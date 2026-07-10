This may be faster than std::complex<long double> because it does not do some NaN checks that the standard library apparently does.

I put here the code I used to benchmark division, in which I'm slightly faster and it depends on the run. Note however that some accuracy is missed! Either in mine, theirs, or both. So for now this lies here, dormant.