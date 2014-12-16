#include<FindAndLift.h>

FindAndLift::FindAndLift(ArRobot* myRobot, ArACTS_1_2* acts){
    this->myRobot = myRobot;
    this->state = IDLE;
    this->acts = acts;

    this->activate();
}

FindAndLift::~FindAndLift(){
    if(acts->isConnected()){
        this->deactivate();
    }

    delete gripper;
}

void FindAndLift::activate(){

    if(!acts->isConnected()){
        acts->openPort(myRobot);
    }

    gripper = new ArGripper(myRobot);
    ptz = myRobot->getPTZ();

}

void FindAndLift::deactivate(){
    acts->closePort();
}

bool FindAndLift::fire(){

    if (acts->isConnected()) {

        acts->getBlob(1, 1, &blob);

        switch(state){
            case(IDLE):{
                myRobot->setVel(0.0);
                myRobot->setRotVel(0.0);
                //ptz->tilt(0.0);
                gripper->gripperDeploy();

                if(acts->getNumBlobs(1) > 0){
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

                if(acts->getNumBlobs(1) > 0){
                    state = ADJUSTING;
                }

                printf("SEARCHING: TILT: %f\n", tilt);

            }break;
            case(ADJUSTING):{
                int xcg = blob.getXCG();

                int marginLeft = 1;
                int marginRight = 1;
                int halfScreenW = SCREENWIDTH / 2;

                printf("ADJUSTING: ");

                //Object is centered and ready to be approached
                if(xcg > (halfScreenW - marginLeft) && xcg < (halfScreenW + marginRight)){
                    printf("FOUND OBJECT!\n");
                    myRobot->setRotVel(0.6);
                    state = APPROACHING;
                //Object is not centered and robot position needs to be adjusted
                }else if(xcg > (halfScreenW - marginLeft) && xcg > (halfScreenW + marginRight)){
                  printf("TURNING RIGHT\n");
                  myRobot->setRotVel(-2.0);
                }else if(xcg < (halfScreenW - marginLeft) && xcg < (halfScreenW + marginRight)){
                   printf("TURNING LEFT\n");
                   myRobot->setRotVel(2.0);
                }

            }break;
            case(APPROACHING):{
                printf("APPROACHING!\n");

                printf("%f\n", myRobot->getRotVel());

                if(gripper->getBreakBeamState() == 3){
                   myRobot->setVel(0.0);
                   myRobot->setRotVel(0.0);
                   state = LIFTING;
                }else{
                    myRobot->setVel(25.0);
                }


                if(acts->getNumBlobs(1) == 0 && ptz->getTilt() >= -25.0f){
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
                return true;
            }break;
        }

    } else {
        ArLog::log(ArLog::Normal, "Not connected to acts->");
        this->deactivate();
    }

    return false;
}

void FindAndLift::printChannel(int channel){
    int numBlobs = acts->getNumBlobs(channel);
    if (numBlobs > 0) {
        ArLog::log(ArLog::Normal, "%d blobs in channel %d", numBlobs, channel);
    }

    for (int i = 0; i < numBlobs; ++i) {
        int blobNo = i+1;
        if(acts->getBlob(channel, blobNo, &blob)) {
            ArLog::log(ArLog::Normal, " Blob %d:",blobNo);
            printBlobInfo(blob);
        } else {
            ArLog::log(ArLog::Normal, " Can’t get blob %d:",blobNo);
        }
    }
}

void FindAndLift::printBlobInfo(ArACTSBlob &blob){

    ArLog::log(ArLog::Normal, " Area: %d",blob.getArea());
    ArLog::log(ArLog::Normal, " BoundingBox: (%d, %d, %d, %d)",
    blob.getTop(), blob.getLeft(), blob.getBottom(), blob.getRight());
    ArLog::log(ArLog::Normal, " Position: (%d, %d)",
    blob.getXCG(), blob.getYCG());

}


