//
//  State.h
//  Assignment 1
//
//  Created by Andy Truong on 5/4/20.
//  Copyright © 2020 Andy Truong. All rights reserved.
//

#ifndef State_h
#define State_h

//**************************************************************************
//This class specifies the state
//**************************************************************************

//
//I hereby certify that no other part of this submission has been copied from any other sources
//including the Internet, books or other student’s work except the ones I have listed below. No part of
//the code has been written/produced for me by another person or copied from any other source.
//I hold a copy of this assignment that I can produce if the original is lost or damaged.
//

class State {
private:
    int board[BOARDSIZE][BOARDSIZE];
public:
    
        //Constructor
    State() {
        for (int i = 0; i < BOARDSIZE; i++)
            for (int j = 0; j < BOARDSIZE; j++)
                board[i][j] = 0;
    }//end constructor
    
        //Copy construtor
    State(State& s) {
        for (int i = 0; i < BOARDSIZE; i++)
            for (int j = 0; j < BOARDSIZE; j++)
                setValue(i, j, s.getValue(i, j));
    }//end copy consturtor
    
    State nextState(Action a) {
        State nextState(*this);
        nextState.moveBlock(a.source, a.destination);
        nextState.printBoard();
        return nextState;
    }//end nextState
    
        //overloads assignment operator
    bool operator==(State& s) {
        for (int i = 0; i < BOARDSIZE; i++)
            for (int j = 0; j < BOARDSIZE; j++)
                if (getValue(i, j) != s.getValue(i, j))
                    return false;
        return true;
    }//end assignment operator overload
    
    priority_queue<Action> possibleActions() {
        //returns all possible actions in a priority_queue
        priority_queue<Action> actions;
        Action a;
        for (int i = 0; i < BOARDSIZE; i++)
            for (int j = 0; j < BOARDSIZE; j++)
                if (isEmptyColumn(j) && j != i) {
                    a.setAction(i, j, 0);
                    actions.push(a);
                }
        return actions;
    }//end possibleActions
    
    void printBoard() {
        cout << " --- --- --- " << endl;
        for (int i = 0; i < BOARDSIZE; i++) {
            for (int j = 0; j < BOARDSIZE; j++) {
                cout << "| " << board[BOARDSIZE - i - 1][j] << " ";
            }
            cout << "|" << endl;
        }
        cout << " --- --- --- " << endl;
    }//end printBoard
    
    void randomiseBoard() {
        for (int i = 1; i <= MAX_BLOCK; i++) {
            int row = rand() % BOARDSIZE;
            int col = rand() % BOARDSIZE;
            
            if (board[row][col] == 0)
                board[row][col] = i;
            else
                i = --i;
        }
        pushDown();
    }//end randomiseBoard
    
    void pushDown() {
        for (int j = 0; j < BOARDSIZE; j++) {
            stack<int>myStack;
            for (int i = 0; i < BOARDSIZE; i++)
                if (board[BOARDSIZE - i - 1][j] != 0)
                    myStack.push(board[BOARDSIZE - i - 1][j]);
            for (int i = 0; i < BOARDSIZE; i++) {
                if (!myStack.empty()) {
                    board[i][j] = myStack.top();
                    myStack.pop();
                }
                else
                    board[i][j] = 0;
            }
        }
    }//end pushDown
    
    /* ******************** ACTIONS ******************** */
    int getValue(int row, int col) {return board[row][col];}//end getValue
    
    int getValue(Goal g) {return board[g.row][g.col];}//end getValue overload
    
    void setValue(int row, int col, int val) {board[row][col] = val;}//end setValue
    
    void setValue(Goal g) {board[g.row][g.col] = g.block;}//end setValue overload
    
    bool isUnderBlock(int row, int col) {return (board[row + 1][col] > 0 && board[row + 1][col] <+ MAX_BLOCK);}//end isUnderBlock
    
