/*
 * main.cxx
 *
 * A simple H.323 "net telephone" application.
 *
 * Copyright (c) 2000 Equivalence Pty. Ltd.
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is Portable Windows Library.
 *
 * The Initial Developer of the Original Code is Equivalence Pty. Ltd.
 *
 * Contributor(s): ______________________________________.
 *
 * $Revision$
 * $Author$
 * $Date$
 */

#include <ptlib.h>

#include <opal_config.h>

#if OPAL_IAX2
#include <iax2/iax2.h>
#endif

#if OPAL_CAPI
#include <lids/capi_ep.h>
#endif

#if OPAL_SIP
#include <sip/sip.h>
#endif

#if OPAL_H323
#include <h323/h323.h>
#include <h323/gkclient.h>
#endif

#if OPAL_FAX
#include <t38/t38proto.h>
#endif

#include <opal/transcoders.h>
#include <codec/opalpluginmgr.h>
#include <lids/lidep.h>

#include <ptlib/config.h>
#include <ptclib/pstun.h>

#include "main.h"
#include "../../version.h"


#define new PNEW

PCREATE_PROCESS(SimpleOpalProcess);

///////////////////////////////////////////////////////////////

SimpleOpalProcess::SimpleOpalProcess()
  : PProcess("Open Phone Abstraction Library", "SimpleOPAL",
             MAJOR_VERSION, MINOR_VERSION, BUILD_TYPE, BUILD_NUMBER)
{
}


