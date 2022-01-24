#ifndef FTIME_H_
#define FTIME_H_

#include	<cstdint>
#include	<ctime>

auto getTM() -> struct tm *;
auto getDay() -> int64_t;
auto getMonth() -> int64_t;
auto getYear() -> int64_t;
auto getYearIsLeap(int64_t) -> int64_t;

#endif // FTIME_H_