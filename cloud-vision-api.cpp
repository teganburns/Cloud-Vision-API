#include <iostream>
#include <unistd.h>
#include <fstream>
#include <typeinfo>

using namespace std;

#include <grpc++/grpc++.h>

#include "Cloud-Vision-API.grpc.pb.h"
#include "google_type.pb.h"
#include "google_rpc.pb.h"

// Uncomment line below to enable debugging //
//#define DEBUG

using namespace google::cloud::vision::v1;

string SCOPE = "vision.googleapis.com";


int main( int argc, char* argv[] ) {

    //system("clear");

    GOOGLE_PROTOBUF_VERIFY_VERSION;


    //-------------//
    // Set up Objs //
    //-------------//

    BatchAnnotateImagesRequest requests; // Consists of mutiple AnnotateImage requests // 

    BatchAnnotateImagesResponse responses;
    AnnotateImageResponse response;


    //----------------------//
    // Set up Configuration //
    //----------------------//

    // Image Source //
    requests.add_requests();
    //requests.mutable_requests( 0 )->mutable_image()->set_content( ); // base64 of local image
    requests.mutable_requests( 0 )->mutable_image()->mutable_source()->set_gcs_image_uri( "https://storage.cloud.google.com/personal_projects/photo.jpg?_ga=1.201480470.603983257.1489802776" );
    //requests.mutable_requests( 0 )->mutable_image_context(); // optional?? 

    // Features // 
    requests.mutable_requests( 0 )->add_features();
    //requests.mutable_requests( 0 )->mutable_features( 0 )->set_type( Feature_Type_TEXT_DETECTION );
    requests.mutable_requests( 0 )->mutable_features( 0 )->set_type( Feature_Type_FACE_DETECTION );
    //requests.mutable_requests( 0 )->mutable_features( 0 )->add_type( Feature_Type_LANDMARK_DETECTION );
    //requests.mutable_requests( 0 )->mutable_features( 0 )->add_type( Feature_Type_LOGO_DETECTION );
    //requests.mutable_requests( 0 )->mutable_features( 0 )->add_type( Feature_Type_LABEL_DETECTION );
    //requests.mutable_requests( 0 )->mutable_features( 0 )->add_type( Feature_Type_SAFE_SEARCH_DETECTION );
    //requests.mutable_requests( 0 )->mutable_features( 0 )->add_type( Feature_Type_IMAGE_PROPTERTIES );
    //requests.mutable_requests( 0 )->mutable_features( 0 )->set_max_results( 5 );


    // Print Configuration //
    std::cout << "\n\n---- Checking Request ----" << std::endl;
    std::cout << "Image Source: ";
    requests.mutable_requests( 0 )->mutable_image()->has_source() ? std::cout << "OK" << std::endl  :  std::cout << "FALSE" << std::endl; 

    std::cout << "Request has Image: ";
    requests.mutable_requests( 0 )->has_image() ? std::cout << "OK" << std::endl  :  std::cout << "FALSE" << std::endl;

    std::cout << "BatchRequests size: " << requests.requests_size() << std::endl;



    //--------------//
    // Send Request //
    //--------------//
    std::cout << "\n---- Sending Request ----" << std::endl;
    grpc::Status status;
    grpc::ClientContext context;

    std::cout << "Getting GoogleDefaultCredentials...";
    auto creds = grpc::GoogleDefaultCredentials();
    std::cout << "DONE!\nCreating Channel...";
    auto channel = ::grpc::CreateChannel( SCOPE, creds );
    std::cout << "DONE!\nGetting Status...";
    std::unique_ptr< ImageAnnotator::Stub> stub( ImageAnnotator::NewStub( channel ) );
    status = stub->BatchAnnotateImages( &context, requests, &responses );
    std::cout << "DONE!" << std::endl;

    sleep(1);


    //---------------//
    // Read Response //
    //---------------//
    std::cout << "\n\n------ Responses ------" << std::endl;
    if ( status.ok() ) {
        std::cout << "Status returned OK\nResponses size: " << responses.responses_size() << std::endl;

        response = responses.responses( 0 );
        // response.has_error()

        std::cout << "\n\n----Face Annotations----" << std::endl;
        std::cout << "FaceAnnotations size: " << response.face_annotations_size() << std::endl;
        if ( response.face_annotations_size() > 0 ) {
            if ( response.face_annotations( 0 ).has_bounding_poly() ) {
                // mutable_bounding_poly();            
            
            }
            if ( response.face_annotations( 0 ).has_fd_bounding_poly( ) ) {
                //response.face_annotations( 0 ).fd_bounding_poly();
                std::cout << "FaceAnnotations: " << response.face_annotations( 0 ).has_fd_bounding_poly() << std::endl;
            }

            /*
            for ( int i = 0; i < response.face_annotations().landmarks_size(); i++ ) {
                std::cout << "Landmarks Size: " << response.face_annotations().landmarks_size() << std::endl;
                // response.face_annotations().landmarks( int index );
            
            }
            
            std::cout << "Roll: " << response.face_annotations().roll_angle() << std::endl;
            std::cout << "Pan: " << response.face_annotations().pan_angle() << std::endl;
            std::cout << "Tilt: " << response.face_annotations().tilt_angle() << std::endl;

            */

            // TODO: finish @ detection_confidence // 

        } else { std::cout << "NONE" << std::endl; }


        /*
        std::cout << "\n\n----Landmark Annotations----" << std::endl;
        if ( response.has_landmark_annotations() ) {
            //response.landmark_annotations() // returns EntityAnnotation obj
        
        }


        std::cout << "\n\n----Logo Annotations----" << std::endl;
        if ( response.has_logo_annotations() ) {
            //responses.logo_annotations() // returns EntityAnnotation obj
        } else { std::cout << "NONE" << std::endl; }


        std::cout << "\n\n----Label Annotations----" << std::endl;
        if ( response.has_label_annotations()  ) {
        
        } else { std::cout << "NONE" << std::endl; }


        std::cout << "\n\n----Text Annotations----" << std::endl;
        if ( response.has_text_annotations() ) {
        
        } else { std::cout << "NONE" << std::endl; }


        std::cout << "\n\n----Full Text Annotations----" << std::endl;
        if ( response.has_text_annotations() ) { // TODO: this is the same as about check proto.h for def //
        
        } else { std::cout << "NONE" << std::endl; }


        std::cout << "\n\n----Safe Search Annotations----" << std::endl;
        if ( response.has_safe_search_annotation() ) {
        
        } else { std::cout << "NONE" << std::endl; }


        std::cout << "\n\n----Image Properties Annotations----" << std::endl;
        if ( response.has_image_properties_annotation()  ) {
        
        } else { std::cout << "NONE" << std::endl; }

        std::cout << "\n\n----Crop Hints Annotations----" << std::endl;
        if (  response.has_crop_hints_annotation() ) {
        
        } else { std::cout << "NONE" << std::endl; }


        std::cout << "\n\n----Web Detection----" << std::endl;
        if ( response.has_web_detection()  ) {
        
        } else { std::cout << "NONE" << std::endl; }
        
        */


        // error




    } else if (  status.ok() ){
        std::cout << "Status Returned Canceled" << std::endl;

        sleep(0.5);
    }else {
        std::cerr << "RPC failed" << std::endl;
        sleep(0.5);
        std::cout << status.error_code() << ": " << status.error_message() << status.ok() << std::endl;
    }

    google::protobuf::ShutdownProtobufLibrary();

    std::cout << "\nAll Finished!" << std::endl;

    return 0;
}

