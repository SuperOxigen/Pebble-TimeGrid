# Pebble-TimeGrid
A Pebble Watch Face

## Design

Displays the pebble watch system time as a grid of colored squares encoded through binary.

Ex 08:37

|:black_square_button:|:black_square_button:|:black_square_button:|:black_square_button:| `0 = 0000`

|:white_square_button:|:black_square_button:|:black_square_button:|:black_square_button:| `8 = 1000`

|:black_square_button:|:black_square_button:|:white_square_button:|:white_square_button:| `3 = 0011`

|:black_square_button:|:white_square_button:|:white_square_button:|:white_square_button:| `7 = 0111`

## API

The actual display can be modified for other uses.

1. Creating __SquareGrid__

`SquareGrid * square_grid_create(void)`

2. Destroying __SquareGrid__

`void square_grid_destroy(SquareGrid * grid)`

3. Add __SquareGrid__ to a layer

`void square_grid_add_parent(SquareGrid * grid, Layer * parent)`

4. Setting __SquareGrid__'s cell values

`void square_grid_set_values(SquareGrid * grid, unit8_t (*)[GRID_ROW_COUNT])`

For now, dimensions are not modifiable through the API.

### API Example

Initialization

```
static void init(void) {
    window = window_create();
    // Other intialization code

    grid = square_grid_create(); // Create new grid
    square_grid_add_parent(grid, window_get_root_layer(window)); // Add it to main display
}
```

Set values

```
static void foo(void) {
    uint8_t checker_values = { 3, 10, 3, 10 }; // Checkers board appearance
    square_grid_set_values(grid, &checker_values);
}
```

Deinitialization

```
static void deinit(void) {
    square_grid_destroy(grid); // Best to call first
    window_destroy(window);
}
```
