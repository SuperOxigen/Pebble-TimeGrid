#pragma once
#include <pebble.h>
#include "tgutils.h"
#include "square_grid_cell.h"

typedef struct SquareRow {
    SquareCell * cells[ROW_CELL_COUNT];
    TextLayer * top_padding, * bottom_padding,
              * left_padding, * right_padding;
    uint8_t value;
    GRect rect;
    uint8_t padding;
} SquareRow;

SquareRow * square_grid_row_create(uint8_t value, GRect, uint8_t);

void square_grid_row_destroy(SquareRow *);

void square_grid_row_set_value(SquareRow *, uint8_t value);

void square_grid_row_add_parent(SquareRow *, Layer *);

void square_grid_row_set_cell_padding(SquareRow *, uint8_t, uint16_t);
