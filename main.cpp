#include "main.hpp"

int main()
{
    px.clrscr();

    bool gIsGameOver = false;

    while( !gIsGameOver )
    {

        px.text( "Welcome to Dice, the collection of dice games." );
        px.nl(1);
        px.text( "\t1. Bones - Ones and Fives");
        px.text( "\t2. Craps - Sevens and Elevens");
        px.text( "\t3. Hight or Low - 1 to 50 4 chances");
        px.nl(1);
        px.getI( gInt, "Please make a choice either by number: " );

        switch( gInt )
        {
            case 1:
                Bones();
            break;

            default:
                px.text("Invalid entry");
        }
    }
    return 0;
}

void Bones()
{
    gString.clear();
    bool gIsNotDone = false;

    while( gIsNotDone )
    {
        px.getS( gString, "Welcome to Bones. Would you like to provide a name? Leave blank if not." );

        px.text( gString, false);
        px.text( "\tIs this your name? ");
        px.pause();
        gIsNotDone = true;
    }

}
