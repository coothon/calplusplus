#ifndef FORMAT_HXX_
#define FORMAT_HXX_

#include	<stdexcept>
#include	<string>
#include	<vector>

#include "cal.hxx"
#include "ftime.hxx"

auto GetHeading(int64_t, int64_t) -> std::string;
auto GetHeading_m(int64_t) -> std::string;
auto GetHeading_y(int64_t) -> std::string;
auto GetDays() -> std::string;
auto DatePrediction(int64_t, int64_t, int64_t) -> int;
auto GetCalendar(int64_t, int64_t, int64_t) -> std::vector<std::string>;

const int DAYS_OF_WEEK = 7; // This won't change anytime soon

const std::string namedMonths[] = { "January",
									"February",
									"March",
									"April",
									"May",
									"June",
									"July",
									"August",
									"September",
									"October",
									"November",
									"December" };

const int64_t monthSizes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const std::string namedDays[] = { "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su" };

const std::string longNamedDays[] = { "Monday",
									  "Tuesday",
									  "Wednesday",
									  "Thursday",
									  "Friday",
									  "Saturday",
									  "Sunday" };

const std::string stringedNums[] = { " 1", " 2", " 3", " 4", " 5", " 6", " 7",
									 " 8", " 9", "10", "11", "12", "13", "14",
									 "15", "16", "17", "18", "19", "20", "21",
									 "22", "23", "24", "25", "26", "27", "28",
									 "29", "30", "31" };

#endif // FORMAT_HXX_