void SimpleOpalProcess::Main()
{
  cout << GetName()
       << " Version " << GetVersion(true)
       << " by " << GetManufacturer()
       << " on " << GetOSClass() << ' ' << GetOSName()
       << " (" << GetOSVersion() << '-' << GetOSHardware() << ")\n\n";

  // Get and parse all of the command line arguments.
  PArgList & args = GetArguments();
  args.Parse(
             "a-auto-answer."
             "b-bandwidth:"
             "D-disable:"
             "d-dial-peer:"
             "-disableui."
             "e-silence."
             "f-fast-disable."
             "g-gatekeeper:"
             "G-gk-id:"
             "-gk-token:"
             "-disable-grq."
             "h-help."
             "H-no-h323."
#if OPAL_PTLIB_SSL
             "-no-h323s."
             "-h323s-listen:"
             "-h323s-gk:"
#endif
             "-h323-listen:"
             "I-no-sip."
             "j-jitter:"
             "l-listen."
#if OPAL_LID
             "L-no-lid."
             "-lid:"
             "-country:"
#endif
             "-no-std-dial-peer."
#if PTRACING
             "o-output:"
#endif
             "O-option:"
             "P-prefer:"
             "p-password:"
             "-portbase:"
             "-portmax:"
             "R-require-gatekeeper."
             "r-register-sip:"
             "-rtp-base:"
             "-rtp-max:"
             "-rtp-tos:"
             "s-sound:"
             "S-no-sound."
             "-sound-in:"
             "-sound-out:"
             "-srcep:"
             "-sip-listen:"
             "-sip-proxy:"
             "-sip-domain:"
             "-sip-contact-nomultiple."
             "-sip-contact-noprivate."  
             "-sip-user-agent:"
             "-sip-ui:"
             "-stun:"
             "T-h245tunneldisable."
             "-translate:"
             "-tts:"

#if PTRACING
             "t-trace."
#endif
             "-tcp-base:"
             "-tcp-max:"
             "u-user:"
             "-udp-base:"
             "-udp-max:"
#if OPAL_VIDEO
             "C-ratecontrol:"
             "-rx-video." "-no-rx-video."
             "-tx-video." "-no-tx-video."
             "-grabber:"
             "-grabdriver:"
             "-grabchannel:"
             "-display:"
             "-displaydriver:"
             "-preview:"
             "-previewdriver:"
             "-video-size:"
             "-video-rate:"
             "-video-bitrate:"
#endif
#if OPAL_IVR
             "V-no-ivr."
             "x-vxml:"
#endif
#if OPAL_IAX2
             "X-no-iax2."
	     "-iaxport:"
#endif
#if OPAL_CAPI
             "-no-capi."
#endif
          , false);


  if (args.HasOption('h') || (!args.HasOption('l') && args.GetCount() == 0)) {
    cout << "Usage : " << GetFile().GetTitle() << " [options] -l\n"
            "      : " << GetFile().GetTitle() << " [options] [alias@]hostname   (no gatekeeper)\n"
            "      : " << GetFile().GetTitle() << " [options] alias[@hostname]   (with gatekeeper)\n"
            "General options:\n"
            "  -l --listen             : Listen for incoming calls.\n"
            "  -d --dial-peer spec     : Set dial peer for routing calls (see below)\n"
            "     --no-std-dial-peer   : Do not include the standard dial peers\n"
            "  -a --auto-answer        : Automatically answer incoming calls.\n"
            "  -u --user name          : Set local alias name(s) (defaults to login name).\n"
            "  -p --password pwd       : Set password for user (gk or SIP authorisation).\n"
            "  -D --disable media      : Disable the specified codec (may be used multiple times)\n"
            "  -P --prefer media       : Prefer the specified codec (may be used multiple times)\n"
            "  -O --option fmt:opt=val : Set codec option (may be used multiple times)\n"
            "                          :  fmt is name of codec, eg \"H.261\"\n"
            "                          :  opt is name of option, eg \"Target Bit Rate\"\n"
            "                          :  val is value of option, eg \"48000\"\n"
            "  --srcep ep              : Set the source endpoint to use for making calls\n"
            "  --disableui             : disable the user interface\n"
            "\n"
            "Audio options:\n"
            "  -j --jitter [min-]max   : Set minimum (optional) and maximum jitter buffer (in milliseconds).\n"
            "  -e --silence            : Disable transmitter silence detection.\n"
            "\n"
#if OPAL_VIDEO
            "Video options:\n"
            "     --rx-video           : Start receiving video immediately.\n"
            "     --tx-video           : Start transmitting video immediately.\n"
            "     --no-rx-video        : Don't start receiving video immediately.\n"
            "     --no-tx-video        : Don't start transmitting video immediately.\n"
            "     --grabber dev        : Set the video grabber device.\n"
            "     --grabdriver dev     : Set the video grabber driver (if device name is ambiguous).\n"
            "     --grabchannel num    : Set the video grabber device channel.\n"
            "     --display dev        : Set the remote video display device.\n"
            "     --displaydriver dev  : Set the remote video display driver (if device name is ambiguous).\n"
            "     --preview dev        : Set the local video preview device.\n"
            "     --previewdriver dev  : Set the local video preview driver (if device name is ambiguous).\n"
            "     --video-size size    : Set the size of the video for all video formats, use\n"
            "                          : \"qcif\", \"cif\", WxH etc\n"
            "     --video-rate rate    : Set the frame rate of video for all video formats\n"
            "     --video-bitrate rate : Set the bit rate for all video formats\n"
            "     -C string            : Enable and select video rate control algorithm\n"
            "\n"
#endif

#if OPAL_SIP
            "SIP options:\n"
            "  -I --no-sip             : Disable SIP protocol.\n"
            "  -r --register-sip host  : Register with SIP server.\n"
            "     --sip-proxy url      : SIP proxy information, may be just a host name\n"
            "                          : or full URL eg sip:user:pwd@host\n"
            "     --sip-listen iface   : Interface/port(s) to listen for SIP requests\n"
            "                          : '*' is all interfaces, (default udp$:*:5060)\n"
            "     --sip-user-agent name: SIP UserAgent name to use.\n"
            "     --sip-ui type        : Set type of user indications to use for SIP. Can be one of 'rfc2833', 'info-tone', 'info-string'.\n"
            "     --sip-domain str     : set authentication domain/realm\n"
            "     --sip-contact-nomultiple : do not send multiple contacts in Contact field\n"
            "     --sip-contact-noprivate  : do not send private contacts in Contact field\n"
            "\n"
#endif

#if OPAL_H323
            "H.323 options:\n"
            "  -H --no-h323            : Disable H.323 protocol.\n"
#if OPAL_PTLIB_SSL
            "     --no-h323s           : Do not create secure H.323 endpoint\n"
#endif
            "  -g --gatekeeper host    : Specify gatekeeper host, '*' indicates broadcast discovery.\n"
            "  -G --gk-id name         : Specify gatekeeper identifier.\n"
#if OPAL_PTLIB_SSL
            "     --h323s-gk host      : Specify gatekeeper host for secure H.323 endpoint\n"
#endif
            "  -R --require-gatekeeper : Exit if gatekeeper discovery fails.\n"
            "     --gk-token str       : Set gatekeeper security token OID.\n"
            "     --disable-grq        : Do not send GRQ when registering with GK\n"
            "  -b --bandwidth bps      : Limit bandwidth usage to bps bits/second.\n"
            "  -f --fast-disable       : Disable fast start.\n"
            "  -T --h245tunneldisable  : Disable H245 tunnelling.\n"
            "     --h323-listen iface  : Interface/port(s) to listen for H.323 requests\n"
#if OPAL_PTLIB_SSL
            "     --h323s-listen iface : Interface/port(s) to listen for secure H.323 requests\n"
#endif
            "                          : '*' is all interfaces, (default tcp$:*:1720)\n"
#endif

            "\n"
#if OPAL_LID
            "Line Interface options:\n"
            "  -L --no-lid             : Do not use line interface device.\n"
            "     --lid device         : Select line interface device (eg Quicknet:013A17C2, default *:*).\n"
            "     --country code       : Select country to use for LID (eg \"US\", \"au\" or \"+61\").\n"
            "\n"
#endif
            "Sound card options:\n"
            "  -S --no-sound           : Do not use sound input/output device.\n"
            "  -s --sound device       : Select sound input/output device.\n"
            "     --sound-in device    : Select sound input device.\n"
            "     --sound-out device   : Select sound output device.\n"
            "\n"
#if OPAL_IVR
            "IVR options:\n"
            "  -V --no-ivr             : Disable IVR.\n"
            "  -x --vxml file          : Set vxml file to use for IVR.\n"
            "  --tts engine            : Set the text to speech engine\n"
            "\n"
#endif
            "IP options:\n"
            "     --translate ip       : Set external IP address if masqueraded\n"
            "     --portbase n         : Set TCP/UDP/RTP port base\n"
            "     --portmax n          : Set TCP/UDP/RTP port max\n"
            "     --tcp-base n         : Set TCP port base (default 0)\n"
            "     --tcp-max n          : Set TCP port max (default base+99)\n"
            "     --udp-base n         : Set UDP port base (default 6000)\n"
            "     --udp-max n          : Set UDP port max (default base+199)\n"
            "     --rtp-base n         : Set RTP port base (default 5000)\n"
            "     --rtp-max n          : Set RTP port max (default base+199)\n"
            "     --rtp-tos n          : Set RTP packet IP TOS bits to n\n"
#ifdef P_STUN
	    "     --stun server        : Set STUN server\n"
#endif
            "\n"
            "Debug options:\n"
            PTRACE_ARGLIST
#if OPAL_IAX2
            "  -X --no-iax2            : Remove support for iax2\n"
            "     --iaxport n          : Set port to use (def. 4569)\n"
#endif
#if OPAL_CAPI
            "     --no-capi            : Remove support for CAPI ISDN\n"
#endif
            "  -h --help               : This help message.\n"
            "\n"
            "\n"
            "Dial peer specification:\n"
"  General form is pattern=destination where pattern is a regular expression\n"
"  matching the incoming calls destination address and will translate it to\n"
"  the outgoing destination address for making an outgoing call. For example,\n"
"  picking up a PhoneJACK handset and dialling 2, 6 would result in an address\n"
"  of \"pots:26\" which would then be matched against, say, a spec of\n"
"  pots:26=h323:10.0.1.1, resulting in a call from the pots handset to\n"
"  10.0.1.1 using the H.323 protocol.\n"
"\n"
"  As the pattern field is a regular expression, you could have used in the\n"
"  above .*:26=h323:10.0.1.1 to achieve the same result with the addition that\n"
"  an incoming call from a SIP client would also be routed to the H.323 client.\n"
"\n"
"  Note that the pattern has an implicit ^ and $ at the beginning and end of\n"
"  the regular expression. So it must match the entire address.\n"
"\n"
"  If the specification is of the form @filename, then the file is read with\n"
"  each line consisting of a pattern=destination dial peer specification. Lines\n"
"  without and equal sign or beginning with '#' are ignored.\n"
"\n"
"  The standard dial peers that will be included are:\n"
"    If SIP is enabled but H.323 & IAX2 are disabled:\n"
"      pots:.*\\*.*\\*.* = sip:<dn2ip>\n"
"      pots:.*         = sip:<da>\n"
"      pc:.*           = sip:<da>\n"
"\n"
"    If SIP & IAX2 are not enabled and H.323 is enabled:\n"
"      pots:.*\\*.*\\*.* = h323:<dn2ip>\n"
"      pots:.*         = h323:<da>\n"
"      pc:.*           = h323:<da>\n"
"\n"
"    If POTS is enabled:\n"
"      h323:.* = pots:<dn>\n"
"      sip:.*  = pots:<dn>\n"
"      iax2:.* = pots:<dn>\n"
"\n"
"    If POTS is not enabled and the PC sound system is enabled:\n"
"      iax2:.* = pc:\n"
"      h323:.* = pc:\n"
"      sip:. * = pc:\n"
"\n"
#if OPAL_IVR
"    If IVR is enabled then a # from any protocol will route it it, ie:\n"
"      .*:#  = ivr:\n"
"\n"
#endif
#if OPAL_IAX2
"    If IAX2 is enabled then you can make a iax2 call with a command like:\n"
"       simpleopal -I -H  iax2:guest@misery.digium.com/s\n"
"           ((Please ensure simplopal is the only iax2 app running on your box))\n"
#endif
            << endl;
    return;
  }

  PTRACE_INITIALISE(args);

  // Create the Opal Manager and initialise it
  opal = new MyManager;

  if (opal->Initialise(args))
    opal->Main(args);

  cout << "Exiting " << GetName() << endl;

  delete opal;
}


