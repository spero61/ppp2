// Define a Group to be a container of Shapes with suitable operations applied to the various members of the Group.
// Hint: Vector_ref. Use a Group to define a checkers (draughts) board where pieces can be moved under program control.

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

class Group : public Shape {
   public:
    Group(int size_arg) : size{size_arg} {}
    void add_tile(Shape& shape) { v_tiles.push_back(shape); }
    void add_piece(Shape& shape) { v_pieces.push_back(shape); }
    void init_tiles(Vector_ref<Graph_lib::Rectangle>& tiles);
    void init_pieces(Vector_ref<Graph_lib::Circle>& pieces);

    void draw_lines() const override;
    void move_piece(int index, int move_x, int move_y);

   private:
    Vector_ref<Shape> v_tiles;
    Vector_ref<Shape> v_pieces;
    int size;
};

void Group::draw_lines() const {
    for (int i = 0; i < v_tiles.size(); ++i) {
        v_tiles[i].draw();
    }
    for (int i = 0; i < v_pieces.size(); ++i) {
        v_pieces[i].draw();
    }
}

void Group::move_piece(int index, int move_x, int move_y) {
    int dx = move_x * size;
    int dy = move_y * size;
    v_pieces[index].move(dx, dy);
}

void Group::init_tiles(Vector_ref<Graph_lib::Rectangle>& tiles) {
    // initialize tiles on checker board
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            tiles.push_back(new Graph_lib::Rectangle{Point{j * size, i * size}, size, size});
        }
    }

    for (int i = 0; i < tiles.size(); ++i) {
        int index{i};
        if ((i / 8) % 2 == 0) index += 1;  // change the first color of the tile in turn, line by line

        if (index % 2 == 0)
            tiles[i].set_fill_color(Color{16 * 7 + 1});  // dark tiles
        else
            tiles[i].set_fill_color(Color{16 * 13 + 6});  // bright tiles
        add_tile(tiles[i]);
    }
}

void Group::init_pieces(Vector_ref<Graph_lib::Circle>& pieces) {
    const int r{static_cast<int>(size / 2)};
    // initialize pieces on checker board
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            // black pieces
            if (i == 1 && j % 2 == 0)
                pieces.push_back(new Graph_lib::Circle{Point{j * size + r, i * size + r}, static_cast<int>(r * 0.8)});  // circle's diameter is 80% of the tile's side length
            if (i == 0 || i == 2) {
                if (j % 2 != 0)
                    pieces.push_back(new Graph_lib::Circle{Point{j * size + r, i * size + r}, static_cast<int>(r * 0.8)});
            }

            //white pieces
            if (i == 6 && j % 2 != 0)
                pieces.push_back(new Graph_lib::Circle{Point{j * size + r, i * size + r}, static_cast<int>(r * 0.8)});
            if (i == 5 || i == 7) {
                if (j % 2 == 0)
                    pieces.push_back(new Graph_lib::Circle{Point{j * size + r, i * size + r}, static_cast<int>(r * 0.8)});
            }
        }
    }

    for (int i = 0; i < pieces.size(); ++i) {
        pieces[i].set_color(Color::invisible);

        if (i < pieces.size() / 2)
            pieces[i].set_fill_color(Color{16 * 13 + 2});  // pink
        else
            pieces[i].set_fill_color(Color{16 * 15 + 2});  // violet

        add_piece(pieces[i]);
    }
}

int main() {
    try {
        Point tl(100, 100);  // top-left
        Simple_window win(tl, 830, 830, "Checker board using Group");
        win.wait_for_button();

        constexpr int size{100};
        Group checker{size};
        win.attach(checker);

        // initialize checker----------------------------------

        Vector_ref<Graph_lib::Rectangle> tiles;
        checker.init_tiles(tiles);
        win.wait_for_button();

        Vector_ref<Graph_lib::Circle> pieces;
        checker.init_pieces(pieces);

        // -----------------------------------------------------

        // draw x axis and y axis for legend--------------------
        Axis xa{Axis::x, Point{0, size * 8 + 20}, size * 8, 8};
        xa.set_color(Color::dark_blue);
        win.attach(xa);

        Axis ya{Axis::y, Point{size * 8 + 20, size * 8}, size * 8, 8};
        ya.set_color(Color::dark_blue);  // choose a color
        win.attach(ya);

        int ascii_one{49};  // ASCII decimal 49 is equal to '1'
        Vector_ref<Mark> legend_x;
        for (int i = 0; i < 8; ++i) {
            legend_x.push_back(new Mark{Point{50 + i * size, size * 8 + 10}, static_cast<char>(ascii_one++)});
        }
        ascii_one = 49;
        for (int i = 0; i < legend_x.size(); ++i) {
            win.attach(legend_x[i]);
        }

        Vector_ref<Mark> legend_y;
        for (int i = 0; i < 8; ++i) {
            legend_x.push_back(new Mark{Point{size * 8 + 10, 50 + i * size}, static_cast<char>(ascii_one++)});
        }
        ascii_one = 49;
        for (int i = 0; i < legend_x.size(); ++i) {
            win.attach(legend_x[i]);
        }
        win.wait_for_button();
        // -----------------------------------------------------

        // move a piece
        //
        // note: For simplicity I did not make a table so that
        // a user can pick a piece to move by notating (x, y) coordinate.
        // Instead, I used pieces[index] to choose a specific piece to move.
        // Also I have not implemented when pieces are duplicated in the same tile.

        // pink pieces(12pcs): pieces[0] to pieces[11]
        // - from top left pink piece(2,1) to the right then change the line.
        // violet pieces(12pcs): pieces[12] to pieces[23]
        // - from top left violet piece(1,6) to the right then change the line.

        checker.move_piece(10, 1, 1);
        win.wait_for_button();

        checker.move_piece(13, -1, -1);
        win.wait_for_button();

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}
