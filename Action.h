//
//  Action.h
//  Assignment 1
//
//  Created by Andy Truong on 6/4/20.
//  Copyright © 2020 Andy Truong. All rights reserved.
//

#ifndef Action_h
#define Action_h

//**************************************************************************
//This class specifies an action, notation (source col, destination col)
//Heuristic is hidden
//**************************************************************************

//
//I hereby certify that no other part of this submission has been copied from any other sources
//including the Internet, books or other student’s work except the ones I have listed below. No part of
//the code has been written/produced for me by another person or copied from any other source.
//I hold a copy of this assignment that I can produce if the original is lost or damaged.
//

struct Action {
public:
    int source;
    int destination;
    int heuristic;
    
    void setHeuristic(int h) {heuristic = h;}//end setHeuristic
    void setAction(int s, int d, int h) {source = s; destination = d; heuristic = h;}//end setAction
    void printAction() {cout << "(" << source << ", " << destination << ")";}//end printActtion
    
    bool operator<(const Action& a) const {return heuristic < a.heuristic;}//end lessthan operator
};

#endif /* Action_h */
