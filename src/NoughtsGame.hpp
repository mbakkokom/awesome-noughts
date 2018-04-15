#pragma once

#include <sigc++/sigc++.h>

class NoughtsGame {
public:
    static constexpr int INVALID_COORD = -1;

    typedef enum {
        GAME_NONE=0,
        GAME_RUNNING=1,
        GAME_WON=4,
        GAME_DRAW=8
    } GameStatus;

    typedef enum {
        STROKE_NONE=0,
        STROKE_HORIZONTAL=32,
        STROKE_VERTICAL=64,
        STROKE_DIAGONAL=96
    } GameStroke;

    typedef enum {
        PLAYER_NONE=0,
        PLAYER_CROSS,
        PLAYER_NOUGHT
    } PlayerTurn;

    typedef struct {
        int direction;
        int x;
        int y;
    } GameCoord;

    int getState();
    PlayerTurn getTurn();
    PlayerTurn getTile(int x, int y);
    GameCoord getStroke();

    bool playTile(int x, int y);
    void setPlayer(PlayerTurn player);
    void togglePlayer();

    typedef sigc::signal<void, NoughtsGame::GameStatus, NoughtsGame::PlayerTurn> GameEventSignal;
    GameEventSignal signal_game_event();
protected:
    int boardCheck();

    PlayerTurn mTiles[9] = { PLAYER_NONE };

    int mState = GAME_RUNNING;
    PlayerTurn mTurn = PLAYER_CROSS;

    GameCoord mStroke = { .direction = STROKE_NONE, .x = INVALID_COORD, .y = INVALID_COORD };
private:
    GameEventSignal game_event;
};
