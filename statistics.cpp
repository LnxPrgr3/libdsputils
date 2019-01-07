#include "include/statistics.h"
#include <cmath>

namespace dsp {
	template <typename T>
	struct range {
		T begin;
		T end;
	};
}

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

template <typename T>
inline dsp::range<T> find_range(const T *data, size_t size) {
	dsp::range<T> range = { 0, 0 };
	if (size > 0) {
		range.begin = range.end = data[0];
		for (size_t i = 1; i < size; ++i) {
			if (range.begin > data[i])
				range.begin = data[i];
			if (range.end < data[i])
				range.end = data[i];
		}
	}
	return range;
}

template <typename T>
inline void histogram_impl(size_t *output, size_t bins, const T *data, size_t size, dsp::range<T> range) {
	T step = (range.end - range.begin) / (bins - 1);
	for (size_t i = 0; i < bins; ++i) {
		output[i] = 0;
	}
	for (size_t i = 0; i < size; ++i) {
		const size_t bin = (size_t)round(step * (data[i] - range.begin));
		++output[bin];
	}
}

range histogram(size_t *output, size_t bins, const double *data, size_t size) {
	dsp::range<double> range = find_range(data, size);
	histogram_impl(output, bins, data, size, range);
	::range res = { range.begin, range.end };
	return res;
}

rangef histogramf(size_t *output, size_t bins, const float *data, size_t size) {
	dsp::range<float> range = find_range(data, size);
	histogram_impl(output, bins, data, size, range);
	::rangef res = { range.begin, range.end };
	return res;
}