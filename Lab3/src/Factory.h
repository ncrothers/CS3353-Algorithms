#ifndef FACTORY_H
#define FACTORY_H

class Algorithm;

class Factory {
public:
	enum TSPAlgos {
		NAIVEBF = 0,
		DP,
		LAST
	};

	static Algorithm* Create(TSPAlgos algo);

};

#endif