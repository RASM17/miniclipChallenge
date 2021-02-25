#include "../include/BlockWall.h"

BlockWall::BlockWall(){
	initBlockWall();
}

/**
	Init block wall 
	the column is limit by NCOLS in constants header
*/
void BlockWall::initBlockWall() {
	srand(time(NULL));

	for (int i = (NROWS - 1); i >= 0; i--) {
		for (int j = 0; j < NCOLS; j++)	{
			if (j > (int)STARTCOL) {
				blockWall.matrix[i][j] = rand() % (BTYPES + 1); //+1 to get values between 0 and 5
			}
			else {
				blockWall.matrix[i][j] = 0;
			}
		}
	}

	// Repair holes in wall
	// If 0 is choosen and if there exist top block
	repairBlockWall();
}

/**
	Clear Block Wall
*/
void BlockWall::clearBlockWall() {
	for (auto block : blockWall.matrix)	{
		block = 0;
	}
}

/**
	Check for empty spaces
	in rows and cols
*/
void BlockWall::repairBlockWall() {
	for (int j = 0; j < NCOLS; j++)	{
		repairCol(j);
		// If a column is empty, push left
		if (j != 0 && blockWall.matrix[NROWS - 1][j] == 0)	{
			fillEmptyCol(j);
		}
	}
}

/**
	Checks if column needs Repair if so
	calls BlockFall to repair
	@param col - Column
*/
void BlockWall::repairCol(int col) {
	while (colCheck(col)) {
		blockFall(col);							// Moves the blocks downwards to fix spaces
	}
}

/**
	Verifies if column needs repairs
	@param col - Column
	@return - True if needs repair False if not
*/
bool BlockWall::colCheck(int col) {
	bool foundBlock = false;						//Block exists?

	// Start searching from the top
	for (int i = 0; i < NROWS; i++)	{
		if (blockWall.matrix[i][col] != 0) {		// Found a block
			foundBlock = true;
		}
		else {										// Found an empty space
			if (foundBlock) {						// If there is a block on top
				return true;
			}
		}
	}
	return false;
}

/**
	Move columns if empty
	@param col - Column
*/
void BlockWall::fillEmptyCol(int col) {
	for (int j = col; j > 0; j--) {
		for (int i = 0; i < NROWS; i++)	{
			blockWall.matrix[i][j] = blockWall.matrix[i][j - 1];
			blockWall.matrix[i][j - 1] = 0;
		}
	}
}

/**
	Push columns to the left
*/
void BlockWall::pushWallLeft() {
	for (int j = 1; j < NCOLS; j++)	{
		for (int i = 0; i < NROWS; i++) {
			blockWall.matrix[i][j - 1] = blockWall.matrix[i][j];
			blockWall.matrix[i][j] = 0;
		}

		if (j == NCOLS - 1) {
			for (int i = 0; i < NROWS; i++) {
				// +1 because remainder goes from 4 to 0 (BTYPES=5)
				blockWall.matrix[i][j] = rand() % (BTYPES + 1);
			}
			repairCol(j);
		}
	}
}


/**
	Drop Blocks if there is empty blocks bellow
	@param col - Column
*/
void BlockWall::blockFall(int col) {
	// Start from bottom
	for (int i = NROWS - 1; i > 0; i--) {
		// Checks for spaces
		if (blockWall.matrix[i][col] == 0) {
			for (int x = i; x > 0; x--) {
				// Check if top row has a block
				// if so swap and replace the row with empty
				if (blockWall.matrix[x - 1][col] != 0) {
					blockWall.matrix[x][col] = blockWall.matrix[x - 1][col];
					blockWall.matrix[x - 1][col] = 0;
				}
			}
		}
	}
}

/**
	Deletes clicked Block
	@param row - Row
	@param col - Column
	@return Number of blocks destroyed
*/
int BlockWall::breakBlock(int row, int col) {
	// If empty no need to search
	int nBlocks = 0;
	switch (blockWall.matrix[row][col]) {
		// Bombs
		case 6:
			nBlocks = clearRadius(row, col);
			break;
		case 7:
			nBlocks = clearRow(row);
			break;
		case 8:
			nBlocks = clearCol(col);
			break;
		// Normal blocks
		default:
			nBlocks = breakCombo(row, col);
		}
	if (nBlocks > 0) {
		repairBlockWall();
	}
	return nBlocks;

}

