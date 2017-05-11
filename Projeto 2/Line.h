#pragma once

#include <iostream>
#include <string>
#include <vector>




class Line {
private:

	unsigned int id;
	unsigned int freq;
	std::vector<std::string> busStopList;
	std::vector<int> timesList;

public:
	Line() {};
	Line(unsigned int id, unsigned int freq, std::vector< std::string> busStopList, std::vector<int> timesList);
	Line(std::string textLine);

	// metodos get
	
	unsigned int getId() const;
	unsigned int getFreq() const;
	std::vector<std::string> getBusStops() const;
	std::string getBusStop(unsigned int index) const;
	unsigned int getTiming(unsigned int index) const;
	std::vector<int> getTimings() const;

	// set methods

	void setId(unsigned int ID);
	void setFreq(unsigned int ID);
	void setBusStops(std::vector< std::string> busStops);
	void setTimings(std::vector<int> timings);

	void setBusStops(std::string busStop, unsigned int index);
	void setTimings(int time, unsigned int index);

	// other methods

	unsigned int timeLine();

};
