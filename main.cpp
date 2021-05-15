#include <iostream>
#include "solver.h"
#include <vector>
#include <random>

using namespace std;
vector<vector<vector<int>>> vecBoard = {{{1, 2, 3},
                                         {5, 6, 0},
                                         {4, 7, 8}},

                                        {{1, 2, 3, 4},
                                         {5, 6, 7, 8},
                                         {9, 10, 11, 0},
                                         {13, 14, 15, 12}},

                                        {{1, 2, 3, 4},
                                         {5, 6, 7, 8},
                                         {9, 10, 11, 12},
                                         {13, 14, 15, 0}},

                                        {{1, 0, 2, 3},
                                         {5, 6, 7, 4},
                                         {9, 10, 11, 8},
                                         {13, 14, 15, 12}},

                                        {{1, 0, 2, 3},
                                         {6, 5, 7, 4},
                                         {9, 10, 11, 8},
                                         {13, 14, 15, 12}},

                                        {{1, 2, 3, 4, 5, 6, 7, 8},
                                         {9, 10, 11, 12, 13, 14, 15, 16},
                                         {17, 18, 19, 20, 21, 22, 23, 24},
                                         {25, 26, 27, 28, 29, 30, 31, 32},
                                         {33, 34, 35, 36, 37, 38, 39, 40},
                                         {41, 42, 43, 44, 45, 46, 0, 48},
                                         {49, 50, 51, 52, 53, 54, 47, 56},
                                         {57, 58, 59, 60, 61, 62, 55, 63}}};

void testMyBoards(){
    for (int i=0; i<vecBoard.size(); i++){
        std::cout<<i<<" test:"<<std::endl;
        board nowBoard(vecBoard[i]);
        std::cout<<nowBoard.to_string();
        std::cout<<"Solution: "<<std::endl;
        if (!nowBoard.is_solvable()){
            std::cout<<"Don't solve"<<std::endl;
        } else{
            solver nowSolver(nowBoard);
            std::cout<<"Solve in "<<nowSolver.moves()<<" moves:"<<std::endl;
            for (const auto &j : nowSolver) {
                cout << j.to_string() << endl;
            }
        }
        std::cout<<"=================================="<<std::endl;
    }
}

void randBoards(){
    std::cout<<"Random test:"<<std::endl;
    board nowBoard(4);
    std::cout<<nowBoard.to_string();
    std::cout<<"Solution: "<<std::endl;
    if (!nowBoard.is_solvable()){
        std::cout<<"Don't solve"<<std::endl;
    } else{
        solver nowSolver(nowBoard);
        std::cout<<"Solve in "<<nowSolver.moves()<<" moves:"<<std::endl;
        for (const auto &j : nowSolver) {
            cout << j.to_string() << endl;
        }
    }
}
int main() {
    testMyBoards();
    randBoards();
}
