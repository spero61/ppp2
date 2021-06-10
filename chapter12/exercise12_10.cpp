#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

int main() {
    try {
        Point tl{100, 100};
        Simple_window win{tl, 800, 600, "adjust the window size then click next"};
        win.wait_for_button();

        const int x_fltk_headers{300};
        const int y_fltk_headers{20};
        const int width_fltk_headers{110};
        const int height_fltk_headers{45};

        Graph_lib::Rectangle fltk_headers_01(Point(x_fltk_headers, y_fltk_headers), width_fltk_headers, height_fltk_headers);
        fltk_headers_01.set_fill_color(Color::yellow);
        win.attach(fltk_headers_01);

        Graph_lib::Rectangle fltk_headers_02(Point(x_fltk_headers + 7, y_fltk_headers + 7), width_fltk_headers, height_fltk_headers);
        fltk_headers_02.set_fill_color(Color::yellow);
        win.attach(fltk_headers_02);

        Graph_lib::Rectangle fltk_headers_03(Point(x_fltk_headers + 14, y_fltk_headers + 14), width_fltk_headers, height_fltk_headers);
        fltk_headers_03.set_fill_color(Color::yellow);
        win.attach(fltk_headers_03);

        Text fltk_headers_text(Point(x_fltk_headers + 22, y_fltk_headers + 33), "FLTK headers");
        win.attach(fltk_headers_text);

        const int x_fltk_code{500};
        const int y_fltk_code{50};
        const int width_fltk_code{90};
        const int height_fltk_code{45};

        Graph_lib::Rectangle fltk_code_01(Point(x_fltk_code, y_fltk_code), width_fltk_code, height_fltk_code);
        fltk_code_01.set_fill_color(Color::yellow);
        win.attach(fltk_code_01);

        Graph_lib::Rectangle fltk_code_02(Point(x_fltk_code + 7, y_fltk_code + 7), width_fltk_code, height_fltk_code);
        fltk_code_02.set_fill_color(Color::yellow);
        win.attach(fltk_code_02);

        Graph_lib::Rectangle fltk_code_03(Point(x_fltk_code + 14, y_fltk_code + 14), width_fltk_code, height_fltk_code);
        fltk_code_03.set_fill_color(Color::yellow);
        win.attach(fltk_code_03);

        Text fltk_code_text(Point(x_fltk_code + 22, y_fltk_code + 33), "FLTK code");
        win.attach(fltk_code_text);

        Graph_lib::Open_polyline fltk_code_to_headers;
        fltk_code_to_headers.add(Point(x_fltk_code, y_fltk_code + height_fltk_code / 2));
        fltk_code_to_headers.add(Point(x_fltk_headers + 125, y_fltk_headers + 30));
        win.attach(fltk_code_to_headers);

        Graph_lib::Polygon fltk_code_to_headers_arrow;
        fltk_code_to_headers_arrow.add(Point(x_fltk_headers + 123, y_fltk_headers + 28));
        fltk_code_to_headers_arrow.add(Point(x_fltk_headers + 123 + 3, y_fltk_headers + 28 + 5));
        fltk_code_to_headers_arrow.add(Point(x_fltk_headers + 123 + 6, y_fltk_headers + 28));
        fltk_code_to_headers_arrow.set_fill_color(Color::black);
        win.attach(fltk_code_to_headers_arrow);

        const int x_window_h{290};
        const int y_window_h{170};
        const int width_window_h{160};
        const int height_window_h{60};

        Graph_lib::Rectangle window_h(Point(x_window_h, y_window_h), width_window_h, height_window_h);
        window_h.set_fill_color(Color::yellow);
        win.attach(window_h);

        Text window_h_text01(Point(x_window_h, y_window_h - 7), "Window.h:");
        window_h_text01.set_font(Font::helvetica_bold);
        win.attach(window_h_text01);

        Text window_h_text02(Point(x_window_h + 7, y_window_h + 15), "// window interface:");
        win.attach(window_h_text02);

        Text window_h_text03(Point(x_window_h + 7, y_window_h + 30), "class Window{...};");
        window_h_text03.set_font(Font::helvetica_bold);
        win.attach(window_h_text03);

        Text window_h_text04(Point(x_window_h + 7, y_window_h + 45), "...");
        win.attach(window_h_text04);

        // straight line to upward
        Graph_lib::Open_polyline window_h_to_fltk_headers;
        window_h_to_fltk_headers.add(Point(x_window_h + width_window_h / 2, y_window_h));
        window_h_to_fltk_headers.add(Point(x_window_h + width_window_h / 2, y_fltk_headers + 60));
        win.attach(window_h_to_fltk_headers);

        Graph_lib::Polygon window_h_to_fltk_headers_arrow;
        window_h_to_fltk_headers_arrow.add(Point(x_window_h + width_window_h / 2, y_fltk_headers + 60));
        window_h_to_fltk_headers_arrow.add(Point(x_window_h + width_window_h / 2 - 3, y_fltk_headers + 60 + 6));
        window_h_to_fltk_headers_arrow.add(Point(x_window_h + width_window_h / 2 + 3, y_fltk_headers + 60 + 6));
        window_h_to_fltk_headers_arrow.set_fill_color(Color::black);
        win.attach(window_h_to_fltk_headers_arrow);

        const int x_graph_h{80};
        const int y_graph_h{220};
        const int width_graph_h{170};
        const int height_graph_h{60};

        Graph_lib::Rectangle graph_h(Point(x_graph_h, y_graph_h), width_graph_h, height_graph_h);
        graph_h.set_fill_color(Color::yellow);
        win.attach(graph_h);

        Text graph_h_text01(Point(x_graph_h, y_graph_h - 7), "Graph.h:");
        graph_h_text01.set_font(Font::helvetica_bold);
        win.attach(graph_h_text01);

        Text graph_h_text02(Point(x_graph_h + 7, y_graph_h + 15), "// graphing interface:");
        win.attach(graph_h_text02);

        Text graph_h_text03(Point(x_graph_h + 7, y_graph_h + 30), "struct Shape{...};");
        graph_h_text03.set_font(Font::helvetica_bold);
        win.attach(graph_h_text03);

        Text graph_h_text04(Point(x_graph_h + 7, y_graph_h + 45), "...");
        win.attach(graph_h_text04);

        const int x_point_h{80};
        const int y_point_h{100};
        const int width_point_h{165};
        const int height_point_h{30};

        Graph_lib::Rectangle point_h(Point(x_point_h, y_point_h), width_point_h, height_point_h);
        point_h.set_fill_color(Color::yellow);
        win.attach(point_h);

        Text point_h_text01(Point(x_point_h, y_point_h - 7), "Point.h:");
        point_h_text01.set_font(Font::helvetica_bold);
        win.attach(point_h_text01);

        Text point_h_text02(Point(x_point_h + 7, y_point_h + 18), "struct Point{...};");
        point_h_text02.set_font(Font::helvetica_bold);
        win.attach(point_h_text02);

        // straight line to upward window_h_to_fltk_headers
        Graph_lib::Open_polyline graph_h_to_point_h;
        graph_h_to_point_h.add(Point(x_graph_h + width_graph_h / 2, y_graph_h));
        graph_h_to_point_h.add(Point(x_graph_h + width_graph_h / 2, y_point_h + height_point_h));
        win.attach(graph_h_to_point_h);

        Graph_lib::Polygon graph_h_to_point_h_arrow;
        graph_h_to_point_h_arrow.add(Point(x_graph_h + width_graph_h / 2, y_point_h + height_point_h));
        graph_h_to_point_h_arrow.add(Point(x_graph_h + width_graph_h / 2 - 3, y_point_h + height_point_h + 6));
        graph_h_to_point_h_arrow.add(Point(x_graph_h + width_graph_h / 2 + 3, y_point_h + height_point_h + 6));
        graph_h_to_point_h_arrow.set_fill_color(Color::black);
        win.attach(graph_h_to_point_h_arrow);

        Graph_lib::Open_polyline graph_h_to_fltk_headers;
        graph_h_to_point_h.add(Point(x_graph_h + width_graph_h / 2, y_graph_h));
        graph_h_to_point_h.add(Point(x_fltk_headers + 15, y_fltk_headers + height_fltk_headers + 15));
        win.attach(graph_h_to_point_h);

        Graph_lib::Polygon graph_h_to_fltk_headers_arrow;
        graph_h_to_fltk_headers_arrow.add(Point(x_fltk_headers + 15, y_fltk_headers + height_fltk_headers + 15));
        graph_h_to_fltk_headers_arrow.add(Point(x_fltk_headers + 15 - 6, y_fltk_headers + height_fltk_headers + 15 + 2));
        graph_h_to_fltk_headers_arrow.add(Point(x_fltk_headers + 15 + 1, y_fltk_headers + height_fltk_headers + 15 + 5));
        graph_h_to_fltk_headers_arrow.set_fill_color(Color::black);
        win.attach(graph_h_to_fltk_headers_arrow);

        Graph_lib::Open_polyline window_h_to_point_h;
        window_h_to_point_h.add(Point(x_window_h + 15, y_window_h));
        window_h_to_point_h.add(Point(x_point_h + width_point_h - 30, y_point_h + height_point_h));
        win.attach(window_h_to_point_h);

        Graph_lib::Polygon window_h_to_point_h_arrow;
        window_h_to_point_h_arrow.add(Point(x_point_h + width_point_h - 30, y_point_h + height_point_h));
        window_h_to_point_h_arrow.add(Point(x_point_h + width_point_h - 30 + 3, y_point_h + height_point_h + 5));
        window_h_to_point_h_arrow.add(Point(x_point_h + width_point_h - 30 + 6, y_point_h + height_point_h));
        window_h_to_point_h_arrow.set_fill_color(Color::black);
        win.attach(window_h_to_point_h_arrow);

        win.set_label("Ch12 Exercise10");
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