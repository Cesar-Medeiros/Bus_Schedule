#include "Header.h"

void linesWithStop(std::vector<Line> lines)
{
	Line line;
	int lineCode;
	string desiredStop;

	cout << "What's the stop you with to check? " << endl;

	cin.clear();
	cin.ignore(256, '\n');
	getline(cin, desiredStop);

	bool anyLine = false;

	for (size_t i = 0; i < lines.size(); i++)
	{
		line = lines.at(i);
		for (int j = 0; j < line.getBusStops().size(); j++)
		{
			if (line.getBusStop(j) == desiredStop)
			{
				anyLine = true;
				cout << "The stop exists at line " << lines.at(i).getId() << endl;
			}
		}
	}
	if (anyLine == false) cout << "The stop doesn't exist on any line" << endl;
}