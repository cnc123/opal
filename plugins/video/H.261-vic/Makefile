#
# Makefile for vic H.261
#
# Copyright (C) 2004 Post Increment, All Rights Reserved
#
# The contents of this file are subject to the Mozilla Public License
# Version 1.0 (the "License"); you may not use this file except in
# compliance with the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS"
# basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
# the License for the specific language governing rights and limitations
# under the License.
#
# The Original Code is Open H323 library.
#
# The Initial Developer of the Original Code is Post Increment
#
# Contributor(s): ______________________________________.
#
# $Revision$
# $Author$
# $Date$
#

BASENAME := h261_vic

COMMONDIR := $(abspath ../common)
SRCDIR    := $(CURDIR)/vic
SOURCES   := $(CURDIR)/h261vic.cxx \
             $(SRCDIR)/encoder-h261.cxx \
             $(SRCDIR)/transmitter.cxx \
             $(SRCDIR)/vid_coder.cxx \
             $(SRCDIR)/p64encoder.cxx \
             $(SRCDIR)/p64.cxx \
             $(SRCDIR)/dct.cxx \
             $(SRCDIR)/huffcode.c \
             $(SRCDIR)/bv.c \


CPPFLAGS += -I$(COMMONDIR)

INSTALL_DIR = $(VID_PLUGIN_DIR)
include $(dir $(lastword $(MAKEFILE_LIST)))../../plugin_inc.mak


###########################################
