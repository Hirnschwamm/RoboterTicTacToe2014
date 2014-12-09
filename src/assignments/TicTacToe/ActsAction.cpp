#include<ActsAction.h>

ActsAction::ActsAction() :
    ArAction("ActsAction", "Robot turns to object, approaches it, grabs it"){
    state = IDLE;
}

ActsAction::~ActsAction(){
    if(acts.isConnected()){
        acts.closePort();
    }

    delete gripper;
}

void ActsAction::activate(){

    ArLog::log(ArLog::Normal, "Activate!");
    acts.openPort(myRobot);
    ArAction::activate();

    gripper = new ArGripper(myRobot);
    ptz = myRobot->getPTZ();

}

void ActsAction::deactivate(){

    acts.closePort();
    ArAction::deactivate();

}

ArActionDesired *ActsAction::fire(ArActionDesired currentDesired){
 /*    if (acts.isConnected()) {
            for (int channel = 1; channel <= acts.NUM_CHANNELS; ++channel)
            {
                printChannel(channel);
            }
        } else {
            ArLog::log(ArLog::Normal, "Not connected to ACTS.");
            this->deactivate();
        }*/

    if (acts.isConnected()) {

        acts.getBlob(1, 1, &blob);

        switch(state){
            case(IDLE):{
                myRobot->setVel(0.0);
                myRobot->setRotVel(0.0);
                ptz->tilt(0.0);
                gripper->gripperDeploy();

                if(acts.getNumBlobs(1) > 0){
                    state = ADJUSTING;


                    printBlobInfo(blob);
                }else{
                    state = SEARCHING;
                }


            }break;
            case(SEARCHING):{
                myRobot->setVel(0.0);
                myRobot->setRotVel(0.0);

                double tilt = ptz->getTilt();

                if(tilt > -25.0){
                    ptz->tilt(tilt - 2.0);
                }else{
                    state = APPROACHING;
                }

                if(acts.getNumBlobs(1) > 0){
                    state = ADJUSTING;
                }

                printf("SEARCHING: TILT: %f\n", tilt);

            }break;
            case(ADJUSTING):{
                int xcg = blob.getXCG();

                int margin = 3;
                int halfScreenW = SCREENWIDTH / 2;

                printf("ADJUSTING: ");


                //Object is centered and ready to be approached
                if(xcg > (halfScreenW - margin) && xcg < (halfScreenW + margin)){
                    printf("FOUND OBJECT!\n");
                    myRobot->setRotVel(0.0);
                    state = APPROACHING;
                //Object is not centered and robot position needs to be adjusted
                }else if(xcg > (halfScreenW - margin) && xcg > (halfScreenW + margin)){
                  printf("TURNING RIGHT\n");
                  myRobot->setRotVel(-2.0);
                }else if(xcg < (halfScreenW - margin) && xcg < (halfScreenW + margin)){
                   printf("TURNING LEFT\n");
                   myRobot->setRotVel(2.0);
                }

            }break;
            case(APPROACHING):{
                printf("APPROACHING!\n");

                if(gripper->getBreakBeamState() == 3){
                   myRobot->setVel(0.0);
                   state = LIFTING;
                }else{
                    myRobot->setVel(15.0);
                }


                if(acts.getNumBlobs(1) == 0 && ptz->getTilt() >= -25.0f){
                    state = SEARCHING;
                }
            }break;
            case(LIFTING):{
                if(gripper->getPaddleState() != 3){
                    gripper->gripperStore();
                    state = DONE;
                }
            }break;
            case(DONE):{
                ptz->tilt(0.0);
            }break;
        }

    } else {
        ArLog::log(ArLog::Normal, "Not connected to ACTS.");
        this->deactivate();
    }

    return 0;
}

void ActsAction::printChannel(int channel){
    int numBlobs = acts.getNumBlobs(channel);
    if (numBlobs > 0) {
        ArLog::log(ArLog::Normal, "%d blobs in channel %d", numBlobs, channel);
    }

    for (int i = 0; i < numBlobs; ++i) {
        int blobNo = i+1;
        if(acts.getBlob(channel, blobNo, &blob)) {
            ArLog::log(ArLog::Normal, " Blob %d:",blobNo);
            printBlobInfo(blob);
        } else {
            ArLog::log(ArLog::Normal, " Can’t get blob %d:",blobNo);
        }
    }
}

void ActsAction::printBlobInfo(ArACTSBlob &blob){

    ArLog::log(ArLog::Normal, " Area: %d",blob.getArea());
    ArLog::log(ArLog::Normal, " BoundingBox: (%d, %d, %d, %d)",
    blob.getTop(), blob.getLeft(), blob.getBottom(), blob.getRight());
    ArLog::log(ArLog::Normal, " Position: (%d, %d)",
    blob.getXCG(), blob.getYCG());

}


