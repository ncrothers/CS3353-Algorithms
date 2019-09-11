/*

Abstract Algorithm class

*/

#ifndef ALGORITHM_H
#define ALGORITHM_H

class Algorithm {
public:
	enum SortAlgos {
		BUBBLE = 0,
		INSERTION,
		MERGE,
		LAST
	};

    virtual void Load(const char[]) = 0;
    virtual void Execute() = 0;
    virtual void Display(SortAlgos, int) = 0;
    virtual void Save(SortAlgos, int) = 0;
};

#endif ALGORITHM_H