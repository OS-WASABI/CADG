/* soapCAPSoapHttpService.cpp
   Generated by gSOAP 2.8.75 for ipaws.h

gSOAP XML Web services tools
Copyright (C) 2000-2018, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soapCAPSoapHttpService.h"

CAPSoapHttpService::CAPSoapHttpService()
{	this->soap = soap_new();
	this->soap_own = true;
	CAPSoapHttpService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

CAPSoapHttpService::CAPSoapHttpService(const CAPSoapHttpService& rhs)
{	this->soap = rhs.soap;
	this->soap_own = false;
}

CAPSoapHttpService::CAPSoapHttpService(struct soap *_soap)
{	this->soap = _soap;
	this->soap_own = false;
	CAPSoapHttpService_init(_soap->imode, _soap->omode);
}

CAPSoapHttpService::CAPSoapHttpService(soap_mode iomode)
{	this->soap = soap_new();
	this->soap_own = true;
	CAPSoapHttpService_init(iomode, iomode);
}

CAPSoapHttpService::CAPSoapHttpService(soap_mode imode, soap_mode omode)
{	this->soap = soap_new();
	this->soap_own = true;
	CAPSoapHttpService_init(imode, omode);
}

CAPSoapHttpService::~CAPSoapHttpService()
{	if (this->soap_own)
	{	this->destroy();
		soap_free(this->soap);
	}
}

void CAPSoapHttpService::CAPSoapHttpService_init(soap_mode imode, soap_mode omode)
{	soap_imode(this->soap, imode);
	soap_omode(this->soap, omode);
	static const struct Namespace namespaces[] = {
        { "SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL },
        { "SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL },
        { "xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL },
        { "xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL },
        { "ns2", "http://gov.fema.ipaws.services/caprequest", NULL, NULL },
        { "ns3", "http://gov.fema.ipaws.services/capresponse", NULL, NULL },
        { "ns4", "urn:oasis:names:tc:emergency:cap:1.2", NULL, NULL },
        { "ns1", "http://gov.fema.ipaws.services/IPAWS_CAPService/", NULL, NULL },
        { NULL, NULL, NULL, NULL}
    };
	soap_set_namespaces(this->soap, namespaces);
}

void CAPSoapHttpService::destroy()
{	soap_destroy(this->soap);
	soap_end(this->soap);
}

void CAPSoapHttpService::reset()
{	this->destroy();
	soap_done(this->soap);
	soap_initialize(this->soap);
	CAPSoapHttpService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

#ifndef WITH_PURE_VIRTUAL
CAPSoapHttpService *CAPSoapHttpService::copy()
{	CAPSoapHttpService *dup = SOAP_NEW_UNMANAGED(CAPSoapHttpService);
	if (dup)
	{	soap_done(dup->soap);
		soap_copy_context(dup->soap, this->soap);
	}
	return dup;
}
#endif

CAPSoapHttpService& CAPSoapHttpService::operator=(const CAPSoapHttpService& rhs)
{	if (this->soap != rhs.soap)
	{	if (this->soap_own)
			soap_free(this->soap);
		this->soap = rhs.soap;
		this->soap_own = false;
	}
	return *this;
}

int CAPSoapHttpService::soap_close_socket()
{	return soap_closesock(this->soap);
}

int CAPSoapHttpService::soap_force_close_socket()
{	return soap_force_closesock(this->soap);
}

int CAPSoapHttpService::soap_senderfault(const char *string, const char *detailXML)
{	return ::soap_sender_fault(this->soap, string, detailXML);
}

int CAPSoapHttpService::soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_sender_fault_subcode(this->soap, subcodeQName, string, detailXML);
}

int CAPSoapHttpService::soap_receiverfault(const char *string, const char *detailXML)
{	return ::soap_receiver_fault(this->soap, string, detailXML);
}

int CAPSoapHttpService::soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_receiver_fault_subcode(this->soap, subcodeQName, string, detailXML);
}

void CAPSoapHttpService::soap_print_fault(FILE *fd)
{	::soap_print_fault(this->soap, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void CAPSoapHttpService::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this->soap, os);
}
#endif

char *CAPSoapHttpService::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this->soap, buf, len);
}
#endif

void CAPSoapHttpService::soap_noheader()
{	this->soap->header = NULL;
}

void CAPSoapHttpService::soap_header(_ns1__CAPHeaderTypeDef *ns1__CAPHeaderTypeDef)
{
	::soap_header(this->soap);
	this->soap->header->ns1__CAPHeaderTypeDef = ns1__CAPHeaderTypeDef;
}

::SOAP_ENV__Header *CAPSoapHttpService::soap_header()
{	return this->soap->header;
}

#ifndef WITH_NOIO
int CAPSoapHttpService::run(int port, int backlog)
{	if (!soap_valid_socket(this->soap->master) && !soap_valid_socket(this->bind(NULL, port, backlog)))
		return this->soap->error;
	for (;;)
	{	if (!soap_valid_socket(this->accept()))
		{	if (this->soap->errnum == 0) // timeout?
				this->soap->error = SOAP_OK;
			break;
		}
		if (this->serve())
			break;
		this->destroy();
	}
	return this->soap->error;
}

#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
int CAPSoapHttpService::ssl_run(int port, int backlog)
{	if (!soap_valid_socket(this->soap->master) && !soap_valid_socket(this->bind(NULL, port, backlog)))
		return this->soap->error;
	for (;;)
	{	if (!soap_valid_socket(this->accept()))
		{	if (this->soap->errnum == 0) // timeout?
				this->soap->error = SOAP_OK;
			break;
		}
		if (this->ssl_accept() || this->serve())
			break;
		this->destroy();
	}
	return this->soap->error;
}
#endif

SOAP_SOCKET CAPSoapHttpService::bind(const char *host, int port, int backlog)
{	return soap_bind(this->soap, host, port, backlog);
}

SOAP_SOCKET CAPSoapHttpService::accept()
{	return soap_accept(this->soap);
}

#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
int CAPSoapHttpService::ssl_accept()
{	return soap_ssl_accept(this->soap);
}
#endif
#endif

int CAPSoapHttpService::serve()
{
#ifndef WITH_FASTCGI
	this->soap->keep_alive = this->soap->max_keep_alive + 1;
#endif
	do
	{
#ifndef WITH_FASTCGI
		if (this->soap->keep_alive > 0 && this->soap->max_keep_alive > 0)
			this->soap->keep_alive--;
#endif
		if (soap_begin_serve(this->soap))
		{	if (this->soap->error >= SOAP_STOP)
				continue;
			return this->soap->error;
		}
		if ((dispatch() || (this->soap->fserveloop && this->soap->fserveloop(this->soap))) && this->soap->error && this->soap->error < SOAP_STOP)
		{
#ifdef WITH_FASTCGI
			soap_send_fault(this->soap);
#else
			return soap_send_fault(this->soap);
#endif
		}
#ifdef WITH_FASTCGI
		soap_destroy(this->soap);
		soap_end(this->soap);
	} while (1);
#else
	} while (this->soap->keep_alive);
#endif
	return SOAP_OK;
}

static int serve___ns1__getRequest(struct soap*, CAPSoapHttpService*);
static int serve___ns1__postCAP(struct soap*, CAPSoapHttpService*);
static int serve___ns1__getMessage(struct soap*, CAPSoapHttpService*);

int CAPSoapHttpService::dispatch()
{	return dispatch(this->soap);
}

int CAPSoapHttpService::dispatch(struct soap* soap)
{
	CAPSoapHttpService_init(soap->imode, soap->omode);

	soap_peek_element(soap);
	if (!soap_match_tag(soap, soap->tag, "ns1:getRequestTypeDef"))
		return serve___ns1__getRequest(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns1:postCAPRequestTypeDef"))
		return serve___ns1__postCAP(soap, this);
	if (!soap_match_tag(soap, soap->tag, "ns1:getMessageTypeDef"))
		return serve___ns1__getMessage(soap, this);
	return soap->error = SOAP_NO_METHOD;
}

static int serve___ns1__getRequest(struct soap *soap, CAPSoapHttpService *service)
{	struct __ns1__getRequest soap_tmp___ns1__getRequest;
	ns3__responseParameterList ns1__getResponseTypeDef;
	ns1__getResponseTypeDef.soap_default(soap);
	soap_default___ns1__getRequest(soap, &soap_tmp___ns1__getRequest);
	if (!soap_get___ns1__getRequest(soap, &soap_tmp___ns1__getRequest, "-ns1:getRequest", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->getRequest(soap_tmp___ns1__getRequest.ns1__getRequestTypeDef, ns1__getResponseTypeDef);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	ns1__getResponseTypeDef.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__getResponseTypeDef.soap_put(soap, "ns1:getResponseTypeDef", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__getResponseTypeDef.soap_put(soap, "ns1:getResponseTypeDef", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__postCAP(struct soap *soap, CAPSoapHttpService *service)
{	struct __ns1__postCAP soap_tmp___ns1__postCAP;
	_ns1__postCAPResponseTypeDef ns1__postCAPResponseTypeDef;
	ns1__postCAPResponseTypeDef.soap_default(soap);
	soap_default___ns1__postCAP(soap, &soap_tmp___ns1__postCAP);
	if (!soap_get___ns1__postCAP(soap, &soap_tmp___ns1__postCAP, "-ns1:postCAP", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->postCAP(soap_tmp___ns1__postCAP.ns1__postCAPRequestTypeDef, ns1__postCAPResponseTypeDef);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	ns1__postCAPResponseTypeDef.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__postCAPResponseTypeDef.soap_put(soap, "ns1:postCAPResponseTypeDef", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__postCAPResponseTypeDef.soap_put(soap, "ns1:postCAPResponseTypeDef", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

static int serve___ns1__getMessage(struct soap *soap, CAPSoapHttpService *service)
{	struct __ns1__getMessage soap_tmp___ns1__getMessage;
	_ns1__messageResponseTypeDef ns1__messageResponseTypeDef;
	ns1__messageResponseTypeDef.soap_default(soap);
	soap_default___ns1__getMessage(soap, &soap_tmp___ns1__getMessage);
	if (!soap_get___ns1__getMessage(soap, &soap_tmp___ns1__getMessage, "-ns1:getMessage", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = service->getMessage(soap_tmp___ns1__getMessage.ns1__getMessageTypeDef, ns1__messageResponseTypeDef);
	if (soap->error)
		return soap->error;
	soap->encodingStyle = NULL; /* use SOAP literal style */
	soap_serializeheader(soap);
	ns1__messageResponseTypeDef.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if ((soap->mode & SOAP_IO_LENGTH))
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__messageResponseTypeDef.soap_put(soap, "ns1:messageResponseTypeDef", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__messageResponseTypeDef.soap_put(soap, "ns1:messageResponseTypeDef", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
/* End of server object code */
