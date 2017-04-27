#pragma once

#include <iostream>
#include <string>
#include <vector>



using namespace std;

class Line {
private:

	unsigned int id;
	unsigned int freq;
	vector<string> busStopList;
	vector<int> timesList;

public:
	Line() {};
	Line(string textLine);

	// metodos get
	
	unsigned int getId() const;
	unsigned int getFreq() const;
	vector<string> getBusStops() const;
	std::string getBusStop(unsigned int index) const;
	unsigned int getTiming(unsigned int index) const;
	vector<int> getTimings() const;

	// set methods

	void setId(unsigned int ID);
	void setFreq(unsigned int ID);
	void setBusStops(vector<string> busStops);
	void setTimings(vector<int> timings);

	void setBusStops(string busStop, unsigned int index);
	void setTimings(int time, unsigned int index);

	// other methods

};
