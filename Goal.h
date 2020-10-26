//
//  Goal.h
//  Assignment 1
//
//  Created by Andy Truong on 6/4/20.
//  Copyright © 2020 Andy Truong. All rights reserved.
//

#ifndef Goal_h
#define Goal_h

//**************************************************************************
//This class specifies the Atom Goal, notation is (block, row, col)
//**************************************************************************

//
//I hereby certify that no other part of this submission has been copied from any other sources
//including the Internet, books or other student’s work except the ones I have listed below. No part of
//the code has been written/produced for me by another person or copied from any other source.
//I hold a copy of this assignment that I can produce if the original is lost or damaged.
//

//Definition of the Goal
struct Goal{
    int block;
    int row;
    int col;
    void printGoal() {cout << "(" << block << ", " << row << ", " << col << ")" << endl;}
    
    bool operator<(const Goal& g) const {
        //overloads less-than operator to compare Goals
        if (row > g.row)
            return true;
        else if (row == g.row)
            return col > g.col;
        else
            return false;
    } //end less-than operator
};
#endif /* Goal_h */
