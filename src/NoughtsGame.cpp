#include "NoughtsGame.hpp"

int NoughtsGame::getState() {
	return mState;
}

NoughtsGame::PlayerTurn NoughtsGame::getTile(int x, int y) {
	if (x < 0 || x >= 3 || y < 0 || y >= 3) {
		return PLAYER_NONE;
	} else {
		return mTiles[(y * 3) + x];
	}
}

NoughtsGame::PlayerTurn NoughtsGame::getTurn() {
	return mTurn;
}

NoughtsGame::GameCoord NoughtsGame::getStroke() {
	return mStroke;
}

bool NoughtsGame::setTile(int x, int y) {
	return true;
}

void NoughtsGame::setPlayer(NoughtsGame::PlayerTurn player) {

}

void NoughtsGame::togglePlayer() {

}

void NoughtsGame::boardCheck() {

}