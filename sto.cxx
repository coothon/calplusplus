#include "sto.hxx"

// Delete singular file
auto DelFile(std::string const &fPath) -> void {
	fs::remove(fPath);
}

// Delete all files in given folder, including folder
auto DelAll(std::string const &fPath) -> void {
	if (fPath.compare(".") == 0) throw std::runtime_error("\n\nERROR: Please don't delete the directory of the file.\n");
	fs::remove_all(fPath);
	fs::create_directory(fPath);
}

// Empty log file and rewrite
auto TruncFile(std::string const &fPath, int64_t day, int64_t month, int64_t year, bool active) -> void {
	std::ofstream calFile(fPath, std::ios_base::trunc);

	calFile << day << '\n';
	calFile << month << '\n';
	calFile << year << '\n';
	calFile << (active ? "true" : "false");

	calFile.close();
}

// Get files in a given folder with a given extension
auto get_all(std::string const &root, std::string const &ext) -> std::vector<std::string> {
	std::vector<std::string> paths;
	if (!fs::exists(root)) fs::create_directory(root);
	if (fs::is_directory(root)) {
		for (auto const &entry : fs::recursive_directory_iterator(root)) {
			if (fs::is_regular_file(entry) && entry.path().extension() == ext) {
				paths.emplace_back(entry.path());
			}
		}
	}

	return paths;
}

// Return list of strings from given file
auto GetFile(std::string const &fPath) -> std::vector<std::string> {

	std::ifstream calFile(fPath, std::ios::in);


	std::string line;
	std::vector<std::string> out = std::vector<std::string>();

	while (std::getline(calFile, line)) out.push_back(line);

	calFile.close();
	return out;
}

// attempt std::stoi, return value passed by reference
auto IsNumber(std::string const &sussyNummy, int64_t *outNum) -> bool {

	try {
		*outNum = static_cast<int64_t>(std::stoi(sussyNummy));
		return true;
	} catch (const std::exception &e) {
		return false;
	}
}

// Hardcoded input parser, will most likely crash on unreliable inputs
auto ParseFile(std::vector<std::string> const &fileContents) -> dateData {
	int64_t _day = 0;
	int64_t _month = 0;
	int64_t _year = 0;
	bool _state = false;

	_state = IsNumber(fileContents[0], &_day);
	_state = IsNumber(fileContents[1], &_month);
	_state = IsNumber(fileContents[2], &_year);
	_state = _state && (fileContents[3].compare("true") == 0);

	return { _day, _month, _year, _state };
}

// Add data to Program, for readability
auto IntegrateFile(dateData const &data) -> void { globalProgress.push_back(data); }
