#include "cal.hxx"

std::vector<dateData> globalProgress = std::vector<dateData>();

// Get flagged days in given month
auto GetAllDayStates(int64_t month, int64_t year) -> std::vector<int64_t> {
	
	std::vector<int64_t> out = std::vector<int64_t>();

	for (dateData const &date: globalProgress) {
		if (date.month != month) continue;
		if (date.year != year) continue;

		if (date.state) out.push_back(date.day);

	}

	return out;
}