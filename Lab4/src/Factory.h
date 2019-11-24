#ifndef FACTORY_H
#define FACTORY_H

class TSP;

class Factory {
public:
	enum class TSPAlgos {
		GENETIC = 0,
		TABU,
		LAST
	};

	static TSP* Create(TSPAlgos algo);

};

#endif