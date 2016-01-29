#include "square_grid_row.h"

static inline GRect square_grid_row_get_cell_rect(SquareRow * row, uint8_t i) {
    return  GRect(  ((row->rect.size.w - (2 * row->padding)) * i / ROW_CELL_COUNT) + row->padding,
                    (row->rect.origin.y + row->padding),
                    ((row->rect.size.w - (2 * row->padding)) / ROW_CELL_COUNT),
                    (row->rect.size.h - (2 * row->padding)));
}

static void square_grid_row_add_padding(SquareRow * row) {
    if (row) {
        if (!row->top_padding) {
            row->top_padding = text_layer_create((GRect) {
                .origin = (GPoint) { .x = row->padding, 
                                     .y = row->rect.origin.y },
                .size   = (GSize)  { .h = row->padding,
                                     .w = row->rect.size.w - (2 * row->padding) } });
            text_layer_set_background_color(row->top_padding, GColorBlack);
        }
        if (!row->bottom_padding) {
            row->bottom_padding = text_layer_create((GRect) {
                .origin = (GPoint) { .x = row->padding,
                                     .y = row->rect.origin.y + row->rect.size.h - row->padding },
                .size   = (GSize)  { .h = row->padding,
                                     .w = row->rect.size.w - (2 * row->padding) } });
            text_layer_set_background_color(row->bottom_padding, GColorBlack);
        }
        if (!row->left_padding) {
            row->left_padding = text_layer_create((GRect) {
                .origin = (GPoint) { .x = 0,                    .y = row->rect.origin.y },
                .size   = (GSize)  { .h = row->rect.size.h,     .w = row->padding } });
            text_layer_set_background_color(row->left_padding, GColorBlack);
        }
        if (!row->right_padding) {
            row->right_padding = text_layer_create((GRect) {
                .origin = (GPoint) { .x = row->rect.size.w - row->padding,
                                     .y = row->rect.origin.y },
                .size   = (GSize)  { .h = row->rect.size.h,
                                     .w = row->padding } });
            text_layer_set_background_color(row->right_padding, GColorBlack);
        }
    }
}

SquareRow * square_grid_row_create(uint8_t value, GRect rect, uint8_t padding) {
    SquareRow * row = malloc(sizeof(SquareRow));

    if (row) {
        row->top_padding = NULL;
        row->bottom_padding = NULL;
        row->left_padding = NULL;
        row->right_padding = NULL;
        row->rect = rect;
        row->padding = padding;

        for (uint8_t i = 0; i < ROW_CELL_COUNT && i < MAX_UINT8; i++) {
            row->cells[i] = square_grid_cell_create(BLACK, square_grid_row_get_cell_rect(row, i), GRID_CELL_EDGE);
        }

        square_grid_row_add_padding(row);
        square_grid_row_set_value(row, value);
    } else {

    }

    return row;
}

void square_grid_row_destroy(SquareRow * row) {
    if (row) {
        for (uint8_t i = 0; i < ROW_CELL_COUNT && i < MAX_UINT8; i++) if (row->cells[i]) {
            square_grid_cell_destroy(row->cells[i]);
        }
        if (row->top_padding)    text_layer_destroy(row->top_padding);
        if (row->bottom_padding) text_layer_destroy(row->bottom_padding);
        if (row->left_padding)   text_layer_destroy(row->left_padding);
        if (row->right_padding)  text_layer_destroy(row->right_padding);
        free(row);
    }
}

static inline SquareCellState square_grid_row_convert_state(bool b) {
    if (b) {
        return WHITE;
    } else {
        return BLACK;
    }
}

void square_grid_row_set_value(SquareRow * row, uint8_t value) {
    if (row) {
        row->value = value;
        uint8_t mask = BIT3;
        for (uint8_t i = 0; i < ROW_CELL_COUNT && i < MAX_UINT8; i++) {
            square_grid_cell_set_state(row->cells[i],
                square_grid_row_convert_state(mask & value));
            mask = mask >> 1;
        }
    }
}

void square_grid_row_add_parent(SquareRow * row, Layer * parent) {
    if (row && parent) {
        for (uint8_t i = 0; i < ROW_CELL_COUNT && i < MAX_UINT8; i++) if (row->cells[i]) {
            square_grid_cell_add_parent(row->cells[i], parent);
        }
        if (row->top_padding)    layer_add_child(parent, text_layer_get_layer(row->top_padding));
        if (row->bottom_padding) layer_add_child(parent, text_layer_get_layer(row->bottom_padding));
        if (row->left_padding)   layer_add_child(parent, text_layer_get_layer(row->left_padding));
        if (row->right_padding)  layer_add_child(parent, text_layer_get_layer(row->right_padding));
    }
}
