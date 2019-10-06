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
		DFS,
		DIJKSTRA,
		ASTAR
	};

    virtual void Load(const char[]) = 0;
    virtual void Execute() = 0;
    virtual void Display(SearchAlgos, int) = 0;
    virtual void Save(SearchAlgos, int) = 0;
};

#endif ALGORITHM_H