///////////////////////////////////////////////////////////////

MyManager::MyManager()
{
#if OPAL_LID
  potsEP = NULL;
#endif
  pcssEP = NULL;

#if OPAL_H323
  h323EP = NULL;
#endif
#if OPAL_SIP
  sipEP  = NULL;
#endif
#if OPAL_IAX2
  iax2EP = NULL;
#endif
#if OPAL_CAPI
  capiEP = NULL;
#endif
#if OPAL_IVR
  ivrEP  = NULL;
#endif
#if OPAL_FAX
  faxEP = NULL;
#endif

  pauseBeforeDialing = false;
}


MyManager::~MyManager()
{
#if OPAL_LID
  // Must do this before we destroy the manager or a crash will result
  if (potsEP != NULL)
    potsEP->RemoveAllLines();
#endif
}


PBoolean MyManager::Initialise(PArgList & args)
{
#if OPAL_VIDEO
  // Set the various global options
  if (args.HasOption("rx-video"))
    SetAutoStartReceiveVideo(true);
  if (args.HasOption("no-rx-video"))
    SetAutoStartReceiveVideo(false);
  if (args.HasOption("tx-video"))
    SetAutoStartTransmitVideo(true);
  if (args.HasOption("no-tx-video"))
    SetAutoStartTransmitVideo(false);

  // video input options
  if (args.HasOption("grabber")) {
    PVideoDevice::OpenArgs video = GetVideoInputDevice();
    video.deviceName = args.GetOptionString("grabber");
    video.driverName = args.GetOptionString("grabdriver");
    video.channelNumber = args.GetOptionString("grabchannel").AsInteger();
    if (args.HasOption("video-rate")) 
      video.rate = args.GetOptionString("video-rate").AsUnsigned();
    if (!SetVideoInputDevice(video)) {
      cerr << "Unknown grabber device " << video.deviceName << "\n"
              "Available devices are:" << setfill(',') << PVideoInputDevice::GetDriversDeviceNames("") << endl;
      return false;
    }
  }

  // remote video display options
  if (args.HasOption("display")) {
    PVideoDevice::OpenArgs video = GetVideoOutputDevice();
    video.deviceName = args.GetOptionString("display");
    video.driverName = args.GetOptionString("displaydriver");
    if (!SetVideoOutputDevice(video)) {
      cerr << "Unknown display device " << video.deviceName << "\n"
              "Available devices are:" << setfill(',') << PVideoOutputDevice::GetDriversDeviceNames("") << endl;
      return false;
    }
  }

  // local video preview options
  if (args.HasOption("preview")) {
    PVideoDevice::OpenArgs video = GetVideoPreviewDevice();
    video.deviceName = args.GetOptionString("preview");
    video.driverName = args.GetOptionString("previewdriver");
	if (!SetVideoPreviewDevice(video)) {
      cerr << "Unknown preview device " << video.deviceName << "\n"
              "Available devices are:" << setfill(',') << PVideoOutputDevice::GetDriversDeviceNames("") << endl;
      return false;
    }
  }
#endif

  if (args.HasOption('j')) {
    unsigned minJitter;
    unsigned maxJitter;
    PStringArray delays = args.GetOptionString('j').Tokenise(",-");
    if (delays.GetSize() < 2) {
      maxJitter = delays[0].AsUnsigned();
      minJitter = PMIN(GetMinAudioJitterDelay(), maxJitter);
    }
    else {
      minJitter = delays[0].AsUnsigned();
      maxJitter = delays[1].AsUnsigned();
    }
    if (minJitter >= 20 && minJitter <= maxJitter && maxJitter <= 1000)
      SetAudioJitterDelay(minJitter, maxJitter);
    else {
      cerr << "Jitter should be between 20 and 1000 milliseconds.\n";
      return false;
    }
  }

  silenceDetectParams.m_mode = args.HasOption('e') ? OpalSilenceDetector::NoSilenceDetection
                                                   : OpalSilenceDetector::AdaptiveSilenceDetection;

  if (args.HasOption('D'))
    SetMediaFormatMask(args.GetOptionString('D').Lines());
  if (args.HasOption('P'))
    SetMediaFormatOrder(args.GetOptionString('P').Lines());

  cout << "Jitter buffer: "  << GetMinAudioJitterDelay() << '-' << GetMaxAudioJitterDelay() << " ms\n";

#if P_NAT
  if (args.HasOption("translate")) {
    SetNATServer("Fixed", args.GetOptionString("translate"));
    cout << "External address set to " << GetNATServer() << '\n';
  }
#endif

  if (args.HasOption("portbase")) {
    unsigned portbase = args.GetOptionString("portbase").AsUnsigned();
    unsigned portmax  = args.GetOptionString("portmax").AsUnsigned();
    SetTCPPorts  (portbase, portmax);
    SetUDPPorts  (portbase, portmax);
    SetRtpIpPorts(portbase, portmax);
  } else {
    if (args.HasOption("tcp-base"))
      SetTCPPorts(args.GetOptionString("tcp-base").AsUnsigned(),
                  args.GetOptionString("tcp-max").AsUnsigned());

    if (args.HasOption("udp-base"))
      SetUDPPorts(args.GetOptionString("udp-base").AsUnsigned(),
                  args.GetOptionString("udp-max").AsUnsigned());

    if (args.HasOption("rtp-base"))
      SetRtpIpPorts(args.GetOptionString("rtp-base").AsUnsigned(),
                    args.GetOptionString("rtp-max").AsUnsigned());
  }

  if (args.HasOption("rtp-tos")) {
    unsigned tos = args.GetOptionString("rtp-tos").AsUnsigned();
    if (tos > 255) {
      cerr << "IP Type Of Service bits must be 0 to 255.\n";
      return false;
    }
    SetMediaTypeOfService(tos);
  }

  cout << "TCP ports: " << GetTCPPortBase() << '-' << GetTCPPortMax() << "\n"
          "UDP ports: " << GetUDPPortBase() << '-' << GetUDPPortMax() << "\n"
          "RTP ports: " << GetRtpIpPortBase() << '-' << GetRtpIpPortMax() << "\n"
          "RTP IP TOS: 0x" << hex << (unsigned)GetMediaTypeOfService() << dec << "\n"
#ifdef P_STUN
          "STUN server: "
#endif
          << flush;

#ifdef P_STUN
  if (args.HasOption("stun"))
    SetNATServer("STUN", args.GetOptionString("stun"));

  if (m_natMethod != NULL)
    cout << m_natMethod->GetServer() << " replies " << m_natMethod->GetNatTypeName();
  else
    cout << "None";
  cout << '\n';
#endif

  OpalMediaFormatList allMediaFormats;

  ///////////////////////////////////////
  // Open the LID if parameter provided, create LID based endpoint
#if OPAL_LID
  if (!args.HasOption('L')) {
    PStringArray devices = args.GetOptionString("lid").Lines();
    if (devices.IsEmpty() || devices[0] == "*" || devices[0] == "*:*")
      devices = OpalLineInterfaceDevice::GetAllDevices();
    for (PINDEX d = 0; d < devices.GetSize(); d++) {
      PINDEX colon = devices[d].Find(':');
      OpalLineInterfaceDevice * lid = OpalLineInterfaceDevice::Create(devices[d].Left(colon));
      if (lid->Open(devices[d].Mid(colon+1).Trim())) {
        if (args.HasOption("country")) {
          PString country = args.GetOptionString("country");
          if (!lid->SetCountryCodeName(country))
            cerr << "Could not set LID to country name \"" << country << '"' << endl;
        }

        // Create LID protocol handler, automatically adds to manager
        if (potsEP == NULL)
          potsEP = new OpalLineEndPoint(*this);
        if (potsEP->AddDevice(lid)) {
          cout << "Line interface device \"" << devices[d] << "\" added." << endl;
          allMediaFormats += potsEP->GetMediaFormats();
        }
      }
      else {
        cerr << "Could not open device \"" << devices[d] << '"' << endl;
        delete lid;
      }
    }
  }
#endif

  ///////////////////////////////////////
  // Create PC Sound System handler

  if (!args.HasOption('S')) {
    pcssEP = new MyPCSSEndPoint(*this);

    pcssEP->autoAnswer = args.HasOption('a');
    cout << "Auto answer is " << (pcssEP->autoAnswer ? "on" : "off") << "\n";
          
    if (!pcssEP->SetSoundDevice(args, "sound", PSoundChannel::Recorder))
      return false;
    if (!pcssEP->SetSoundDevice(args, "sound", PSoundChannel::Player))
      return false;
    if (!pcssEP->SetSoundDevice(args, "sound-in", PSoundChannel::Recorder))
      return false;
    if (!pcssEP->SetSoundDevice(args, "sound-out", PSoundChannel::Player))
      return false;

    allMediaFormats += pcssEP->GetMediaFormats();

    cout << "Sound output device: \"" << pcssEP->GetSoundChannelPlayDevice() << "\"\n"
            "Sound  input device: \"" << pcssEP->GetSoundChannelRecordDevice() << "\"\n"
#if OPAL_VIDEO
			"Video preview device: \"" << GetVideoPreviewDevice().deviceName << "\"\n"
            "Video output device: \"" << GetVideoOutputDevice().deviceName << "\"\n"
            "Video  input device: \"" << GetVideoInputDevice().deviceName << '"'
#endif
         << endl;
  }

#if OPAL_H323

  ///////////////////////////////////////
  // Create H.323 protocol handler
  if (!args.HasOption("no-h323")) {
    h323EP = new H323EndPoint(*this);
    if (!InitialiseH323EP(args, false, h323EP))
      return false;
  }

#endif

#if OPAL_IAX2
  ///////////////////////////////////////
  // Create IAX2 protocol handler

  if (!args.HasOption("no-iax2")) {
    iax2EP = new IAX2EndPoint(*this);

    PStringArray listeners;
    if (args.HasOption("iaxport"))
      listeners += "udp$*:" + args.GetOptionString("iaxport");
    iax2EP->StartListeners(listeners);

    if (!iax2EP->InitialisedOK()) {
      cerr << "IAX2 Endpoint is not initialised correctly" << endl;
      cerr << "Is there another application using the iax port? " << endl;
      return false;
    }

    if (args.HasOption('p'))
      iax2EP->SetPassword(args.GetOptionString('p'));
    
    if (args.HasOption('u')) {
      PStringArray aliases = args.GetOptionString('u').Lines();
      iax2EP->SetLocalUserName(aliases[0]);
    }
  }
#endif

#if OPAL_CAPI
  ///////////////////////////////////////
  // Create CAPI handler

  if (!args.HasOption("no-capi")) {
    capiEP = new OpalCapiEndPoint(*this);
    
    if (!capiEP->OpenControllers())
      cerr << "CAPI Endpoint failed to initialise any controllers." << endl;
  }
#endif

#if OPAL_SIP

  ///////////////////////////////////////
  // Create SIP protocol handler

  if (!args.HasOption("no-sip")) {
    sipEP = new SIPEndPoint(*this);

    if (args.HasOption("sip-user-agent"))
      sipEP->SetUserAgent(args.GetOptionString("sip-user-agent"));

    PString str = args.GetOptionString("sip-ui");
    if (str *= "rfc2833")
      sipEP->SetSendUserInputMode(OpalConnection::SendUserInputAsRFC2833);
    else if (str *= "info-tone")
      sipEP->SetSendUserInputMode(OpalConnection::SendUserInputAsTone);
    else if (str *= "info-string")
      sipEP->SetSendUserInputMode(OpalConnection::SendUserInputAsString);

    if (args.HasOption("sip-proxy"))
      sipEP->SetProxy(args.GetOptionString("sip-proxy"));

    // Get local username, multiple uses of -u indicates additional aliases
    if (args.HasOption('u')) {
      PStringArray aliases = args.GetOptionString('u').Lines();
      sipEP->SetDefaultLocalPartyName(aliases[0]);
    }

    // Start the listener thread for incoming calls.
    PStringArray listeners = args.GetOptionString("sip-listen").Lines();
    if (!sipEP->StartListeners(listeners)) {
      cerr <<  "Could not open any SIP listener from "
            << setfill(',') << listeners << endl;
      return false;
    }
    cout <<  "SIP started on " << setfill(',') << sipEP->GetListeners() << setfill(' ') << endl;

    if (args.HasOption('r')) {
      SIPRegister::Params params;
      params.m_registrarAddress = args.GetOptionString('r');
      params.m_addressOfRecord = args.GetOptionString('u');
      params.m_password = args.GetOptionString('p');
      params.m_realm = args.GetOptionString("sip-domain");
      if (args.HasOption("sip-contact-nomultiple"))
        params.m_compatibility = SIPRegister::e_CannotRegisterMultipleContacts;
      else if (args.HasOption("sip-contact-noprivate"))
        params.m_compatibility = SIPRegister::e_CannotRegisterPrivateContacts  ;
      PString aor;
      if (sipEP->Register(params, aor))
        cout << "Using SIP registrar " << params.m_registrarAddress << " for " << aor << endl;
      else
        cout << "Could not use SIP registrar " << params.m_registrarAddress << endl;
      pauseBeforeDialing = true;
    }
  }

#endif


#if OPAL_IVR
  ///////////////////////////////////////
  // Create IVR protocol handler

  if (!args.HasOption('V')) {
    ivrEP = new OpalIVREndPoint(*this);
    if (args.HasOption('x'))
      ivrEP->SetDefaultVXML(args.GetOptionString('x'));

    allMediaFormats += ivrEP->GetMediaFormats();

    PString ttsEngine = args.GetOptionString("tts");
    if (ttsEngine.IsEmpty() && PFactory<PTextToSpeech>::GetKeyList().size() > 0) 
      ttsEngine = PFactory<PTextToSpeech>::GetKeyList()[0];
    if (!ttsEngine.IsEmpty()) 
      ivrEP->SetDefaultTextToSpeech(ttsEngine);
  }
#endif

#if OPAL_FAX
#if OPAL_PTLIB_ASN
  ///////////////////////////////////////
  // Create T38 protocol handler
  {
    OpalMediaFormat fmt(OpalT38); // Force instantiation of T.38 media format
    faxEP = new OpalFaxEndPoint(*this);
    allMediaFormats += faxEP->GetMediaFormats();
  }
#endif
#endif

  ///////////////////////////////////////
  // Set the dial peers

  if (args.HasOption('d')) {
    if (!SetRouteTable(args.GetOptionString('d').Lines())) {
      cerr <<  "No legal entries in dial peer!" << endl;
      return false;
    }
  }

  if (!args.HasOption("no-std-dial-peer")) {
#if OPAL_IVR
    // Need to make sure wildcard on source ep type is first or it won't be
    // selected in preference to the specific entries below
    if (ivrEP != NULL)
      AddRouteEntry(".*:#  = ivr:"); // A hash from anywhere goes to IVR
#endif

#if OPAL_SIP
    if (sipEP != NULL) {
#if OPAL_FAX
      AddRouteEntry("t38:.*             = sip:<da>");
      AddRouteEntry("sip:.*\tfax@.*     = t38:received_fax_%s.tif;receive");
      AddRouteEntry("sip:.*\tsip:329@.* = t38:received_fax_%s.tif;receive");
#endif
      AddRouteEntry("pots:.*\\*.*\\*.*  = sip:<dn2ip>");
      AddRouteEntry("pots:.*            = sip:<da>");
      AddRouteEntry("pc:.*              = sip:<da>");
    }
#endif

#if OPAL_H323
    if (h323EP != NULL) {
      AddRouteEntry("pots:.*\\*.*\\*.* = h323:<dn2ip>");
      AddRouteEntry("pots:.*           = h323:<da>");
      AddRouteEntry("pc:.*             = h323:<da>");
#if OPAL_PTLIB_SSL
      {
        AddRouteEntry("pots:.*\\*.*\\*.* = h323s:<dn2ip>");
        AddRouteEntry("pots:.*           = h323s:<da>");
        AddRouteEntry("pc:.*             = h323s:<da>");
      }
#endif
    }
#endif

#if OPAL_LID
    if (potsEP != NULL) {
#if OPAL_H323
      AddRouteEntry("h323:.* = pots:<du>");
#if OPAL_PTLIB_SSL
      //if (h323sEP != NULL) 
        AddRouteEntry("h323s:.* = pots:<du>");
#endif
#endif
#if OPAL_SIP
      AddRouteEntry("sip:.*  = pots:<du>");
#endif
    }
    else
#endif // OPAL_LID
    if (pcssEP != NULL) {
#if OPAL_H323
      AddRouteEntry("h323:.* = pc:");
#if OPAL_PTLIB_SSL
      //if (h323sEP != NULL) 
        AddRouteEntry("h323s:.* = pc:");
#endif
#endif
#if OPAL_SIP
      AddRouteEntry("sip:.*  = pc:");
#endif
    }
  }
                                                                                                                                            
#if OPAL_IAX2
  if (pcssEP != NULL) {
    AddRouteEntry("iax2:.* = pc:");
    AddRouteEntry("pc:.*   = iax2:<da>");
  }
#endif

#if OPAL_CAPI
  if (capiEP != NULL) {
    AddRouteEntry("isdn:.* = pc:");
    AddRouteEntry("pc:.*   = isdn:<da>");
  }
#endif

#if OPAL_FAX
  if (faxEP != NULL) {
    AddRouteEntry("sip:.*  = t38:<da>");
    AddRouteEntry("sip:.*  = fax:<da>");
  }
#endif

  PString defaultSrcEP = pcssEP != NULL ? "pc:*"
                                      #if OPAL_LID
                                        : potsEP != NULL ? "pots:*"
                                      #endif
                                      #if OPAL_IVR
                                        : ivrEP != NULL ? "ivr:#"
                                      #endif
                                      #if OPAL_SIP
                                        : sipEP != NULL ? "sip:localhost"
                                      #endif
                                      #if OPAL_H323
                                        : h323EP != NULL ? "sip:localhost"
                                      #endif
                                        : "";
  srcEP = args.GetOptionString("srcep", defaultSrcEP);

  if (FindEndPoint(srcEP.Left(srcEP.Find(':'))) == NULL)
    srcEP = defaultSrcEP;

  allMediaFormats = OpalTranscoder::GetPossibleFormats(allMediaFormats); // Add transcoders
  allMediaFormats.RemoveNonTransportable();
  allMediaFormats.Remove(GetMediaFormatMask());
  allMediaFormats.Reorder(GetMediaFormatOrder());

  cout << "Local endpoint type: " << srcEP << "\n"
          "Codecs removed: " << setfill(',') << GetMediaFormatMask() << "\n"
          "Codec order: " << GetMediaFormatOrder() << "\n"
          "Available codecs: " << allMediaFormats << setfill(' ') << endl;

#if OPAL_VIDEO
  PString rcOption = args.GetOptionString('C');
  OpalMediaFormat::GetAllRegisteredMediaFormats(allMediaFormats);
  for (PINDEX i = 0; i < allMediaFormats.GetSize(); i++) {
    OpalMediaFormat mediaFormat = allMediaFormats[i];
    if (mediaFormat.GetMediaType() == OpalMediaType::Video()) {
      if (args.HasOption("video-size")) {
        PString sizeStr = args.GetOptionString("video-size");
        unsigned width, height;
        if (PVideoFrameInfo::ParseSize(sizeStr, width, height)) {
            mediaFormat.SetOptionInteger(OpalVideoFormat::FrameWidthOption(), width);
            mediaFormat.SetOptionInteger(OpalVideoFormat::FrameHeightOption(), height);
        }
        else
          cerr << "Unknown video size \"" << sizeStr << '"' << endl;
      }

      if (args.HasOption("video-rate")) {
        unsigned rate = args.GetOptionString("video-rate").AsUnsigned();
        unsigned frameTime = 90000 / rate;
        mediaFormat.SetOptionInteger(OpalMediaFormat::FrameTimeOption(), frameTime);
      }
      if (args.HasOption("video-bitrate")) {
        unsigned rate = args.GetOptionString("video-bitrate").AsUnsigned();
        mediaFormat.SetOptionInteger(OpalMediaFormat::TargetBitRateOption(), rate);
      }
      if (!rcOption.IsEmpty())
        mediaFormat.SetOptionString(OpalVideoFormat::RateControllerOption(), rcOption);
      OpalMediaFormat::SetRegisteredMediaFormat(mediaFormat);
    }
  }
#endif

  PStringArray options = args.GetOptionString('O').Lines();
  for (PINDEX i = 0; i < options.GetSize(); i++) {
    const PString & optionDescription = options[i];
    PINDEX colon = optionDescription.Find(':');
    PINDEX equal = optionDescription.Find('=', colon+2);
    if (colon == P_MAX_INDEX || equal == P_MAX_INDEX) {
      cerr << "Invalid option description \"" << optionDescription << '"' << endl;
      continue;
    }
    OpalMediaFormat mediaFormat = optionDescription.Left(colon);
    if (mediaFormat.IsEmpty()) {
      cerr << "Invalid media format in option description \"" << optionDescription << '"' << endl;
      continue;
    }
    PString optionName = optionDescription(colon+1, equal-1);
    if (!mediaFormat.HasOption(optionName)) {
      cerr << "Invalid option name in description \"" << optionDescription << '"' << endl;
      continue;
    }
    PString valueStr = optionDescription.Mid(equal+1);
    if (!mediaFormat.SetOptionValue(optionName, valueStr)) {
      cerr << "Invalid option value in description \"" << optionDescription << '"' << endl;
      continue;
    }
    OpalMediaFormat::SetRegisteredMediaFormat(mediaFormat);
    cout << "Set option \"" << optionName << "\" to \"" << valueStr << "\" in \"" << mediaFormat << '"' << endl;
  }

#if PTRACING
  allMediaFormats = OpalMediaFormat::GetAllRegisteredMediaFormats();
  ostream & traceStream = PTrace::Begin(3, __FILE__, __LINE__);
  traceStream << "Simple\tRegistered media formats:\n";
  for (PINDEX i = 0; i < allMediaFormats.GetSize(); i++)
    allMediaFormats[i].PrintOptions(traceStream);
  traceStream << PTrace::End;
#endif
  return true;
}

