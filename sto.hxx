#ifndef STO_HXX_
#define STO_HXX_

#include	<fstream>
#include	<unistd.h>
#include	<cstdint>
#include	<stdexcept>
#include	<string>
#include	<vector>
#include	<filesystem>

namespace fs = std::filesystem;

#include "cal.hxx"

auto DelFile(std::string const &) -> void;
auto DelAll(std::string const &) -> void;
auto TruncFile(std::string const &, int64_t, int64_t, int64_t, bool) -> void;
auto get_all(std::string const &, std::string const &) -> std::vector<std::string>;
auto GetFile(std::string const &) -> std::vector<std::string>;
auto IsNumber(std::string const &, int64_t *) -> bool;
auto ParseFile(std::vector<std::string> const &) -> dateData;
auto IntegrateFile(dateData const &) -> void;

#endif // STO_HXX_