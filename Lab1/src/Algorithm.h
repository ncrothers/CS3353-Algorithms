/*

Abstract Algorithm class

*/

#ifndef ALGORITHM_H
#define ALGORITHM_H

class Algorithm {
public:
    virtual void Load(const char[]) = 0;
    virtual void Execute() = 0;
    virtual void Display(SortAlgos, int) = 0;
    virtual void Stats() = 0;
    virtual void Select() = 0;
    virtual void Save() = 0;
    virtual void Configure() = 0;

    enum SortAlgos{ BUBBLE = 0, 
                    INSERTION, 
                    MERGE, 
                    LAST };
};

#endif ALGORITHM_H