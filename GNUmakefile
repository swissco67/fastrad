#****************************************************************
#* GNUmakefile for construction of project: Ht
#*
#* Creation: 2019/11/22 by Fastrad ((C) 2019)
#* Last Modified: 
#*****************************************************************
#
APP_NAME := Ht

PROJECT_TOP := $(GDMLROOT)/CPPGDML

REQUIRED_PACKAGES := Common/Saxana \
		             Common/Processes \
		             Common/Writer \
                     G4Binding/G4Evaluator \
		             G4Binding/G4Processor \
		             G4Binding/G4Subscribers \
		             G4Binding/G4Writer

PROJECT_INCLUDES  += -I$(PROJECT_TOP)/Common/Schema

# Define external dependencies
REQUIRE_XERCESC  := any
REQUIRE_CLHEP    := any
REQUIRE_GEANT4   := any

all: $(APP_NAME)_target

# Build this package
include $(PROJECT_TOP)/config/make/application.gmk

