##  -- This project is not maintained. Don't expect anyhting to work. 🤷🏼 --

# Overview


## Cloud Vision API (C++)
C++ gRPC implmentations using Google's Vision API. Not to be confused with their Video API. Checkout Google's [Vision API](https://cloud.google.com/vision/docs/reference/rpc/).

ALL projects  use  gRPC wich you can checkout at their [Main Website](http://www.grpc.io/) or the [Git Repo](https://github.com/grpc/grpc)


## Usage

### Prerequisites

Install and configure [Protocol Buffers (proto3)](https://developers.google.com/protocol-buffers/) along with gRPC. The [Quickstart](http://www.grpc.io/docs/quickstart/cpp.html) section on grpc.io covers the installation/setup process in more detail. 

```
Arch Linux:
Note: This installs both gRPC and Proto3.

yaourt -S grpc
```

### Tweak the code
There are section of the code you will need to change before using. These sections should be marked with a comment "// TODO: [SEARCHABLE_REFRENCE]". Each TODO comment in the code should have a corrosponding TODO comment at the bottom of the page with details. Read the comment on that line and it's corrosponding TODO comment found on the bottom of the page.


### Compile
In order to compile this you will need to use *make*.

### Running
Currently the program takes no arguments, this will change once it's updated to support requests with local image files. 

```
./cloud-vision-api
```

### Your results

The results you get back from the API may seem incomplete. I'm currently looking into why some of the results are incomplete. Regardless, for refrence you can compare your results with [Example_Output.txt](/Example_Output.txt) and the image used [photo.jpg](/photo.jpg).


## Plase note!! 

### Proto file naming change

~~As of 3/21/2017 if you create the proto file based off of Google's Cloud Vision Documentation page the enum "Likelihood" has a property named "UNKNOWN". This nameing method causes an error b/c "UNKNOWN" is a predefined whatver-ya-call-it in C++.~~

~~This can easily be fixed by changing the enum property "UNKNOWN" to "NOT_KNOWN". (Which has already been done for convenience sake)  **BE AWARE: doing so may cause future issues in later development.**~~

### TextProperty  
    
As of 3/21/2017 it is not clearly noted in Google's Documentation that the "TextProperty" message is [nested](https://developers.google.com/protocol-buffers/docs/proto3#nested). 

Therefore when using the "TextProperty" message it must be used as "TextAnnotation.TextProperty". (This has already been changed in the .proto file). **You don't need to worry about this unless you decide to mess with the proto files**


## Support

The prefered method to get support, help or ask a question (and I'd be happy to help!) is through the issues section on Github. In the off chance you don't get a response Google has a support page [here](https://cloud.google.com/vision/docs/support) that states the following.

"Ask a question about Google Cloud Vision API on [Stack Overflow](http://stackoverflow.com/questions/tagged/google-cloud-vision). Please use the tag google-cloud-vision for questions about Cloud Vision API. This tag not only receives responses from the Stack Overflow community, but also from Google engineers, who monitor the tag and offer unofficial support."

"Join the [cloud-vision-discuss](https://groups.google.com/forum/#!forum/cloud-vision-discuss) Google group to discuss Cloud Vision API and receive Cloud Vision API announcements and updates."






