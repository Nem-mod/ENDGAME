#include "header.h"

int A3(int randAy, int Ay3, int Ax3 , int *Ay3r) {
    switch(randAy) {
        case 0:
            mvprintw(Ay3  , Ax3, "        __,---//////////,        .///");
            mvprintw(Ay3 + 1 , Ax3, "     __  ) ) ) ) ) )''////      /////");
            mvprintw(Ay3 + 2 , Ax3, " _,-' ))'. ) ) ) ) ) ) ) ) )'-. //////");
            mvprintw(Ay3 + 3 , Ax3, "/  ()_)))))\\  ) ) ) ) ) ) ) ) )////////");
            mvprintw(Ay3 + 4 , Ax3, "\\______ )))))) ) ) ) ) ) ) ) )\\\\\\\\\\\\\\\\");
            mvprintw(Ay3 + 5 , Ax3, "  '''''/)))/ ) ) ) ) ) ) ) ),-'\\\\\\\\\\\\\\");
            mvprintw(Ay3 + 6 , Ax3, "  ___,')),') ) ) ) )_),,--'     \\\\\\\\\\\\");
            mvprintw(Ay3 + 7 , Ax3, " (________.\\\\)_),--'             '\\\\\\\\");
            mvprintw(Ay3 + 8 , Ax3, "          -\\\\\\                    '\\\\\\");
            Ax3 = Ax3 - 1;
            *Ay3r = Ay3;
        break;
        case 1:
            mvprintw(Ay3 + 10 , Ax3, "        __,---//////////,        .///");
            mvprintw(Ay3 + 11 , Ax3, "     __  ) ) ) ) ) )''////      /////");
            mvprintw(Ay3 + 12 , Ax3, " _,-' ))'. ) ) ) ) ) ) ) ) )'-. //////");
            mvprintw(Ay3 + 13 , Ax3, "/  ()_)))))\\  ) ) ) ) ) ) ) ) )////////");
            mvprintw(Ay3 + 14 , Ax3, "\\______ )))))) ) ) ) ) ) ) ) )\\\\\\\\\\\\\\\\");
            mvprintw(Ay3 + 15 , Ax3, "  '''''/)))/ ) ) ) ) ) ) ) ),-'\\\\\\\\\\\\\\");
            mvprintw(Ay3 + 16 , Ax3, "  ___,')),') ) ) ) )_),,--'     \\\\\\\\\\\\");
            mvprintw(Ay3 + 17 , Ax3, " (________.\\\\)_),--'             '\\\\\\\\");
            mvprintw(Ay3 + 18 , Ax3, "          -\\\\\\                    '\\\\\\");
            Ax3 = Ax3 - 1;
            *Ay3r = Ay3 + 10;
        break;
        case 2:
            mvprintw(Ay3 + 25 , Ax3, "        __,---//////////,        .///");
            mvprintw(Ay3 + 26 , Ax3, "     __  ) ) ) ) ) )''////      /////");
            mvprintw(Ay3 + 27 , Ax3, " _,-' ))'. ) ) ) ) ) ) ) ) )'-. //////");
            mvprintw(Ay3 + 28 , Ax3, "/  ()_)))))\\  ) ) ) ) ) ) ) ) )////////");
            mvprintw(Ay3 + 29 , Ax3, "\\______ )))))) ) ) ) ) ) ) ) )\\\\\\\\\\\\\\\\");
            mvprintw(Ay3 + 30 , Ax3, "  '''''/)))/ ) ) ) ) ) ) ) ),-'\\\\\\\\\\\\\\");
            mvprintw(Ay3 + 31 , Ax3, "  ___,')),') ) ) ) )_),,--'     \\\\\\\\\\\\");
            mvprintw(Ay3 + 32 , Ax3, " (________.\\\\)_),--'             '\\\\\\\\");
            mvprintw(Ay3 + 33 , Ax3, "          -\\\\\\                    '\\\\\\");
            Ax3 = Ax3 - 1;
            *Ay3r = Ay3 + 25;
        break;
        case 3:
            mvprintw(Ay3 - 20 , Ax3, "        __,---//////////,        .///");
            mvprintw(Ay3 - 19 , Ax3, "     __  ) ) ) ) ) )''////      /////");
            mvprintw(Ay3 - 18 , Ax3, " _,-' ))'. ) ) ) ) ) ) ) ) )'-. //////");
            mvprintw(Ay3 - 17 , Ax3, "/  ()_)))))\\  ) ) ) ) ) ) ) ) )////////");
            mvprintw(Ay3 - 16 , Ax3, "\\______ )))))) ) ) ) ) ) ) ) )\\\\\\\\\\\\\\\\");
            mvprintw(Ay3 - 15 , Ax3, "  '''''/)))/ ) ) ) ) ) ) ) ),-'\\\\\\\\\\\\\\");
            mvprintw(Ay3 - 14 , Ax3, "  ___,')),') ) ) ) )_),,--'     \\\\\\\\\\\\");
            mvprintw(Ay3 - 13 , Ax3, " (________.\\\\)_),--'             '\\\\\\\\");
            mvprintw(Ay3 - 12 , Ax3, "          -\\\\\\                    '\\\\\\");
            Ax3 = Ax3 - 1;
            *Ay3r = Ay3 -20 ;
        break;
        case 4:
            mvprintw(Ay3 + 35 , Ax3, "        __,---//////////,        .///");
            mvprintw(Ay3 + 36 , Ax3, "     __  ) ) ) ) ) )''////      /////");
            mvprintw(Ay3 + 37 , Ax3, " _,-' ))'. ) ) ) ) ) ) ) ) )'-. //////");
            mvprintw(Ay3 + 38 , Ax3, "/  ()_)))))\\  ) ) ) ) ) ) ) ) )////////");
            mvprintw(Ay3 + 39 , Ax3, "\\______ )))))) ) ) ) ) ) ) ) )\\\\\\\\\\\\\\\\");
            mvprintw(Ay3 + 40 , Ax3, "  '''''/)))/ ) ) ) ) ) ) ) ),-'\\\\\\\\\\\\\\");
            mvprintw(Ay3 + 41 , Ax3, "  ___,')),') ) ) ) )_),,--'     \\\\\\\\\\\\");
            mvprintw(Ay3 + 42 , Ax3, " (________.\\\\)_),--'             '\\\\\\\\");
            mvprintw(Ay3 + 43 , Ax3, "          -\\\\\\                    '\\\\\\");
            Ax3 = Ax3 - 1;
            *Ay3r = Ay3 + 35;
        break;
    }
    return Ax3;
}
