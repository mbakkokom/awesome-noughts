#include "NoughtsGame.hpp"

#include <iostream>

int NoughtsGame::getState() {
	return mState;
}

NoughtsGame::PlayerTurn NoughtsGame::getTile(int x, int y) {
	if (x < 0 || x >= 3 || y < 0 || y >= 3)
		return PLAYER_NONE;
	else
		return mTiles[(y * 3) + x];
}

NoughtsGame::PlayerTurn NoughtsGame::getTurn() {
	return mTurn;
}

NoughtsGame::GameCoord NoughtsGame::getStroke() {
	return mStroke;
}

bool NoughtsGame::playTile(int x, int y) {
	int id = (y * 3) + x;

	std::cout << "NoughtsGame::playTile x=" << x << " y=" << y << " id=" << id << std::endl;

	if (x < 0 || x >= 3 || y < 0 || y >= 3) {
		return false;
	} else if (mTiles[id] != PLAYER_NONE || mState != GAME_RUNNING) {
		return false;
	} else {
		std::cout << "NoughtsGame::playTile fall through state=" << mState << std::endl;

		mTiles[id] = mTurn;

		if (boardCheck() == GAME_RUNNING)
			togglePlayer();

		game_event.emit((GameStatus) mState, mTurn);
	}

	return true;
}

void NoughtsGame::setPlayer(NoughtsGame::PlayerTurn player) {
	mTurn = player;
}

void NoughtsGame::togglePlayer() {
	std::cout << "NoughtsGame::togglePlayer mTurn=" << mTurn << std::endl;
	switch(mTurn) {
	case PLAYER_CROSS:
		mTurn = PLAYER_NOUGHT;
		break;
	case PLAYER_NONE:
	case PLAYER_NOUGHT:
		mTurn = PLAYER_CROSS;
		break;
	}
}

int NoughtsGame::boardCheck() {
	std::cout << "NoughtsGame::boardCheck mState = " << mState << std::endl;

	int cn = 0;

	if (mState != GAME_RUNNING) {
		return mState;
	}

	for (PlayerTurn &t : mTiles) {
		if (t == PLAYER_CROSS || t == PLAYER_NOUGHT) {
			cn++;
		}
	}

	if (mTiles[0] == mTiles[4] && mTiles[0] == mTiles[8] && (mTiles[0] == PLAYER_CROSS || mTiles[0] == PLAYER_NOUGHT)) {
		mStroke.direction = STROKE_DIAGONAL;
		mStroke.x = 0;
		mState = GAME_WON;
		return mState;
	} else if (mTiles[2] == mTiles[4] && mTiles[2] == mTiles[6] && (mTiles[2] == PLAYER_CROSS || mTiles[2] == PLAYER_NOUGHT)) {
		mStroke.direction = STROKE_DIAGONAL;
		mStroke.x = 2;
		mState = GAME_WON;
		return mState;
	}

	for (size_t x=0; x<3; x++) {
		if (mTiles[x] == mTiles[x+3] && mTiles[x] == mTiles[x+6] && (mTiles[x] == PLAYER_CROSS || mTiles[x] == PLAYER_NOUGHT)) {
			mStroke.direction = STROKE_VERTICAL;
			mStroke.x = x;
			mState = GAME_WON;
			return mState;
		}
	}

	for (size_t y=0; y<9; y+=3) {
		if (mTiles[y] == mTiles[y+1] && mTiles[y] == mTiles[y+2] && (mTiles[y] == PLAYER_CROSS || mTiles[y] == PLAYER_NOUGHT)) {
			mStroke.direction = STROKE_HORIZONTAL;
			mStroke.y = y/3;
			mState = GAME_WON;
			return mState;
		}
	}

	if (cn == 9 && mState == GAME_RUNNING) {
		mState = GAME_DRAW;
		return mState;
	}

	return mState;
}

NoughtsGame::GameEventSignal NoughtsGame::signal_game_event() {
	return game_event;
}