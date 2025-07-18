#ifdef BUILD_DLL
# define API __attribute__((visibility("default")))
#else
# define API 
#endif