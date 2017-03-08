#include <iostream>
#include <unistd.h>
#include <fstream>
#include <typeinfo>

using namespace std;

#include <grpc++/grpc++.h>
#include "google_cloud_vision_v1.grpc.pb.h"
#include "google_type.grpc.pb.h"

// Uncomment line below to enable debugging //
//#define DEBUG

int main( int argc, char* argv[] ) {

    //system("clear");

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    cout << "\nAll Finished!" << endl;

    //google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
