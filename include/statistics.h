#pragma once

#include "extern.h"
#include <stddef.h>

struct range {
	double start;
	double end;
};

struct rangef {
	float start;
	float end;
};

DSP_EXPORT double mean(const double *data, size_t size);
DSP_EXPORT float meanf(const float *data, size_t size);
DSP_EXPORT double variance(const double *data, size_t size);
DSP_EXPORT float variancef(const float *data, size_t size);
DSP_EXPORT double stddev(const double *data, size_t size);
DSP_EXPORT float stddevf(const float *data, size_t size);
DSP_EXPORT double typical_error(const double *data, size_t size);
DSP_EXPORT float typical_errorf(const float *data, size_t size);
DSP_EXPORT range histogram(size_t *output, size_t bins, const double *data, size_t size);
DSP_EXPORT rangef histogramf(size_t *output, size_t bins, const float *data, size_t size);
DSP_EXPORT double gaussian(double mean, double stddev, double x);
DSP_EXPORT float gaussianf(float mean, float stddev, float x);

#ifdef __cplusplus

#include <functional>

#define IMPL(func) \
	template <typename T> \
	T func(const T *, size_t); \
	\
	template <> \
	inline double func<double>(const double *data, size_t size) { \
		return ::func(data, size); \
	} \
	\
	template <> \
	inline float func<float>(const float *data, size_t size) { \
		return ::func ## f(data, size); \
	} \
	\
	template <typename T, size_t N> \
	inline T func(const T(&data)[N]) { \
		return func(data, N); \
	}

namespace dsp {
	IMPL(mean);
	IMPL(variance);
	IMPL(stddev);
	IMPL(typical_error);

	inline ::range histogram(size_t *output, size_t bins, const double *data, size_t size) {
		return ::histogram(output, bins, data, size);
	}

	inline ::rangef histogramf(size_t *output, size_t bins, const float *data, size_t size) {
		return ::histogramf(output, bins, data, size);
	}

	template <typename T>
	inline T gaussian(T mean, T stddev, T x);

	template <>
	inline double gaussian<double>(double mean, double stddev, double x) {
		return ::gaussian(mean, stddev, x);
	}

	template <>
	inline float gaussian<float>(float mean, float stddev, float x) {
		return ::gaussianf(mean, stddev, x);
	}

	template <typename T>
	inline std::function<T(T)> gaussian(T mean, T stddev) {
		return [=](T x) { return gaussian(mean, stddev, x); };
	}
}

#undef IMPL

#endif