#pragma once
#include "board.h"
#include <unordered_map>
struct solver{
    explicit solver(board &nowBoard);
    solver(solver &nowSolver);

    unsigned int moves() const;

    solver &operator= (const solver &nowSolver);

    struct iterator{
        iterator (const std::vector <board>::iterator &it, const int &sizeVecBoard, const int &num);
        iterator (const iterator &nowIt);
        iterator();
        ~iterator();
        board operator*();

        iterator &operator++();
        iterator &operator=(const iterator &nowIt);

        bool operator==(const iterator &nowIt);
        bool operator!=(const iterator &nowIt);
    private:
        unsigned int sizeIt;
        unsigned int indIt;
        std::vector <board>::iterator itBegin;
    };
    iterator begin();
    iterator end();

private:
    std::vector <board> ansBoards;
    board firstBoard;
    board lastBoard;

    void solve();

    struct hashBoard{
        int operator() (const board &nowBoard) const;
    };
    struct equalBoard{
        int operator() (const board &first, const board &second) const;
    };
    struct cmp{
        bool operator() (const std::pair <int, board> &first, const std::pair <int, board> &second)const;
    };
};
