#include "include/noise.h"
#include <random>
#include <limits>

std::mt19937 r32_1, r32_2;
std::mt19937_64 r64_1, r64_2;

inline void seed_if_needed() {
	bool seeded = false;
	if (!seeded) {
		std::minstd_rand rng;
		r32_1.seed(rng());
		r32_2.seed(rng());
		r64_1.seed((uint64_t)rng() << 32 | rng());
		r64_2.seed((uint64_t)rng() << 32 | rng());
		seeded = true;
	}
}

// TODO: center around zero
template <typename T>
inline void rectangular_noise_impl(T *output, size_t size, T scale) {
	seed_if_needed();
	for (size_t i = 0; i < size; ++i) {
		output[i] = (T)2 * scale * ((T)r32_1() / (T)std::numeric_limits<uint32_t>::max() - (T)0.5);
	}
}

void rectangular_noise(double *output, size_t size, double scale) {
	return rectangular_noise_impl(output, size, scale);
}

void rectangular_noisef(float *output, size_t size, float scale) {
	return rectangular_noise_impl(output, size, scale);
}