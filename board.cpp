#include "board.h"

#include <algorithm>

board::board()=default;
board::~board(){
    boardToSolve.clear();
    rightBoard.clear();
};

board::board (const board &nowBoard)=default;

board::board(const std::vector < std::vector <int> > &a): boardToSolve(a){
    sizeBoard=boardToSolve.size();
    initRightBoard();
    for (int i=0; i<sizeBoard; i++)
        for (int j=0; j<sizeBoard; j++)
            if (boardToSolve[i][j]==0){
                emptyCell={i, j};
            }
};

board::board(const int &sizeB): sizeBoard(sizeB){
    boardToSolve.resize(sizeBoard, std::vector <int> (sizeBoard));
    std::vector <int> randomNum(sizeBoard*sizeBoard);
    for (int i=0; i<sizeBoard*sizeBoard; i++){
        randomNum[i]=i;
    }
    std::shuffle (randomNum.begin(), randomNum.end(), std::mt19937(std::random_device()()));
    for (int i=0; i<sizeBoard*sizeBoard; i++){
        boardToSolve[i/sizeBoard][i%sizeBoard] = randomNum[i];
        if (randomNum[i]==0)
            emptyCell={i/sizeBoard, i%sizeBoard};
    }
    initRightBoard();
};

unsigned int board::size() const{
    return sizeBoard;
};

unsigned int board::hamming() const{
    int ans=0;
    for (int i=0; i<sizeBoard*sizeBoard-1; i++){
        if (boardToSolve[i/sizeBoard][i%sizeBoard]!=i+1) ans++;
    }
    if (boardToSolve[sizeBoard-1][sizeBoard-1]!=0) ans++;
    return ans;
};

unsigned int board::manhattan() const{
    int ans=0;
    for (int i=0; i<sizeBoard; i++){
        for (int j=0; j<sizeBoard; j++){
            if (boardToSolve[i][j]!=rightBoard[i][j]){
                int column, row;
                if (boardToSolve[i][j]==0){
                    column=sizeBoard-1;
                    row=column;
                } else{
                    row=boardToSolve[i][j]/sizeBoard - ((boardToSolve[i][j]%sizeBoard==0) ? 1 : 0);
                    column=(sizeBoard+boardToSolve[i][j]%sizeBoard-1)%sizeBoard;
                }
                ans+=abs(row-i)+abs(column-j);
            }
        }
    }
    return ans;
};

bool board::is_goal() const{
    for (int i=0; i<sizeBoard; i++)
        for (int j=0; j<sizeBoard; j++)
            if (boardToSolve[i][j]!=rightBoard[i][j]) return false;
    return true;
};

bool board::is_solvable() const{
    int ans=0;
    std::vector <int> lineBoard;
    for (int i=0; i<sizeBoard; i++)
        for (int j=0; j<sizeBoard; j++)
            lineBoard.push_back(boardToSolve[i][j]);

    for (int i=1; i<sizeBoard*sizeBoard; i++){
        if (lineBoard[i]==0) ans+=i/sizeBoard+1;
        else{
            for (int j=i-1; j>-1; j--){
                if (lineBoard[i]<lineBoard[j]) ans++;
            }
        }
    }
    return ans%2==0;
};

bool operator== (const board &first, const board &second){
    return first.boardToSolve == second.boardToSolve;
};
bool operator!= (const board &first, const board &second){
    return first.boardToSolve != second.boardToSolve;
};
bool operator> (const board &first, const board &second){
    return first.boardToSolve > second.boardToSolve;
};
bool operator< (const board &first, const board &second){
    return first.boardToSolve < second.boardToSolve;
};

std::string board::to_string() const{
    std::string ans="";
    for (int i=0; i<sizeBoard; i++){
        for (int j=0; j<sizeBoard; j++)
            ans+=std::to_string(boardToSolve[i][j])+" ";
        ans+="\n";
    }
    return ans;
};


std::ostream &operator<< (std::ostream &out, const board &nowBoard){
    out << nowBoard.to_string();
    return out;
};

const std::vector<int> &board::operator[] (const int &nowInd) const{
    return boardToSolve[nowInd];
};

board &board::operator= (const board &nowBoard) = default;

//my
const std::pair <int, int> &board::where_empty_cell() const{
    return emptyCell;
};
const std::vector < std::vector <int> > &board::now_board() const{
    return boardToSolve;
};
const std::vector < std::vector <int> > &board::right_board() const{
    return rightBoard;
};

void board::initRightBoard(){
    rightBoard.resize(sizeBoard, std::vector <int> (sizeBoard));
    for (int i=0; i<sizeBoard*sizeBoard; i++){
        rightBoard[i/sizeBoard][i%sizeBoard]=i+1;
    }
    rightBoard[sizeBoard-1][sizeBoard-1]=0;
};
