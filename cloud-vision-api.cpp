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

void print_entity_annotation ( ) {



}

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
    requests.mutable_requests( 0 )->mutable_image()->mutable_source()->set_gcs_image_uri( "gs://personal_projects/photo.jpg" ); // TODO [GCS_URL] // 
    //requests.mutable_requests( 0 )->mutable_image()->mutable_source()->set_gcs_image_uri( "gs://personal_projects/photo_korea.jpg" ); // TODO [GCS_URL] // 
    //requests.mutable_requests( 0 )->mutable_image_context(); // optional?? 

    // Features // 
    requests.mutable_requests( 0 )->add_features();
    requests.mutable_requests( 0 )->add_features();
    requests.mutable_requests( 0 )->add_features();
    requests.mutable_requests( 0 )->add_features();
    requests.mutable_requests( 0 )->add_features();
    requests.mutable_requests( 0 )->add_features();
    requests.mutable_requests( 0 )->add_features();
    requests.mutable_requests( 0 )->add_features();
    requests.mutable_requests( 0 )->add_features();

    requests.mutable_requests( 0 )->mutable_features( 0 )->set_type( Feature_Type_FACE_DETECTION );
    requests.mutable_requests( 0 )->mutable_features( 1 )->set_type( Feature_Type_LANDMARK_DETECTION );
    requests.mutable_requests( 0 )->mutable_features( 2 )->set_type( Feature_Type_LOGO_DETECTION );
    requests.mutable_requests( 0 )->mutable_features( 3 )->set_type( Feature_Type_LABEL_DETECTION );
    requests.mutable_requests( 0 )->mutable_features( 4 )->set_type( Feature_Type_TEXT_DETECTION );
    requests.mutable_requests( 0 )->mutable_features( 5 )->set_type( Feature_Type_SAFE_SEARCH_DETECTION );
    requests.mutable_requests( 0 )->mutable_features( 6 )->set_type( Feature_Type_IMAGE_PROPERTIES );
    requests.mutable_requests( 0 )->mutable_features( 7 )->set_type( Feature_Type_CROP_HINTS );
    requests.mutable_requests( 0 )->mutable_features( 8 )->set_type( Feature_Type_WEB_DETECTION );

    //requests.mutable_requests( 0 )->mutable_features( 0 )->set_max_results( int );


    // Print Configuration //
    std::cout << "\n\n---- Checking Request ----" << std::endl;
    std::cout << "Features size: " << requests.mutable_requests( 0 )->features_size() << std::endl;
    for ( int i = 0; i < requests.mutable_requests( 0 )->features_size(); i++ ) {
        //requests.mutable_requests( 0 ).features( int ); // Feature
        //requests.mutable_requests( 0 ).features( i ).type(); // Feature_Type
        std::cout << "Feature " << i << " name: " << Feature_Type_Name( requests.mutable_requests( 0 )->features( i ).type() ) << std::endl;
        std::cout << "max results: " << requests.mutable_requests( 0 )->features( i ).max_results() << std::endl;

    }

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



    //---------------//
    // Read Response //
    //---------------//
    std::cout << "\n\n------ Responses ------" << std::endl;
    if ( status.ok() ) {
        std::cout << "Status returned OK\nResponses size: " << responses.responses_size() << std::endl;

        for ( int h = 0; h < responses.responses_size(); h++ ) {
            response = responses.responses( h );

            std::cout << "Response has Error: " << response.has_error() << std::endl;

            std::cout << "\n\n----Face Annotations----" << std::endl;
            std::cout << "Size: " << response.face_annotations_size() << std::endl;
            for ( int i = 0; i <  response.face_annotations_size(); i++ ) {

                if ( response.face_annotations( i ).has_bounding_poly() ) {
                    //response.face_annotation( i ).bounding_poly();
                    std::cout << "Has Bounding Poly: "
                        << response.face_annotations( i ).has_bounding_poly()
                        << std::endl;

                    for ( int j = 0; j < response.face_annotations( i ).bounding_poly().vertices_size(); j++ ) {
                        std::cout
                            << "\tvert: "
                            << response.face_annotations( i ).bounding_poly().vertices( j ).x() // vertex
                            << ","
                            << response.face_annotations( i ).bounding_poly().vertices( j ).y() // vertex
                            << std::endl;
                    }
                }

                if ( response.face_annotations( i ).has_fd_bounding_poly() ) {
                    //response.face_annotations( 0 ).fd_bounding_poly();
                    for ( int j = 0; j < response.face_annotations( i ).fd_bounding_poly().vertices_size(); j++ ) {
                        std::cout
                            << "FD Bounding Poly: "
                            << response.face_annotations( i ).fd_bounding_poly().vertices( j ).x() // vertex
                            << ","
                            << response.face_annotations( i ).fd_bounding_poly().vertices( j ).y() // vertex
                            << std::endl;
                    }
                }

                // TODO [FA_LANDMARK] //
                for ( int j = 0; j < response.face_annotations( i ).landmarks_size(); j++ ) {
                    //response.face_annotations( i ).landmarks( j ). // FaceAnnotation_Landmarks
                    std::cout << "FaceAnnotationLandmark: "
                        << "\n\tType: "
                        << FaceAnnotation_Landmark_Type_Name( response.face_annotations( i ).landmarks( j ).type() )
                        << "\n\tValue: "
                        << response.face_annotations( i ).landmarks( j ).type()
                        << "\n\ti: " << i << "  j: " << j;
                    
                    if ( response.face_annotations( i ).landmarks( j ).has_position() ) {
                        std::cout
                        << "X: "
                        << response.face_annotations( i ).landmarks( j ).position().x()
                        << "  Y: "
                        << response.face_annotations( i ).landmarks( j ).position().y()
                        << "  Z: "
                        << response.face_annotations( i ).landmarks( j ).position().z();
                    
                    } else {
                        std::cout << "\n\tNO POSITION";
                    }
                    std::cout
                    << std::endl;
                
                }
                
                std::cout << "roll angle: "
                    << response.face_annotations( i ).roll_angle() // float
                    << "\npan angle: "
                    << response.face_annotations( i ).pan_angle() // float
                    << "\ntilt angle: "
                    << response.face_annotations( i ).tilt_angle() // float
                    << "\ndetection confidence: "
                    << response.face_annotations( i ).detection_confidence() // float
                    << "\nlandmarking confidence: "
                    << response.face_annotations( i ).landmarking_confidence() // float
                    << std::endl;

                std::cout << "Alt Info:"
                    << "\n\tJoy: "
                    << Likelihood_Name( response.face_annotations( i ).joy_likelihood() )
                    << "\n\tSorrow: "
                    << Likelihood_Name( response.face_annotations( i ).sorrow_likelihood() )
                    << "\n\tAnger: "
                    << Likelihood_Name( response.face_annotations( i ).anger_likelihood() )
                    << "\n\tSuprise: "
                    << Likelihood_Name( response.face_annotations( i ).suprise_likelihood() )
                    << "\n\tUnder Exposed: "
                    << Likelihood_Name( response.face_annotations( i ).under_exposed_likelihood() )
                    << "\n\tBlured: "
                    << Likelihood_Name( response.face_annotations( i ).blurred_likelihood() )
                    << "\n\tHeadwear: "
                    << Likelihood_Name( response.face_annotations( i ).headwear_likelihood() )
                    << std::endl;



            }


            std::cout << "\n\n----Landmark Annotations----" << std::endl;
            std::cout << "Size: " << response.landmark_annotations_size() << std::endl;

            for ( int i = 0; i < response.landmark_annotations_size(); i++ ) {
                response.landmark_annotations( i ); // EntityAnnotation
                // 4977
                response.landmark_annotations( i ).mid(); // string
                response.landmark_annotations( i ).locale(); //string
                response.landmark_annotations( i ).description(); // string
                response.landmark_annotations( i ).score(); // float 
                response.landmark_annotations( i ).confidence(); // float
                response.landmark_annotations( i ).topicality(); // float

                /*
                response.landmark_annotations( int )// ---- BoundingPoly ---- //
                response.landmark_annotations( int ).has_bounding_poly(); //bool
                response.landmark_annotations( int ).bounding_poly(); // BoundingPoly
                response.landmark_annotations( int ).bounding_poly().verticies_size(); // int
                response.landmark_annotations( int ).bounding_poly().verticies( int ); // Vertex
                response.landmark_annotations( int ).bounding_poly().verticies( int ).x(); // google::protobuf::int32
                response.landmark_annotations( int ).bounding_poly().verticies( int ).y(); // google::protobuf::int32

                response.landmark_annotations( int )// ---- LocationInfo ---- //
                response.landmark_annotations( int ).locations_size(); // int
                response.landmark_annotations( int ).locations( int ); // LocationInfo
                response.landmark_annotations( int ).locations( int ).has_lat_lng(); // bool
                response.landmark_annotations( int ).locations( int ).lat_lng(); // LatLng
                response.landmark_annotations( int ).locations( int ).lat_lng().latitude(); // double
                response.landmark_annotations( int ).locations( int ).lat_lng().longtude(); // double

                response.landmark_annotations( int )// ---- Propert ---- //
                response.landmark_annotations( int ).properties_size(); // int
                response.landmark_annotations( int ).properties( int ); // Property
                response.landmark_annotations( int ).properties( int ).name(); //string
                response.landmark_annotations( int ).properties( int ).value(); // string
                response.landmark_annotations( int ).properties( int ).unit64_value(); // google::protobuf
                */
                //
                std::cout
                    << "Label "
                    << i 
                    << "\n\tmid: "
                    << response.landmark_annotations( i ).mid() // string
                    << "\n\tlocale: "
                    << response.landmark_annotations( i ).locale() // string
                    << "\n\tdescription: "
                    << response.landmark_annotations( i ).description() // string
                    << "\n\tscore: "
                    << response.landmark_annotations( i ).score() // float
                    << "\n\tconfidence: "
                    << response.landmark_annotations( i ).confidence() // float
                    << "\n\ttopicality: "
                    << response.landmark_annotations( i ).topicality() // float
                    << std::endl;

                std::cout
                    << "\tHas Bounding Poly: "
                    << response.landmark_annotations(i ).has_bounding_poly()
                    << std::endl;

                if ( response.landmark_annotations( i ).has_bounding_poly() ) {
                    std::cout
                        << "\t\tVerticies: "
                        << response.landmark_annotations( i ).bounding_poly().vertices_size()
                        << std::endl;

                    for ( int j = 0; j < response.landmark_annotations( i ).bounding_poly().vertices_size(); j++ ) {
                        std::cout
                            << "\t\tvert " << j << ": "
                            << response.landmark_annotations( i ).bounding_poly().vertices( j ).x()
                            << ", "
                            << response.landmark_annotations( i ).bounding_poly().vertices( j ).y()
                            << std::endl;
                    }
                }

                std::cout
                    << "\tLocations: "
                    << response.landmark_annotations( i ).locations_size()
                    << std::endl;

                for ( int j = 0; j < response.landmark_annotations( i ).locations_size(); j++ ) {
                    if ( response.landmark_annotations( i ).locations( j ).has_lat_lng() ) {
                        std::cout
                            << j
                            << ": "
                            << response.landmark_annotations( i ).locations( j ).lat_lng().latitude() // double
                            << " , "
                            << response.landmark_annotations( i ).locations( j ).lat_lng().longitude() // double
                            << std::endl;
                    
                    }
                }

                std::cout
                    << "\tProperties: "
                    << response.landmark_annotations( i ).properties_size()
                    << std::endl;

                for ( int j = 0; j < response.landmark_annotations( i ).properties_size(); j++ ) {
                    std::cout
                        << "\tname: "
                        << response.landmark_annotations( i ).properties( j ).name() // string
                        << "\t\nvalue: "
                        << response.landmark_annotations( i ).properties( j ).value() // string
                        << "\t\nuint64 value: "
                        << response.landmark_annotations( i ).properties( j ).uint64_value() // uint64
                        << std::endl;
                
                }

            }

            std::cout << "\n\n----Logo Annotations----" << std::endl;
            std::cout << "Size: " << response.logo_annotations_size() << std::endl;
            for ( int i = 0; i <  response.logo_annotations_size(); i++ ) {
                //response.logo_annotations( i ); // EntityAnnotation
                std::cout
                    << "Label "
                    << i 
                    << "\n\tmid: "
                    << response.logo_annotations( i ).mid() // string
                    << "\n\tlocale: "
                    << response.logo_annotations( i ).locale() // string
                    << "\n\tdescription: "
                    << response.logo_annotations( i ).description() // string
                    << "\n\tscore: "
                    << response.logo_annotations( i ).score() // float
                    << "\n\tconfidence: "
                    << response.logo_annotations( i ).confidence() // float
                    << "\n\ttopicality: "
                    << response.logo_annotations( i ).topicality() // float
                    << std::endl;

                std::cout
                    << "\tHas Bounding Poly: "
                    << response.logo_annotations(i ).has_bounding_poly()
                    << std::endl;

                if ( response.logo_annotations( i ).has_bounding_poly() ) {
                    std::cout
                        << "\tVerticies: "
                        << response.logo_annotations( i ).bounding_poly().vertices_size()
                        << std::endl;

                    for ( int j = 0; j < response.logo_annotations( i ).bounding_poly().vertices_size(); j++ ) {
                        std::cout
                            << "\t\tvert " << j << ": "
                            << response.logo_annotations( i ).bounding_poly().vertices( j ).x()
                            << ", "
                            << response.logo_annotations( i ).bounding_poly().vertices( j ).y()
                            << std::endl;
                    }
                }

                std::cout
                    << "\tLocations: "
                    << response.logo_annotations( i ).locations_size()
                    << std::endl;

                for ( int j = 0; j < response.logo_annotations( i ).locations_size(); j++ ) {
                    if ( response.logo_annotations( i ).locations( j ).has_lat_lng() ) {
                        std::cout
                            << j
                            << ": "
                            << response.logo_annotations( i ).locations( j ).lat_lng().latitude() // double
                            << " , "
                            << response.logo_annotations( i ).locations( j ).lat_lng().longitude() // double
                            << std::endl;
                    
                    }
                }

                std::cout
                    << "\tProperties: "
                    << response.logo_annotations( i ).properties_size()
                    << std::endl;

                for ( int j = 0; j < response.logo_annotations( i ).properties_size(); j++ ) {
                    std::cout
                        << "\tname: "
                        << response.logo_annotations( i ).properties( j ).name() // string
                        << "\t\nvalue: "
                        << response.logo_annotations( i ).properties( j ).value() // string
                        << "\t\nuint64 value: "
                        << response.logo_annotations( i ).properties( j ).uint64_value() // uint64
                        << std::endl;
                
                }


            }

            std::cout << "\n\n----Label Annotations----" << std::endl;
            std::cout << "Size: " << response.label_annotations_size() << std::endl;
            for ( int i = 0; i < response.label_annotations_size(); i++ ) {
                //response.label_annotations( i ); // EntityAnnotation
                std::cout
                    << "Label "
                    << i 
                    << "\n\tmid: "
                    << response.label_annotations( i ).mid() // string
                    << "\n\tlocale: "
                    << response.label_annotations( i ).locale() // string
                    << "\n\tdescription: "
                    << response.label_annotations( i ).description() // string
                    << "\n\tscore: "
                    << response.label_annotations( i ).score() // float
                    << "\n\tconfidence: "
                    << response.label_annotations( i ).confidence() // float
                    << "\n\ttopicality: "
                    << response.label_annotations( i ).topicality() // float
                    << std::endl;

                std::cout
                    << "\tHas Bounding Poly: "
                    << response.label_annotations(i ).has_bounding_poly()
                    << std::endl;

                if ( response.label_annotations( i ).has_bounding_poly() ) {
                    std::cout
                        << "\tVerticies: "
                        << response.label_annotations( i ).bounding_poly().vertices_size()
                        << std::endl;

                    for ( int j = 0; j < response.label_annotations( i ).bounding_poly().vertices_size(); j++ ) {
                        std::cout
                            << "\t\tvert " << j << ": "
                            << response.label_annotations( i ).bounding_poly().vertices( j ).x()
                            << ", "
                            << response.label_annotations( i ).bounding_poly().vertices( j ).y()
                            << std::endl;
                    }
                }

                std::cout
                    << "\tLocations: "
                    << response.label_annotations( i ).locations_size()
                    << std::endl;

                for ( int j = 0; j < response.label_annotations( i ).locations_size(); j++ ) {
                    if ( response.label_annotations( i ).locations( j ).has_lat_lng() ) {
                        std::cout
                            << j
                            << ": "
                            << response.label_annotations( i ).locations( j ).lat_lng().latitude() // double
                            << " , "
                            << response.label_annotations( i ).locations( j ).lat_lng().longitude() // double
                            << std::endl;
                    
                    }
                }

                std::cout
                    << "\tProperties: "
                    << response.label_annotations( i ).properties_size()
                    << std::endl;

                for ( int j = 0; j < response.label_annotations( i ).properties_size(); j++ ) {
                    std::cout
                        << "\tname: "
                        << response.label_annotations( i ).properties( j ).name() // string
                        << "\t\nvalue: "
                        << response.label_annotations( i ).properties( j ).value() // string
                        << "\t\nuint64 value: "
                        << response.label_annotations( i ).properties( j ).uint64_value() // uint64
                        << std::endl;
                
                }


            }

            std::cout << "\n\n----Text Annotations----" << std::endl;
            std::cout << "Size: " << response.text_annotations_size() << std::endl;
            for ( int i = 0; i < response.text_annotations_size(); i++ ) {
                //response.text_annotations( i ); // EntityAnnotation
                std::cout
                    << "Label "
                    << i 
                    << "\n\tmid: "
                    << response.text_annotations( i ).mid() // string
                    << "\n\tlocale: "
                    << response.text_annotations( i ).locale() // string
                    << "\n\tdescription: "
                    << response.text_annotations( i ).description() // string
                    << "\n\tscore: "
                    << response.text_annotations( i ).score() // float
                    << "\n\tconfidence: "
                    << response.text_annotations( i ).confidence() // float
                    << "\n\ttopicality: "
                    << response.text_annotations( i ).topicality() // float
                    << std::endl;

                std::cout
                    << "\tHas Bounding Poly: "
                    << response.text_annotations(i ).has_bounding_poly()
                    << std::endl;

                if ( response.text_annotations( i ).has_bounding_poly() ) {
                    std::cout
                        << "\tVerticies: "
                        << response.text_annotations( i ).bounding_poly().vertices_size()
                        << std::endl;

                    for ( int j = 0; j < response.text_annotations( i ).bounding_poly().vertices_size(); j++ ) {
                        std::cout
                            << "\t\tvert " << j << ": "
                            << response.text_annotations( i ).bounding_poly().vertices( j ).x()
                            << ", "
                            << response.text_annotations( i ).bounding_poly().vertices( j ).y()
                            << std::endl;
                    }
                }

                std::cout
                    << "\tLocations: "
                    << response.text_annotations( i ).locations_size()
                    << std::endl;

                for ( int j = 0; j < response.text_annotations( i ).locations_size(); j++ ) {
                    if ( response.text_annotations( i ).locations( j ).has_lat_lng() ) {
                        std::cout
                            << j
                            << ": "
                            << response.text_annotations( i ).locations( j ).lat_lng().latitude() // double
                            << " , "
                            << response.text_annotations( i ).locations( j ).lat_lng().longitude() // double
                            << std::endl;
                    
                    }
                }

                std::cout
                    << "\tProperties: "
                    << response.text_annotations( i ).properties_size()
                    << std::endl;

                for ( int j = 0; j < response.text_annotations( i ).properties_size(); j++ ) {
                    std::cout
                        << "\tname: "
                        << response.text_annotations( i ).properties( j ).name() // string
                        << "\t\nvalue: "
                        << response.text_annotations( i ).properties( j ).value() // string
                        << "\t\nuint64 value: "
                        << response.text_annotations( i ).properties( j ).uint64_value() // uint64
                        << std::endl;
                
                }

            
            }

            std::cout << "\n\n----Full Text Annotation----" << std::endl;
            if ( response.has_full_text_annotation() ) {
                std::cout << response.has_full_text_annotation() << std::endl;
                response.full_text_annotation(); // TextAnnotation
            
            } else { std::cout << "NONE" << std::endl; }


            std::cout << "\n\n----Safe Search Annotation----" << std::endl;
            if ( response.has_safe_search_annotation() ) {
                response.safe_search_annotation(); // SafeSearchAnnotation 

            } else { std::cout << "NONE" << std::endl; }


            std::cout << "\n\n----Image Properties Annotations----" << std::endl;
            if ( response.has_image_properties_annotation()  ) {
                std::cout << response.has_image_properties_annotation() << std::endl; // ImageProperties
                //response.image_properties_annotation(); // ImageProperties
                response.image_properties_annotation().has_dominant_colors();
                std::cout << "Dominant Colors: " << response.image_properties_annotation().has_dominant_colors() << std::endl;

                //response.image_properties_annotation().dominant_colors(); // DominantColorsAnnotation
                //response.image_properties_annotation().dominant_colors().colors_size(); // int
                std::cout << "\tSize: " << response.image_properties_annotation().dominant_colors().colors_size() << std::endl;
                for ( int i = 0; i <  response.image_properties_annotation().dominant_colors().colors_size(); i++ ) {
                    //response.image_properties_annotation().dominant_colors().colors( int ); // ColorInfo
                    //response.image_properties_annotation().dominant_colors().colors( i ).has_color();
                    std::cout << "Has Color: " << response.image_properties_annotation().dominant_colors().colors( i ).has_color() << std::endl;
                    //response.image_properties_annotation().dominant_colors().colors( i ).color(); // Color
                    response.image_properties_annotation().dominant_colors().colors( i ).color().red(); // float
                    response.image_properties_annotation().dominant_colors().colors( i ).color().green(); // float
                    response.image_properties_annotation().dominant_colors().colors( i ).color().blue(); // float
                    response.image_properties_annotation().dominant_colors().colors( i ).color().has_alpha();
                    response.image_properties_annotation().dominant_colors().colors( i ).color().alpha(); // FloatValue
                    response.image_properties_annotation().dominant_colors().colors( i ).color().alpha().value(); // float

                }

            } else { std::cout << "NONE" << std::endl; }


            std::cout << "\n\n----Crop Hints Annotations----" << std::endl;

            if ( response.has_crop_hints_annotation() ) {
                std::cout << "Size: " << response.crop_hints_annotation().crop_hints_size() << std::endl; 
                for ( int i = 0; i < response.crop_hints_annotation().crop_hints_size(); i++ ) {
                    std::cout << "BoundingPoly: " << response.crop_hints_annotation().crop_hints( i ).has_bounding_poly() << std::endl;
                    std::cout << "\tVertSize: " << response.crop_hints_annotation().crop_hints( i ).bounding_poly().vertices_size() << std::endl;
                    for ( int j = 0; j < response.crop_hints_annotation().crop_hints( i ).bounding_poly().vertices_size(); j++ ) {
                        std::cout << "\tVert: X: " << response.crop_hints_annotation().crop_hints( i ).bounding_poly().vertices( j ).x() << " Y: " << response.crop_hints_annotation().crop_hints( i ).bounding_poly().vertices( j ).y() << std::endl;
                    
                    }
                }
            } else { std::cout << "NONE" << std::endl; }


            std::cout << "\n\n----Web Detection----" << std::endl;
            if ( response.has_web_detection()  ) {
                
                std::cout << "WebEntities: " << response.web_detection().web_entities_size() << std::endl;
                for ( int i = 0; i < response.web_detection().web_entities_size(); i++ ) {
                    response.web_detection().web_entities( i ).entity_id(); // string
                    response.web_detection().web_entities( i ).score(); // float
                    response.web_detection().web_entities( i ).description(); // string
                }

                std::cout << "Full Matching Images: " << response.web_detection().full_matching_images_size() << std::endl;
                for ( int i = 0; i < response.web_detection().full_matching_images_size(); i++ ) {
                    std::cout << "\tScore: "
                        << response.web_detection().full_matching_images( i ).score() // float
                        << "    URL: "
                        << response.web_detection().full_matching_images( i ).url() // string
                        << std::endl;
                }
                
                std::cout << "Partially Matching Images: " << response.web_detection().partial_matching_images_size() << std::endl;
                for ( int i = 0; i < response.web_detection().partial_matching_images_size(); i++ ) {
                    std::cout << "\tScore: "
                        << response.web_detection().partial_matching_images( i ).score() // float
                        << "    URL: "
                        << response.web_detection().partial_matching_images( i ).url() // string
                        << std::endl;
                }

                std::cout << "Pages With Matching Images: " << response.web_detection().pages_with_matching_images_size() << std::endl;
                for ( int i = 0; i < response.web_detection().pages_with_matching_images_size(); i ++ ) {
                    std::cout << "\tScore: "
                        << response.web_detection().pages_with_matching_images( i ).score() // float
                        << "    URL: "
                        << response.web_detection().pages_with_matching_images( i ).url() // string
                        << std::endl;
                }

                
            
            
            } else { std::cout << "NONE" << std::endl; }

        }


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
// TODO: [GCS_URL] User Spcific, you will need to upload a picture to google cloud storageand replace the "gs://personal_projects/photo.jpg" with your gcs path. //
// TODO: [FA_LANDMARK] FaceAnnotation_Landmark not returning data correctly //
