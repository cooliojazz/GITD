#include "Player.h"


void Player::move(directionT direction) {
    if (currentTile->moveValid(direction)) {
        switch (direction) {				//Note: Doesn't contain any code for playing movement animation
            case NORTH:
                currentTile = currentLevel->getTile(currentTile->getXLoc(), currentTile->getYLoc() - 1);
            case EAST:
                currentTile = currentLevel->getTile(currentTile->getXLoc() + 1, currentTile->getYLoc());
            case SOUTH:
                currentTile = currentLevel->getTile(currentTile->getXLoc(), currentTile->getYLoc() + 1);
            case WEST:
                currentTile = currentLevel->getTile(currentTile->getXLoc() - 1, currentTile->getYLoc());
        }

        if (currentLevel->getEnd() == currentTile) {
            currentLevel = currentLevel->getNextLevel();
            currentTile = currentLevel->getStart();
			assignSounds();
        }
    }
}

void Player::useBell() {
    int xDiff = currentTile->getXLoc() - currentLevel->getEnd()->getXLoc(); //The X-difference between the players current tile and the level's end tile
    int yDiff = currentTile->getYLoc() - currentLevel->getEnd()->getYLoc(); //The Y-difference between the players current tile and the level's end tile

    int distance = sqrt(xDiff ^ 2 + yDiff ^ 2);  //The straight distance between the player's tile and the end

	int volLevel;

	if (distance < 2)
	{
		volLevel = 100;
	}
	else if (distance < 4)
	{
		volLevel = 75;
	}
	else
	{
		volLevel = 50;
	}

	Mix_Volume(-1, volLevel);

	if (xDiff > 0)
		//Play sound for West (send in distance as param for volume/loudness)
		Mix_PlayChannel(-1, West, 0);
    else if (xDiff < 0)
        //Play sound for East (send in distance as param for volume/loudness)
		Mix_PlayChannel(-1, East, 0);

    if (yDiff > 0)
        //Play sound for North (send in distance as param for volume/loudness)
		Mix_PlayChannel(-1, North, 0);
    else if (yDiff < 0)
        //Play sound for South (send in distance as param for volume/loudness)
		Mix_PlayChannel(-1, South, 0);
}

void Player::laserOn(directionT direction) {
    //Use SDL_SetRenderDrawColor(renderer, 0, 255, 0, ?) to get a green color
    //Use SDL_RenderDrawLine(renderer, playerX, playerY, destX, destY) to draw a line
    //Need a direction in the input params
    //Need to test where there is a wall (? tiles in desired direction, if not, to edge of screen
    laser = true;
}

void Player::laserOff() {
    //?????????????????????
    laser = false;
}

Level* Player::getLevel() {
    return currentLevel;
}

void Player::setLevel(Level *inLevel) {
    currentLevel = inLevel;
}

void Player::setTile(Tile *inTile) {
    currentTile = inTile;
}

void Player::setNorth(Mix_Chunk *newSound)
{
	 North = newSound;
}

void Player::setEast(Mix_Chunk *newSound)
{
	East = newSound;
}

void Player::setSouth(Mix_Chunk *newSound)
{
	South = newSound;
}

void Player::setWest(Mix_Chunk *newSound)
{
	West = newSound;
}

void Player::assignSounds() {
	int start = rand() % 4;
	Mix_Chunk *temp1;
	Mix_Chunk *temp2;

	switch (start) {
		//case 0 is default
	case 1:				
		//sound temp = North
		temp1 = North;
		//sound north = east
		North = East;
		//sound east = south
		East = South;
		//sound south = west
		South = West;
		//sound west = temp
		West = temp1;
		true;
	case 2:				
		//sound temp1 = North
		temp1 = North;
		//sound temp2 = east
		temp2 = East;
		//sound north = south
		North = South;
		//sound east = west
		East = West;
		//sound south = temp
		South = temp1;
		//sound west = east
		West = temp2;
		true;
	case 3:				
		//sound temp = north
		temp1 = North;
		//sound north = west
		North = West;
		//sound west = south
		West = South;
		//sound south = east
		South = East;
		//sound east = temp
		East = temp1;
		true;
	}
}
