#include "square_grid_cell.h"

static inline GColor square_grid_cell_get_color() {
    return GColorWhite;
}

static inline GColor square_grid_cell_get_center_color(SquareCell * cell) {
    if (cell->state == WHITE) {
        return GColorBlack;
    } else {
        return square_grid_cell_get_color();
    }
}

static inline GColor square_grid_cell_get_outer_color(SquareCell * cell) {
    if (cell->state == WHITE) {
        return square_grid_cell_get_color();
    } else {
        return GColorBlack;
    }
}

static void square_grid_cell_add_layers(SquareCell * cell) {
    if (cell) {
        if (!cell->top_layer) {
            cell->top_layer = text_layer_create((GRect) {
                .origin = (GPoint) { .x = cell->rect.origin.x, .y = cell->rect.origin.y },
                .size   = (GSize)  { .h = cell->padding,       .w = cell->rect.size.w } });
            text_layer_set_background_color(cell->top_layer, GColorBlack);
        }
        if (!cell->bottom_layer) {
            cell->bottom_layer = text_layer_create((GRect) {
                .origin = (GPoint) { .x = cell->rect.origin.x,
                                     .y = cell->rect.origin.y + cell->rect.size.h - cell->padding },
                .size   = (GSize)  { .h = cell->padding,
                                     .w = cell->rect.size.w } });
            text_layer_set_background_color(cell->bottom_layer, GColorBlack);
        }
        if (!cell->left_layer) {
            cell->left_layer = text_layer_create((GRect) {
                .origin = (GPoint) { .x = cell->rect.origin.x,
                                     .y = cell->rect.origin.y + cell->padding },
                .size   = (GSize)  { .h = cell->rect.size.h - (2 * cell->padding),
                                     .w = cell->padding } });
            text_layer_set_background_color(cell->left_layer, GColorBlack);
        }
        if (!cell->right_layer) {
            cell->right_layer = text_layer_create((GRect) {
                .origin = (GPoint) { .x = cell->rect.origin.x + cell->rect.size.w - cell->padding,
                                     .y = cell->rect.origin.y + cell->padding },
                .size   = (GSize)  { .h = cell->rect.size.h - (2 * cell->padding),
                                     .w = cell->padding } });
            text_layer_set_background_color(cell->right_layer, GColorBlack);
        }
        if (!cell->center_layer) {
            cell->center_layer = text_layer_create((GRect) {
                .origin = (GPoint) { .x = cell->rect.origin.x + cell->padding,
                                     .y = cell->rect.origin.y + cell->padding },
                .size   = (GSize)  { .h = cell->rect.size.h - (2 * cell->padding),
                                     .w = cell->rect.size.w - (2 * cell->padding) } });
            text_layer_set_background_color(cell->center_layer, GColorBlack);   
        }
    }
}

SquareCell * square_grid_cell_create(SquareCellState state, GRect rect, uint16_t padding) {
    SquareCell * cell = malloc(sizeof(SquareCell));

    if (cell) {
        cell->center_layer = NULL;
        cell->state = state;
        cell->rect = rect;
        cell->padding = padding;

        square_grid_cell_add_layers(cell);
    } else {

    }

    return cell;
}

void square_grid_cell_destroy(SquareCell * cell) {
    if (cell) {
        if (cell->center_layer) {
            text_layer_destroy(cell->center_layer);
            cell->center_layer = NULL;
        }
        if (cell->top_layer) {
            text_layer_destroy(cell->top_layer);
            cell->top_layer = NULL;
        }
        if (cell->bottom_layer) {
            text_layer_destroy(cell->bottom_layer);
            cell->bottom_layer = NULL;
        }
        if (cell->left_layer) {
            text_layer_destroy(cell->left_layer);
            cell->left_layer = NULL;
        }
        if (cell->right_layer) {
            text_layer_destroy(cell->right_layer);
            cell->right_layer = NULL;
        }
        free(cell);
    }
}

void square_grid_cell_set_state(SquareCell * cell, SquareCellState state) {
    if (cell) {
        cell->state = state;

        GColor color = square_grid_cell_get_center_color(cell);
        text_layer_set_background_color(cell->center_layer, color);
        
        color = square_grid_cell_get_outer_color(cell);
        text_layer_set_background_color(cell->top_layer, color);
        text_layer_set_background_color(cell->bottom_layer, color);
        text_layer_set_background_color(cell->left_layer, color);
        text_layer_set_background_color(cell->right_layer, color);
    }
}

void square_grid_cell_add_parent(SquareCell * cell, Layer * parent) {
    if (cell && parent) {
        if (cell->center_layer) layer_add_child(parent, text_layer_get_layer(cell->center_layer));
        if (cell->top_layer)    layer_add_child(parent, text_layer_get_layer(cell->top_layer));
        if (cell->bottom_layer) layer_add_child(parent, text_layer_get_layer(cell->bottom_layer));
        if (cell->left_layer)   layer_add_child(parent, text_layer_get_layer(cell->left_layer));
        if (cell->right_layer)  layer_add_child(parent, text_layer_get_layer(cell->right_layer));
    }
}
