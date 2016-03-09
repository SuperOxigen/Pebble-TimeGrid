#pragma once
#include <pebble.h>
#include "tgutils.h"

typedef enum SquareCellState { WHITE, BLACK } SquareCellState;

typedef struct SquareCell {
    TextLayer * center_layer, * top_layer,
              * bottom_layer, * left_layer,
              * right_layer;
    SquareCellState state;
    GRect rect;
    uint16_t padding;
} SquareCell;

SquareCell * square_grid_cell_create(SquareCellState, GRect, uint16_t);

void square_grid_cell_destroy(SquareCell *);

void square_grid_cell_set_state(SquareCell *, SquareCellState);

void square_grid_cell_add_parent(SquareCell *, Layer *);

void square_grid_cell_set_padding(SquareCell *, uint16_t);
