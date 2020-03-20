#pragma once
#include "Window.h"
#include "Tile.h"

using namespace Graph_lib;
enum class MouseButton { left = FL_LEFT_MOUSE, right = FL_RIGHT_MOUSE }; //

// Minesweeper GUI
class MinesweeperWindow : public Graph_lib::Window
{
public:
	//storrelsen til hver rute
	static constexpr int cellSize = 30;
	MinesweeperWindow(Point xy, int width, int height, int mines, const string& title);
private:

	Point xy;
	string title;
	const int width;//width i miner 
	const int height;//heigth i miner
	const int mines;//Antall miner
	Vector_ref<Tile> tiles; // Vektor som inneholder alle tiles

	//Height og Width i piksler
	int Height() const { return height * cellSize; }
	int Width() const { return width * cellSize; }

	// Faa en liste med naborutene rundt en tile
	vector<Point> adjacentPoints(Point xy) const;
	//tell miner basert paa liste
	int countMines(vector<Point> coords) const;

	//Sjekk at punkt er paa brettet og gjor det til Tile
	bool inRange(Point xy) const { return xy.x >= 0 && xy.x < Width() && xy.y >= 0 && xy.y < Height(); }
	Tile& at(Point xy) { return tiles[xy.x / cellSize + (xy.y / cellSize) * width]; }
	const Tile& at(Point xy) const { return tiles[xy.x / cellSize + (xy.y / cellSize) * width]; }

	//aapne og flagge rute
	void openTile(Point xy);
	void flagTile(Point xy);

	//callback funksjon for tile knappen
	static void cb_click(Address, Address pw);
	static void cb_restart(Address, Address pw); 
	static void cb_quit(Address, Address pw);

	Out_box won;
	Out_box lost;
	Out_box numOfMines;

	int tilesOpened{0}; //Counts how many tiles that have been opened. 
	int tilesFlagged{0}; //Counts how many tiles that are flagged. 

	void flagMinesWhenWinner();
	void crossMinesWhenLoser(); 

	bool gameEnded{false}; //Used to check whether game is finished or not. 
	Button restartBtn;
	Button quitBtn;

	int restart();
	void quit();
};
