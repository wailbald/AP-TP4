#include <math.h>
#include <stdio.h>
#include <stdint.h>

uint64_t rdtsc()
{
	int rdtsc;
	__asm__ volatile("rdtsc;\n" : "=A" (rdtsc));
	return rdtsc;
}

double pearson_correlation(uint64_t t, double *restrict x, double *restrict y)
{
	double s1 = 0.0;
	double s2 = 0.0;
	double s3 = 0.0;

	for(uint64_t i = 0; i < t; i++)
	{
		s1 += x[i]*y[i];
	}

	for(uint64_t i =0; i < t; i++)
	{
		s2 += x[i];
	}

	for(uint64_t i =0; i < t; i++)
	{
		s3 += y[i];
	}

	s2 *= s3;
	s1 -= s2;
}

int main()
{
	srand(getpid);

	for(int i = 0; i < 1000000; i*=2)
	{
		double *restrict x = aligned_alloc(64,i*sizeof(double));
		double *restrict y = aligned_alloc(64,i*sizeof(double));

		for(int j = 0; j < i; i++)
		{
			x[j] = (rand()%1000)/(rand()%100);
			y[j] = (rand()%1000)/(rand()%100);
		}

		uint64_t before = rdtsc();
			
		double result = pearson_correlation();

		uint64_t after = rdtsc();
	}

	printf("%lu\n",after - before);
}