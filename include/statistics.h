#pragma once

#include "extern.h"
#include <stddef.h>

DSP_EXPORT double mean(const double *data, size_t size);
DSP_EXPORT float meanf(const float *data, size_t size);
DSP_EXPORT double variance(const double *data, size_t size);
DSP_EXPORT float variancef(const float *data, size_t size);

#ifdef __cplusplus

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
}

#undef IMPL

#endif