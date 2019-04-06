# CMAC Conversion
This functionality is intended to perform the final XML conversion into the CMAC format
necessary for CMSPs to then send out an alert to the appropriate recipients. It achieves
this by first taking in the CAP message data provided by the AOI and creating a CMAC
data object based on the logic provided by the ATIS-0700037 PDF. The CAP message is
assumed to be validated by the AOI prior to CMAC data object creation. Therefore,
little validation is performed in the CMAC data object creation process beyond any
additional validation required by the ATIS documentation. Once the CMAC data object is
created, it is passed to the XML convert function found in cmac_converter.cpp. This
XML data is then ready to be sent out by the CADG to the CMSPs.

# TO-DO ITEMS FOR THE NEXT TEAM (Provided by Ross Arcemont)
- Currently, all of the XML conversion to CMAC works as intended when provided a
test pre-constructed CMAC data object. However, the current output of the function is
an XML file. To my current understanding of the system, the output should instead be
an XML string. This can be achieved without too much hassle via the PUGIXML library.
You should still confirm if the necessary output is an XML string. I suspect this
detail is hidden somewhere in the ATIS documentation, but you may need to ask the
sponsor for additional information if necessary.
- The CMAC data object creation functionality currently does not exist. I have
provided you with a starting point function found in rest-server/src/model/cmac/cmac_alert.hpp.
In order to complete the message-creation-to-delivery pipeline, this functionality must be
implemented. Included with that function are instructions for how the function
could potentially be implemented. The function is also commented out currently,
because it does not function correctly at all. It is there to serve as a starting point.

# To run this code:
1. cd into soap/cmac-conversion
2. Use "sudo g++-8 -std=c++17 -o cmacTest cmac_converter.cpp" (Minus the quotes)
3. Use "./cmacTest" (Minus the quotes)