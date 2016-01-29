#pragma once
#include <pebble.h>
#include "tgutils.h"
#include "square_grid_row.h"

typedef struct SquareGrid {
    SquareRow * rows[GRID_ROW_COUNT];
    uint8_t values[GRID_ROW_COUNT];
} SquareGrid;

SquareGrid * square_grid_create();
void square_grid_destroy(SquareGrid *);
void square_grid_set_values(SquareGrid *, uint8_t (*)[GRID_ROW_COUNT]);
void square_grid_add_parent(SquareGrid *, Layer *);
