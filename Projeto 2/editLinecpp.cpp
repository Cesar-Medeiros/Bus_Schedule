/*
case 2:
{

	for (int i = 0; i < busLine.stops.size(); i++) cout << i + 1 << "Time between " << busLine.stops[i] << " and " << busLine.stops[i + 1] << " --- " << busLine.duration[i] << endl;
	int stopC = inputFiltered(1, busLine.stops.size());
	stopC--;

	int tempDuration = inputFiltered(1, 10000);

	busLine.stops[stopC] = tempDuration;

	break;
}
case 3:
{
	cout << "Insert 0 if you want to exit" << endl << endl;
	vector <string> newStops;
	string tempStop;

	while (cin >> tempStop)
	{
		if (tempStop == "0") break;
		newStops.push_back(tempStop);
	}

	busLine.stops = newStops;
	break;
}
*/