#if OPAL_H323

PBoolean MyManager::InitialiseH323EP(PArgList & args, PBoolean secure, H323EndPoint * h323EP)
{
  h323EP->DisableFastStart(args.HasOption('f'));
  h323EP->DisableH245Tunneling(args.HasOption('T'));
  h323EP->SetSendGRQ(!args.HasOption("disable-grq"));


  // Get local username, multiple uses of -u indicates additional aliases
  if (args.HasOption('u')) {
    PStringArray aliases = args.GetOptionString('u').Lines();
    h323EP->SetLocalUserName(aliases[0]);
    for (PINDEX i = 1; i < aliases.GetSize(); i++)
      h323EP->AddAliasName(aliases[i]);
  }

  if (args.HasOption('b')) {
    OpalBandwidth initialBandwidth = args.GetOptionString('b').AsUnsigned();
    if (initialBandwidth == 0) {
      cerr << "Illegal bandwidth specified." << endl;
      return false;
    }
    h323EP->SetInitialBandwidth(OpalBandwidth::RxTx, initialBandwidth);
  }

  h323EP->SetGkAccessTokenOID(args.GetOptionString("gk-token"));

  PString prefix = h323EP->GetPrefixName();

  cout << prefix << " Local username: " << h323EP->GetLocalUserName() << "\n"
       << prefix << " FastConnect is " << (h323EP->IsFastStartDisabled() ? "off" : "on") << "\n"
       << prefix << " H245Tunnelling is " << (h323EP->IsH245TunnelingDisabled() ? "off" : "on") << "\n"
       << prefix << " gk Token OID is " << h323EP->GetGkAccessTokenOID() << endl;


  // Start the listener thread for incoming calls.
  PStringArray listeners = args.GetOptionString(secure ? "h323s-listen" : "h323-listen").Lines();
  if (!h323EP->StartListeners(listeners)) {
    cerr <<  "Could not open any " << prefix << " listener from "
         << setfill(',') << listeners << endl;
    return false;
  }
  cout << prefix << " listeners: " << setfill(',') << h323EP->GetListeners() << setfill(' ') << endl;


  if (args.HasOption('p'))
    h323EP->SetGatekeeperPassword(args.GetOptionString('p'));

  // Establish link with gatekeeper if required.
  if (args.HasOption(secure ? "h323s-gk" : "gatekeeper")) {
    PString gkHost      = args.GetOptionString(secure ? "h323s-gk" : "gatekeeper");
    if (gkHost == "*")
      gkHost = PString::Empty();
    PString gkIdentifer = args.GetOptionString('G');
    PString gkInterface = args.GetOptionString(secure ? "h323s-listen" : "h323-listen");
    cout << "Gatekeeper: " << flush;
    if (h323EP->UseGatekeeper(gkHost, gkIdentifer, gkInterface))
      cout << *h323EP->GetGatekeeper() << endl;
    else {
      cout << "none." << endl;
      cerr << "Could not register with gatekeeper";
      if (!gkIdentifer)
        cerr << " id \"" << gkIdentifer << '"';
      if (!gkHost)
        cerr << " at \"" << gkHost << '"';
      if (!gkInterface)
        cerr << " on interface \"" << gkInterface << '"';
      if (h323EP->GetGatekeeper() != NULL) {
        switch (h323EP->GetGatekeeper()->GetRegistrationFailReason()) {
          case H323Gatekeeper::InvalidListener :
            cerr << " - Invalid listener";
            break;
          case H323Gatekeeper::DuplicateAlias :
            cerr << " - Duplicate alias";
            break;
          case H323Gatekeeper::SecurityDenied :
            cerr << " - Security denied";
            break;
          case H323Gatekeeper::TransportError :
            cerr << " - Transport error";
            break;
          default :
            cerr << " - Error code " << h323EP->GetGatekeeper()->GetRegistrationFailReason();
        }
      }
      cerr << '.' << endl;
      if (args.HasOption("require-gatekeeper")) 
        return false;
    }
  }
  return true;
}

