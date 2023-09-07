#ifndef ZENITH_MISC_H
#define ZENITH_MISC_H

#ifdef DEBUG
#define debug_print(fmt, args...) printf(fmt, ##args)

// TODO: maybe put flags here for various parts of the system?
#else
#define debug_print(fmt, args...)
#endif

#endif // ZENITH_MISC_H