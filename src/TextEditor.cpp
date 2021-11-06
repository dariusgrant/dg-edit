#include "TextEditor.hpp"
#include <FL/fl_ask.h>
#include <FL/Fl_File_Chooser.h>
#include <algorithm>

namespace dg {
    TextEditor::TextEditor(int x, int y, std::string t)
        : Fl_Double_Window( x, y, t.data() )
        , filename( "" )
        , is_modified( false )
        , is_loading( false )
        , editor( new Fl_Text_Editor(0, 30, x, y) )
        , text_buffer( new Fl_Text_Buffer() )
        , menu_bar( new Fl_Menu_Bar( 0, 0, x, 30) )
    {
        editor->buffer( text_buffer.get() );
        editor->textfont( FL_COURIER );

        text_buffer->add_modify_callback( changed_cb, this );

        menu_bar->add( "File", 0, nullptr, nullptr, FL_SUBMENU );
        menu_bar->add( "File/Save", 0, static_cast<Fl_Callback*>( save_cb ), this );
        menu_bar->add( "File/Save As", 0, static_cast<Fl_Callback*>( saveas_cb ), this );
    }

    void TextEditor::changed_cb(int, int n_inserted, int n_deleted, int, const char *, void *w) {
        TextEditor* win = static_cast<TextEditor*>( w );
        if( win->is_modified ) return;

        win->is_modified = true;

        if( !win->filename.empty() ) {
            set_title_on_modify( win );
        }
    }

    void TextEditor::save_cb(Fl_Widget *, void *w){
        TextEditor* win = static_cast<TextEditor*>( w );
        if( win->filename.empty() ) {
            printf( "No file name -> Calling: saveas_cb\n" );
            saveas_cb( nullptr, w );
            return;
        }

        save_file( *win );
    }

    void TextEditor::saveas_cb(Fl_Widget *, void *w) {
        TextEditor* win = static_cast<TextEditor*>( w );
        const char* f = fl_file_chooser( "Save File As:", ".txt", win->filename.data() );

        if( f == nullptr ) return;

        win->filename = f;
        save_file( *win );
    }

    bool TextEditor::should_save(TextEditor &w){
        if( !w.is_modified ) return false;

        int option = fl_choice( "The current file has not been saved.\n" \
                                "Would you like to save it now?",
                                "Save", "Cancel", "Discard" );

        switch( option ) {
        case 0:
            //save_cb( nullptr, w );
            printf("Saving\n");
            save_file( w );
            return true;
        default:
            return false;
        }
    }

    void TextEditor::save_file(TextEditor &w) {
        if( w.text_buffer->savefile( w.filename.data() ) != 0 ) {
            fl_alert( "Error writing to file \'%s\':\n%s", w.filename.data(), strerror( errno ) );
        } else {
            auto i = w.filename.find_last_of( '/' );
            std::string sub = w.filename.substr( i + 1 );
            w.label( sub.data() );
            w.is_modified = false;
        }
    }

    void TextEditor::load_file(TextEditor *w, const std::string s) {
        w->is_loading = true;

        auto r = w->text_buffer->loadfile( s.data() );
        if ( r != 0 ) {
            fl_alert( "Error reading from file \'%s\':\n%s.", w->filename.data(), strerror( errno ) );
        }

        w->filename = s.data();
        w->label( w->filename.data() );
        w->is_loading = false;

    }

    void TextEditor::set_title_on_modify(TextEditor *w) {
        if( w->is_modified ) {
            auto i = w->filename.find_last_of( '/' );
            std::string sub = w->filename.substr( i + 1 );
            w->label( ( sub + " (modified)" ).data() );
        }
    }
}
