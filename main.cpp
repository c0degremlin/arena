#include "main.hpp"

int main()
{
    px.clrscr();
    px.text( "Welcome. " );
    px.number( 0, false);
    px.text( " ", false);
    px.shortNumber( -32766, false );
    px.pause("Paused", "Paused duo");
    return 0;
}