#endif  //OPAL_H323


#if OPAL_PTLIB_CONFIG_FILE
void MyManager::NewSpeedDial(const PString & ostr)
{
  PString str = ostr;
  PINDEX idx = str.Find(' ');
  if (str.IsEmpty() || (idx == P_MAX_INDEX)) {
    cout << "Must specify speedial number and string" << endl;
    return;
  }
 
  PString key  = str.Left(idx).Trim();
  PString data = str.Mid(idx).Trim();
 
  PConfig config("Speeddial");
  config.SetString(key, data);
 
  cout << "Speedial " << key << " set to " << data << endl;
}
#endif // OPAL_PTLIB_CONFIG_FILE
 

void MyManager::Main(PArgList & args)
{
  OpalConnection::StringOptions stringOptions;

  // See if making a call or just listening.
  switch (args.GetCount()) {
    case 0 :
      cout << "Waiting for incoming calls\n";
      break;

    case 1 :
      if (pauseBeforeDialing) {
        cout << "Pausing to allow registration to occur..." << flush;
        PThread::Sleep(2000);
        cout << "done" << endl;
      }

      cout << "Initiating call to \"" << args[0] << "\"\n";
      SetUpCall(srcEP, args[0], currentCallToken, 0, 0, &stringOptions);
      break;

    default :
      if (pauseBeforeDialing) {
        cout << "Pausing to allow registration to occur..." << flush;
        PThread::Sleep(2000);
        cout << "done" << endl;
      }
      cout << "Initiating call from \"" << args[0] << "\"to \"" << args[1] << "\"\n";
      SetUpCall(args[0], args[1], currentCallToken, 0, 0, &stringOptions);
      break;
  }

  if (args.HasOption("disableui")) {
    while (FindCallWithLock(currentCallToken) != NULL) 
      PThread::Sleep(1000);
  }
  else {
    cout << "Press ? for help." << endl;

    PStringStream help;

    help << "Select:\n"
            "  0-9 : send user indication message\n"
            "  *,# : send user indication message\n"
            "  M   : send text message to remote user\n"
            "  C   : Connect to remote host\n"
            "  S   : Display statistics\n"
            "  O   : Put call on hold\n"
            "  T   : Transfer remote to new destination or held call\n"
            "  H   : Hang up phone\n"
            "  L   : List speed dials\n"
            "  D   : Create new speed dial\n"
            "  {}  : Increase/reduce record volume\n"
            "  []  : Increase/reduce playback volume\n"
      "  V   : Display current volumes\n";
     
    PConsoleChannel console(PConsoleChannel::StandardInput);
    for (;;) {
      // display the prompt
      cout << "Command ? " << flush;
       
       
      // terminate the menu loop if console finished
      char ch = (char)console.peek();
      if (console.eof()) {
        cout << "\nConsole gone - menu disabled" << endl;
        goto endSimpleOPAL;
      }
       
      PString line;
      console >> line;
      line = line.LeftTrim();
      ch = line[0];
      line = line.Mid(1).Trim();

      PTRACE(3, "console in audio test is " << ch);
      switch (tolower(ch)) {
      case 'x' :
      case 'q' :
        goto endSimpleOPAL;

      case '?' :       
        cout << help ;
        break;

#if OPAL_HAS_MIXER
      case 'z':
        if (currentCallToken.IsEmpty())
         cout << "Cannot stop or start record whilst no call in progress.\n";
        else if (ch == 'z') {
          StartRecording(currentCallToken, "record.wav");
          cout << "Recording started.\n";
        }
        else {
          StopRecording(currentCallToken);
          cout << "Recording stopped.\n";
        }
        break;
#endif
        
      case 'y' :
        if ( pcssEP != NULL &&
            !pcssEP->incomingConnectionToken &&
            !pcssEP->AcceptIncomingConnection(pcssEP->incomingConnectionToken))
          cout << "Could not answer connection " << pcssEP->incomingConnectionToken << endl;
        break;

      case 'n' :
        if ( pcssEP != NULL &&
            !pcssEP->incomingConnectionToken &&
            !pcssEP->RejectIncomingConnection(pcssEP->incomingConnectionToken))
          cout << "Could not reject connection " << pcssEP->incomingConnectionToken << endl;
        break;

      case 'b' :
        if ( pcssEP != NULL &&
            !pcssEP->incomingConnectionToken &&
            !pcssEP->RejectIncomingConnection(pcssEP->incomingConnectionToken, OpalConnection::EndedByLocalBusy))
          cout << "Could not reject connection " << pcssEP->incomingConnectionToken << endl;
        break;

#if OPAL_PTLIB_CONFIG_FILE
      case 'l' :
        ListSpeedDials();
        break;
 
      case 'd' :
        NewSpeedDial(line);
        break;
#endif // OPAL_PTLIB_CONFIG_FILE
        
      case 'h' :
        HangupCurrentCall();
        break;

      case 'c' :
        StartCall(line);
        break;

      case 'o' :
        HoldRetrieveCall();
        break;

      case 't' :
        TransferCall(line);
        break;

      case 'r':
        cout << "Current call token is \"" << currentCallToken << "\"\n";
        if (!heldCallToken.IsEmpty())
          cout << "Held call token is \"" << heldCallToken << "\"\n";
        break;

      case 'm' :
        SendMessageToRemoteNode(line);
        break;

      case 'f' :
        SendTone('x');
        break;

      default:
        if (isdigit(ch) || ch == '*' || ch == '#')
          SendTone(ch);
        break;
      }
    }
  endSimpleOPAL:
    if (!currentCallToken.IsEmpty())
      HangupCurrentCall();
  }

  cout << "Console finished " << endl;
}

