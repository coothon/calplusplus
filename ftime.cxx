#include "ftime.hxx"

auto getTM() -> struct tm *{
	time_t t = time(NULL);
	struct tm *out = localtime(&t);
	return out;
}

auto getDay() -> int64_t {
	struct tm in = *getTM();
	int64_t tmp = in.tm_mday;
	return tmp - 1;
}

auto getMonth() -> int64_t {
	struct tm in = *getTM();
	int64_t tmp = in.tm_mon;
	return tmp;
}

auto getYear() -> int64_t {
	struct tm in = *getTM();
	int64_t tmp = in.tm_year + 1900;
	return tmp;
}

// true: in % ref == 0
// false: in % ref == 1

// false: in !% ref == 0
// true: in !% ref == 1

auto getYearIsLeap(int64_t inYear) -> int64_t {
	// PEAK BRAINPOWER
	return inYear % 4 ? false : inYear % 100 ? true : inYear % 400 ? false : true;
}