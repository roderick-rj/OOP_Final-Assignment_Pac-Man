// creates a maze
#include "Maze.h"
#include "entities/Block.h"
#include "entities/Dot.h"

#include <iostream>
#include <fstream>

const float Maze::SQUARE_SIZE = 32.0F;

// constructor
Maze::Maze(unsigned int level)
{
	// loads in a level file.
	switch (level)
	{
	case 1:
		loadData("data/level_01.txt");
	}
}

// loads the file data
void Maze::loadData(std::string fileName)
{
	std::ifstream file(fileName, std::ios::in); // opens up the file
	
	try
	{
		if (!file)
			throw "Error accessing file. Default area loaded.";

		
	}
	catch (const char * ex)
	{
		std::cout << ex << std::endl;
		return; // leaves default values in maze.
	}


}

// gets the player's spawn point in the maze.
Vec2 Maze::getPlayerSpawn() const { return plyrSpawn; }

// generates the maze graphics
std::vector<entity::Entity *> Maze::generate()
{
	std::vector<entity::Entity *> gameObjects; // a vector of game objects
	bool added = false; // becomes true if something was just added.

	for (int i = 0; i < ROW_MAX; i++) // going through each row
	{
		for (int j = 0; j < COL_MAX; j++) // going through each column
		{
			/*
			 * The maze map. The position is set opposite to how it appears in the array (e.g. row(0) is the top of the map, not the bottom.
				* 0 - empty
				* 1 - block 
				* 2 - pacdot ~the things pacman collects
				* 3 - power pellet
				* 4 - ghost pen ~ the ghost spawns on top of this area.
				* 5 - player ~ sets their position in the maze
			*/
			switch (map[i][j])
			{
			case 1: // block
				gameObjects.push_back(new entity::Block()); // sets hte position of the block
				added = true;
				break;

			case 2: // pac-dot
				gameObjects.push_back(new entity::Dot());
				added = true;
				break;

			case 3: // power pellet
				gameObjects.push_back(new entity::Pellet());
				added = true;

			case 5: // player position; uses the last instance of this number, even though there should only be one.
				plyrSpawn = (Vec2(j * SQUARE_SIZE + SQUARE_SIZE / 2.0F, COL_MAX * SQUARE_SIZE - i * SQUARE_SIZE + SQUARE_SIZE / 2.0F));
			}

			if (added) // if the item was added, its position is set
				gameObjects.at(gameObjects.size() - 1)->setPosition(Vec2(j * SQUARE_SIZE + SQUARE_SIZE / 2.0F, COL_MAX * SQUARE_SIZE - i * SQUARE_SIZE + SQUARE_SIZE / 2.0F));

			added = false; // reset for next loop

		}
	}


	return gameObjects;
}

