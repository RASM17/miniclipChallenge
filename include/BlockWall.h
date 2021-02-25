#pragma once

#include "Configurations.h"
#include "SDL.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
#include <queue> 
#include <map>
struct blockWallStruct										// Matrix wrapper so I can return it easilly
{
	int matrix[NROWS][NCOLS];
};

class BlockWall
{
public:
	BlockWall();
	/**
		Returns the current Block Wall
	*/
	blockWallStruct& getWall() { return blockWall; };

	/**
	Init block wall
	the column is limit by NCOLS in constants header
	*/
	void initBlockWall();	
	/**
	Clear Block Wall
	*/
	void clearBlockWall();
	/**
	Deletes clicked Block
	@param row - Row
	@param col - Column
	@return Number of blocks destroyed
	*/
	int breakBlock(int row, int col);		
	/**
	Push columns to the left
	*/
	void pushWallLeft();
	/**
	Set a Block with a certain value
	Uses a Search Queue to find the adjacent blocks of the same type
	and a Delete Set to delete all the block with the same type
	@param row - Row
	@param col - Column
	@param bType = blockType 0 empty 1-5 Blocks 6 Bomb
	*/
	void setBlock(int row, int col, int bType);
	// Return result of blocks destroyed by BOMB
	std::map<int, int> getMapBomb(){ return bombMap; }
	//  Clean map of blocks destroyed by BOMB
	void clearMapBomb() { bombMap.clear(); };
private:
	// Block Wall
	blockWallStruct blockWall;
	/**
	Check for empty spaces
	in rows and cols
	*/
	void repairBlockWall();
	/**
	Checks if column needs Repair if so
	calls BlockFall to repair
	@param col - Column
	*/
	void repairCol(int col);							
	/**
	Verifies if column needs repairs
	@param col - Column
	@return - True if needs repair False if not
	*/
	bool colCheck(int col);
	/**
	Drop Blocks if there is empty blocks bellow
	@param col - Column
	*/
	void blockFall(int col);
	/**
	Check for empty spaces
	in rows and cols
	*/
	void fillEmptyCol(int col);
	/**
	Search for combos of blocks
	Uses a Search Queue to find the adjacent blocks of the same type
	and a Delete Set to delete all the block with the same type
	@param row - Row
	@param col - Column
	@return Number of blocks destroyed
	*/
	int breakCombo(int row, int col);
	/**
	clearRadius - clears blocks in a radius(BOMBEFFECT) of the bomb
	@param row - Row
	@param col - Column
	@return nrBlocks - Number of blocks destroyed
	*/
	int clearRadius(int row, int col);
	/**
	Clear col - Bomb effects clears entire column
	@param col - Column
	@return nrBlocks - Number of blocks destroyed
	*/
	int clearCol(int col);
	/**
	Clear row - Bomb effects clears entire row
	@param row - Row
	@return nrBlocks - Number of blocks destroyed
	*/
	int clearRow(int row);

	// Map representing blocks destroyed by bomb effect for statistics
	std::map<int, int> bombMap;
	// Update bombMap
	void updateBombMap(int bType);

};