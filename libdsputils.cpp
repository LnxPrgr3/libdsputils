#ifdef _WINDOWS
#undef EXPORT
#define EXPORT extern "C" __declspec( dllexport )
#else
#define EXPORT extern "C" __attribute__ ((visibility ("default")))
#endif
