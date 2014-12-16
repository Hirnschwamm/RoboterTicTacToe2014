#include <Aria.h>
#include <defaultrobotserver.h>

#include<TicTacToeAction.h>

int main(int argc, char **argv) {

    DefaultRobotServer server;
    server.init(argc, argv);

    TicTacToeAction tictactoeaction(true);
    server.addAction(tictactoeaction);
    tictactoeaction.activate();

    ArLog::log(ArLog::Normal, "run...");
    server.run();

    Aria::exit(0);
    return 0;
}
