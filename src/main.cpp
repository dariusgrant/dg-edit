#include "TextEditor.hpp"

int main(int argc, char *argv[])
{
    dg::TextEditor editor( 1000, 1000 );

    if ( argc > 1 ) {
        dg::TextEditor::load_file( &editor, argv[1] );
    }

    editor.show();

    return Fl::run();
}
