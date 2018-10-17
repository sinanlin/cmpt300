#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define PRIME_OFFSET 1000000000
#define PRIME_DITHER 100000

_Bool isPrime(long long number) {
	for (long long check = 2; check < number; check++) {
		if (number % check == 0) {
			return false;
		}
	}
	return true;
}

long long findPrime(int seed)
{
	srand(seed);
	long long dither = rand() % PRIME_DITHER;
	long long startAt = PRIME_OFFSET + dither * dither;
	printf("   #%d: starting to search from %lld.\n", seed, startAt);

	while (true) {
		if (isPrime(startAt)) {
			break;
		}
		startAt++;
	}
	return startAt;
}