void MyManager::HangupCurrentCall()
{
  PString & token = currentCallToken.IsEmpty() ? heldCallToken : currentCallToken;

  PSafePtr<OpalCall> call = FindCallWithLock(token);
  if (call == NULL)
    cout << "No call to hang up!\n";
  else {
    cout << "Clearing call " << *call << endl;
    call->Clear();
    token.MakeEmpty();
  }
}


void MyManager::HoldRetrieveCall()
{
  if (currentCallToken.IsEmpty() && heldCallToken.IsEmpty()) {
    cout << "Cannot do hold while no call in progress\n";
    return;
  }

  if (heldCallToken.IsEmpty()) {
    PSafePtr<OpalCall> call = FindCallWithLock(currentCallToken);
    if (call == NULL)
      cout << "Current call disappeared!\n";
    else if (call->Hold()) {
      cout << "Call held.\n";
      heldCallToken = currentCallToken;
      currentCallToken.MakeEmpty();
    }
  }
  else {
    PSafePtr<OpalCall> call = FindCallWithLock(heldCallToken);
    if (call == NULL)
      cout << "Held call disappeared!\n";
    else if (call->Retrieve()) {
      cout << "Call retrieved.\n";
      currentCallToken = heldCallToken;
      heldCallToken.MakeEmpty();
    }
  }
}


