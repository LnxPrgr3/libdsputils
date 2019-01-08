#pragma once

#include "extern.h"
#include <stddef.h>

DSP_EXPORT void rectangular_noise(double *output, size_t size, double scale = 1);
DSP_EXPORT void rectangular_noisef(float *output, size_t size, float scale = 1);

#ifdef __cplusplus
namespace dsp {
	template <typename T>
	inline void rectangular_noise(T *, size_t, T = 1);

	template <>
	inline void rectangular_noise<double>(double *output, size_t size, double scale) {
		return ::rectangular_noise(output, size, scale);
	}

	template <>
	inline void rectangular_noise<float>(float *output, size_t size, float scale) {
		return ::rectangular_noisef(output, size, scale);
	}

	template <typename T, size_t N>
	inline void rectangular_noise(T(&output)[N], T scale = 1) {
		return rectangular_noise(output, N, scale);
	}
}
#endif