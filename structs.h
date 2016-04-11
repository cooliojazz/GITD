#ifndef STRUCTS_H
#define	STRUCTS_H

enum directionT {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};
    
enum tileT {
    START = 0,
    DEADEND = 1,
    STRAIGHT = 2,
    BEND = 3,
    TJUNCT = 4,
    FOURWAY = 5,
    EXIT = 6
};

#endif	/* STRUCTS_H */