void MyManager::TransferCall(const PString & dest)
{
  if (currentCallToken.IsEmpty()) {
    cout << "Cannot do transfer while no call in progress\n";
    return;
  }

  if (dest.IsEmpty() && heldCallToken.IsEmpty()) {
    cout << "Must supply a destination for transfer, or have a call on hold!\n";
    return;
  }

  PSafePtr<OpalCall> call = FindCallWithLock(currentCallToken);
  if (call == NULL) {
    cout << "Current call disappeared!\n";
    return;
  }

  if (!call->Transfer(dest))
    cout << "Call transfer failed!\n";
}


void MyManager::SendMessageToRemoteNode(const PString & str)
{
  if (str.IsEmpty()) {
    cout << "Must supply a message to send!\n";
    return;
  }

  PSafePtr<OpalCall> call = FindCallWithLock(currentCallToken);
  if (call == NULL) {
    cout << "Cannot send a message while no call in progress\n";
    return;
  }

  PSafePtr<OpalConnection> conn = call->GetConnection(0);
  while (conn != NULL) {
    conn->SendUserInputString(str);
    cout << "Sent \"" << str << "\" to " << conn->GetRemotePartyName() << endl;
    ++conn;
  }
}

void MyManager::SendTone(const char tone)
{
  if (currentCallToken.IsEmpty()) {
    cout << "Cannot send a digit while no call in progress\n";
    return;
  }

  PSafePtr<OpalCall> call = FindCallWithLock(currentCallToken);
  if (call == NULL) {
    cout << "Cannot send a message while no call in progress\n";
    return;
  }

  PSafePtr<OpalConnection> conn = call->GetConnection(0);
  while (conn != NULL) {
    conn->SendUserInputTone(tone, 180);
    cout << "Sent \"" << tone << "\" to " << conn->GetRemotePartyName() << endl;
    ++conn;
  }
}


