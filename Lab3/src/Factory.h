#ifndef FACTORY_H
#define FACTORY_H

class TSP;

class Factory {
public:
	enum TSPAlgos {
		NAIVEBF = 0,
		DP,
		LAST
	};

	static TSP* Create(TSPAlgos algo);

};

#endif