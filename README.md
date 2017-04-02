# Overview

**__THE CODE HERE IS STILL IN DEVELOPMENT. IN OTHER WORDS DON'T WASTE YOUR TIME TRYING TO FIGURE OUT HOW TO USE THIS B/C I'LL HAVE A USEABLE VERSON AVAIABLE SOON (maybe a few days)__**


## Cloud Vision API (C++)
C++ gRPC implmentations using Google's Vision API. Not to be confused with their Video API. Checkout Google's [Vision API](https://cloud.google.com/vision/docs/reference/rpc/).

ALL projects  use  gRPC wich you can checkout at their [Main Website](http://www.grpc.io/) or the [Git Repo](https://github.com/grpc/grpc)


## Usage

### Prerequisites
To use this you need to install and configure the [Google Cloud SDK](https://cloud.google.com/sdk/).

``` Arch linux: 

yaourt -S google-cloud-sdk
```

Install and configure [Protocol Buffers (proto3)](https://developers.google.com/protocol-buffers/) along with gRPC. The [Quickstart](http://www.grpc.io/docs/quickstart/cpp.html) section on grpc.io covers the installation/setup process in more detail. 

```Arch Linux:
Note: This installs both gRPC and Proto3.

yaourt -S grpc
```

### Tweak the code
There are section of the code you will need to change before using. These sections should be marked with a comment "TODO". Read the comment on that line and it's corrosponding TODO comment found on the bottom of the page.


### Compile
In order to compile this you will need to use *make*.

### Running
Currently it takes no arguments, this will change once it's updated to support requests with  local files. 


## Plase note!! 

### Proto file naming change

~~As of 3/21/2017 if you create the proto file based off of Google's Cloud Vision Documentation page the enum "Likelihood" has a property named "UNKNOWN". This nameing method causes an error b/c "UNKNOWN" is a predefined whatver-ya-call-it in C++.~~

~~This can easily be fixed by changing the enum property "UNKNOWN" to "NOT_KNOWN". (Which has already been done for convenience sake)  **BE AWARE: doing so may cause future issues in later development.**~~


```
    Note that enum values use C++ scoping rules, meaning that enum values are siblings of their type, not children of it.  Therefore, "UNKNOWN" must be unique within "google_cloud_vision_v1", not just within "Likelihood".

```

### TextProperty  
    
As of 3/21/2017 it is not clearly noted in Google's Documentation that the "TextProperty" message is [nested](https://developers.google.com/protocol-buffers/docs/proto3#nested). 

Therefore when using the "TextProperty" message it must be used as "TextAnnotation.TextProperty". (This has already been changed in the .proto file). **You don't need to worry about this unless you decide to mess with the proto files**






