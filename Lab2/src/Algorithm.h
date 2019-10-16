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

	enum SearchAlgos {
		BFS = SortAlgos::LAST,
		RECURBFS,
		DFS,
		RECURDFS,
		DIJKSTRA,
		ASTAR,
		END
	};

    virtual void Load(const char[]) = 0;
    virtual void Execute(SearchAlgos algo, int start, int dest) = 0;
	virtual void Select(int type) = 0;
    virtual void Display(SearchAlgos) = 0;
	virtual void Stats(SearchAlgos algo, int type) = 0;
    virtual void Save(SearchAlgos, int) = 0;
};

#endif ALGORITHM_H