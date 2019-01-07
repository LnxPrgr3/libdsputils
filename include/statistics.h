#pragma once

#include "extern.h"
#include <stddef.h>

DSP_EXPORT double mean(const double *data, size_t size);
DSP_EXPORT float meanf(const float *data, size_t size);

#ifdef __cplusplus

namespace dsp {
	template <typename T>
	T mean(const T *, size_t);

	template <>
	inline double mean<double>(const double *data, size_t size) {
		return ::mean(data, size);
	}

	template <>
	inline float mean<float>(const float *data, size_t size) {
		return ::meanf(data, size);
	}

	template <typename T, size_t N>
	inline T mean(const T(&data)[N]) {
		return mean(data, N);
	}
}

#endif