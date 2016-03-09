#pragma once

#define MAX_UINT8   0xFFu
#define MAX_UINT16  0xFFFFu
#define MAX_INT8    0x7F
#define MAX_INT16   0x7FFF

#define MAX_WIDTH 144
#define MAX_HEIGHT 168

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08

#define ROW_CELL_COUNT 4
#define GRID_ROW_COUNT 4
#define ROW_HEIGHT (MAX_HEIGHT / GRID_ROW_COUNT)

#define ROW_PADDING 4
#define GRID_CELL_EDGE 12
#define GRID_CELL_MAX_EDGE 12
#define GRID_CELL_MIN_EDGE 6

#define PADDING_DELAY 1250
