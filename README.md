#Initial commit
---
**PLEASE NOTE THIS WILL JUST COMPILE THE PROTO FILES**
**THE PROGRAM DOES _NOTHING_**

This is just the "template" for the gRPC implimentations of Google's "Cloud Vision API".
https://cloud.google.com/vision/docs/reference/rpc/

## Cloud Vision API (C++)
C++ implmentations using Google's Speech (v1Beta1) API. Checkout Google's [Speech API](https://cloud.google.com/speech/)
ALL projects  use  gRPC wich you can checkout at their [Main Website](http://www.grpc.io/) or the [Git Repo](https://github.com/grpc/grpc)

## Plase note!! 

### Proto file naming change

As of 3/21/2017 if you create the proto file based off of Google's Cloud Vision Documentation page the enum "Likelihood" has a property named "UNKNOWN". This nameing method causes an error b/c "UNKNOWN" is a predefined whatver-ya-call-it in C++. 

This can easily be fixed by changing the enum property "UNKNOWN" to "NOT_KNOWN". (Which has already been done for convenience sake)  **BE AWARE: doing so may cause future issues in later development.** 


```
    Note that enum values use C++ scoping rules, meaning that enum values are siblings of their type, not children of it.  Therefore, "UNKNOWN" must be unique within "google_cloud_vision_v1", not just within "Likelihood".

```

### TextProperty  
    
As of 3/21/2017 it is not clearly noted in Google's Documentation that the "TextProperty" message is [nested](https://developers.google.com/protocol-buffers/docs/proto3#nested). 

Therefore when using the "TextProperty" message it must be used as "TextAnnotation.TextProperty". (This has already been changed in the .proto file)
