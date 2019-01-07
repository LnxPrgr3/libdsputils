#include "include/statistics.h"

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