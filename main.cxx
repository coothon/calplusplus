#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdint>
#include	<stdexcept>
#include	<string>
#include	<vector>
#include	<filesystem>

namespace fs = std::filesystem;

#include "format.hxx"
#include "cal.hxx"
#include "ftime.hxx"
#include "sto.hxx"

static const std::string YEAR_FORMAT_DELIM = "\t";
static const std::string YEAR_FORMAT_BLANK = "                    ";

// CACHE FILE FORMAT:
//
// <day>   < |
// <month> < easier to do it this way, may aswell hardcode some more
// <year>  < |
// <state> < redundant, serves no purpose, but easier to leave it in

// Date assumed false unless otherwise in file, if there is a file

auto PrintOne(int64_t day, int64_t month, int64_t year) -> void {
	std::cout << std::endl;
	std::cout << GetHeading(month, year) << '\n';
	std::cout << GetDays() << '\n';
	for (std::string const &str: GetCalendar(day, month, year)) {
		std::cout << str << '\n';
	}
	std::cout << std::endl;
}

auto PrintYear(int64_t day, int64_t month, int64_t year) -> void {

	std::cout << '\n' << YEAR_FORMAT_BLANK << YEAR_FORMAT_DELIM << GetHeading_y(year) <<YEAR_FORMAT_DELIM << YEAR_FORMAT_BLANK << '\n';

	std::cout << std::endl;
	for (int i = 0; i < 12; i += 3) {
		int64_t _day = -1;
		
		std::cout << GetHeading_m(i) << YEAR_FORMAT_DELIM;
		std::cout << GetHeading_m(i + 1) << YEAR_FORMAT_DELIM;
		std::cout << GetHeading_m(i + 2) << '\n';

		std::cout << GetDays() << YEAR_FORMAT_DELIM;
		std::cout << GetDays() << YEAR_FORMAT_DELIM;
		std::cout << GetDays() << '\n';

		std::vector<std::string> m0 = GetCalendar(i == month ? day : _day, i, year);
		std::vector<std::string> m1 = GetCalendar(i + 1 == month ? day : _day, i + 1, year);
		std::vector<std::string> m2 = GetCalendar(i + 2 == month ? day : _day, i + 2, year);

		for (size_t j = 0; j < 6; ++j) std::cout << (j >= m0.size() ? YEAR_FORMAT_BLANK : m0[j]) << YEAR_FORMAT_DELIM << (j >= m1.size() ? YEAR_FORMAT_BLANK : m1[j]) << YEAR_FORMAT_DELIM << (j >= m2.size() ? YEAR_FORMAT_BLANK : m2[j]) << '\n';

		m0.clear();
		m1.clear();
		m2.clear();
	}
	std::cout << std::endl;
}

auto main(int argc, char **argv) -> int {

	// Force correct usage with no help page
	if (argc > 2 && argc < 4) throw std::runtime_error("\n\nERROR: Not enough arguments provided.\n");
	if (argc > 5) throw std::runtime_error("\n\nERROR: More than four arguments provided.\n");

	// Default the date to current date
	int64_t day = getDay();
	int64_t month = getMonth();
	int64_t year = getYear();

	// Can you tell i like throwing errors yet?
	if (argc >= 4) {
		try {
			int64_t _year = static_cast<int64_t>(std::stoi(argv[3]));

			int64_t _month = static_cast<int64_t>(std::stoi(argv[2]));
			if (_month < 1 || _month > 12) throw std::runtime_error("\n\nERROR: Month provided out of range (must be 1 - 12).\n");
			
			int64_t _day = static_cast<int64_t>(std::stoi(argv[1]));
			if (_day < 1 || _day > monthSizes[_month - 1]) throw std::runtime_error("\n\nERROR: Day provided out of range (must be 1 - <month limit>).\n");

			day = _day - 1;
			month = _month - 1;
			year = _year;

		} catch(const std::exception &e) {
			throw std::runtime_error(e.what());
		}
	}

	// Process additional commands
	if (argc == 5) {
		std::string tmp(argv[4]);
		if (tmp.compare("+") == 0) {
			TruncFile(std::string("./data/").append(std::string(std::to_string(day)+"-"+std::to_string(month)+"-"+std::to_string(year)).append(".log")), day, month, year, true);
		} else if(tmp.compare("-") == 0) {
			DelFile(std::string("./data/").append(std::string(std::to_string(day)+"-"+std::to_string(month)+"-"+std::to_string(year)).append(".log")));
		} else if (tmp.compare("-y") == 0 || tmp.compare("year") == 0){
			for (std::string const &file: get_all("./data", ".log")) {
				IntegrateFile(ParseFile(GetFile(file)));
			}
			PrintYear(day, month, year);
			return EXIT_SUCCESS;
		}
	}

	if (argc == 2) {
		std::string tmp(argv[1]);
		if (tmp.compare("+") == 0) {
			TruncFile(std::string("./data/").append(std::string(std::to_string(day)+"-"+std::to_string(month)+"-"+std::to_string(year)).append(".log")), day, month, year, true);
		} else if(tmp.compare("-") == 0) {
			DelFile(std::string("./data/").append(std::string(std::to_string(day)+"-"+std::to_string(month)+"-"+std::to_string(year)).append(".log")));
		} else if (tmp.compare("clear") == 0) {
			DelAll("./data/");
		} else if (tmp.compare("-h") == 0 || tmp.compare("help") == 0) {
			std::cout << "USAGE: cal++ <options>\n";
			std::cout << "\t\tOR\n";
			std::cout << "USAGE: cal++ < dd > < mm > < yyyy > < +/- >\n";
			std::cout << "\v options: < -h/help > < -y/year > < +/- > < clear >\n";
			return EXIT_SUCCESS;
		} else if (tmp.compare("-y") == 0 || tmp.compare("year") == 0){
			for (std::string const &file: get_all("./data", ".log")) {
				IntegrateFile(ParseFile(GetFile(file)));
			}
			PrintYear(day, month, year);
			return EXIT_SUCCESS;
		}

	}

	// Get files './data/*.log' and pass data to the globalProgress
	for (std::string const &file: get_all("./data", ".log")) {
		IntegrateFile(ParseFile(GetFile(file)));
	}

	// The actual calendar
	PrintOne(day, month, year);

	return EXIT_SUCCESS;
}