void MyManager::StartCall(const PString & dest)
{
  if (!currentCallToken.IsEmpty()) {
    cout << "Cannot make call whilst call in progress\n";
    return;
  }

  if (dest.IsEmpty()) {
    cout << "Must supply hostname to connect to!\n";
    return ;
  }

  PString str = dest;

#if OPAL_PTLIB_CONFIG_FILE
  // check for speed dials, and match wild cards as we go
  PString key, prefix;
  if ((str.GetLength() > 1) && (str[str.GetLength()-1] == '#')) {
 
    key = str.Left(str.GetLength()-1).Trim(); 
    str = PString();
    PConfig config("Speeddial");
    PINDEX p;
    for (p = key.GetLength(); p > 0; p--) {
 
      PString newKey = key.Left(p);
      prefix = newKey;
      PINDEX q;
 
      // look for wild cards
      str = config.GetString(newKey + '*').Trim();
      if (!str.IsEmpty())
        break;
 
      // look for digit matches
      for (q = p; q < key.GetLength(); q++)
        newKey += '?';
      str = config.GetString(newKey).Trim();
      if (!str.IsEmpty())
        break;
    }
    if (str.IsEmpty())
      cout << "Speed dial \"" << key << "\" not defined\n";
  }
#endif // OPAL_PTLIB_CONFIG_FILE

  if (!str.IsEmpty())
    SetUpCall(srcEP, str, currentCallToken);

  return;
}

#if OPAL_PTLIB_CONFIG_FILE
void MyManager::ListSpeedDials()
{
  PConfig config("Speeddial");
  PStringList keys = config.GetKeys();
  if (keys.GetSize() == 0) {
    cout << "No speed dials defined\n";
    return;
  }
 
  PINDEX i;
  for (i = 0; i < keys.GetSize(); i++)
    cout << keys[i] << ":   " << config.GetString(keys[i]) << endl;
}
#endif // OPAL_PTLIB_CONFIG_FILE

void MyManager::OnEstablishedCall(OpalCall & call)
{
  currentCallToken = call.GetToken();
  cout << "In call with " << call.GetPartyB() << " using " << call.GetPartyA() << endl;  
}

void MyManager::OnClearedCall(OpalCall & call)
{
  if (currentCallToken == call.GetToken())
    currentCallToken.MakeEmpty();
  else if (heldCallToken == call.GetToken())
    heldCallToken.MakeEmpty();

  PString remoteName = '"' + call.GetPartyB() + '"';
  switch (call.GetCallEndReason()) {
    case OpalConnection::EndedByRemoteUser :
      cout << remoteName << " has cleared the call";
      break;
    case OpalConnection::EndedByCallerAbort :
      cout << remoteName << " has stopped calling";
      break;
    case OpalConnection::EndedByRefusal :
      cout << remoteName << " did not accept your call";
      break;
    case OpalConnection::EndedByNoAnswer :
      cout << remoteName << " did not answer your call";
      break;
    case OpalConnection::EndedByTransportFail :
      cout << "Call with " << remoteName << " ended abnormally";
      break;
    case OpalConnection::EndedByCapabilityExchange :
      cout << "Could not find common codec with " << remoteName;
      break;
    case OpalConnection::EndedByNoAccept :
      cout << "Did not accept incoming call from " << remoteName;
      break;
    case OpalConnection::EndedByAnswerDenied :
      cout << "Refused incoming call from " << remoteName;
      break;
    case OpalConnection::EndedByNoUser :
      cout << "Gatekeeper or registrar could not find user " << remoteName;
      break;
    case OpalConnection::EndedByNoBandwidth :
      cout << "Call to " << remoteName << " aborted, insufficient bandwidth.";
      break;
    case OpalConnection::EndedByUnreachable :
      cout << remoteName << " could not be reached.";
      break;
    case OpalConnection::EndedByNoEndPoint :
      cout << "No phone running for " << remoteName;
      break;
    case OpalConnection::EndedByHostOffline :
      cout << remoteName << " is not online.";
      break;
    case OpalConnection::EndedByConnectFail :
      cout << "Transport error calling " << remoteName;
      break;
    default :
      cout << "Call with " << remoteName << " completed";
  }
  PTime now;
  cout << ", on " << now.AsString("w h:mma") << ". Duration "
       << setprecision(0) << setw(5) << (now - call.GetStartTime())
       << "s." << endl;

  OpalManager::OnClearedCall(call);
}


PBoolean MyManager::OnOpenMediaStream(OpalConnection & connection,
                                  OpalMediaStream & stream)
{
  if (!OpalManager::OnOpenMediaStream(connection, stream))
    return false;

  cout << "Started ";

  PCaselessString prefix = connection.GetEndPoint().GetPrefixName();
  if (prefix == "pc" || prefix == "pots")
    cout << (stream.IsSink() ? "playing " : "grabbing ") << stream.GetMediaFormat();
  else if (prefix == "ivr")
    cout << (stream.IsSink() ? "streaming " : "recording ") << stream.GetMediaFormat();
  else
    cout << (stream.IsSink() ? "sending " : "receiving ") << stream.GetMediaFormat()
          << (stream.IsSink() ? " to " : " from ")<< prefix;

  cout << endl;

  return true;
}



void MyManager::OnUserInputString(OpalConnection & connection, const PString & value)
{
  cout << "User input received: \"" << value << '"' << endl;
  OpalManager::OnUserInputString(connection, value);
}


///////////////////////////////////////////////////////////////

MyPCSSEndPoint::MyPCSSEndPoint(MyManager & mgr)
  : OpalPCSSEndPoint(mgr)
{
}


PBoolean MyPCSSEndPoint::OnShowIncoming(const OpalPCSSConnection & connection)
{
  incomingConnectionToken = connection.GetToken();

  if (autoAnswer)
    AcceptIncomingConnection(incomingConnectionToken);
  else {
    PTime now;
    cout << "\nCall on " << now.AsString("w h:mma")
         << " from " << connection.GetRemotePartyName()
         << ", answer (Yes/No/Busy)? " << flush;
  }

  return true;
}


PBoolean MyPCSSEndPoint::OnShowOutgoing(const OpalPCSSConnection & connection)
{
  PTime now;
  cout << connection.GetRemotePartyName() << " is ringing on "
       << now.AsString("w h:mma") << " ..." << endl;
  return true;
}


PBoolean MyPCSSEndPoint::SetSoundDevice(PArgList & args,
                                    const char * optionName,
                                    PSoundChannel::Directions dir)
{
  if (!args.HasOption(optionName))
    return true;

  PString dev = args.GetOptionString(optionName);

  if (dir == PSoundChannel::Player) {
    if (SetSoundChannelPlayDevice(dev))
      return true;
  }
  else {
    if (SetSoundChannelRecordDevice(dev))
      return true;
  }

  cerr << "Device for " << optionName << " (\"" << dev << "\") must be one of:\n";

  PStringArray names = PSoundChannel::GetDeviceNames(dir);
  for (PINDEX i = 0; i < names.GetSize(); i++)
    cerr << "  \"" << names[i] << "\"\n";

  return false;
}

// End of File ///////////////////////////////////////////////////////////////
