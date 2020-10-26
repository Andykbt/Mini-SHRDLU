//
//  Solver.h
//  Assignment 1
//
//  Created by Andy Truong on 8/4/20.
//  Copyright © 2020 Andy Truong. All rights reserved.
//

#ifndef Solver_h
#define Solver_h

#include "Action.h"
#include "Goal.h"
#include "State.h"

//**************************************************************************
//This class specifies the solver class
//contains multiple methods that solve the mini-SHRDLU problem
//**************************************************************************

//
//I hereby certify that no other part of this submission has been copied from any other sources
//including the Internet, books or other student’s work except the ones I have listed below. No part of
//the code has been written/produced for me by another person or copied from any other source.
//I hold a copy of this assignment that I can produce if the original is lost or damaged.
//

class Solver {
    priority_queue<Action> a;
    int steps = 1;
    
public:
    
    //blind search | recursive implementation
    bool search(State state, Goal g) {
        int random;
        if (state.getValue(g) == g.block)
            return true;
        else if (steps > 100)
            return false;
        else {
            a = state.possibleActions();
            random = rand() % a.size();
            cout << "\nStep " << steps << ": " << endl;
            
            for (int i = 0; i < random; i++)
                a.pop();
            
            Action temp = a.top();
            state.moveBlock(temp);
            state.printBoard();
            
            steps++;
            return search(state, g);
        }
        return false;
    }//end of search
    
    //heuristic search | recursive implementation
    bool heuristicSearch(State& state, Goal g) {
        if (state.getValue(g) == g.block)
            return true;
        else if (steps > 100)
            return false;
        else {
            Action action;
            a = setHeuristic(state.possibleActions(), state, g);
            action = a.top();

            cout << "\nStep " << steps << ": ";
            cout << "Moving col "<< action.source << " to col "<< action.destination << " with a heuristic of " << action.heuristic << endl;
    
            state.moveBlock(action);
            state.printBoard();
            
            steps++;
            return heuristicSearch(state, g);
        }
        return false;
    }//end heuristic search
    
    //sets heuristic for each action
    priority_queue<Action> setHeuristic(priority_queue<Action> actions, State s, Goal g) {
        priority_queue<Action> heuristicActions;
        Action tempAction;
        
        while (!actions.empty()) {
            State nextState(s);
            tempAction = actions.top();
            nextState.moveBlock(tempAction);
            
            if (nextState.getValue(g.row, g.col) == g.block)
                tempAction.setHeuristic(100);
            else if (nextState.isEmptyBlock(g.row, g.col) && nextState.getRow(g.block) == BOARDSIZE - 1)
                tempAction.setHeuristic(90);
            else if (nextState.getRow(g.block) == BOARDSIZE - 1 && nextState.getCol(g.block) != g.col)
                tempAction.setHeuristic(80);
            else if (nextState.getBlockDepth(g.block) < s.getBlockDepth(g.block))
                tempAction.setHeuristic(70);
            else if (nextState.getRow(g.block) == BOARDSIZE - 1)
                tempAction.setHeuristic(60);
            else if (nextState.getBlockDepth(g.row, g.col) < s.getBlockDepth(g.row, g.col))
                tempAction.setHeuristic(50);
            else if (nextState.isEmptyBlock(g.row, g.col))
                tempAction.setHeuristic(40);
            else if (nextState.getCol(g.block) != g.col)
                tempAction.setHeuristic(30);
            else if (nextState.isTopBlock(g.block))
                tempAction.setHeuristic(20);
            else if (!nextState.isTopBlock(g.block))
                tempAction.setHeuristic(0);
            else
                tempAction.setHeuristic(5);
            
            heuristicActions.push(tempAction);
            actions.pop();
        }
        return heuristicActions;
    }//end setHeuristic
    
    //disjunctive solver | returns true when any one of multiple goals is reached
    bool disjunctiveSolver(State s, stack<Goal> g) {
        if (s.getValue(g.top().row, g.top().col) == g.top().block)
            return true;
        else if (steps > 100) {
            steps = 0;
            cout << "Goal not found, attempting next goal." << endl;
            g.pop();
            return disjunctiveSolver(s, g);
        } else if (!g.empty()) {
            cout << "Finding goal: ";
            g.top().printGoal();
            return heuristicSearch(s, g.top());
        } else
            return false;
    }//end disjunctiveSolver
    
    //conjunctive solver | returns true if all goals can exist in one state
    bool conjunctiveSolver(State s, priority_queue<Goal> g) {
        priority_queue<Goal> goals;
        State goalState;
        Goal temp;
        int gSize = g.size();
        int blocksNeeded = 0;
        
        for (int i = 0; i < gSize; i++) {//puts all goals into temp goalState
            temp = g.top();
            goalState.setValue(temp.row, temp.col, temp.block);
            g.pop();
        }
        for (int i = 0; i < BOARDSIZE; i++) //counts how many blocks are needed to achieve goal state
            for (int j = 0; j < BOARDSIZE; j++)
                if (goalState.isUnderBlock(i, j) && goalState.getValue(i, j) == 0)
                    blocksNeeded++;
        
        for (int block = 1; block <= MAX_BLOCK; block++) {
            if (goalState.doesBlockExist(block)) {//if a block is already in goalstate push to g2
                temp.block = block;
                temp.row = goalState.getRow(block);
                temp.col = goalState.getCol(block);
                goals.push(temp);
            } else if (blocksNeeded == 0)//else if no blocks are needed break;
                break;
            else {  //else a block doesn't exist in goal state
                temp.block = block;
                blocksNeeded--;
                for (int i = 0; i < BOARDSIZE; i++)
                    for (int j = 0; j < BOARDSIZE; j++)
                        if (goalState.isUnderBlock(i, j) && goalState.getValue(i, j) == 0) {
                            cout << "(" << i << ", " << j << ")" << endl;
                            goalState.setValue(i, j, block);
                            temp.row = i;
                            temp.col = j;
                            break;
                        }
                goals.push(temp);
            }
        }
        goalState.printBoard();
        return conjunctiveSearch(s, goals);
    }//end conjunctiveSolver
    
    bool conjunctiveSearch(State s, priority_queue<Goal> g) {
        Goal temp;
        if (steps > 100)
            return false;
        else if (!g.empty()) {
            temp = g.top();
            temp.printGoal();
            heuristicSearch(s, temp);
            g.pop();
            return conjunctiveSearch(s, g);
        }
        return true;
    }//end conjunctiveSearch
};

#endif /* Solver_h */
