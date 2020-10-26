//
//  main.cpp
//  Assignment 1
//
//  Created by Andy Truong on 5/4/20.
//  Copyright © 2020 Andy Truong. All rights reserved.
//

//
//I hereby certify that no other part of this submission has been copied from any other sources
//including the Internet, books or other student’s work except the ones I have listed below. No part of
//the code has been written/produced for me by another person or copied from any other source.
//I hold a copy of this assignment that I can produce if the original is lost or damaged.
//

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

const int BOARDSIZE = 3;
const int MAX_BLOCK = (BOARDSIZE * BOARDSIZE) - BOARDSIZE;

#include "Mini-SHRDLU.h"
#include "Action.h"
#include "Solver.h"
#include "Goal.h"
#include "State.h"

using namespace std;

int main() {
    srand(time(NULL));
    mSHRDLU mini;
    mini.start();
    
    return 0;
}
