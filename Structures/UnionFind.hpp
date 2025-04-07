//talgov44@gmail.com
#ifndef UNION_FIND_H
#define UNION_FIND_H

namespace graph {

    class UnionFind {
    private:
        int* parent;
        int* rank;

    public:
        UnionFind(int size);
        ~UnionFind();
        int find(int x);
        void unionSets(int x, int y);
    };

}

#endif // UNION_FIND_H
