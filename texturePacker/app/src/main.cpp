#include "include/tpapplication.h"
#include "include/tpconsoleapplication.h"
#include "common/include/publisher.h"
#include "common/include/fileutils.h"
#include "common/include/config.h"

bool isConsole(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    if (isConsole(argc, argv))
    {
        TPConsoleApplication ta(argc, argv);
        if (false==ta.checkConsole())
        {
            return 0;
        }

        if (ta.isInitCache())
        {
            return ta.initCache();
        }

        ta.runConsole();

        return ta.exec();
    }
    else
    {
        TpApplication ta(argc, argv);

        ta.initMainWindow();

        return ta.exec();
    }
}

bool isConsole(int argc, char *argv[])
{
    for(int i = 0; i<argc; i++)
    {
        QString param = argv[i];

        if (param.toLower() == "-no-gui")
        {
            return true;
        }
    }

    return false;
}
