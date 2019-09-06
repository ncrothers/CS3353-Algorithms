/*

Abstract Algorithm class

*/

#ifndef ALGORITHM_H
#define ALGORITHM_H

class Algorithm {
public:
    virtual void Load() = 0;
    virtual void Execute() = 0;
    virtual void Display() = 0;
    virtual void Stats() = 0;
    virtual void Select() = 0;
    virtual void Save() = 0;
    virtual void Configure();

    enum SortAlgos{ BUBBLE = 0, 
                    MERGE, 
                    INSERTION, 
                    LAST };

    

};

#endif ALGORITHM_H