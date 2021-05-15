#pragma once

#include <vector>
#include <string>
struct board{
    board();
    ~board();
    board (const board &nowBoard);

    explicit board(const std::vector < std::vector <int> > &a);
    explicit board(const int &sizeB);

    unsigned int size() const;

    unsigned int hamming() const;
    unsigned int manhattan() const;

    bool is_goal() const;
    bool is_solvable() const;

    friend bool operator== (const board &first, const board &second);
    friend bool operator!= (const board &first, const board &second);
    friend bool operator> (const board &first, const board &second);
    friend bool operator< (const board &first, const board &second);

    std::string to_string() const;
    friend std::ostream &operator<< (std::ostream &out, const board &nowBoard);

    const std::vector<int> &operator[] (const int &nowInd) const;
    board &operator= (const board &nowBoard);

    //my
    const std::pair <int, int> &where_empty_cell() const;
    const std::vector < std::vector <int> > &now_board() const;
    const std::vector < std::vector <int> > &right_board() const;
private:
    std::vector < std::vector <int> > boardToSolve;
    std::vector < std::vector <int> > rightBoard;
    std::pair <int, int> emptyCell;
    unsigned int sizeBoard;
    void initRightBoard();
};
