#include <iostream>
#include <string>
#include "../pugixml-1.9/src/pugixml.hpp"

#ifndef CADG_REST_SERVER_CMAC_CONVERTER_H
#define CADG_REST_SERVER_CMAC_CONVERTER_H
///Provides mechanisms through a static convert method to convert incoming SOAP CAP documents into CMAC XML documents
/**
 * Converts any syntactically correct SOAP CAP document into a CMAC XML document.
 * Example use: CMAC::convert("../file/path/soapname.xml", "../file/path/to/save/cmacname.xml");
 */
class CMAC {
public:
    ///Converts any syntactically correct SOAP CAP document into a CMAC XML document.
    /**
     * Converts syntactically correct SOAP CAP documents into CMAC XML documents.
     * Pulls the SOAP XML document content in the soap_filename argument into memory
     * for content needed in the upcoming CMAC XML document structure. The CMAC
     * document structure is then created and filled with content from the
     * SOAP XML document before saving to the filepath and filename in the
     * cmac_filename argument.
     * @param soap_filename     Filepath and filename of the SOAP document to be converted
     * @param cmac_filename     Filepath and filename of the CMAC document to be saved
     */
    static void convert(std::string soap_filename, std::string cmac_filename);
};
#endif //CADG_REST_SERVER_CMAC_CONVERTER_H