    bool doesBlockExist(int val) {
        for (int i = 0; i < BOARDSIZE; i++)
            for (int j = 0; j < BOARDSIZE; j++)
                if (board[i][j] == val)
                    return true;
        return false;
    }//end doesBlockExist
    
    int findRow(int val) {
        for (int i = 0; i < BOARDSIZE; i++)
            for (int j = 0; j < BOARDSIZE; j++)
                if (board[i][j] == val)
                    return i;
        return -1;
    }//end findRow
    
    int findCol(int val) {
        for (int i = 0; i < BOARDSIZE; i++)
            for (int j = 0; j < BOARDSIZE; j++)
                if (board[i][j] == val)
                    return j;
        return -1;
    }//end findCol
    
    int getBlockDepth(int val) {
        for (int i = 0; i < BOARDSIZE; i++) {
            for (int j = 0; j < BOARDSIZE; j++) {
                if (board[i][j] == val) {
                    if (i == 0 && getValue(i + 1, j) != 0 && getValue(i + 2, j) != 0)
                        return 2;
                    else if (i == 0 && getValue(i + 1, j) != 0 && getValue(i + 2, j) == 0)
                        return 1;
                    else if (i == 1 && getValue(i + 1, j) != 0)
                        return 1;
                    else
                        return 0;
                }
            }
        }
        return -1;
    };//end getBlockDepth

    
    int getBlockDepth(int i, int j) {
        if (i == 0 && getValue(i + 1, j) != 0 && getValue(i + 2, j) != 0)
            return 2;
        else if (i == 0 && getValue(i + 1, j) != 0 && getValue(i + 2, j) == 0)
            return 1;
        else if (i == 1 && getValue(i + 1, j) != 0)
            return 1;
        else
            return 0;
    }//end getBlockDepth overload
    
    bool isTopBlock(int val) {
        for (int i = 0; i < BOARDSIZE; i++)
            for (int j = 0; j < BOARDSIZE; j++) {
                if (board[i][j] == val) {
                    if (i == BOARDSIZE - 1 || board[i + 1][j] == 0)
                        return true;
                } else
                    return false;
            }
        return false;
    }//end isTopBlock
    
    int getRow(int val) {
        for (int i = 0; i < BOARDSIZE; i++)
            for (int j = 0; j < BOARDSIZE; j++)
                if (board[i][j] == val)
                    return i;
        return -1;
    }//end getRow
    
    int getCol(int val) {
        for (int i = 0; i < BOARDSIZE; i++)
            for (int j = 0; j < BOARDSIZE; j++)
            if (board[i][j] == val)
                return j;
        return -1;
    }//end getCol
    
    bool isEmptyColumn(int col) {
        for (int i = 0; i < BOARDSIZE; i++)
            if (board[i][col] == 0)
                return true;
        return false;
    }//end isEmptyColumn
    
    bool isEmptyBlock(int row, int col) {
        if (board[row][col] == 0)
            return true;
        return false;
    }//end isEmptyBlock
    
    int removeBlockFrom(int column) {
        int block;
        
        for (int i = BOARDSIZE - 1; i >= 0; i--)
            if (board[i][column] != 0) {
                block = board[i][column];
                board[i][column] = 0;
                return block;
            }
        return -1;
    }//end removeBlockFrom
    
    bool insertBlockTo(int col, int val) {
        for (int i = 0; i < BOARDSIZE; i++)
            if (board[BOARDSIZE - 1 - i][col] == 0) {
                board[BOARDSIZE - 1 - i][col] = val;
                return true;
            }
        return false;
    }//end insertBlockTo
    
    bool moveBlock(int source, int destination) {
        if (insertBlockTo(destination, removeBlockFrom(source))) {
            pushDown();
            return true;
        }
        return false;
    }//end moveBlock
    
    bool moveBlock(Action action) {
        if (insertBlockTo(action.destination, removeBlockFrom(action.source))) {
            pushDown();
            return true;
        }        
        return false;
    }//end moveBlock overload
};
#endif /* State_h */