/**
	Search for combos of blocks
	Uses a Search Queue to find the adjacent blocks of the same type
	and a Delete Set to delete all the block with the same type
	@param row - Row
	@param col - Column
	@return Number of blocks destroyed
*/
int BlockWall::breakCombo(int row, int col)
{
	// Block Clicked
	const int blockType = blockWall.matrix[row][col];
	std::pair<int, int> clickedBlock(row, col);

	// Possibel directions Left, Up, Down, Right
	std::vector<std::pair<int, int>> directions = { {0,-1}, {-1,0}, {1,0}, {0,1} };

	// Delete Set
	std::set<std::pair<int, int>> deleteBlockSet = {};
	// Search Queue
	std::queue<std::pair<int, int>> searchQueue = {};

	searchQueue.push(clickedBlock);
	while (searchQueue.size() > 0) {
		std::pair<int, int> currentBlock(searchQueue.front().first, searchQueue.front().second);
		for (auto dir : directions) {

			std::pair<int, int> searchBlock(currentBlock.first + dir.first, currentBlock.second + dir.second);
			// Check bounds
			if (searchBlock.first > (NROWS - 1) || searchBlock.first < 0 || searchBlock.second >(NCOLS - 1) || searchBlock.second < 0) {
				continue;
			}

			if (blockWall.matrix[searchBlock.first][searchBlock.second] == blockType && !deleteBlockSet.count(searchBlock)) {
				// Add to the block set to be deleted after
				deleteBlockSet.emplace(searchBlock);
				//Add to Queue to be searched after
				searchQueue.push(searchBlock);
			}
		}
		// Pop the first in queue
		searchQueue.pop();
	}
	// Delete blocks
	for (auto block : deleteBlockSet) {
		blockWall.matrix[block.first][block.second] = 0;
	}
	// Return number of combo
	return (int)deleteBlockSet.size();
}


/**
	Set a Block with a certain value
	Uses a Search Queue to find the adjacent blocks of the same type
	and a Delete Set to delete all the block with the same type
	@param row - Row
	@param col - Column
	@param bType = blockType 0 empty 1-5 Blocks 6 Bomb
*/
void BlockWall::setBlock(int row, int col, int bType) {
	blockWall.matrix[row][col] = bType;
	repairBlockWall();
}


/**
	clearRadius - clears blocks in a radius(BOMBEFFECT) of the bomb
	@param row - Row
	@param col - Column
	@return nrBlocks - Number of blocks destroyed
*/
int BlockWall::clearRadius(int row, int col) {
	int nrBlocks = 0;
	// Inside radius and inside matrix
	for (int i = row - BOMBEFFECT; i <= row + BOMBEFFECT && i <= NROWS; i++) {
		for (int j = col - BOMBEFFECT; j <= col + BOMBEFFECT && j <= NCOLS; j++) {
			// Compare if not empty so points dont sum
			if (blockWall.matrix[i][j] != 0) {
				updateBombMap(blockWall.matrix[i][j] - 1);
				blockWall.matrix[i][j] = 0;
				nrBlocks++;
			}
		}
	}
	return nrBlocks;
}

/**
	Clear row - Bomb effects clears entire row
	@param row - Row
	@return nrBlocks - Number of blocks destroyed
*/
int BlockWall::clearRow(int row) {
	int nrBlocks = 0;
	for (int j = 0; j <= NCOLS; j++) {
		// Compare if not empty so points dont sum
		if (blockWall.matrix[row][j] != 0) {
			updateBombMap(blockWall.matrix[row][j] -1);
			blockWall.matrix[row][j] = 0;
			nrBlocks++;
		}
	}
	return nrBlocks;
}


void BlockWall::updateBombMap(int bType) {
	if (bType < BTYPES) {
		if (bombMap.find(bType) != bombMap.end()) {
			bombMap[bType] += 1;
		}
		else {
			bombMap[bType] = 1;
		}
	}
}

/**
	Clear col - Bomb effects clears entire column
	@param col - Column
	@return nrBlocks - Number of blocks destroyed
*/
int BlockWall::clearCol(int col) {
	int nrBlocks = 0;
	for (int i = 0; i <= NROWS; i++) {
		// Compare if not empty so points dont sum
		if (blockWall.matrix[i][col] != 0) {
			updateBombMap(blockWall.matrix[i][col]-1);
			blockWall.matrix[i][col] = 0;
			nrBlocks++;
		}
	}
	return nrBlocks;
}