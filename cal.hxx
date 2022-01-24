#ifndef CAL_HXX_
#define CAL_HXX_

#include	<cstdint>
#include	<vector>

typedef struct DateData {
	int64_t day;
	int64_t month;
	int64_t year;

	bool state;

	//std::vector<std::string> todo;

} dateData;



extern std::vector<dateData> globalProgress;



auto GetAllDayStates(int64_t, int64_t) -> std::vector<int64_t> ;

#endif // CAL_HXX_