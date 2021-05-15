#include "solver.h"
#include <unordered_set>
#include <queue>
#include <algorithm>

solver::solver(board &nowBoard): firstBoard (nowBoard){
    lastBoard=board(firstBoard.right_board());
    solve();
};
solver::solver(solver &nowSolver)=default;

unsigned int solver::moves() const{
    return (ansBoards.size()!=0) ? ansBoards.size()-1 : 0;
};

solver::iterator solver::begin(){
    iterator beginIt(ansBoards.begin(), ansBoards.size(), 0);
    return beginIt;
};
solver::iterator solver::end(){
    iterator endIt(ansBoards.begin(), ansBoards.size(), ansBoards.size());
    return endIt;
};

solver &solver::operator= (const solver &nowSolver)=default;

solver::iterator::iterator (const std::vector <board>::iterator &it, const int &sizeVecBoard, const int &num): itBegin(it), sizeIt(sizeVecBoard), indIt(num){};
solver::iterator::iterator (const iterator &nowIt)=default;
solver::iterator::iterator()=default;
solver::iterator::~iterator()=default;

board solver::iterator::operator*(){
    return *(itBegin + indIt);

};

solver::iterator &solver::iterator::operator++(){
    indIt++;
    return *this;
};

solver::iterator &solver::iterator::operator=(const solver::iterator &nowIt){
    itBegin=nowIt.itBegin;
    indIt=nowIt.indIt;
    sizeIt=nowIt.sizeIt;
};

bool solver::iterator::operator==(const solver::iterator &nowIt){
    auto first=itBegin+indIt;
    auto second=nowIt.itBegin+nowIt.indIt;
    return first==second;
};
bool solver::iterator::operator!=(const solver::iterator &nowIt){
    auto first=itBegin+indIt;
    auto second=nowIt.itBegin+nowIt.indIt;
    return first!=second;
};

void solver::solve(){
    if (firstBoard.is_solvable()==false) return;
    std::unordered_set <board, hashBoard> wasBoards;
    std::unordered_map <board, int, hashBoard, equalBoard> sumHamMan;
    std::unordered_map <board, board, hashBoard, equalBoard> parentBoard;
    sumHamMan[firstBoard]=0;
    std::priority_queue <std::pair <int, board>, std::vector<std::pair<int, board>>, cmp> q;
    q.push({0, firstBoard});
    std::pair<int, board> nowBoard;
    std::pair <int, int> emptyCell, nowGoTo;;
    std::vector <std::pair <int, int> > goTo = {{0,1}, {1, 0}, {0, -1}, {-1, 0}};
    while (!q.empty()){
        nowBoard=q.top(); q.pop();
        if (!nowBoard.second.is_goal()){
            wasBoards.insert(nowBoard.second);
            emptyCell=nowBoard.second.where_empty_cell();
            for (int i=0; i<4; i++){
                nowGoTo=goTo[i];
                int column=emptyCell.second+nowGoTo.second;
                int row=emptyCell.first+nowGoTo.first;
                if (row<nowBoard.second.size() && column<nowBoard.second.size() && row>-1 && column>-1){
                    board newBoard;
                    std::vector <std::vector <int> > newVec = nowBoard.second.now_board();
                    std::swap(newVec[emptyCell.first][emptyCell.second], newVec[row][column]);
                    newBoard=board(newVec);
                    int newHamMan=newBoard.hamming()+newBoard.manhattan();
                    if (!wasBoards.count(newBoard)){
                        sumHamMan[newBoard]=newHamMan;
                        q.push({newHamMan, newBoard});
                        parentBoard[newBoard]=nowBoard.second;
                    }
                    if (sumHamMan[newBoard] > newHamMan){
                        sumHamMan[newBoard]=newHamMan;
                        q.push({newHamMan, newBoard});
                        parentBoard[newBoard]=nowBoard.second;
                    }
                }
            }
        } else{
            board now=lastBoard;
            while (now!=firstBoard){
                ansBoards.push_back(now);
                now=parentBoard[now];
            }
            ansBoards.push_back(now);
            reverse(ansBoards.begin(), ansBoards.end());
            return;
        }
    }


};

int solver::hashBoard::operator()(const board &nowBoard) const{
    int ans=0;
    for (int i=0; i<nowBoard.size(); i++){
        for (int j=0; j<nowBoard.size(); j++){
            ans+=i*j*nowBoard[i][j];
        }
    }
    return ans;
};
int solver::equalBoard::operator() (const board &first, const board &second) const{
    return first==second;
};

bool solver::cmp::operator() (const std::pair <int, board> &first, const std::pair <int, board> &second)const{
    return first.first > second.first;
};
