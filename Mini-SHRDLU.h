//
//  Mini-SHRDLU.h
//  Assignment 1
//
//  Created by Andy Truong on 8/4/20.
//  Copyright © 2020 Andy Truong. All rights reserved.
//

#ifndef Mini_SHRDLU_h
#define Mini_SHRDLU_h

#include "Solver.h"

//**************************************************************************
// This class initialises the necessary components to solve the mini-SHRDLU
//**************************************************************************

//
//I hereby certify that no other part of this submission has been copied from any other sources
//including the Internet, books or other student’s work except the ones I have listed below. No part of
//the code has been written/produced for me by another person or copied from any other source.
//I hold a copy of this assignment that I can produce if the original is lost or damaged.
//

class mSHRDLU {
private:
    int choice;
    State initialState;
public:
    void createInitialState() {
        cout << "Initial Board: \n";
        initialState.randomiseBoard();
        initialState.printBoard();
    }
    
    bool setGoal(Goal& goal) {
        bool validB = false;
        bool validR = false;
        bool validC = false;
        int b, r, c;
        
        cout << "Input a goal in the format (block, row, col)\nBlock (1-6): ";
        cin >> b;
        if (b <= MAX_BLOCK && b > 0)
            validB = true;
        cout << "Row (0-2 bottom-up): ";
        cin >> r;
        if (r >= 0 && r <= BOARDSIZE-1)
            validR = true;
        cout << "Col (0-2 left-right): ";
        cin >> c;
        if (c >= 0 && c <= BOARDSIZE-1)
            validC = true;
        
        if (!validB || !validR || !validC) {
            cout << "Out of range";
            return false;
        }
        else {
            goal.block = b;
            goal.row = r;
            goal.col = c;
            return true;
        }
    }//end setGoal
    
    void setMultipleGoals(stack<Goal>& goals) {
        Goal g;
        char key = 'g';
        
        while (key == 'g') {
            setGoal(g);
            goals.push(g);
            cout << "Press g to input more goals; Press s (or other letters) to start search." << endl;
            cin >> key;
        }
    }//end setMultiple Goals
    
    void setMultipleGoals(priority_queue<Goal>& goals) {
        Goal g;
        char key = 'g';
        
        while (key == 'g') {
            setGoal(g);
            goals.push(g);
            cout << "Press g to input more goals; Press s (or other letters) to start search." << endl;
            cin >> key;
        }
    }//end setMultiple Goals overload
    
    void chooseSolver() {
        cout << "Choose a level to run: ";
        cout << "\n1. Single goal solver without heuristics ";
        cout << "\n2. Single goal solver with heuristics ";
        cout << "\n3. Disjunctive goal solver ";
        cout << "\n4. Conjunctive goal solver ";
        cout << endl;
        
        do {
            cin >> choice;
        } while (choice < 1 && choice < 3);
    }//end chooseSolver
    
    void start() {
        Solver solver;
        Goal goal;
        createInitialState();
        chooseSolver();
    
        if (choice == 1) {
            if (setGoal(goal))
                solver.search(initialState, goal);
        }
        else if (choice == 2) {
            if (setGoal(goal))
                solver.heuristicSearch(initialState, goal);
        }
        else if (choice == 3) {
            stack<Goal> goals;
            setMultipleGoals(goals);
            solver.disjunctiveSolver(initialState, goals);
        }
        else if (choice == 4) {
            priority_queue<Goal> qGoals;
            setMultipleGoals(qGoals);
            solver.conjunctiveSearch(initialState, qGoals);
        }
    }//end start
};
#endif /* Mini_SHRDLU_h */
