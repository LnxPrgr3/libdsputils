#include "include/statistics.h"
#include <cmath>

template <typename T>
inline T square(T x) {
	return x * x;
}

#define IMPL(func) \
	template <typename T> \
	inline T func ## _impl(const T *, size_t); \
	\
	double func(const double *data, size_t size) { \
		return func ## _impl(data, size); \
	} \
	\
	float func ## f(const float *data, size_t size) { \
		return func ## _impl(data, size); \
	} \
	\
	template <typename T> \
	inline T func ## _impl(const T *data, size_t size)

IMPL(mean) {
	T result = 0;
	for (size_t i = 0; i < size; ++i) {
		result += data[i];
	}
	return result / size;
}

IMPL(variance) {
	T average = dsp::mean(data, size);
	T result = 0;
	for (size_t i = 0; i < size; ++i) {
		result += square(data[i] - average);
	}
	return result / size;
}

IMPL(stddev) {
	return sqrt(dsp::variance(data, size));
}

IMPL(typical_error) {
	T dev = dsp::stddev(data, size);

	return dev / (pow((T)size, (T)0.5));
}