CXX = g++
CPPFLAGS += -I/usr/local/include -pthread
CXXFLAGS += -std=c++14
LDFLAGS += -L/usr/local/lib -lgrpc++ \
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed \
           -lprotobuf -lpthread -ldl

#LIBS=-lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -lpthread
#INC=~/Documents/Development/git/SMFL/include

PROTO_TARGET=google_cloud_vision_v1
PROTO_PROTOC=protoc
PROTO_PATH=.
PROTO_PROTO=proto

CPP_TARGET=main

GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

PROTOS_PATH = .


vpath %.proto $(PROTOS_PATH)


all: system-check main_cpp

main_cpp: google_cloud_vision_v1.pb.o google_cloud_vision_v1.grpc.pb.o google_type.pb.o google_type.grpc.pb.o main.o
	$(CXX) $^ $(LDFLAGS) $(LIBS) -o $@

.PRECIOUS: %.grpc.pb.cc
%.grpc.pb.cc: %.proto
	$(PROTO_PROTOC) -I $(PROTOS_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) google_cloud_vision_v1.proto google_type.proto
.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTO_PROTOC) -I $(PROTOS_PATH) --cpp_out=. google_cloud_vision_v1.proto google_type.proto

clean:
	$(RM) $(CPP_TARGET)_cpp *.o *.pb.cc *.pb.h



# The following is to test your system and ensure a smoother experience.
# They are by no means necessary to actually compile a grpc-enabled software.

PROTOC_CMD = which $(PROTO_PROTOC)
PROTOC_CHECK_CMD = $(PROTO_PROTOC) --version | grep -q libprotoc.3
PLUGIN_CHECK_CMD = which $(GRPC_CPP_PLUGIN)
HAS_PROTOC = $(shell $(PROTOC_CMD) > /dev/null && echo true || echo false)
ifeq ($(HAS_PROTOC),true)
HAS_VALID_PROTOC = $(shell $(PROTOC_CHECK_CMD) 2> /dev/null && echo true || echo false)
endif
HAS_PLUGIN = $(shell $(PLUGIN_CHECK_CMD) > /dev/null && echo true || echo false)

SYSTEM_OK = false
ifeq ($(HAS_VALID_PROTOC),true)
ifeq ($(HAS_PLUGIN),true)
SYSTEM_OK = true
endif
endif

system-check:
ifneq ($(HAS_VALID_PROTOC),true)
	@echo " DEPENDENCY ERROR"
	@echo
	@echo "You don't have protoc 3.0.0 installed in your path."
	@echo "Please install Google protocol buffers 3.0.0 and its compiler."
	@echo "You can find it here:"
	@echo
	@echo "   https://github.com/google/protobuf/releases/tag/v3.0.0"
	@echo
	@echo "Here is what I get when trying to evaluate your version of protoc:"
	@echo
	-$(PROTOC) --version
	@echo
	@echo
endif
ifneq ($(SYSTEM_OK),true)
	@false
endif
