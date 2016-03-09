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

static inline GRect square_grid_cell_get_top_rect(SquareCell * cell) {
    return (GRect) {
        .origin = (GPoint) { .x = cell->rect.origin.x, .y = cell->rect.origin.y },
        .size   = (GSize)  { .h = cell->padding,       .w = cell->rect.size.w } };
}

static inline GRect square_grid_cell_get_bottom_rect(SquareCell * cell) {
    return (GRect) {
        .origin = (GPoint) { .x = cell->rect.origin.x,
                             .y = cell->rect.origin.y + cell->rect.size.h - cell->padding },
        .size   = (GSize)  { .h = cell->padding,
                             .w = cell->rect.size.w } };
}

static inline GRect square_grid_cell_get_left_rect(SquareCell * cell) {
    return (GRect) {
        .origin = (GPoint) { .x = cell->rect.origin.x,
                             .y = cell->rect.origin.y + cell->padding },
        .size   = (GSize)  { .h = cell->rect.size.h - (2 * cell->padding),
                             .w = cell->padding } };
}

static inline GRect square_grid_cell_get_right_rect(SquareCell * cell) {
    return (GRect) {
        .origin = (GPoint) { .x = cell->rect.origin.x + cell->rect.size.w - cell->padding,
                             .y = cell->rect.origin.y + cell->padding },
        .size   = (GSize)  { .h = cell->rect.size.h - (2 * cell->padding),
                             .w = cell->padding } };
}

static inline GRect square_grid_cell_get_center_rect(SquareCell * cell) {
    return (GRect) {
        .origin = (GPoint) { .x = cell->rect.origin.x + cell->padding,
                             .y = cell->rect.origin.y + cell->padding },
        .size   = (GSize)  { .h = cell->rect.size.h - (2 * cell->padding),
                             .w = cell->rect.size.w - (2 * cell->padding) } };
}

static void square_grid_cell_add_layers(SquareCell * cell) {
    if (cell) {
        if (!cell->top_layer) {
            cell->top_layer = text_layer_create(square_grid_cell_get_top_rect(cell));
            text_layer_set_background_color(cell->top_layer, GColorBlack);
        }
        if (!cell->bottom_layer) {
            cell->bottom_layer = text_layer_create(square_grid_cell_get_bottom_rect(cell));
            text_layer_set_background_color(cell->bottom_layer, GColorBlack);
        }
        if (!cell->left_layer) {
            cell->left_layer = text_layer_create(square_grid_cell_get_left_rect(cell));
            text_layer_set_background_color(cell->left_layer, GColorBlack);
        }
        if (!cell->right_layer) {
            cell->right_layer = text_layer_create(square_grid_cell_get_right_rect(cell));
            text_layer_set_background_color(cell->right_layer, GColorBlack);
        }
        if (!cell->center_layer) {
            cell->center_layer = text_layer_create(square_grid_cell_get_center_rect(cell));
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

#ifdef PBL_PLATFORM_APLITE
static void square_grid_cell_animation_started(Animation * animation, void * data) {

}

static void square_grid_cell_animation_stopped(Animation * animation, bool finished, void * data) {
    if (data) {
        property_animation_destroy((PropertyAnimation *) data);
    }
}

static AnimationHandlers cell_anim_handler = {
    .started = (AnimationStartedHandler) square_grid_cell_animation_started,
    .stopped = (AnimationStoppedHandler) square_grid_cell_animation_stopped
};
#endif

static void square_grid_cell_set_animation(SquareCell * cell, uint16_t padding) {
    if (cell) {
        GRect top_to_rect, top_from_rect, bottom_to_rect, bottom_from_rect,
              left_to_rect, left_from_rect, right_to_rect, right_from_rect,
              center_to_rect, center_from_rect;
        Animation * center_anim, * top_anim, * bottom_anim, * right_anim, * left_anim;
        PropertyAnimation * center_prop_anim, * top_prop_anim, * bottom_prop_anim, * right_prop_anim, * left_prop_anim;

        center_from_rect = square_grid_cell_get_center_rect(cell);
        top_from_rect    = square_grid_cell_get_top_rect(cell);
        bottom_from_rect = square_grid_cell_get_bottom_rect(cell);
        right_from_rect  = square_grid_cell_get_right_rect(cell);
        left_from_rect   = square_grid_cell_get_left_rect(cell);

        cell->padding = padding;

        center_to_rect = square_grid_cell_get_center_rect(cell);
        top_to_rect    = square_grid_cell_get_top_rect(cell);
        bottom_to_rect = square_grid_cell_get_bottom_rect(cell);
        right_to_rect  = square_grid_cell_get_right_rect(cell);
        left_to_rect   = square_grid_cell_get_left_rect(cell);

        center_prop_anim = property_animation_create_layer_frame(
            text_layer_get_layer(cell->center_layer),
            &center_from_rect, &center_to_rect);
        top_prop_anim = property_animation_create_layer_frame(
            text_layer_get_layer(cell->top_layer),
            &top_from_rect, &top_to_rect);
        bottom_prop_anim = property_animation_create_layer_frame(
            text_layer_get_layer(cell->bottom_layer),
            &bottom_from_rect, &bottom_to_rect);
        right_prop_anim = property_animation_create_layer_frame(
            text_layer_get_layer(cell->right_layer),
            &right_from_rect, &right_to_rect);
        left_prop_anim = property_animation_create_layer_frame(
            text_layer_get_layer(cell->left_layer),
            &left_from_rect, &left_to_rect);

        center_anim = property_animation_get_animation(center_prop_anim);
        top_anim = property_animation_get_animation(top_prop_anim);
        bottom_anim = property_animation_get_animation(bottom_prop_anim);
        right_anim = property_animation_get_animation(right_prop_anim);
        left_anim = property_animation_get_animation(left_prop_anim);

        animation_set_duration(center_anim, PADDING_DELAY);
        animation_set_duration(top_anim, PADDING_DELAY);
        animation_set_duration(bottom_anim, PADDING_DELAY);
        animation_set_duration(right_anim, PADDING_DELAY);
        animation_set_duration(left_anim, PADDING_DELAY);

#ifdef PBL_PLATFORM_APLITE
        // Used for garbage collection of prop animations

        animation_set_handlers(center_anim, cell_anim_handler, center_prop_anim);
        animation_set_handlers(top_anim, cell_anim_handler, top_prop_anim);
        animation_set_handlers(bottom_anim, cell_anim_handler, bottom_prop_anim);
        animation_set_handlers(right_anim, cell_anim_handler, right_prop_anim);
        animation_set_handlers(left_anim, cell_anim_handler, left_prop_anim);

#endif

        animation_schedule(center_anim);
        animation_schedule(top_anim);
        animation_schedule(bottom_anim);
        animation_schedule(right_anim);
        animation_schedule(left_anim);
    }
}

void square_grid_cell_set_padding(SquareCell * cell, uint16_t padding) {
    if (cell && padding < cell->rect.size.w / 2 && padding < cell ->rect.size.h / 2) {
        square_grid_cell_set_animation(cell, padding);
    }
}
