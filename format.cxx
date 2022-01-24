#include "format.hxx"

// Centered month and year
auto GetHeading(int64_t month, int64_t year) -> std::string {
	
	if (month < 0 || month > 11) throw std::runtime_error("\n\nERROR: Month formatting index out of range (application bug).\n");

	// Get name of month and insert year after
	std::string out = namedMonths[month];
	
	out.append(" ");
	out.append(std::to_string(year));

	int padding = out.size();

	// Pad with whitespace to 20 char width
	for (int i = 0; i < (20 - padding)/2; ++i) {
		out.insert(0, " ");
		out.push_back(' ');
	}

	// If 20 - padding is an odd number, insert extra space in front.
	// Ensures 20 char width (unless the year is huge)
	if ((20 - padding) % 2 != 0) out.insert(0, " ");
	
	out.insert(0, "\033[3;4m");
	out.append("\033[0m");

	return out;
}

auto GetHeading_m(int64_t month) -> std::string {
	
	if (month < 0 || month > 11) throw std::runtime_error("\n\nERROR: Month formatting index out of range (application bug).\n");

	// Get name of month and insert year after
	std::string out = namedMonths[month];

	int padding = out.size();

	// Pad with whitespace to 20 char width
	for (int i = 0; i < (20 - padding)/2; ++i) {
		out.insert(0, " ");
		out.push_back(' ');
	}

	// If 20 - padding is an odd number, insert extra space in front.
	// Ensures 20 char width (unless the year is huge)
	if ((20 - padding) % 2 != 0) out.insert(0, " ");
	
	out.insert(0, "\033[3;4m");
	out.append("\033[0m");

	return out;
}

auto GetHeading_y(int64_t year) -> std::string {

	std::string out = std::to_string(year);

	int padding = out.size();

	// Pad with whitespace to 20 char width
	for (int i = 0; i < (20 - padding)/2; ++i) {
		out.insert(0, " ");
		out.push_back(' ');
	}

	// If 20 - padding is an odd number, insert extra space in front.
	// Ensures 20 char width (unless the year is huge)
	if ((20 - padding) % 2 != 0) out.insert(0, " ");
	
	out.insert(0, "\033[3;7m");
	out.append("\033[0m");

	return out;
}

// Print Mo - Su text
auto GetDays() -> std::string {

	std::string out = "\033[1;31m";
	
	// Sequentially append Days of the week and whitespaces
	for (int i = 0; i < DAYS_OF_WEEK; ++i) {
		out.append(namedDays[i]);
		out.append(" ");
	}

	// Remove last whitespace, excluding null char '\0'
	out.erase(out.end() - 1);
	out.append("\033[0m");
	
	return out;
}

// Returns the weekday of the given date, used for the first day of the month
auto DatePrediction(int64_t day, int64_t month, int64_t year) -> int {
	if (month == 1) {
		month = 13;
		year--;
	}
	if (month == 2) {
		month = 14;
		year--;
	}

	int64_t q = day;
	int64_t m = month;
	int64_t k = year % 100;
	int64_t j = year / 100;

	int64_t h = q + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j;

	h = h % 7;
	switch (h) {
		case 0:
			return 5; // Saturday
		case 1:
			return 6; // Sunday
		case 2:
			return 0; // Monday
		case 3:
			return 1; // Tuesday
		case 4:
			return 2; // Wednesday
		case 5:
			return 3; // Thursday
		case 6:
			return 4; // Friday
		default:
			throw std::runtime_error("\n\nERROR: date prediction algorithm failed.\n");
	}
}

// Print the 1 - 31 numbers
auto GetCalendar(int64_t day, int64_t month, int64_t year) -> std::vector<std::string> {

	if (month < 0 || month > 11) throw std::runtime_error("\n\nERROR: Month formatting index out of range (application bug).\n");

	int64_t monthSize = monthSizes[month];
	if (getYearIsLeap(year)) monthSize += month == 1 ? 1 : 0;
	
	if (day < -1 || day > monthSize - 1) throw std::runtime_error("\n\nERROR: Day formatting index out of range (application bug).\n");


	std::vector<std::string> tmp = std::vector<std::string>();

	int64_t firstDay = DatePrediction(1, month + 1, year);

	std::string firstCol = "";

	std::vector<int64_t> checkState = GetAllDayStates(month, year);

	int64_t dayCounter = 0;
	for (int i = 0; i < DAYS_OF_WEEK; ++i) {
		if (i >= firstDay) {
			for (int64_t const &checkedDay: checkState) {
				if (checkedDay == dayCounter) {
					firstCol.append("\033[9;3m");
				}
			}
			if (dayCounter == day) firstCol.append("\033[1;7m");
			firstCol.append(stringedNums[dayCounter++]);
			firstCol.append("\033[0m");
		} else {
			firstCol.append("  ");
		}
		firstCol.append(" ");
	}
	firstCol.erase(firstCol.end() - 1);
	tmp.push_back(firstCol);

	for (int i = 0; i < 5; ++i) {
		if (dayCounter >= monthSize) break;
		std::string currCol = "";
		for (int j = 0; j < DAYS_OF_WEEK; ++j) {
			for (int64_t const &checkedDay: checkState) {
				if (checkedDay == dayCounter) {
					currCol.append("\033[9;3m");
				}
			}
			if (dayCounter == day) currCol.append("\033[1;7m");
			if (dayCounter >= monthSize) {
				currCol.append("  ");
			} else {
				currCol.append(stringedNums[dayCounter++]);
			}
			currCol.append("\033[0m");
			currCol.append(" ");
		}
		currCol.erase(currCol.end() - 1);
		tmp.push_back(currCol);
	}

	return tmp;
}