#include "square_grid.h"

static inline GRect square_grid_get_row_rect(uint8_t i) {
    return  (GRect) {
        .origin = (GPoint) { .x = 0,
                             .y = i * MAX_HEIGHT / GRID_ROW_COUNT },
        .size   = (GSize)  { .h = MAX_HEIGHT / GRID_ROW_COUNT,
                             .w = MAX_WIDTH } };
}

SquareGrid * square_grid_create() {
    SquareGrid * grid = malloc(sizeof(SquareGrid));
    if (grid) {
        for (uint8_t i = 0; i < GRID_ROW_COUNT && i < MAX_UINT8; i++) {
            grid->rows[i] = square_grid_row_create(0, square_grid_get_row_rect(i), ROW_PADDING);
            grid->values[i] = 0;
        }
    }
    return grid;
}

void square_grid_destroy(SquareGrid * grid) {
    if (grid) {
        for (uint8_t i = 0; i < GRID_ROW_COUNT && i < MAX_UINT8; i++) if (grid->rows[i]) {
            square_grid_row_destroy(grid->rows[i]);
        }
        free(grid);
    }
}

void square_grid_set_values(SquareGrid * grid, uint8_t (*values)[GRID_ROW_COUNT]) {
    if (grid && values) {
        for (uint8_t i = 0; i < GRID_ROW_COUNT && i < MAX_UINT8; i++) if (grid->rows[i]) {
            square_grid_row_set_value(grid->rows[i], (*values)[i]);
        }
    }
}

void square_grid_add_parent(SquareGrid * grid, Layer * parent) {
    if (grid && parent) {
        for (uint8_t i = 0; i < GRID_ROW_COUNT && i < MAX_UINT8; i++) if (grid->rows[i]) {
            square_grid_row_add_parent(grid->rows[i], parent);
        }
    }
}

void square_grid_set_cell_padding(SquareGrid * grid, uint8_t x, uint8_t y, uint16_t padding) {
    if (grid && y < GRID_ROW_COUNT) {
        square_grid_row_set_cell_padding(grid->rows[y], x, padding);
    }
}

void square_grid_reset_cell_padding(SquareGrid * grid, uint8_t x, uint8_t y) {
    square_grid_set_cell_padding(grid, x, y, GRID_CELL_EDGE);
}
