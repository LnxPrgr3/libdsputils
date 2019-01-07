#pragma once

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif

#ifdef _WINDOWS
#define DSP_EXPORT EXTERN_C __declspec( dllexport )
#else
#define DSP_EXPORT EXTERN_C __attribute__ ((visibility ("default")))
#endif