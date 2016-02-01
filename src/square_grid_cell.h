#pragma once
#include <pebble.h>
#include "tgutils.h"

typedef enum SquareCellState { WHITE, BLACK } SquareCellState;

#define GRID_CELL_EDGE 12

typedef struct SquareCell {
    TextLayer * center_layer, * top_layer,
              * bottom_layer, * left_layer,
              * right_layer;
#ifdef PBL_PLATFORM_APLITE
    PropertyAnimation * center_prop_anim, * top_prop_anim,
                      * bottom_prop_anim, * left_prop_anim,
                      * right_prop_anim;
#endif
    SquareCellState state;
    GRect rect;
    uint16_t padding;
} SquareCell;

SquareCell * square_grid_cell_create(SquareCellState, GRect, uint16_t);

void square_grid_cell_destroy(SquareCell *);

void square_grid_cell_set_state(SquareCell *, SquareCellState);

void square_grid_cell_add_parent(SquareCell *, Layer *);

void square_grid_cell_set_padding(SquareCell *, uint16_t);
