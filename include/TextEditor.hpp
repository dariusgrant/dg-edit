#pragma once

#include <FL/Fl.h>
#include <FL/Fl_Double_Window.h>
#include <FL/Fl_Text_Editor.h>
#include <FL/Fl_Menu_Bar.h>
#include <memory>
#include <string>

namespace dg {


class TextEditor : public Fl_Double_Window {
public:
    std::string filename;
    bool is_modified;
    bool is_loading;
    std::unique_ptr<Fl_Text_Editor> editor;
    std::unique_ptr<Fl_Text_Buffer> text_buffer;
    std::unique_ptr<Fl_Menu_Bar> menu_bar;

public:
    TextEditor( int x, int y, std::string t = "Untitled" );

    static void changed_cb( int, int n_inserted, int n_deleted, int, const char*, void* w );

    static void save_cb( Fl_Widget*, void* w );

    static void saveas_cb( Fl_Widget*, void* w );

    static bool should_save( TextEditor& w );

    static void save_file( TextEditor& w );

    static void load_file( TextEditor* w, const std::string s );

    static void set_title_on_modify( TextEditor* w );

};}
