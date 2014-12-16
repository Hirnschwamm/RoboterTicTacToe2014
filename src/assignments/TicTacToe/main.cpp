#include <Aria.h>
#include <defaultrobotserver.h>

#include<ActsAction.h>

int main(int argc, char **argv) {

    DefaultRobotServer server;
    server.init(argc, argv);

    printf("asfdsdfgsd\n");

    ActsAction actsAction;
    server.addAction(actsAction);
    actsAction.activate();

    ArLog::log(ArLog::Normal, "run...");
    server.run();

    Aria::exit(0);
    return 0;
}
