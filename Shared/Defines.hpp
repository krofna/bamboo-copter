#ifndef DEFINES_HPP
#define DEFINES_HPP

#define TILE_SIZE 64
#define HEARTBEAT 50 // Server
#define GAME_HEARTBEAT 16 // Client

enum
{
    MOVE_UP     = 1,
    MOVE_DOWN   = 2,
    MOVE_LEFT   = 3,
    MOVE_RIGHT  = 4
};

enum
{
    UPDATE_FIELD_X = 1,
    UPDATE_FIELD_Y = 2
};

#endif
