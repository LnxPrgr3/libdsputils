#include "include/statistics.h"

template <typename T>
T mean_impl(const T *data, size_t size) {
	T result = 0;
	for (size_t i = 0; i < size; ++i) {
		result += data[i];
	}
	return result / size;
}

double mean(const double *data, size_t size) {
	return mean_impl(data, size);
}

float meanf(const float *data, size_t size) {
	return mean_impl(data, size);
}