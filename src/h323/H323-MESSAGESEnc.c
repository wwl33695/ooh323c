/*
 * Copyright (C) 2004 by Objective Systems, Inc.
 *
 * This software is furnished under an open source license and may be
 * used and copied only in accordance with the terms of this license.
 * The text of the license may generally be found in the root
 * directory of this installation in the COPYING file.  It
 * can also be viewed online at the following URL:
 *
 *   http://www.obj-sys.com/open/license.html
 *
 * Any redistributions of this file including modified versions must
 * maintain this copyright notice.
 *
 *****************************************************************************/

#include "ooasn1.h"
#include "H323-MESSAGES.h"

/**************************************************************/
/*                                                            */
/*  ScreeningIndicator                                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ScreeningIndicator (OOCTXT* pctxt, H225ScreeningIndicator value)
{
   int stat = ASN_OK;
   ASN1UINT ui;
   ASN1BOOL extbit;

   extbit = 0;

   switch (value) {
      case userProvidedNotScreened: ui = 0; break;
      case userProvidedVerifiedAndPassed: ui = 1; break;
      case userProvidedVerifiedAndFailed: ui = 2; break;
      case networkProvided: ui = 3; break;
      default: ui = value; extbit = 1;
   }

   /* extension bit */

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {
      stat = encodeSmallNonNegWholeNumber (pctxt, ui);
   }
   else {
      stat = encodeConsUnsigned (pctxt, ui, 0, 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  NumberDigits                                              */
/*                                                            */
/**************************************************************/

extern EXTERN const char* gs_H323_MESSAGES_NumberDigits_CharSet;

EXTERN int asn1PE_H225NumberDigits (OOCTXT* pctxt, H225NumberDigits value)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 128, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeConstrainedStringEx (pctxt, value, gs_H323_MESSAGES_NumberDigits_CharSet, 4, 4, 7);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TBCD_STRING                                               */
/*                                                            */
/**************************************************************/

extern EXTERN const char* gs_H323_MESSAGES_TBCD_STRING_CharSet;

EXTERN int asn1PE_H225TBCD_STRING (OOCTXT* pctxt, H225TBCD_STRING value)
{
   int stat = ASN_OK;

   stat = encodeConstrainedStringEx (pctxt, value, gs_H323_MESSAGES_TBCD_STRING_CharSet, 4, 4, 7);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GloballyUniqueID                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GloballyUniqueID (OOCTXT* pctxt, H225GloballyUniqueID* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 16, 16, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ConferenceIdentifier                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ConferenceIdentifier (OOCTXT* pctxt, H225ConferenceIdentifier* pvalue)
{
   int stat = ASN_OK;

   stat = asn1PE_H225GloballyUniqueID (pctxt, pvalue);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RequestSeqNum                                             */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RequestSeqNum (OOCTXT* pctxt, H225RequestSeqNum value)
{
   int stat = ASN_OK;

   if ( (value >= 1) ) {
      stat = encodeConsUnsigned (pctxt, value, 1U, 65535U);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }
   else
      return LOG_ASN1ERR (pctxt, ASN_E_CONSVIO);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GatekeeperIdentifier                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GatekeeperIdentifier (OOCTXT* pctxt, H225GatekeeperIdentifier value)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 128, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBMPString (pctxt, value, 0);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  BandWidth                                                 */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225BandWidth (OOCTXT* pctxt, H225BandWidth value)
{
   int stat = ASN_OK;

   stat = encodeConsUnsigned (pctxt, value, 0U, ASN1UINT_MAX);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallReferenceValue                                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallReferenceValue (OOCTXT* pctxt, H225CallReferenceValue value)
{
   int stat = ASN_OK;

   stat = encodeConsUnsigned (pctxt, value, 0U, 65535U);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  EndpointIdentifier                                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225EndpointIdentifier (OOCTXT* pctxt, H225EndpointIdentifier value)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 128, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBMPString (pctxt, value, 0);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ProtocolIdentifier                                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ProtocolIdentifier (OOCTXT* pctxt, H225ProtocolIdentifier value)
{
   int stat = ASN_OK;

   stat = encodeObjectIdentifier (pctxt, &value);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TimeToLive                                                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TimeToLive (OOCTXT* pctxt, H225TimeToLive value)
{
   int stat = ASN_OK;

   stat = encodeConsUnsigned (pctxt, value, 1U, ASN1UINT_MAX);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H248PackagesDescriptor                                    */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H248PackagesDescriptor (OOCTXT* pctxt, H225H248PackagesDescriptor value)
{
   int stat = ASN_OK;

   stat = encodeOctetString (pctxt, value.numocts, value.data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H248SignalsDescriptor                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H248SignalsDescriptor (OOCTXT* pctxt, H225H248SignalsDescriptor value)
{
   int stat = ASN_OK;

   stat = encodeOctetString (pctxt, value.numocts, value.data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GenericIdentifier                                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GenericIdentifier (OOCTXT* pctxt, H225GenericIdentifier* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 3);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 2);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* standard */
         case 1:
            if ( (pvalue->u.standard >= 0 && pvalue->u.standard <= 16383) ) {
               extbit = 0;
            }
            else extbit = 1;

            /* extension bit */

            stat = encodeBit (pctxt, extbit);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

            if (extbit) {
               stat = encodeUnconsInteger (pctxt, pvalue->u.standard);
               if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            }
            else {
               stat = encodeConsInteger (pctxt, pvalue->u.standard, 0, 16383);
               if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            }
            break;

         /* oid */
         case 2:
            stat = encodeObjectIdentifier (pctxt, pvalue->u.oid);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* nonStandard */
         case 3:
            stat = asn1PE_H225GloballyUniqueID (pctxt, pvalue->u.nonStandard);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress_ipAddress_ip                             */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress_ipAddress_ip (OOCTXT* pctxt, H225TransportAddress_ipAddress_ip* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 4, 4, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress_ipAddress                                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress_ipAddress (OOCTXT* pctxt, H225TransportAddress_ipAddress* pvalue)
{
   int stat = ASN_OK;

   /* encode ip */

   stat = asn1PE_H225TransportAddress_ipAddress_ip (pctxt, &pvalue->ip);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode port */

   stat = encodeConsUnsigned (pctxt, pvalue->port, 0U, 65535U);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress_ipSourceRoute_ip                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress_ipSourceRoute_ip (OOCTXT* pctxt, H225TransportAddress_ipSourceRoute_ip* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 4, 4, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress_ipSourceRoute_route_element              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress_ipSourceRoute_route_element (OOCTXT* pctxt, H225TransportAddress_ipSourceRoute_route_element* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 4, 4, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225TransportAddress_ipSourceRoute_route_element    */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225TransportAddress_ipSourceRoute_route_element (OOCTXT* pctxt, H225_SeqOfH225TransportAddress_ipSourceRoute_route_element* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = asn1PE_H225TransportAddress_ipSourceRoute_route_element (pctxt, &pvalue->elem[xx1]);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress_ipSourceRoute_routing                    */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress_ipSourceRoute_routing (OOCTXT* pctxt, H225TransportAddress_ipSourceRoute_routing* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 2);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* strict */
         case 1:
            /* NULL */
            break;

         /* loose */
         case 2:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress_ipSourceRoute                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress_ipSourceRoute (OOCTXT* pctxt, H225TransportAddress_ipSourceRoute* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode ip */

   stat = asn1PE_H225TransportAddress_ipSourceRoute_ip (pctxt, &pvalue->ip);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode port */

   stat = encodeConsUnsigned (pctxt, pvalue->port, 0U, 65535U);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode route */

   stat = asn1PE_H225_SeqOfH225TransportAddress_ipSourceRoute_route_element (pctxt, &pvalue->route);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode routing */

   stat = asn1PE_H225TransportAddress_ipSourceRoute_routing (pctxt, &pvalue->routing);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress_ipxAddress_node                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress_ipxAddress_node (OOCTXT* pctxt, H225TransportAddress_ipxAddress_node* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 6, 6, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress_ipxAddress_netnum                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress_ipxAddress_netnum (OOCTXT* pctxt, H225TransportAddress_ipxAddress_netnum* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 4, 4, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress_ipxAddress_port                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress_ipxAddress_port (OOCTXT* pctxt, H225TransportAddress_ipxAddress_port* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 2, 2, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress_ipxAddress                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress_ipxAddress (OOCTXT* pctxt, H225TransportAddress_ipxAddress* pvalue)
{
   int stat = ASN_OK;

   /* encode node */

   stat = asn1PE_H225TransportAddress_ipxAddress_node (pctxt, &pvalue->node);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode netnum */

   stat = asn1PE_H225TransportAddress_ipxAddress_netnum (pctxt, &pvalue->netnum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode port */

   stat = asn1PE_H225TransportAddress_ipxAddress_port (pctxt, &pvalue->port);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress_ip6Address_ip                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress_ip6Address_ip (OOCTXT* pctxt, H225TransportAddress_ip6Address_ip* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 16, 16, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress_ip6Address                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress_ip6Address (OOCTXT* pctxt, H225TransportAddress_ip6Address* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode ip */

   stat = asn1PE_H225TransportAddress_ip6Address_ip (pctxt, &pvalue->ip);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode port */

   stat = encodeConsUnsigned (pctxt, pvalue->port, 0U, 65535U);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress_netBios                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress_netBios (OOCTXT* pctxt, H225TransportAddress_netBios* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 16, 16, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress_nsap                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress_nsap (OOCTXT* pctxt, H225TransportAddress_nsap* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 20, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H221NonStandard                                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H221NonStandard (OOCTXT* pctxt, H225H221NonStandard* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode t35CountryCode */

   stat = encodeConsUnsigned (pctxt, pvalue->t35CountryCode, 0U, 255U);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode t35Extension */

   stat = encodeConsUnsigned (pctxt, pvalue->t35Extension, 0U, 255U);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode manufacturerCode */

   stat = encodeConsUnsigned (pctxt, pvalue->manufacturerCode, 0U, 65535U);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  NonStandardIdentifier                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225NonStandardIdentifier (OOCTXT* pctxt, H225NonStandardIdentifier* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 2);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* object */
         case 1:
            stat = encodeObjectIdentifier (pctxt, pvalue->u.object);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* h221NonStandard */
         case 2:
            stat = asn1PE_H225H221NonStandard (pctxt, pvalue->u.h221NonStandard);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  NonStandardParameter                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225NonStandardParameter (OOCTXT* pctxt, H225NonStandardParameter* pvalue)
{
   int stat = ASN_OK;

   /* encode nonStandardIdentifier */

   stat = asn1PE_H225NonStandardIdentifier (pctxt, &pvalue->nonStandardIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode data */

   stat = encodeOctetString (pctxt, pvalue->data.numocts, pvalue->data.data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportAddress                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportAddress (OOCTXT* pctxt, H225TransportAddress* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 7);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 6);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* ipAddress */
         case 1:
            stat = asn1PE_H225TransportAddress_ipAddress (pctxt, pvalue->u.ipAddress);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* ipSourceRoute */
         case 2:
            stat = asn1PE_H225TransportAddress_ipSourceRoute (pctxt, pvalue->u.ipSourceRoute);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* ipxAddress */
         case 3:
            stat = asn1PE_H225TransportAddress_ipxAddress (pctxt, pvalue->u.ipxAddress);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* ip6Address */
         case 4:
            stat = asn1PE_H225TransportAddress_ip6Address (pctxt, pvalue->u.ip6Address);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* netBios */
         case 5:
            stat = asn1PE_H225TransportAddress_netBios (pctxt, pvalue->u.netBios);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* nsap */
         case 6:
            stat = asn1PE_H225TransportAddress_nsap (pctxt, pvalue->u.nsap);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* nonStandardAddress */
         case 7:
            stat = asn1PE_H225NonStandardParameter (pctxt, pvalue->u.nonStandardAddress);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 8);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  PublicTypeOfNumber                                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225PublicTypeOfNumber (OOCTXT* pctxt, H225PublicTypeOfNumber* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 6);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* unknown */
         case 1:
            /* NULL */
            break;

         /* internationalNumber */
         case 2:
            /* NULL */
            break;

         /* nationalNumber */
         case 3:
            /* NULL */
            break;

         /* networkSpecificNumber */
         case 4:
            /* NULL */
            break;

         /* subscriberNumber */
         case 5:
            /* NULL */
            break;

         /* abbreviatedNumber */
         case 6:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  PublicPartyNumber                                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225PublicPartyNumber (OOCTXT* pctxt, H225PublicPartyNumber* pvalue)
{
   int stat = ASN_OK;

   /* encode publicTypeOfNumber */

   stat = asn1PE_H225PublicTypeOfNumber (pctxt, &pvalue->publicTypeOfNumber);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode publicNumberDigits */

   stat = asn1PE_H225NumberDigits (pctxt, pvalue->publicNumberDigits);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  PrivateTypeOfNumber                                       */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225PrivateTypeOfNumber (OOCTXT* pctxt, H225PrivateTypeOfNumber* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 6);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* unknown */
         case 1:
            /* NULL */
            break;

         /* level2RegionalNumber */
         case 2:
            /* NULL */
            break;

         /* level1RegionalNumber */
         case 3:
            /* NULL */
            break;

         /* pISNSpecificNumber */
         case 4:
            /* NULL */
            break;

         /* localNumber */
         case 5:
            /* NULL */
            break;

         /* abbreviatedNumber */
         case 6:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  PrivatePartyNumber                                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225PrivatePartyNumber (OOCTXT* pctxt, H225PrivatePartyNumber* pvalue)
{
   int stat = ASN_OK;

   /* encode privateTypeOfNumber */

   stat = asn1PE_H225PrivateTypeOfNumber (pctxt, &pvalue->privateTypeOfNumber);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode privateNumberDigits */

   stat = asn1PE_H225NumberDigits (pctxt, pvalue->privateNumberDigits);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  PartyNumber                                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225PartyNumber (OOCTXT* pctxt, H225PartyNumber* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 5);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* e164Number */
         case 1:
            stat = asn1PE_H225PublicPartyNumber (pctxt, pvalue->u.e164Number);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* dataPartyNumber */
         case 2:
            stat = asn1PE_H225NumberDigits (pctxt, pvalue->u.dataPartyNumber);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* telexPartyNumber */
         case 3:
            stat = asn1PE_H225NumberDigits (pctxt, pvalue->u.telexPartyNumber);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* privateNumber */
         case 4:
            stat = asn1PE_H225PrivatePartyNumber (pctxt, pvalue->u.privateNumber);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* nationalStandardPartyNumber */
         case 5:
            stat = asn1PE_H225NumberDigits (pctxt, pvalue->u.nationalStandardPartyNumber);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 6);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ANSI_41_UIM_system_id                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ANSI_41_UIM_system_id (OOCTXT* pctxt, H225ANSI_41_UIM_system_id* pvalue)
{
   static Asn1SizeCnst sid_lsize1 = { 0, 1, 4, 0 };
   static Asn1SizeCnst mid_lsize1 = { 0, 1, 4, 0 };
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 2);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* sid */
         case 1:
            stat = addSizeConstraint (pctxt, &sid_lsize1);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

            stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->u.sid);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* mid */
         case 2:
            stat = addSizeConstraint (pctxt, &mid_lsize1);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

            stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->u.mid);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ANSI_41_UIM_systemMyTypeCode                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ANSI_41_UIM_systemMyTypeCode (OOCTXT* pctxt, H225ANSI_41_UIM_systemMyTypeCode* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 1, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ANSI_41_UIM_systemAccessType                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ANSI_41_UIM_systemAccessType (OOCTXT* pctxt, H225ANSI_41_UIM_systemAccessType* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 1, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ANSI_41_UIM_qualificationInformationCode                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ANSI_41_UIM_qualificationInformationCode (OOCTXT* pctxt, H225ANSI_41_UIM_qualificationInformationCode* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 1, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ANSI_41_UIM                                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ANSI_41_UIM (OOCTXT* pctxt, H225ANSI_41_UIM* pvalue)
{
   static Asn1SizeCnst imsi_lsize1 = { 0, 3, 16, 0 };
   static Asn1SizeCnst min_lsize1 = { 0, 3, 16, 0 };
   static Asn1SizeCnst mdn_lsize1 = { 0, 3, 16, 0 };
   static Asn1SizeCnst msisdn_lsize1 = { 0, 3, 16, 0 };
   static Asn1SizeCnst esn_lsize1 = { 0, 16, 16, 0 };
   static Asn1SizeCnst mscid_lsize1 = { 0, 3, 16, 0 };
   static Asn1SizeCnst sesn_lsize1 = { 0, 16, 16, 0 };
   static Asn1SizeCnst soc_lsize1 = { 0, 3, 16, 0 };
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.imsiPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.minPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.mdnPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.msisdnPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.esnPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.mscidPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.systemMyTypeCodePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.systemAccessTypePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.qualificationInformationCodePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.sesnPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.socPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode imsi */

   if (pvalue->m.imsiPresent) {
      stat = addSizeConstraint (pctxt, &imsi_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->imsi);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode min */

   if (pvalue->m.minPresent) {
      stat = addSizeConstraint (pctxt, &min_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->min);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode mdn */

   if (pvalue->m.mdnPresent) {
      stat = addSizeConstraint (pctxt, &mdn_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->mdn);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode msisdn */

   if (pvalue->m.msisdnPresent) {
      stat = addSizeConstraint (pctxt, &msisdn_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->msisdn);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode esn */

   if (pvalue->m.esnPresent) {
      stat = addSizeConstraint (pctxt, &esn_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->esn);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode mscid */

   if (pvalue->m.mscidPresent) {
      stat = addSizeConstraint (pctxt, &mscid_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->mscid);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode system_id */

   stat = asn1PE_H225ANSI_41_UIM_system_id (pctxt, &pvalue->system_id);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode systemMyTypeCode */

   if (pvalue->m.systemMyTypeCodePresent) {
      stat = asn1PE_H225ANSI_41_UIM_systemMyTypeCode (pctxt, &pvalue->systemMyTypeCode);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode systemAccessType */

   if (pvalue->m.systemAccessTypePresent) {
      stat = asn1PE_H225ANSI_41_UIM_systemAccessType (pctxt, &pvalue->systemAccessType);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode qualificationInformationCode */

   if (pvalue->m.qualificationInformationCodePresent) {
      stat = asn1PE_H225ANSI_41_UIM_qualificationInformationCode (pctxt, &pvalue->qualificationInformationCode);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode sesn */

   if (pvalue->m.sesnPresent) {
      stat = addSizeConstraint (pctxt, &sesn_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->sesn);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode soc */

   if (pvalue->m.socPresent) {
      stat = addSizeConstraint (pctxt, &soc_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->soc);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GSM_UIM_tmsi                                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GSM_UIM_tmsi (OOCTXT* pctxt, H225GSM_UIM_tmsi* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 4, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GSM_UIM                                                   */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GSM_UIM (OOCTXT* pctxt, H225GSM_UIM* pvalue)
{
   static Asn1SizeCnst imsi_lsize1 = { 0, 3, 16, 0 };
   static Asn1SizeCnst msisdn_lsize1 = { 0, 3, 16, 0 };
   static Asn1SizeCnst imei_lsize1 = { 0, 15, 16, 0 };
   static Asn1SizeCnst hplmn_lsize1 = { 0, 1, 4, 0 };
   static Asn1SizeCnst vplmn_lsize1 = { 0, 1, 4, 0 };
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.imsiPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tmsiPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.msisdnPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.imeiPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.hplmnPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.vplmnPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode imsi */

   if (pvalue->m.imsiPresent) {
      stat = addSizeConstraint (pctxt, &imsi_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->imsi);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode tmsi */

   if (pvalue->m.tmsiPresent) {
      stat = asn1PE_H225GSM_UIM_tmsi (pctxt, &pvalue->tmsi);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode msisdn */

   if (pvalue->m.msisdnPresent) {
      stat = addSizeConstraint (pctxt, &msisdn_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->msisdn);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode imei */

   if (pvalue->m.imeiPresent) {
      stat = addSizeConstraint (pctxt, &imei_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->imei);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode hplmn */

   if (pvalue->m.hplmnPresent) {
      stat = addSizeConstraint (pctxt, &hplmn_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->hplmn);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode vplmn */

   if (pvalue->m.vplmnPresent) {
      stat = addSizeConstraint (pctxt, &vplmn_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = asn1PE_H225TBCD_STRING (pctxt, pvalue->vplmn);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  MobileUIM                                                 */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225MobileUIM (OOCTXT* pctxt, H225MobileUIM* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 2);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* ansi_41_uim */
         case 1:
            stat = asn1PE_H225ANSI_41_UIM (pctxt, pvalue->u.ansi_41_uim);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* gsm_uim */
         case 2:
            stat = asn1PE_H225GSM_UIM (pctxt, pvalue->u.gsm_uim);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  AliasAddress                                              */
/*                                                            */
/**************************************************************/

extern EXTERN const char* gs_H323_MESSAGES_AliasAddress_dialedDigits_CharSet;

EXTERN int asn1PE_H225AliasAddress (OOCTXT* pctxt, H225AliasAddress* pvalue)
{
   static Asn1SizeCnst dialedDigits_lsize1 = { 0, 1, 128, 0 };
   static Asn1SizeCnst h323_ID_lsize1 = { 0, 1, 256, 0 };
   static Asn1SizeCnst url_ID_lsize1 = { 0, 1, 512, 0 };
   static Asn1SizeCnst email_ID_lsize1 = { 0, 1, 512, 0 };
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 2);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* dialedDigits */
         case 1:
            stat = addSizeConstraint (pctxt, &dialedDigits_lsize1);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

            stat = encodeConstrainedStringEx (pctxt, pvalue->u.dialedDigits, gs_H323_MESSAGES_AliasAddress_dialedDigits_CharSet, 4, 4, 7);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* h323_ID */
         case 2:
            stat = addSizeConstraint (pctxt, &h323_ID_lsize1);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

            stat = encodeBMPString (pctxt, pvalue->u.h323_ID, 0);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* url_ID */
         case 3:
            stat = addSizeConstraint (&lctxt, &url_ID_lsize1);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }

            stat = encodeConstrainedStringEx (&lctxt, pvalue->u.url_ID, 0, 8, 7, 7);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* transportID */
         case 4:
            stat = asn1PE_H225TransportAddress (&lctxt, pvalue->u.transportID);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* email_ID */
         case 5:
            stat = addSizeConstraint (&lctxt, &email_ID_lsize1);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }

            stat = encodeConstrainedStringEx (&lctxt, pvalue->u.email_ID, 0, 8, 7, 7);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* partyNumber */
         case 6:
            stat = asn1PE_H225PartyNumber (&lctxt, pvalue->u.partyNumber);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* mobileUIM */
         case 7:
            stat = asn1PE_H225MobileUIM (&lctxt, pvalue->u.mobileUIM);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Content_compound                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Content_compound (OOCTXT* pctxt, H225Content_compound value)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 512, 0 };
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeLength (pctxt, value.count);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */
   pnode = value.head;

   for (xx1 = 0; xx1 < value.count; xx1++) {
      stat = asn1PE_H225EnumeratedParameter (pctxt, (H225EnumeratedParameter*)((H225EnumeratedParameter*)pnode->data));
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      pnode = pnode->next;
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Content_nested                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Content_nested (OOCTXT* pctxt, H225Content_nested value)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 16, 0 };
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeLength (pctxt, value.count);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */
   pnode = value.head;

   for (xx1 = 0; xx1 < value.count; xx1++) {
      stat = asn1PE_H225GenericData (pctxt, (H225GenericData*)((H225GenericData*)pnode->data));
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      pnode = pnode->next;
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Content                                                   */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Content (OOCTXT* pctxt, H225Content* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 12);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 11);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* raw */
         case 1:
            stat = encodeOctetString (pctxt, pvalue->u.raw->numocts, pvalue->u.raw->data);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* text */
         case 2:
            stat = encodeConstrainedStringEx (pctxt, pvalue->u.text, 0, 8, 7, 7);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* unicode */
         case 3:
            stat = encodeBMPString (pctxt, pvalue->u.unicode, 0);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* bool_ */
         case 4:
            stat = encodeBit (pctxt, (ASN1BOOL)pvalue->u.bool_);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* number8 */
         case 5:
            stat = encodeConsUnsigned (pctxt, pvalue->u.number8, 0U, 255U);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

            break;

         /* number16 */
         case 6:
            stat = encodeConsUnsigned (pctxt, pvalue->u.number16, 0U, 65535U);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

            break;

         /* number32 */
         case 7:
            stat = encodeConsUnsigned (pctxt, pvalue->u.number32, 0U, ASN1UINT_MAX);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

            break;

         /* id */
         case 8:
            stat = asn1PE_H225GenericIdentifier (pctxt, pvalue->u.id);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* alias */
         case 9:
            stat = asn1PE_H225AliasAddress (pctxt, pvalue->u.alias);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* transport */
         case 10:
            stat = asn1PE_H225TransportAddress (pctxt, pvalue->u.transport);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* compound */
         case 11:
            stat = asn1PE_H225Content_compound (pctxt, *pvalue->u.compound);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* nested */
         case 12:
            stat = asn1PE_H225Content_nested (pctxt, *pvalue->u.nested);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 13);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  EnumeratedParameter                                       */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225EnumeratedParameter (OOCTXT* pctxt, H225EnumeratedParameter* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.contentPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode id */

   stat = asn1PE_H225GenericIdentifier (pctxt, &pvalue->id);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode content */

   if (pvalue->m.contentPresent) {
      stat = asn1PE_H225Content (pctxt, &pvalue->content);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GenericData_parameters                                    */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GenericData_parameters (OOCTXT* pctxt, H225GenericData_parameters value)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 512, 0 };
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeLength (pctxt, value.count);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */
   pnode = value.head;

   for (xx1 = 0; xx1 < value.count; xx1++) {
      stat = asn1PE_H225EnumeratedParameter (pctxt, ((H225EnumeratedParameter*)pnode->data));
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      pnode = pnode->next;
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GenericData                                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GenericData (OOCTXT* pctxt, H225GenericData* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.parametersPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode id */

   stat = asn1PE_H225GenericIdentifier (pctxt, &pvalue->id);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode parameters */

   if (pvalue->m.parametersPresent) {
      stat = asn1PE_H225GenericData_parameters (pctxt, pvalue->parameters);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  FeatureDescriptor                                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225FeatureDescriptor (OOCTXT* pctxt, H225FeatureDescriptor* pvalue)
{
   int stat = ASN_OK;

   stat = asn1PE_H225GenericData (pctxt, pvalue);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  FastStartToken                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225FastStartToken (OOCTXT* pctxt, H225FastStartToken* pvalue)
{
   int stat = ASN_OK;

   stat = asn1PE_H235ClearToken (pctxt, pvalue);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  EncodedFastStartToken                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225EncodedFastStartToken (OOCTXT* pctxt, H225EncodedFastStartToken value)
{
   int stat = ASN_OK;

   stat = encodeOpenType (pctxt, value.numocts, value.data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H323_UserInformation_user_data_user_information           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H323_UserInformation_user_data_user_information (OOCTXT* pctxt, H225H323_UserInformation_user_data_user_information* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 131, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  EndpointType_set                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225EndpointType_set (OOCTXT* pctxt, H225EndpointType_set* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 32, 32, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBitString (pctxt, pvalue->numbits, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  VendorIdentifier_productId                                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225VendorIdentifier_productId (OOCTXT* pctxt, H225VendorIdentifier_productId* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 256, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  VendorIdentifier_versionId                                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225VendorIdentifier_versionId (OOCTXT* pctxt, H225VendorIdentifier_versionId* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 256, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CicInfo_cic_element                                       */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CicInfo_cic_element (OOCTXT* pctxt, H225CicInfo_cic_element* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 2, 4, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CicInfo_pointCode                                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CicInfo_pointCode (OOCTXT* pctxt, H225CicInfo_pointCode* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 2, 5, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CarrierInfo_carrierIdentificationCode                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CarrierInfo_carrierIdentificationCode (OOCTXT* pctxt, H225CarrierInfo_carrierIdentificationCode* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 3, 4, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallTerminationCause_releaseCompleteCauseIE               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallTerminationCause_releaseCompleteCauseIE (OOCTXT* pctxt, H225CallTerminationCause_releaseCompleteCauseIE* pvalue)
{
   static Asn1SizeCnst lsize1 = { 0, 2, 32, 0 };
   int stat = ASN_OK;

   stat = addSizeConstraint (pctxt, &lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeOctetString (pctxt, pvalue->numocts, pvalue->data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225AliasAddress                                    */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225AliasAddress (OOCTXT* pctxt, H225_SeqOfH225AliasAddress value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225AliasAddress (pctxt, ((H225AliasAddress*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  VendorIdentifier                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225VendorIdentifier (OOCTXT* pctxt, H225VendorIdentifier* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.enterpriseNumberPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.productIdPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.versionIdPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode vendor */

   stat = asn1PE_H225H221NonStandard (pctxt, &pvalue->vendor);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode productId */

   if (pvalue->m.productIdPresent) {
      stat = asn1PE_H225VendorIdentifier_productId (pctxt, &pvalue->productId);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode versionId */

   if (pvalue->m.versionIdPresent) {
      stat = asn1PE_H225VendorIdentifier_versionId (pctxt, &pvalue->versionId);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.enterpriseNumberPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.enterpriseNumberPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeObjectIdentifier (&lctxt, &pvalue->enterpriseNumber);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GatekeeperInfo                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GatekeeperInfo (OOCTXT* pctxt, H225GatekeeperInfo* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  DataRate                                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225DataRate (OOCTXT* pctxt, H225DataRate* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.channelMultiplierPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode channelRate */

   stat = asn1PE_H225BandWidth (pctxt, pvalue->channelRate);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode channelMultiplier */

   if (pvalue->m.channelMultiplierPresent) {
      if ( (pvalue->channelMultiplier >= 1 && pvalue->channelMultiplier <= 256) ) {
         stat = encodeConsUnsigned (pctxt, pvalue->channelMultiplier, 1U, 256U);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
      else
         return LOG_ASN1ERR (pctxt, ASN_E_CONSVIO);

   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225DataRate                                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225DataRate (OOCTXT* pctxt, H225_SeqOfH225DataRate value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225DataRate (pctxt, ((H225DataRate*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  SupportedPrefix                                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225SupportedPrefix (OOCTXT* pctxt, H225SupportedPrefix* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode prefix */

   stat = asn1PE_H225AliasAddress (pctxt, &pvalue->prefix);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225SupportedPrefix                                 */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225SupportedPrefix (OOCTXT* pctxt, H225_SeqOfH225SupportedPrefix value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225SupportedPrefix (pctxt, ((H225SupportedPrefix*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H310Caps                                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H310Caps (OOCTXT* pctxt, H225H310Caps* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.dataRatesSupportedPresent ||
   pvalue->m.supportedPrefixesPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.dataRatesSupportedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedPrefixesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.dataRatesSupportedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225DataRate (&lctxt, pvalue->dataRatesSupported);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedPrefixesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedPrefix (&lctxt, pvalue->supportedPrefixes);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H320Caps                                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H320Caps (OOCTXT* pctxt, H225H320Caps* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.dataRatesSupportedPresent ||
   pvalue->m.supportedPrefixesPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.dataRatesSupportedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedPrefixesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.dataRatesSupportedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225DataRate (&lctxt, pvalue->dataRatesSupported);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedPrefixesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedPrefix (&lctxt, pvalue->supportedPrefixes);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H321Caps                                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H321Caps (OOCTXT* pctxt, H225H321Caps* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.dataRatesSupportedPresent ||
   pvalue->m.supportedPrefixesPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.dataRatesSupportedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedPrefixesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.dataRatesSupportedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225DataRate (&lctxt, pvalue->dataRatesSupported);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedPrefixesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedPrefix (&lctxt, pvalue->supportedPrefixes);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H322Caps                                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H322Caps (OOCTXT* pctxt, H225H322Caps* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.dataRatesSupportedPresent ||
   pvalue->m.supportedPrefixesPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.dataRatesSupportedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedPrefixesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.dataRatesSupportedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225DataRate (&lctxt, pvalue->dataRatesSupported);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedPrefixesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedPrefix (&lctxt, pvalue->supportedPrefixes);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H323Caps                                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H323Caps (OOCTXT* pctxt, H225H323Caps* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.dataRatesSupportedPresent ||
   pvalue->m.supportedPrefixesPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.dataRatesSupportedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedPrefixesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.dataRatesSupportedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225DataRate (&lctxt, pvalue->dataRatesSupported);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedPrefixesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedPrefix (&lctxt, pvalue->supportedPrefixes);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H324Caps                                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H324Caps (OOCTXT* pctxt, H225H324Caps* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.dataRatesSupportedPresent ||
   pvalue->m.supportedPrefixesPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.dataRatesSupportedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedPrefixesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.dataRatesSupportedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225DataRate (&lctxt, pvalue->dataRatesSupported);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedPrefixesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedPrefix (&lctxt, pvalue->supportedPrefixes);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  VoiceCaps                                                 */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225VoiceCaps (OOCTXT* pctxt, H225VoiceCaps* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.dataRatesSupportedPresent ||
   pvalue->m.supportedPrefixesPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.dataRatesSupportedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedPrefixesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.dataRatesSupportedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225DataRate (&lctxt, pvalue->dataRatesSupported);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedPrefixesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedPrefix (&lctxt, pvalue->supportedPrefixes);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  T120OnlyCaps                                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225T120OnlyCaps (OOCTXT* pctxt, H225T120OnlyCaps* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.dataRatesSupportedPresent ||
   pvalue->m.supportedPrefixesPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.dataRatesSupportedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedPrefixesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.dataRatesSupportedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225DataRate (&lctxt, pvalue->dataRatesSupported);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedPrefixesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedPrefix (&lctxt, pvalue->supportedPrefixes);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  NonStandardProtocol                                       */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225NonStandardProtocol (OOCTXT* pctxt, H225NonStandardProtocol* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.dataRatesSupportedPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode dataRatesSupported */

   if (pvalue->m.dataRatesSupportedPresent) {
      stat = asn1PE_H225_SeqOfH225DataRate (pctxt, pvalue->dataRatesSupported);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode supportedPrefixes */

   stat = asn1PE_H225_SeqOfH225SupportedPrefix (pctxt, pvalue->supportedPrefixes);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  T38FaxAnnexbOnlyCaps                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225T38FaxAnnexbOnlyCaps (OOCTXT* pctxt, H225T38FaxAnnexbOnlyCaps* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.dataRatesSupportedPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode dataRatesSupported */

   if (pvalue->m.dataRatesSupportedPresent) {
      stat = asn1PE_H225_SeqOfH225DataRate (pctxt, pvalue->dataRatesSupported);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode supportedPrefixes */

   stat = asn1PE_H225_SeqOfH225SupportedPrefix (pctxt, pvalue->supportedPrefixes);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode t38FaxProtocol */

   stat = asn1PE_H245DataProtocolCapability (pctxt, &pvalue->t38FaxProtocol);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode t38FaxProfile */

   stat = asn1PE_H245T38FaxProfile (pctxt, &pvalue->t38FaxProfile);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  SIPCaps                                                   */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225SIPCaps (OOCTXT* pctxt, H225SIPCaps* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.dataRatesSupportedPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedPrefixesPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode dataRatesSupported */

   if (pvalue->m.dataRatesSupportedPresent) {
      stat = asn1PE_H225_SeqOfH225DataRate (pctxt, pvalue->dataRatesSupported);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode supportedPrefixes */

   if (pvalue->m.supportedPrefixesPresent) {
      stat = asn1PE_H225_SeqOfH225SupportedPrefix (pctxt, pvalue->supportedPrefixes);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  SupportedProtocols                                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225SupportedProtocols (OOCTXT* pctxt, H225SupportedProtocols* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 9);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 8);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* nonStandardData */
         case 1:
            stat = asn1PE_H225NonStandardParameter (pctxt, pvalue->u.nonStandardData);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* h310 */
         case 2:
            stat = asn1PE_H225H310Caps (pctxt, pvalue->u.h310);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* h320 */
         case 3:
            stat = asn1PE_H225H320Caps (pctxt, pvalue->u.h320);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* h321 */
         case 4:
            stat = asn1PE_H225H321Caps (pctxt, pvalue->u.h321);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* h322 */
         case 5:
            stat = asn1PE_H225H322Caps (pctxt, pvalue->u.h322);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* h323 */
         case 6:
            stat = asn1PE_H225H323Caps (pctxt, pvalue->u.h323);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* h324 */
         case 7:
            stat = asn1PE_H225H324Caps (pctxt, pvalue->u.h324);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* voice */
         case 8:
            stat = asn1PE_H225VoiceCaps (pctxt, pvalue->u.voice);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* t120_only */
         case 9:
            stat = asn1PE_H225T120OnlyCaps (pctxt, pvalue->u.t120_only);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 10);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* nonStandardProtocol */
         case 10:
            stat = asn1PE_H225NonStandardProtocol (&lctxt, pvalue->u.nonStandardProtocol);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* t38FaxAnnexbOnly */
         case 11:
            stat = asn1PE_H225T38FaxAnnexbOnlyCaps (&lctxt, pvalue->u.t38FaxAnnexbOnly);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* sip */
         case 12:
            stat = asn1PE_H225SIPCaps (&lctxt, pvalue->u.sip);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225SupportedProtocols                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225SupportedProtocols (OOCTXT* pctxt, H225_SeqOfH225SupportedProtocols value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225SupportedProtocols (pctxt, ((H225SupportedProtocols*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GatewayInfo                                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GatewayInfo (OOCTXT* pctxt, H225GatewayInfo* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.protocolPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocol */

   if (pvalue->m.protocolPresent) {
      stat = asn1PE_H225_SeqOfH225SupportedProtocols (pctxt, pvalue->protocol);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  McuInfo                                                   */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225McuInfo (OOCTXT* pctxt, H225McuInfo* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.protocolPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.protocolPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.protocolPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedProtocols (&lctxt, pvalue->protocol);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TerminalInfo                                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TerminalInfo (OOCTXT* pctxt, H225TerminalInfo* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TunnelledProtocolAlternateIdentifier                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TunnelledProtocolAlternateIdentifier (OOCTXT* pctxt, H225TunnelledProtocolAlternateIdentifier* pvalue)
{
   static Asn1SizeCnst protocolType_lsize1 = { 0, 1, 64, 0 };
   static Asn1SizeCnst protocolVariant_lsize1 = { 0, 1, 64, 0 };
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.protocolVariantPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolType */

   stat = addSizeConstraint (pctxt, &protocolType_lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeConstrainedStringEx (pctxt, pvalue->protocolType, 0, 8, 7, 7);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolVariant */

   if (pvalue->m.protocolVariantPresent) {
      stat = addSizeConstraint (pctxt, &protocolVariant_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeConstrainedStringEx (pctxt, pvalue->protocolVariant, 0, 8, 7, 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TunnelledProtocol_id                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TunnelledProtocol_id (OOCTXT* pctxt, H225TunnelledProtocol_id* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 2);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* tunnelledProtocolObjectID */
         case 1:
            stat = encodeObjectIdentifier (pctxt, pvalue->u.tunnelledProtocolObjectID);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* tunnelledProtocolAlternateID */
         case 2:
            stat = asn1PE_H225TunnelledProtocolAlternateIdentifier (pctxt, pvalue->u.tunnelledProtocolAlternateID);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TunnelledProtocol                                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TunnelledProtocol (OOCTXT* pctxt, H225TunnelledProtocol* pvalue)
{
   static Asn1SizeCnst subIdentifier_lsize1 = { 0, 1, 64, 0 };
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.subIdentifierPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode id */

   stat = asn1PE_H225TunnelledProtocol_id (pctxt, &pvalue->id);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode subIdentifier */

   if (pvalue->m.subIdentifierPresent) {
      stat = addSizeConstraint (pctxt, &subIdentifier_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeConstrainedStringEx (pctxt, pvalue->subIdentifier, 0, 8, 7, 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225TunnelledProtocol                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225TunnelledProtocol (OOCTXT* pctxt, H225_SeqOfH225TunnelledProtocol value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225TunnelledProtocol (pctxt, ((H225TunnelledProtocol*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  EndpointType                                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225EndpointType (OOCTXT* pctxt, H225EndpointType* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.setPresent ||
   pvalue->m.supportedTunnelledProtocolsPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.vendorPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatekeeperPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatewayPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.mcuPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.terminalPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode vendor */

   if (pvalue->m.vendorPresent) {
      stat = asn1PE_H225VendorIdentifier (pctxt, &pvalue->vendor);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode gatekeeper */

   if (pvalue->m.gatekeeperPresent) {
      stat = asn1PE_H225GatekeeperInfo (pctxt, &pvalue->gatekeeper);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode gateway */

   if (pvalue->m.gatewayPresent) {
      stat = asn1PE_H225GatewayInfo (pctxt, &pvalue->gateway);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode mcu */

   if (pvalue->m.mcuPresent) {
      stat = asn1PE_H225McuInfo (pctxt, &pvalue->mcu);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode terminal */

   if (pvalue->m.terminalPresent) {
      stat = asn1PE_H225TerminalInfo (pctxt, &pvalue->terminal);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode mc */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->mc);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode undefinedNode */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->undefinedNode);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.setPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedTunnelledProtocolsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.setPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225EndpointType_set (&lctxt, &pvalue->set);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedTunnelledProtocolsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225TunnelledProtocol (&lctxt, pvalue->supportedTunnelledProtocols);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225CallReferenceValue                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225CallReferenceValue (OOCTXT* pctxt, H225_SeqOfH225CallReferenceValue* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = asn1PE_H225CallReferenceValue (pctxt, pvalue->elem[xx1]);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Setup_UUIE_conferenceGoal                                 */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Setup_UUIE_conferenceGoal (OOCTXT* pctxt, H225Setup_UUIE_conferenceGoal* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 3);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 2);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* create */
         case 1:
            /* NULL */
            break;

         /* join */
         case 2:
            /* NULL */
            break;

         /* invite */
         case 3:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* capability_negotiation */
         case 4:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* callIndependentSupplementaryService */
         case 5:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Q954Details                                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Q954Details (OOCTXT* pctxt, H225Q954Details* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode conferenceCalling */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->conferenceCalling);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode threePartyService */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->threePartyService);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  QseriesOptions                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225QseriesOptions (OOCTXT* pctxt, H225QseriesOptions* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode q932Full */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->q932Full);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode q951Full */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->q951Full);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode q952Full */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->q952Full);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode q953Full */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->q953Full);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode q955Full */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->q955Full);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode q956Full */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->q956Full);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode q957Full */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->q957Full);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode q954Info */

   stat = asn1PE_H225Q954Details (pctxt, &pvalue->q954Info);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallType                                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallType (OOCTXT* pctxt, H225CallType* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 4);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* pointToPoint */
         case 1:
            /* NULL */
            break;

         /* oneToN */
         case 2:
            /* NULL */
            break;

         /* nToOne */
         case 3:
            /* NULL */
            break;

         /* nToN */
         case 4:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallIdentifier                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallIdentifier (OOCTXT* pctxt, H225CallIdentifier* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode guid */

   stat = asn1PE_H225GloballyUniqueID (pctxt, &pvalue->guid);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  SecurityServiceMode                                       */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225SecurityServiceMode (OOCTXT* pctxt, H225SecurityServiceMode* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 3);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 2);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* nonStandard */
         case 1:
            stat = asn1PE_H225NonStandardParameter (pctxt, pvalue->u.nonStandard);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* none */
         case 2:
            /* NULL */
            break;

         /* default_ */
         case 3:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  SecurityCapabilities                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225SecurityCapabilities (OOCTXT* pctxt, H225SecurityCapabilities* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandard */

   if (pvalue->m.nonStandardPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandard);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode encryption */

   stat = asn1PE_H225SecurityServiceMode (pctxt, &pvalue->encryption);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode authenticaton */

   stat = asn1PE_H225SecurityServiceMode (pctxt, &pvalue->authenticaton);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode integrity */

   stat = asn1PE_H225SecurityServiceMode (pctxt, &pvalue->integrity);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H245Security                                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H245Security (OOCTXT* pctxt, H225H245Security* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 4);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* nonStandard */
         case 1:
            stat = asn1PE_H225NonStandardParameter (pctxt, pvalue->u.nonStandard);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* noSecurity */
         case 2:
            /* NULL */
            break;

         /* tls */
         case 3:
            stat = asn1PE_H225SecurityCapabilities (pctxt, pvalue->u.tls);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* ipsec */
         case 4:
            stat = asn1PE_H225SecurityCapabilities (pctxt, pvalue->u.ipsec);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225H245Security                                    */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225H245Security (OOCTXT* pctxt, H225_SeqOfH225H245Security value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225H245Security (pctxt, ((H225H245Security*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225ClearToken                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225ClearToken (OOCTXT* pctxt, H225_SeqOfH225ClearToken value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H235ClearToken (pctxt, ((H235ClearToken*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CryptoH323Token_cryptoEPPwdHash                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CryptoH323Token_cryptoEPPwdHash (OOCTXT* pctxt, H225CryptoH323Token_cryptoEPPwdHash* pvalue)
{
   int stat = ASN_OK;

   /* encode alias */

   stat = asn1PE_H225AliasAddress (pctxt, &pvalue->alias);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode timeStamp */

   stat = asn1PE_H235TimeStamp (pctxt, pvalue->timeStamp);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode token */

   stat = asn1PE_H235HASHED (pctxt, &pvalue->token);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CryptoH323Token_cryptoGKPwdHash                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CryptoH323Token_cryptoGKPwdHash (OOCTXT* pctxt, H225CryptoH323Token_cryptoGKPwdHash* pvalue)
{
   int stat = ASN_OK;

   /* encode gatekeeperId */

   stat = asn1PE_H225GatekeeperIdentifier (pctxt, pvalue->gatekeeperId);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode timeStamp */

   stat = asn1PE_H235TimeStamp (pctxt, pvalue->timeStamp);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode token */

   stat = asn1PE_H235HASHED (pctxt, &pvalue->token);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CryptoH323Token_cryptoEPCert                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CryptoH323Token_cryptoEPCert (OOCTXT* pctxt, H225CryptoH323Token_cryptoEPCert* pvalue)
{
   int stat = ASN_OK;

   /* encode toBeSigned */

   stat = asn1PE_H235EncodedPwdCertToken (pctxt, pvalue->toBeSigned);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode algorithmOID */

   stat = encodeObjectIdentifier (pctxt, &pvalue->algorithmOID);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode paramS */

   stat = asn1PE_H235Params (pctxt, &pvalue->paramS);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode signature */

   stat = encodeBitString (pctxt, pvalue->signature.numbits, pvalue->signature.data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CryptoH323Token_cryptoGKCert                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CryptoH323Token_cryptoGKCert (OOCTXT* pctxt, H225CryptoH323Token_cryptoGKCert* pvalue)
{
   int stat = ASN_OK;

   /* encode toBeSigned */

   stat = asn1PE_H235EncodedPwdCertToken (pctxt, pvalue->toBeSigned);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode algorithmOID */

   stat = encodeObjectIdentifier (pctxt, &pvalue->algorithmOID);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode paramS */

   stat = asn1PE_H235Params (pctxt, &pvalue->paramS);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode signature */

   stat = encodeBitString (pctxt, pvalue->signature.numbits, pvalue->signature.data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CryptoH323Token_cryptoFastStart                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CryptoH323Token_cryptoFastStart (OOCTXT* pctxt, H225CryptoH323Token_cryptoFastStart* pvalue)
{
   int stat = ASN_OK;

   /* encode toBeSigned */

   stat = asn1PE_H225EncodedFastStartToken (pctxt, pvalue->toBeSigned);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode algorithmOID */

   stat = encodeObjectIdentifier (pctxt, &pvalue->algorithmOID);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode paramS */

   stat = asn1PE_H235Params (pctxt, &pvalue->paramS);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode signature */

   stat = encodeBitString (pctxt, pvalue->signature.numbits, pvalue->signature.data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CryptoH323Token                                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CryptoH323Token (OOCTXT* pctxt, H225CryptoH323Token* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 8);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* cryptoEPPwdHash */
         case 1:
            stat = asn1PE_H225CryptoH323Token_cryptoEPPwdHash (pctxt, pvalue->u.cryptoEPPwdHash);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* cryptoGKPwdHash */
         case 2:
            stat = asn1PE_H225CryptoH323Token_cryptoGKPwdHash (pctxt, pvalue->u.cryptoGKPwdHash);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* cryptoEPPwdEncr */
         case 3:
            stat = asn1PE_H235ENCRYPTED (pctxt, pvalue->u.cryptoEPPwdEncr);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* cryptoGKPwdEncr */
         case 4:
            stat = asn1PE_H235ENCRYPTED (pctxt, pvalue->u.cryptoGKPwdEncr);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* cryptoEPCert */
         case 5:
            stat = asn1PE_H225CryptoH323Token_cryptoEPCert (pctxt, pvalue->u.cryptoEPCert);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* cryptoGKCert */
         case 6:
            stat = asn1PE_H225CryptoH323Token_cryptoGKCert (pctxt, pvalue->u.cryptoGKCert);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* cryptoFastStart */
         case 7:
            stat = asn1PE_H225CryptoH323Token_cryptoFastStart (pctxt, pvalue->u.cryptoFastStart);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* nestedcryptoToken */
         case 8:
            stat = asn1PE_H235CryptoToken (pctxt, pvalue->u.nestedcryptoToken);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 9);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225CryptoH323Token                                 */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225CryptoH323Token (OOCTXT* pctxt, H225_SeqOfH225CryptoH323Token value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225CryptoH323Token (pctxt, ((H225CryptoH323Token*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Setup_UUIE_fastStart                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Setup_UUIE_fastStart (OOCTXT* pctxt, H225Setup_UUIE_fastStart* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = encodeOctetString (pctxt, pvalue->elem[xx1].numocts, pvalue->elem[xx1].data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ScnConnectionType                                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ScnConnectionType (OOCTXT* pctxt, H225ScnConnectionType* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 7);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 6);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* unknown */
         case 1:
            /* NULL */
            break;

         /* bChannel */
         case 2:
            /* NULL */
            break;

         /* hybrid2x64 */
         case 3:
            /* NULL */
            break;

         /* hybrid384 */
         case 4:
            /* NULL */
            break;

         /* hybrid1536 */
         case 5:
            /* NULL */
            break;

         /* hybrid1920 */
         case 6:
            /* NULL */
            break;

         /* multirate */
         case 7:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 8);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ScnConnectionAggregation                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ScnConnectionAggregation (OOCTXT* pctxt, H225ScnConnectionAggregation* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 6);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* auto_ */
         case 1:
            /* NULL */
            break;

         /* none */
         case 2:
            /* NULL */
            break;

         /* h221 */
         case 3:
            /* NULL */
            break;

         /* bonded_mode1 */
         case 4:
            /* NULL */
            break;

         /* bonded_mode2 */
         case 5:
            /* NULL */
            break;

         /* bonded_mode3 */
         case 6:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Setup_UUIE_connectionParameters                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Setup_UUIE_connectionParameters (OOCTXT* pctxt, H225Setup_UUIE_connectionParameters* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode connectionType */

   stat = asn1PE_H225ScnConnectionType (pctxt, &pvalue->connectionType);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode numberOfScnConnections */

   stat = encodeConsUnsigned (pctxt, pvalue->numberOfScnConnections, 0U, 65535U);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode connectionAggregation */

   stat = asn1PE_H225ScnConnectionAggregation (pctxt, &pvalue->connectionAggregation);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Setup_UUIE_language                                       */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Setup_UUIE_language (OOCTXT* pctxt, H225Setup_UUIE_language* pvalue)
{
   static Asn1SizeCnst element_lsize1 = { 0, 1, 32, 0 };
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = addSizeConstraint (pctxt, &element_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeConstrainedStringEx (pctxt, pvalue->elem[xx1], 0, 8, 7, 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  PresentationIndicator                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225PresentationIndicator (OOCTXT* pctxt, H225PresentationIndicator* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 3);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 2);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* presentationAllowed */
         case 1:
            /* NULL */
            break;

         /* presentationRestricted */
         case 2:
            /* NULL */
            break;

         /* addressNotAvailable */
         case 3:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallCreditServiceControl_billingMode                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallCreditServiceControl_billingMode (OOCTXT* pctxt, H225CallCreditServiceControl_billingMode* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 2);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* credit */
         case 1:
            /* NULL */
            break;

         /* debit */
         case 2:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallCreditServiceControl_callStartingPoint                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallCreditServiceControl_callStartingPoint (OOCTXT* pctxt, H225CallCreditServiceControl_callStartingPoint* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 2);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* alerting */
         case 1:
            /* NULL */
            break;

         /* connect */
         case 2:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallCreditServiceControl                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallCreditServiceControl (OOCTXT* pctxt, H225CallCreditServiceControl* pvalue)
{
   static Asn1SizeCnst amountString_lsize1 = { 0, 1, 512, 0 };
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.amountStringPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.billingModePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callDurationLimitPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.enforceCallDurationLimitPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callStartingPointPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode amountString */

   if (pvalue->m.amountStringPresent) {
      stat = addSizeConstraint (pctxt, &amountString_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBMPString (pctxt, pvalue->amountString, 0);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode billingMode */

   if (pvalue->m.billingModePresent) {
      stat = asn1PE_H225CallCreditServiceControl_billingMode (pctxt, &pvalue->billingMode);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode callDurationLimit */

   if (pvalue->m.callDurationLimitPresent) {
      stat = encodeConsUnsigned (pctxt, pvalue->callDurationLimit, 1U, ASN1UINT_MAX);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   }

   /* encode enforceCallDurationLimit */

   if (pvalue->m.enforceCallDurationLimitPresent) {
      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->enforceCallDurationLimit);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode callStartingPoint */

   if (pvalue->m.callStartingPointPresent) {
      stat = asn1PE_H225CallCreditServiceControl_callStartingPoint (pctxt, &pvalue->callStartingPoint);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ServiceControlDescriptor                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ServiceControlDescriptor (OOCTXT* pctxt, H225ServiceControlDescriptor* pvalue)
{
   static Asn1SizeCnst url_lsize1 = { 0, 0, 512, 0 };
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 4);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* url */
         case 1:
            stat = addSizeConstraint (pctxt, &url_lsize1);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

            stat = encodeConstrainedStringEx (pctxt, pvalue->u.url, 0, 8, 7, 7);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* signal */
         case 2:
            stat = asn1PE_H225H248SignalsDescriptor (pctxt, *pvalue->u.signal);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* nonStandard */
         case 3:
            stat = asn1PE_H225NonStandardParameter (pctxt, pvalue->u.nonStandard);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* callCreditServiceControl */
         case 4:
            stat = asn1PE_H225CallCreditServiceControl (pctxt, pvalue->u.callCreditServiceControl);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ServiceControlSession_reason                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ServiceControlSession_reason (OOCTXT* pctxt, H225ServiceControlSession_reason* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 3);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 2);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* open */
         case 1:
            /* NULL */
            break;

         /* refresh */
         case 2:
            /* NULL */
            break;

         /* close */
         case 3:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ServiceControlSession                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ServiceControlSession (OOCTXT* pctxt, H225ServiceControlSession* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.contentsPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode sessionId */

   stat = encodeConsUnsigned (pctxt, pvalue->sessionId, 0U, 255U);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode contents */

   if (pvalue->m.contentsPresent) {
      stat = asn1PE_H225ServiceControlDescriptor (pctxt, &pvalue->contents);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode reason */

   stat = asn1PE_H225ServiceControlSession_reason (pctxt, &pvalue->reason);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225ServiceControlSession                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225ServiceControlSession (OOCTXT* pctxt, H225_SeqOfH225ServiceControlSession value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225ServiceControlSession (pctxt, ((H225ServiceControlSession*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CarrierInfo                                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CarrierInfo (OOCTXT* pctxt, H225CarrierInfo* pvalue)
{
   static Asn1SizeCnst carrierName_lsize1 = { 0, 1, 128, 0 };
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.carrierIdentificationCodePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.carrierNamePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode carrierIdentificationCode */

   if (pvalue->m.carrierIdentificationCodePresent) {
      stat = asn1PE_H225CarrierInfo_carrierIdentificationCode (pctxt, &pvalue->carrierIdentificationCode);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode carrierName */

   if (pvalue->m.carrierNamePresent) {
      stat = addSizeConstraint (pctxt, &carrierName_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeConstrainedStringEx (pctxt, pvalue->carrierName, 0, 8, 7, 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallsAvailable                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallsAvailable (OOCTXT* pctxt, H225CallsAvailable* pvalue)
{
   static Asn1SizeCnst group_lsize1 = { 0, 1, 128, 0 };
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.carrierPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.groupPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode calls */

   stat = encodeConsUnsigned (pctxt, pvalue->calls, 0U, ASN1UINT_MAX);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode group */

   if (pvalue->m.groupPresent) {
      stat = addSizeConstraint (pctxt, &group_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeConstrainedStringEx (pctxt, pvalue->group, 0, 8, 7, 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.carrierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.carrierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CarrierInfo (&lctxt, &pvalue->carrier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225CallsAvailable                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225CallsAvailable (OOCTXT* pctxt, H225_SeqOfH225CallsAvailable value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225CallsAvailable (pctxt, ((H225CallsAvailable*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallCapacityInfo                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallCapacityInfo (OOCTXT* pctxt, H225CallCapacityInfo* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.sipGwCallsAvailablePresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.voiceGwCallsAvailablePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h310GwCallsAvailablePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h320GwCallsAvailablePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h321GwCallsAvailablePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h322GwCallsAvailablePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h323GwCallsAvailablePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h324GwCallsAvailablePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.t120OnlyGwCallsAvailablePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.t38FaxAnnexbOnlyGwCallsAvailablePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.terminalCallsAvailablePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.mcuCallsAvailablePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode voiceGwCallsAvailable */

   if (pvalue->m.voiceGwCallsAvailablePresent) {
      stat = asn1PE_H225_SeqOfH225CallsAvailable (pctxt, pvalue->voiceGwCallsAvailable);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode h310GwCallsAvailable */

   if (pvalue->m.h310GwCallsAvailablePresent) {
      stat = asn1PE_H225_SeqOfH225CallsAvailable (pctxt, pvalue->h310GwCallsAvailable);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode h320GwCallsAvailable */

   if (pvalue->m.h320GwCallsAvailablePresent) {
      stat = asn1PE_H225_SeqOfH225CallsAvailable (pctxt, pvalue->h320GwCallsAvailable);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode h321GwCallsAvailable */

   if (pvalue->m.h321GwCallsAvailablePresent) {
      stat = asn1PE_H225_SeqOfH225CallsAvailable (pctxt, pvalue->h321GwCallsAvailable);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode h322GwCallsAvailable */

   if (pvalue->m.h322GwCallsAvailablePresent) {
      stat = asn1PE_H225_SeqOfH225CallsAvailable (pctxt, pvalue->h322GwCallsAvailable);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode h323GwCallsAvailable */

   if (pvalue->m.h323GwCallsAvailablePresent) {
      stat = asn1PE_H225_SeqOfH225CallsAvailable (pctxt, pvalue->h323GwCallsAvailable);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode h324GwCallsAvailable */

   if (pvalue->m.h324GwCallsAvailablePresent) {
      stat = asn1PE_H225_SeqOfH225CallsAvailable (pctxt, pvalue->h324GwCallsAvailable);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode t120OnlyGwCallsAvailable */

   if (pvalue->m.t120OnlyGwCallsAvailablePresent) {
      stat = asn1PE_H225_SeqOfH225CallsAvailable (pctxt, pvalue->t120OnlyGwCallsAvailable);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode t38FaxAnnexbOnlyGwCallsAvailable */

   if (pvalue->m.t38FaxAnnexbOnlyGwCallsAvailablePresent) {
      stat = asn1PE_H225_SeqOfH225CallsAvailable (pctxt, pvalue->t38FaxAnnexbOnlyGwCallsAvailable);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode terminalCallsAvailable */

   if (pvalue->m.terminalCallsAvailablePresent) {
      stat = asn1PE_H225_SeqOfH225CallsAvailable (pctxt, pvalue->terminalCallsAvailable);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode mcuCallsAvailable */

   if (pvalue->m.mcuCallsAvailablePresent) {
      stat = asn1PE_H225_SeqOfH225CallsAvailable (pctxt, pvalue->mcuCallsAvailable);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.sipGwCallsAvailablePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.sipGwCallsAvailablePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CallsAvailable (&lctxt, pvalue->sipGwCallsAvailable);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallCapacity                                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallCapacity (OOCTXT* pctxt, H225CallCapacity* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.maximumCallCapacityPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.currentCallCapacityPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode maximumCallCapacity */

   if (pvalue->m.maximumCallCapacityPresent) {
      stat = asn1PE_H225CallCapacityInfo (pctxt, &pvalue->maximumCallCapacity);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode currentCallCapacity */

   if (pvalue->m.currentCallCapacityPresent) {
      stat = asn1PE_H225CallCapacityInfo (pctxt, &pvalue->currentCallCapacity);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225CicInfo_cic_element                             */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225CicInfo_cic_element (OOCTXT* pctxt, H225_SeqOfH225CicInfo_cic_element* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = asn1PE_H225CicInfo_cic_element (pctxt, &pvalue->elem[xx1]);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CicInfo                                                   */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CicInfo (OOCTXT* pctxt, H225CicInfo* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode cic */

   stat = asn1PE_H225_SeqOfH225CicInfo_cic_element (pctxt, &pvalue->cic);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode pointCode */

   stat = asn1PE_H225CicInfo_pointCode (pctxt, &pvalue->pointCode);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GroupID_member                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GroupID_member (OOCTXT* pctxt, H225GroupID_member* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = encodeConsUnsigned (pctxt, pvalue->elem[xx1], 0U, 65535U);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GroupID                                                   */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GroupID (OOCTXT* pctxt, H225GroupID* pvalue)
{
   static Asn1SizeCnst group_lsize1 = { 0, 1, 128, 0 };
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.memberPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode member */

   if (pvalue->m.memberPresent) {
      stat = asn1PE_H225GroupID_member (pctxt, &pvalue->member);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode group */

   stat = addSizeConstraint (pctxt, &group_lsize1);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeConstrainedStringEx (pctxt, pvalue->group, 0, 8, 7, 7);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CircuitIdentifier                                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CircuitIdentifier (OOCTXT* pctxt, H225CircuitIdentifier* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.carrierPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cicPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.groupPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode cic */

   if (pvalue->m.cicPresent) {
      stat = asn1PE_H225CicInfo (pctxt, &pvalue->cic);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode group */

   if (pvalue->m.groupPresent) {
      stat = asn1PE_H225GroupID (pctxt, &pvalue->group);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.carrierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.carrierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CarrierInfo (&lctxt, &pvalue->carrier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225GenericData                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225GenericData (OOCTXT* pctxt, H225_SeqOfH225GenericData value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225GenericData (pctxt, ((H225GenericData*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CircuitInfo                                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CircuitInfo (OOCTXT* pctxt, H225CircuitInfo* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.sourceCircuitIDPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destinationCircuitIDPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode sourceCircuitID */

   if (pvalue->m.sourceCircuitIDPresent) {
      stat = asn1PE_H225CircuitIdentifier (pctxt, &pvalue->sourceCircuitID);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode destinationCircuitID */

   if (pvalue->m.destinationCircuitIDPresent) {
      stat = asn1PE_H225CircuitIdentifier (pctxt, &pvalue->destinationCircuitID);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode genericData */

   if (pvalue->m.genericDataPresent) {
      stat = asn1PE_H225_SeqOfH225GenericData (pctxt, pvalue->genericData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225FeatureDescriptor                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225FeatureDescriptor (OOCTXT* pctxt, H225_SeqOfH225FeatureDescriptor value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225FeatureDescriptor (pctxt, ((H225FeatureDescriptor*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Setup_UUIE_parallelH245Control                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Setup_UUIE_parallelH245Control (OOCTXT* pctxt, H225Setup_UUIE_parallelH245Control* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = encodeOctetString (pctxt, pvalue->elem[xx1].numocts, pvalue->elem[xx1].data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ExtendedAliasAddress                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ExtendedAliasAddress (OOCTXT* pctxt, H225ExtendedAliasAddress* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.presentationIndicatorPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.screeningIndicatorPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode address */

   stat = asn1PE_H225AliasAddress (pctxt, &pvalue->address);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode presentationIndicator */

   if (pvalue->m.presentationIndicatorPresent) {
      stat = asn1PE_H225PresentationIndicator (pctxt, &pvalue->presentationIndicator);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode screeningIndicator */

   if (pvalue->m.screeningIndicatorPresent) {
      stat = asn1PE_H225ScreeningIndicator (pctxt, pvalue->screeningIndicator);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225ExtendedAliasAddress                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225ExtendedAliasAddress (OOCTXT* pctxt, H225_SeqOfH225ExtendedAliasAddress value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225ExtendedAliasAddress (pctxt, ((H225ExtendedAliasAddress*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Setup_UUIE                                                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Setup_UUIE (OOCTXT* pctxt, H225Setup_UUIE* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.sourceCallSignalAddressPresent ||
   pvalue->m.remoteExtensionAddressPresent ||
   pvalue->m.callIdentifierPresent ||
   pvalue->m.h245SecurityCapabilityPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.fastStartPresent ||
   pvalue->m.mediaWaitForConnectPresent ||
   pvalue->m.canOverlapSendPresent ||
   pvalue->m.endpointIdentifierPresent ||
   pvalue->m.multipleCallsPresent ||
   pvalue->m.maintainConnectionPresent ||
   pvalue->m.connectionParametersPresent ||
   pvalue->m.languagePresent ||
   pvalue->m.presentationIndicatorPresent ||
   pvalue->m.screeningIndicatorPresent ||
   pvalue->m.serviceControlPresent ||
   pvalue->m.symmetricOperationRequiredPresent ||
   pvalue->m.capacityPresent ||
   pvalue->m.circuitInfoPresent ||
   pvalue->m.desiredProtocolsPresent ||
   pvalue->m.neededFeaturesPresent ||
   pvalue->m.desiredFeaturesPresent ||
   pvalue->m.supportedFeaturesPresent ||
   pvalue->m.parallelH245ControlPresent ||
   pvalue->m.additionalSourceAddressesPresent ||
   pvalue->m.hopCountPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h245AddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.sourceAddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destinationAddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destCallSignalAddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destExtraCallInfoPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destExtraCRVPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callServicesPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode h245Address */

   if (pvalue->m.h245AddressPresent) {
      stat = asn1PE_H225TransportAddress (pctxt, &pvalue->h245Address);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode sourceAddress */

   if (pvalue->m.sourceAddressPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->sourceAddress);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode sourceInfo */

   stat = asn1PE_H225EndpointType (pctxt, &pvalue->sourceInfo);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode destinationAddress */

   if (pvalue->m.destinationAddressPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->destinationAddress);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode destCallSignalAddress */

   if (pvalue->m.destCallSignalAddressPresent) {
      stat = asn1PE_H225TransportAddress (pctxt, &pvalue->destCallSignalAddress);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode destExtraCallInfo */

   if (pvalue->m.destExtraCallInfoPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->destExtraCallInfo);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode destExtraCRV */

   if (pvalue->m.destExtraCRVPresent) {
      stat = asn1PE_H225_SeqOfH225CallReferenceValue (pctxt, &pvalue->destExtraCRV);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode activeMC */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->activeMC);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode conferenceID */

   stat = asn1PE_H225ConferenceIdentifier (pctxt, &pvalue->conferenceID);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode conferenceGoal */

   stat = asn1PE_H225Setup_UUIE_conferenceGoal (pctxt, &pvalue->conferenceGoal);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callServices */

   if (pvalue->m.callServicesPresent) {
      stat = asn1PE_H225QseriesOptions (pctxt, &pvalue->callServices);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode callType */

   stat = asn1PE_H225CallType (pctxt, &pvalue->callType);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 26);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.sourceCallSignalAddressPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.remoteExtensionAddressPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h245SecurityCapabilityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.fastStartPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.mediaWaitForConnectPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.canOverlapSendPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.endpointIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.multipleCallsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.maintainConnectionPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.connectionParametersPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.languagePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.presentationIndicatorPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.screeningIndicatorPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.serviceControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.symmetricOperationRequiredPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.circuitInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.desiredProtocolsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.neededFeaturesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.desiredFeaturesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedFeaturesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.parallelH245ControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.additionalSourceAddressesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.hopCountPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.sourceCallSignalAddressPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225TransportAddress (&lctxt, &pvalue->sourceCallSignalAddress);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.remoteExtensionAddressPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AliasAddress (&lctxt, &pvalue->remoteExtensionAddress);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.callIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallIdentifier (&lctxt, &pvalue->callIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.h245SecurityCapabilityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225H245Security (&lctxt, pvalue->h245SecurityCapability);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.fastStartPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225Setup_UUIE_fastStart (&lctxt, &pvalue->fastStart);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.mediaWaitForConnectPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->mediaWaitForConnect);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.canOverlapSendPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->canOverlapSend);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.endpointIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225EndpointIdentifier (&lctxt, pvalue->endpointIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.multipleCallsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->multipleCalls);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.maintainConnectionPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->maintainConnection);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.connectionParametersPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225Setup_UUIE_connectionParameters (&lctxt, &pvalue->connectionParameters);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.languagePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225Setup_UUIE_language (&lctxt, &pvalue->language);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.presentationIndicatorPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225PresentationIndicator (&lctxt, &pvalue->presentationIndicator);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.screeningIndicatorPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ScreeningIndicator (&lctxt, pvalue->screeningIndicator);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.serviceControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ServiceControlSession (&lctxt, pvalue->serviceControl);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.symmetricOperationRequiredPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.capacityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallCapacity (&lctxt, &pvalue->capacity);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.circuitInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CircuitInfo (&lctxt, &pvalue->circuitInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.desiredProtocolsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedProtocols (&lctxt, pvalue->desiredProtocols);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.neededFeaturesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225FeatureDescriptor (&lctxt, pvalue->neededFeatures);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.desiredFeaturesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225FeatureDescriptor (&lctxt, pvalue->desiredFeatures);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedFeaturesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225FeatureDescriptor (&lctxt, pvalue->supportedFeatures);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.parallelH245ControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225Setup_UUIE_parallelH245Control (&lctxt, &pvalue->parallelH245Control);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.additionalSourceAddressesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ExtendedAliasAddress (&lctxt, pvalue->additionalSourceAddresses);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.hopCountPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         if ( (pvalue->hopCount >= 1 && pvalue->hopCount <= 31) ) {
            stat = encodeConsUnsigned (&lctxt, pvalue->hopCount, 1U, 31U);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
         }
         else
            return LOG_ASN1ERR (pctxt, ASN_E_CONSVIO);

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallProceeding_UUIE_fastStart                             */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallProceeding_UUIE_fastStart (OOCTXT* pctxt, H225CallProceeding_UUIE_fastStart* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = encodeOctetString (pctxt, pvalue->elem[xx1].numocts, pvalue->elem[xx1].data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  FeatureSet                                                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225FeatureSet (OOCTXT* pctxt, H225FeatureSet* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.neededFeaturesPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.desiredFeaturesPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedFeaturesPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode replacementFeatureSet */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->replacementFeatureSet);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode neededFeatures */

   if (pvalue->m.neededFeaturesPresent) {
      stat = asn1PE_H225_SeqOfH225FeatureDescriptor (pctxt, pvalue->neededFeatures);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode desiredFeatures */

   if (pvalue->m.desiredFeaturesPresent) {
      stat = asn1PE_H225_SeqOfH225FeatureDescriptor (pctxt, pvalue->desiredFeatures);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode supportedFeatures */

   if (pvalue->m.supportedFeaturesPresent) {
      stat = asn1PE_H225_SeqOfH225FeatureDescriptor (pctxt, pvalue->supportedFeatures);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallProceeding_UUIE                                       */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallProceeding_UUIE (OOCTXT* pctxt, H225CallProceeding_UUIE* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.callIdentifierPresent ||
   pvalue->m.h245SecurityModePresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.fastStartPresent ||
   pvalue->m.multipleCallsPresent ||
   pvalue->m.maintainConnectionPresent ||
   pvalue->m.fastConnectRefusedPresent ||
   pvalue->m.featureSetPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h245AddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode destinationInfo */

   stat = asn1PE_H225EndpointType (pctxt, &pvalue->destinationInfo);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode h245Address */

   if (pvalue->m.h245AddressPresent) {
      stat = asn1PE_H225TransportAddress (pctxt, &pvalue->h245Address);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 8);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h245SecurityModePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.fastStartPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.multipleCallsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.maintainConnectionPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.fastConnectRefusedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.callIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallIdentifier (&lctxt, &pvalue->callIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.h245SecurityModePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225H245Security (&lctxt, &pvalue->h245SecurityMode);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.fastStartPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallProceeding_UUIE_fastStart (&lctxt, &pvalue->fastStart);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.multipleCallsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->multipleCalls);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.maintainConnectionPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->maintainConnection);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.fastConnectRefusedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Connect_UUIE_fastStart                                    */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Connect_UUIE_fastStart (OOCTXT* pctxt, H225Connect_UUIE_fastStart* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = encodeOctetString (pctxt, pvalue->elem[xx1].numocts, pvalue->elem[xx1].data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Connect_UUIE_language                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Connect_UUIE_language (OOCTXT* pctxt, H225Connect_UUIE_language* pvalue)
{
   static Asn1SizeCnst element_lsize1 = { 0, 1, 32, 0 };
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = addSizeConstraint (pctxt, &element_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeConstrainedStringEx (pctxt, pvalue->elem[xx1], 0, 8, 7, 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Connect_UUIE                                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Connect_UUIE (OOCTXT* pctxt, H225Connect_UUIE* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.callIdentifierPresent ||
   pvalue->m.h245SecurityModePresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.fastStartPresent ||
   pvalue->m.multipleCallsPresent ||
   pvalue->m.maintainConnectionPresent ||
   pvalue->m.languagePresent ||
   pvalue->m.connectedAddressPresent ||
   pvalue->m.presentationIndicatorPresent ||
   pvalue->m.screeningIndicatorPresent ||
   pvalue->m.fastConnectRefusedPresent ||
   pvalue->m.serviceControlPresent ||
   pvalue->m.capacityPresent ||
   pvalue->m.featureSetPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h245AddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode h245Address */

   if (pvalue->m.h245AddressPresent) {
      stat = asn1PE_H225TransportAddress (pctxt, &pvalue->h245Address);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode destinationInfo */

   stat = asn1PE_H225EndpointType (pctxt, &pvalue->destinationInfo);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode conferenceID */

   stat = asn1PE_H225ConferenceIdentifier (pctxt, &pvalue->conferenceID);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 14);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h245SecurityModePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.fastStartPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.multipleCallsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.maintainConnectionPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.languagePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.connectedAddressPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.presentationIndicatorPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.screeningIndicatorPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.fastConnectRefusedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.serviceControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.callIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallIdentifier (&lctxt, &pvalue->callIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.h245SecurityModePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225H245Security (&lctxt, &pvalue->h245SecurityMode);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.fastStartPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225Connect_UUIE_fastStart (&lctxt, &pvalue->fastStart);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.multipleCallsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->multipleCalls);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.maintainConnectionPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->maintainConnection);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.languagePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225Connect_UUIE_language (&lctxt, &pvalue->language);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.connectedAddressPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AliasAddress (&lctxt, pvalue->connectedAddress);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.presentationIndicatorPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225PresentationIndicator (&lctxt, &pvalue->presentationIndicator);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.screeningIndicatorPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ScreeningIndicator (&lctxt, pvalue->screeningIndicator);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.fastConnectRefusedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.serviceControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ServiceControlSession (&lctxt, pvalue->serviceControl);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.capacityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallCapacity (&lctxt, &pvalue->capacity);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Alerting_UUIE_fastStart                                   */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Alerting_UUIE_fastStart (OOCTXT* pctxt, H225Alerting_UUIE_fastStart* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = encodeOctetString (pctxt, pvalue->elem[xx1].numocts, pvalue->elem[xx1].data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Alerting_UUIE                                             */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Alerting_UUIE (OOCTXT* pctxt, H225Alerting_UUIE* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.callIdentifierPresent ||
   pvalue->m.h245SecurityModePresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.fastStartPresent ||
   pvalue->m.multipleCallsPresent ||
   pvalue->m.maintainConnectionPresent ||
   pvalue->m.alertingAddressPresent ||
   pvalue->m.presentationIndicatorPresent ||
   pvalue->m.screeningIndicatorPresent ||
   pvalue->m.fastConnectRefusedPresent ||
   pvalue->m.serviceControlPresent ||
   pvalue->m.capacityPresent ||
   pvalue->m.featureSetPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h245AddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode destinationInfo */

   stat = asn1PE_H225EndpointType (pctxt, &pvalue->destinationInfo);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode h245Address */

   if (pvalue->m.h245AddressPresent) {
      stat = asn1PE_H225TransportAddress (pctxt, &pvalue->h245Address);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 13);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h245SecurityModePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.fastStartPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.multipleCallsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.maintainConnectionPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alertingAddressPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.presentationIndicatorPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.screeningIndicatorPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.fastConnectRefusedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.serviceControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.callIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallIdentifier (&lctxt, &pvalue->callIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.h245SecurityModePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225H245Security (&lctxt, &pvalue->h245SecurityMode);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.fastStartPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225Alerting_UUIE_fastStart (&lctxt, &pvalue->fastStart);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.multipleCallsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->multipleCalls);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.maintainConnectionPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->maintainConnection);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.alertingAddressPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AliasAddress (&lctxt, pvalue->alertingAddress);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.presentationIndicatorPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225PresentationIndicator (&lctxt, &pvalue->presentationIndicator);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.screeningIndicatorPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ScreeningIndicator (&lctxt, pvalue->screeningIndicator);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.fastConnectRefusedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.serviceControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ServiceControlSession (&lctxt, pvalue->serviceControl);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.capacityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallCapacity (&lctxt, &pvalue->capacity);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Information_UUIE_fastStart                                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Information_UUIE_fastStart (OOCTXT* pctxt, H225Information_UUIE_fastStart* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = encodeOctetString (pctxt, pvalue->elem[xx1].numocts, pvalue->elem[xx1].data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Information_UUIE                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Information_UUIE (OOCTXT* pctxt, H225Information_UUIE* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.callIdentifierPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.fastStartPresent ||
   pvalue->m.fastConnectRefusedPresent ||
   pvalue->m.circuitInfoPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.fastStartPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.fastConnectRefusedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.circuitInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.callIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallIdentifier (&lctxt, &pvalue->callIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.fastStartPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225Information_UUIE_fastStart (&lctxt, &pvalue->fastStart);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.fastConnectRefusedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.circuitInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CircuitInfo (&lctxt, &pvalue->circuitInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  SecurityErrors                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225SecurityErrors (OOCTXT* pctxt, H225SecurityErrors* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 16);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 15);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* securityWrongSyncTime */
         case 1:
            /* NULL */
            break;

         /* securityReplay */
         case 2:
            /* NULL */
            break;

         /* securityWrongGeneralID */
         case 3:
            /* NULL */
            break;

         /* securityWrongSendersID */
         case 4:
            /* NULL */
            break;

         /* securityIntegrityFailed */
         case 5:
            /* NULL */
            break;

         /* securityWrongOID */
         case 6:
            /* NULL */
            break;

         /* securityDHmismatch */
         case 7:
            /* NULL */
            break;

         /* securityCertificateExpired */
         case 8:
            /* NULL */
            break;

         /* securityCertificateDateInvalid */
         case 9:
            /* NULL */
            break;

         /* securityCertificateRevoked */
         case 10:
            /* NULL */
            break;

         /* securityCertificateNotReadable */
         case 11:
            /* NULL */
            break;

         /* securityCertificateSignatureInvalid */
         case 12:
            /* NULL */
            break;

         /* securityCertificateMissing */
         case 13:
            /* NULL */
            break;

         /* securityCertificateIncomplete */
         case 14:
            /* NULL */
            break;

         /* securityUnsupportedCertificateAlgOID */
         case 15:
            /* NULL */
            break;

         /* securityUnknownCA */
         case 16:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 17);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ReleaseCompleteReason                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ReleaseCompleteReason (OOCTXT* pctxt, H225ReleaseCompleteReason* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 12);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 11);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* noBandwidth */
         case 1:
            /* NULL */
            break;

         /* gatekeeperResources */
         case 2:
            /* NULL */
            break;

         /* unreachableDestination */
         case 3:
            /* NULL */
            break;

         /* destinationRejection */
         case 4:
            /* NULL */
            break;

         /* invalidRevision */
         case 5:
            /* NULL */
            break;

         /* noPermission */
         case 6:
            /* NULL */
            break;

         /* unreachableGatekeeper */
         case 7:
            /* NULL */
            break;

         /* gatewayResources */
         case 8:
            /* NULL */
            break;

         /* badFormatAddress */
         case 9:
            /* NULL */
            break;

         /* adaptiveBusy */
         case 10:
            /* NULL */
            break;

         /* inConf */
         case 11:
            /* NULL */
            break;

         /* undefinedReason */
         case 12:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 13);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* facilityCallDeflection */
         case 13:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* securityDenied */
         case 14:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* calledPartyNotRegistered */
         case 15:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* callerNotRegistered */
         case 16:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* newConnectionNeeded */
         case 17:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* nonStandardReason */
         case 18:
            stat = asn1PE_H225NonStandardParameter (&lctxt, pvalue->u.nonStandardReason);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* replaceWithConferenceInvite */
         case 19:
            stat = asn1PE_H225ConferenceIdentifier (&lctxt, pvalue->u.replaceWithConferenceInvite);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* genericDataReason */
         case 20:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* neededFeatureNotSupported */
         case 21:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* tunnelledSignallingRejected */
         case 22:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* invalidCID */
         case 23:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* securityError */
         case 24:
            stat = asn1PE_H225SecurityErrors (&lctxt, pvalue->u.securityError);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* hopCountExceeded */
         case 25:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ReleaseComplete_UUIE                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ReleaseComplete_UUIE (OOCTXT* pctxt, H225ReleaseComplete_UUIE* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.callIdentifierPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.busyAddressPresent ||
   pvalue->m.presentationIndicatorPresent ||
   pvalue->m.screeningIndicatorPresent ||
   pvalue->m.capacityPresent ||
   pvalue->m.serviceControlPresent ||
   pvalue->m.featureSetPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.reasonPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode reason */

   if (pvalue->m.reasonPresent) {
      stat = asn1PE_H225ReleaseCompleteReason (pctxt, &pvalue->reason);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 8);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.busyAddressPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.presentationIndicatorPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.screeningIndicatorPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.serviceControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.callIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallIdentifier (&lctxt, &pvalue->callIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.busyAddressPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AliasAddress (&lctxt, pvalue->busyAddress);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.presentationIndicatorPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225PresentationIndicator (&lctxt, &pvalue->presentationIndicator);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.screeningIndicatorPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ScreeningIndicator (&lctxt, pvalue->screeningIndicator);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.capacityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallCapacity (&lctxt, &pvalue->capacity);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.serviceControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ServiceControlSession (&lctxt, pvalue->serviceControl);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  FacilityReason                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225FacilityReason (OOCTXT* pctxt, H225FacilityReason* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 4);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* routeCallToGatekeeper */
         case 1:
            /* NULL */
            break;

         /* callForwarded */
         case 2:
            /* NULL */
            break;

         /* routeCallToMC */
         case 3:
            /* NULL */
            break;

         /* undefinedReason */
         case 4:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* conferenceListChoice */
         case 5:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* startH245 */
         case 6:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* noH245 */
         case 7:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* newTokens */
         case 8:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* featureSetUpdate */
         case 9:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* forwardedElements */
         case 10:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* transportedInformation */
         case 11:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ConferenceList                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ConferenceList (OOCTXT* pctxt, H225ConferenceList* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.conferenceIDPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.conferenceAliasPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode conferenceID */

   if (pvalue->m.conferenceIDPresent) {
      stat = asn1PE_H225ConferenceIdentifier (pctxt, &pvalue->conferenceID);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode conferenceAlias */

   if (pvalue->m.conferenceAliasPresent) {
      stat = asn1PE_H225AliasAddress (pctxt, &pvalue->conferenceAlias);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225ConferenceList                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225ConferenceList (OOCTXT* pctxt, H225_SeqOfH225ConferenceList value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225ConferenceList (pctxt, ((H225ConferenceList*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Facility_UUIE_fastStart                                   */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Facility_UUIE_fastStart (OOCTXT* pctxt, H225Facility_UUIE_fastStart* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = encodeOctetString (pctxt, pvalue->elem[xx1].numocts, pvalue->elem[xx1].data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Facility_UUIE                                             */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Facility_UUIE (OOCTXT* pctxt, H225Facility_UUIE* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.callIdentifierPresent ||
   pvalue->m.destExtraCallInfoPresent ||
   pvalue->m.remoteExtensionAddressPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.conferencesPresent ||
   pvalue->m.h245AddressPresent ||
   pvalue->m.fastStartPresent ||
   pvalue->m.multipleCallsPresent ||
   pvalue->m.maintainConnectionPresent ||
   pvalue->m.fastConnectRefusedPresent ||
   pvalue->m.serviceControlPresent ||
   pvalue->m.circuitInfoPresent ||
   pvalue->m.featureSetPresent ||
   pvalue->m.destinationInfoPresent ||
   pvalue->m.h245SecurityModePresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternativeAddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternativeAliasAddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.conferenceIDPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode alternativeAddress */

   if (pvalue->m.alternativeAddressPresent) {
      stat = asn1PE_H225TransportAddress (pctxt, &pvalue->alternativeAddress);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode alternativeAliasAddress */

   if (pvalue->m.alternativeAliasAddressPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->alternativeAliasAddress);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode conferenceID */

   if (pvalue->m.conferenceIDPresent) {
      stat = asn1PE_H225ConferenceIdentifier (pctxt, &pvalue->conferenceID);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode reason */

   stat = asn1PE_H225FacilityReason (pctxt, &pvalue->reason);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 15);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destExtraCallInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.remoteExtensionAddressPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.conferencesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h245AddressPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.fastStartPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.multipleCallsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.maintainConnectionPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.fastConnectRefusedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.serviceControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.circuitInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destinationInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h245SecurityModePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.callIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallIdentifier (&lctxt, &pvalue->callIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.destExtraCallInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AliasAddress (&lctxt, pvalue->destExtraCallInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.remoteExtensionAddressPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AliasAddress (&lctxt, &pvalue->remoteExtensionAddress);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.conferencesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ConferenceList (&lctxt, pvalue->conferences);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.h245AddressPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225TransportAddress (&lctxt, &pvalue->h245Address);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.fastStartPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225Facility_UUIE_fastStart (&lctxt, &pvalue->fastStart);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.multipleCallsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->multipleCalls);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.maintainConnectionPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->maintainConnection);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.fastConnectRefusedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.serviceControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ServiceControlSession (&lctxt, pvalue->serviceControl);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.circuitInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CircuitInfo (&lctxt, &pvalue->circuitInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.destinationInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225EndpointType (&lctxt, &pvalue->destinationInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.h245SecurityModePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225H245Security (&lctxt, &pvalue->h245SecurityMode);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Progress_UUIE_fastStart                                   */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Progress_UUIE_fastStart (OOCTXT* pctxt, H225Progress_UUIE_fastStart* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = encodeOctetString (pctxt, pvalue->elem[xx1].numocts, pvalue->elem[xx1].data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Progress_UUIE                                             */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Progress_UUIE (OOCTXT* pctxt, H225Progress_UUIE* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.multipleCallsPresent ||
   pvalue->m.maintainConnectionPresent ||
   pvalue->m.fastConnectRefusedPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h245AddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h245SecurityModePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.fastStartPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode destinationInfo */

   stat = asn1PE_H225EndpointType (pctxt, &pvalue->destinationInfo);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode h245Address */

   if (pvalue->m.h245AddressPresent) {
      stat = asn1PE_H225TransportAddress (pctxt, &pvalue->h245Address);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode callIdentifier */

   stat = asn1PE_H225CallIdentifier (pctxt, &pvalue->callIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode h245SecurityMode */

   if (pvalue->m.h245SecurityModePresent) {
      stat = asn1PE_H225H245Security (pctxt, &pvalue->h245SecurityMode);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode tokens */

   if (pvalue->m.tokensPresent) {
      stat = asn1PE_H225_SeqOfH225ClearToken (pctxt, pvalue->tokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode cryptoTokens */

   if (pvalue->m.cryptoTokensPresent) {
      stat = asn1PE_H225_SeqOfH225CryptoH323Token (pctxt, pvalue->cryptoTokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode fastStart */

   if (pvalue->m.fastStartPresent) {
      stat = asn1PE_H225Progress_UUIE_fastStart (pctxt, &pvalue->fastStart);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 2);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.multipleCallsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.maintainConnectionPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.fastConnectRefusedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.multipleCallsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->multipleCalls);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.maintainConnectionPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->maintainConnection);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.fastConnectRefusedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Status_UUIE                                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Status_UUIE (OOCTXT* pctxt, H225Status_UUIE* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callIdentifier */

   stat = asn1PE_H225CallIdentifier (pctxt, &pvalue->callIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode tokens */

   if (pvalue->m.tokensPresent) {
      stat = asn1PE_H225_SeqOfH225ClearToken (pctxt, pvalue->tokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode cryptoTokens */

   if (pvalue->m.cryptoTokensPresent) {
      stat = asn1PE_H225_SeqOfH225CryptoH323Token (pctxt, pvalue->cryptoTokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  StatusInquiry_UUIE                                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225StatusInquiry_UUIE (OOCTXT* pctxt, H225StatusInquiry_UUIE* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callIdentifier */

   stat = asn1PE_H225CallIdentifier (pctxt, &pvalue->callIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode tokens */

   if (pvalue->m.tokensPresent) {
      stat = asn1PE_H225_SeqOfH225ClearToken (pctxt, pvalue->tokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode cryptoTokens */

   if (pvalue->m.cryptoTokensPresent) {
      stat = asn1PE_H225_SeqOfH225CryptoH323Token (pctxt, pvalue->cryptoTokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  SetupAcknowledge_UUIE                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225SetupAcknowledge_UUIE (OOCTXT* pctxt, H225SetupAcknowledge_UUIE* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callIdentifier */

   stat = asn1PE_H225CallIdentifier (pctxt, &pvalue->callIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode tokens */

   if (pvalue->m.tokensPresent) {
      stat = asn1PE_H225_SeqOfH225ClearToken (pctxt, pvalue->tokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode cryptoTokens */

   if (pvalue->m.cryptoTokensPresent) {
      stat = asn1PE_H225_SeqOfH225CryptoH323Token (pctxt, pvalue->cryptoTokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Notify_UUIE                                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Notify_UUIE (OOCTXT* pctxt, H225Notify_UUIE* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callIdentifier */

   stat = asn1PE_H225CallIdentifier (pctxt, &pvalue->callIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode tokens */

   if (pvalue->m.tokensPresent) {
      stat = asn1PE_H225_SeqOfH225ClearToken (pctxt, pvalue->tokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode cryptoTokens */

   if (pvalue->m.cryptoTokensPresent) {
      stat = asn1PE_H225_SeqOfH225CryptoH323Token (pctxt, pvalue->cryptoTokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H323_UU_PDU_h323_message_body                             */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H323_UU_PDU_h323_message_body (OOCTXT* pctxt, H225H323_UU_PDU_h323_message_body* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 7);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 6);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* setup */
         case 1:
            stat = asn1PE_H225Setup_UUIE (pctxt, pvalue->u.setup);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* callProceeding */
         case 2:
            stat = asn1PE_H225CallProceeding_UUIE (pctxt, pvalue->u.callProceeding);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* connect */
         case 3:
            stat = asn1PE_H225Connect_UUIE (pctxt, pvalue->u.connect);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* alerting */
         case 4:
            stat = asn1PE_H225Alerting_UUIE (pctxt, pvalue->u.alerting);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* information */
         case 5:
            stat = asn1PE_H225Information_UUIE (pctxt, pvalue->u.information);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* releaseComplete */
         case 6:
            stat = asn1PE_H225ReleaseComplete_UUIE (pctxt, pvalue->u.releaseComplete);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* facility */
         case 7:
            stat = asn1PE_H225Facility_UUIE (pctxt, pvalue->u.facility);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 8);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* progress */
         case 8:
            stat = asn1PE_H225Progress_UUIE (&lctxt, pvalue->u.progress);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* empty */
         case 9:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* status */
         case 10:
            stat = asn1PE_H225Status_UUIE (&lctxt, pvalue->u.status);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* statusInquiry */
         case 11:
            stat = asn1PE_H225StatusInquiry_UUIE (&lctxt, pvalue->u.statusInquiry);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* setupAcknowledge */
         case 12:
            stat = asn1PE_H225SetupAcknowledge_UUIE (&lctxt, pvalue->u.setupAcknowledge);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* notify */
         case 13:
            stat = asn1PE_H225Notify_UUIE (&lctxt, pvalue->u.notify);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H323_UU_PDU_h4501SupplementaryService                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H323_UU_PDU_h4501SupplementaryService (OOCTXT* pctxt, H225H323_UU_PDU_h4501SupplementaryService* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = encodeOctetString (pctxt, pvalue->elem[xx1].numocts, pvalue->elem[xx1].data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H323_UU_PDU_h245Control                                   */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H323_UU_PDU_h245Control (OOCTXT* pctxt, H225H323_UU_PDU_h245Control* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = encodeOctetString (pctxt, pvalue->elem[xx1].numocts, pvalue->elem[xx1].data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225NonStandardParameter                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225NonStandardParameter (OOCTXT* pctxt, H225_SeqOfH225NonStandardParameter value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225NonStandardParameter (pctxt, ((H225NonStandardParameter*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallLinkage                                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallLinkage (OOCTXT* pctxt, H225CallLinkage* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.globalCallIdPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.threadIdPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode globalCallId */

   if (pvalue->m.globalCallIdPresent) {
      stat = asn1PE_H225GloballyUniqueID (pctxt, &pvalue->globalCallId);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode threadId */

   if (pvalue->m.threadIdPresent) {
      stat = asn1PE_H225GloballyUniqueID (pctxt, &pvalue->threadId);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H323_UU_PDU_tunnelledSignallingMessage_messageContent     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H323_UU_PDU_tunnelledSignallingMessage_messageContent (OOCTXT* pctxt, H225H323_UU_PDU_tunnelledSignallingMessage_messageContent* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = encodeOctetString (pctxt, pvalue->elem[xx1].numocts, pvalue->elem[xx1].data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H323_UU_PDU_tunnelledSignallingMessage                    */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H323_UU_PDU_tunnelledSignallingMessage (OOCTXT* pctxt, H225H323_UU_PDU_tunnelledSignallingMessage* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tunnellingRequiredPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode tunnelledProtocolID */

   stat = asn1PE_H225TunnelledProtocol (pctxt, &pvalue->tunnelledProtocolID);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode messageContent */

   stat = asn1PE_H225H323_UU_PDU_tunnelledSignallingMessage_messageContent (pctxt, &pvalue->messageContent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode tunnellingRequired */

   if (pvalue->m.tunnellingRequiredPresent) {
      /* NULL */
   }

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  StimulusControl                                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225StimulusControl (OOCTXT* pctxt, H225StimulusControl* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.isTextPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h248MessagePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandard */

   if (pvalue->m.nonStandardPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandard);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode isText */

   if (pvalue->m.isTextPresent) {
      /* NULL */
   }

   /* encode h248Message */

   if (pvalue->m.h248MessagePresent) {
      stat = encodeOctetString (pctxt, pvalue->h248Message.numocts, pvalue->h248Message.data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H323_UU_PDU                                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H323_UU_PDU (OOCTXT* pctxt, H225H323_UU_PDU* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.h4501SupplementaryServicePresent ||
   pvalue->m.h245TunnelingPresent ||
   pvalue->m.h245ControlPresent ||
   pvalue->m.nonStandardControlPresent ||
   pvalue->m.callLinkagePresent ||
   pvalue->m.tunnelledSignallingMessagePresent ||
   pvalue->m.provisionalRespToH245TunnelingPresent ||
   pvalue->m.stimulusControlPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode h323_message_body */

   stat = asn1PE_H225H323_UU_PDU_h323_message_body (pctxt, &pvalue->h323_message_body);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 8);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h4501SupplementaryServicePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h245TunnelingPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.h245ControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callLinkagePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tunnelledSignallingMessagePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.provisionalRespToH245TunnelingPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.stimulusControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.h4501SupplementaryServicePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225H323_UU_PDU_h4501SupplementaryService (&lctxt, &pvalue->h4501SupplementaryService);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.h245TunnelingPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->h245Tunneling);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.h245ControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225H323_UU_PDU_h245Control (&lctxt, &pvalue->h245Control);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.nonStandardControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225NonStandardParameter (&lctxt, pvalue->nonStandardControl);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.callLinkagePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallLinkage (&lctxt, &pvalue->callLinkage);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tunnelledSignallingMessagePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225H323_UU_PDU_tunnelledSignallingMessage (&lctxt, &pvalue->tunnelledSignallingMessage);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.provisionalRespToH245TunnelingPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.stimulusControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225StimulusControl (&lctxt, &pvalue->stimulusControl);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H323_UserInformation_user_data                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H323_UserInformation_user_data (OOCTXT* pctxt, H225H323_UserInformation_user_data* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocol_discriminator */

   stat = encodeConsUnsigned (pctxt, pvalue->protocol_discriminator, 0U, 255U);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode user_information */

   stat = asn1PE_H225H323_UserInformation_user_data_user_information (pctxt, &pvalue->user_information);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  H323_UserInformation                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225H323_UserInformation (OOCTXT* pctxt, H225H323_UserInformation* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.user_dataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode h323_uu_pdu */

   stat = asn1PE_H225H323_UU_PDU (pctxt, &pvalue->h323_uu_pdu);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode user_data */

   if (pvalue->m.user_dataPresent) {
      stat = asn1PE_H225H323_UserInformation_user_data (pctxt, &pvalue->user_data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  AddressPattern_range                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225AddressPattern_range (OOCTXT* pctxt, H225AddressPattern_range* pvalue)
{
   int stat = ASN_OK;

   /* encode startOfRange */

   stat = asn1PE_H225PartyNumber (pctxt, &pvalue->startOfRange);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode endOfRange */

   stat = asn1PE_H225PartyNumber (pctxt, &pvalue->endOfRange);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  AddressPattern                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225AddressPattern (OOCTXT* pctxt, H225AddressPattern* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 2);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* wildcard */
         case 1:
            stat = asn1PE_H225AliasAddress (pctxt, pvalue->u.wildcard);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* range */
         case 2:
            stat = asn1PE_H225AddressPattern_range (pctxt, pvalue->u.range);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225TransportAddress                                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225TransportAddress (OOCTXT* pctxt, H225_SeqOfH225TransportAddress value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225TransportAddress (pctxt, ((H225TransportAddress*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  AlternateTransportAddresses                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225AlternateTransportAddresses (OOCTXT* pctxt, H225AlternateTransportAddresses* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.sctpPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.annexEPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode annexE */

   if (pvalue->m.annexEPresent) {
      stat = asn1PE_H225_SeqOfH225TransportAddress (pctxt, pvalue->annexE);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.sctpPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.sctpPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225TransportAddress (&lctxt, pvalue->sctp);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  Endpoint                                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225Endpoint (OOCTXT* pctxt, H225Endpoint* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.alternateTransportAddressesPresent ||
   pvalue->m.circuitInfoPresent ||
   pvalue->m.featureSetPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.aliasAddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callSignalAddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.rasAddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.endpointTypePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.priorityPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.remoteExtensionAddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destExtraCallInfoPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode aliasAddress */

   if (pvalue->m.aliasAddressPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->aliasAddress);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode callSignalAddress */

   if (pvalue->m.callSignalAddressPresent) {
      stat = asn1PE_H225_SeqOfH225TransportAddress (pctxt, pvalue->callSignalAddress);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode rasAddress */

   if (pvalue->m.rasAddressPresent) {
      stat = asn1PE_H225_SeqOfH225TransportAddress (pctxt, pvalue->rasAddress);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode endpointType */

   if (pvalue->m.endpointTypePresent) {
      stat = asn1PE_H225EndpointType (pctxt, &pvalue->endpointType);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode tokens */

   if (pvalue->m.tokensPresent) {
      stat = asn1PE_H225_SeqOfH225ClearToken (pctxt, pvalue->tokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode cryptoTokens */

   if (pvalue->m.cryptoTokensPresent) {
      stat = asn1PE_H225_SeqOfH225CryptoH323Token (pctxt, pvalue->cryptoTokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode priority */

   if (pvalue->m.priorityPresent) {
      if ( (pvalue->priority <= 127) ) {
         stat = encodeConsUnsigned (pctxt, pvalue->priority, 0U, 127U);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
      else
         return LOG_ASN1ERR (pctxt, ASN_E_CONSVIO);

   }

   /* encode remoteExtensionAddress */

   if (pvalue->m.remoteExtensionAddressPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->remoteExtensionAddress);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode destExtraCallInfo */

   if (pvalue->m.destExtraCallInfoPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->destExtraCallInfo);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 2);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternateTransportAddressesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.circuitInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.alternateTransportAddressesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AlternateTransportAddresses (&lctxt, &pvalue->alternateTransportAddresses);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.circuitInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CircuitInfo (&lctxt, &pvalue->circuitInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  UseSpecifiedTransport                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225UseSpecifiedTransport (OOCTXT* pctxt, H225UseSpecifiedTransport* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 2);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* tcp */
         case 1:
            /* NULL */
            break;

         /* annexE */
         case 2:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* sctp */
         case 3:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  AlternateGK                                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225AlternateGK (OOCTXT* pctxt, H225AlternateGK* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatekeeperIdentifierPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode rasAddress */

   stat = asn1PE_H225TransportAddress (pctxt, &pvalue->rasAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode gatekeeperIdentifier */

   if (pvalue->m.gatekeeperIdentifierPresent) {
      stat = asn1PE_H225GatekeeperIdentifier (pctxt, pvalue->gatekeeperIdentifier);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode needToRegister */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->needToRegister);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode priority */

   if ( (pvalue->priority <= 127) ) {
      stat = encodeConsUnsigned (pctxt, pvalue->priority, 0U, 127U);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }
   else
      return LOG_ASN1ERR (pctxt, ASN_E_CONSVIO);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225AlternateGK                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225AlternateGK (OOCTXT* pctxt, H225_SeqOfH225AlternateGK value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225AlternateGK (pctxt, ((H225AlternateGK*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  AltGKInfo                                                 */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225AltGKInfo (OOCTXT* pctxt, H225AltGKInfo* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode alternateGatekeeper */

   stat = asn1PE_H225_SeqOfH225AlternateGK (pctxt, pvalue->alternateGatekeeper);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode altGKisPermanent */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->altGKisPermanent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  SecurityErrors2                                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225SecurityErrors2 (OOCTXT* pctxt, H225SecurityErrors2* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 6);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* securityWrongSyncTime */
         case 1:
            /* NULL */
            break;

         /* securityReplay */
         case 2:
            /* NULL */
            break;

         /* securityWrongGeneralID */
         case 3:
            /* NULL */
            break;

         /* securityWrongSendersID */
         case 4:
            /* NULL */
            break;

         /* securityIntegrityFailed */
         case 5:
            /* NULL */
            break;

         /* securityWrongOID */
         case 6:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  EncryptIntAlg                                             */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225EncryptIntAlg (OOCTXT* pctxt, H225EncryptIntAlg* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 2);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* nonStandard */
         case 1:
            stat = asn1PE_H225NonStandardParameter (pctxt, pvalue->u.nonStandard);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* isoAlgorithm */
         case 2:
            stat = encodeObjectIdentifier (pctxt, pvalue->u.isoAlgorithm);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  NonIsoIntegrityMechanism                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225NonIsoIntegrityMechanism (OOCTXT* pctxt, H225NonIsoIntegrityMechanism* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 4);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* hMAC_MD5 */
         case 1:
            /* NULL */
            break;

         /* hMAC_iso10118_2_s */
         case 2:
            stat = asn1PE_H225EncryptIntAlg (pctxt, pvalue->u.hMAC_iso10118_2_s);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* hMAC_iso10118_2_l */
         case 3:
            stat = asn1PE_H225EncryptIntAlg (pctxt, pvalue->u.hMAC_iso10118_2_l);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* hMAC_iso10118_3 */
         case 4:
            stat = encodeObjectIdentifier (pctxt, pvalue->u.hMAC_iso10118_3);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  IntegrityMechanism                                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225IntegrityMechanism (OOCTXT* pctxt, H225IntegrityMechanism* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 4);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* nonStandard */
         case 1:
            stat = asn1PE_H225NonStandardParameter (pctxt, pvalue->u.nonStandard);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* digSig */
         case 2:
            /* NULL */
            break;

         /* iso9797 */
         case 3:
            stat = encodeObjectIdentifier (pctxt, pvalue->u.iso9797);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* nonIsoIM */
         case 4:
            stat = asn1PE_H225NonIsoIntegrityMechanism (pctxt, pvalue->u.nonIsoIM);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ICV                                                       */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ICV (OOCTXT* pctxt, H225ICV* pvalue)
{
   int stat = ASN_OK;

   /* encode algorithmOID */

   stat = encodeObjectIdentifier (pctxt, &pvalue->algorithmOID);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode icv */

   stat = encodeBitString (pctxt, pvalue->icv.numbits, pvalue->icv.data);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CapacityReportingCapability                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CapacityReportingCapability (OOCTXT* pctxt, H225CapacityReportingCapability* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode canReportCallCapacity */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->canReportCallCapacity);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CapacityReportingSpecification_when                       */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CapacityReportingSpecification_when (OOCTXT* pctxt, H225CapacityReportingSpecification_when* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callStartPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callEndPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callStart */

   if (pvalue->m.callStartPresent) {
      /* NULL */
   }

   /* encode callEnd */

   if (pvalue->m.callEndPresent) {
      /* NULL */
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CapacityReportingSpecification                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CapacityReportingSpecification (OOCTXT* pctxt, H225CapacityReportingSpecification* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode when */

   stat = asn1PE_H225CapacityReportingSpecification_when (pctxt, &pvalue->when);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RasUsageInfoTypes                                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RasUsageInfoTypes (OOCTXT* pctxt, H225RasUsageInfoTypes* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.startTimePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.endTimePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.terminationCausePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardUsageTypes */

   stat = asn1PE_H225_SeqOfH225NonStandardParameter (pctxt, pvalue->nonStandardUsageTypes);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode startTime */

   if (pvalue->m.startTimePresent) {
      /* NULL */
   }

   /* encode endTime */

   if (pvalue->m.endTimePresent) {
      /* NULL */
   }

   /* encode terminationCause */

   if (pvalue->m.terminationCausePresent) {
      /* NULL */
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RasUsageSpecification_when                                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RasUsageSpecification_when (OOCTXT* pctxt, H225RasUsageSpecification_when* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.startPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.endPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.inIrrPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode start */

   if (pvalue->m.startPresent) {
      /* NULL */
   }

   /* encode end */

   if (pvalue->m.endPresent) {
      /* NULL */
   }

   /* encode inIrr */

   if (pvalue->m.inIrrPresent) {
      /* NULL */
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RasUsageSpecification_callStartingPoint                   */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RasUsageSpecification_callStartingPoint (OOCTXT* pctxt, H225RasUsageSpecification_callStartingPoint* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alertingPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.connectPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode alerting */

   if (pvalue->m.alertingPresent) {
      /* NULL */
   }

   /* encode connect */

   if (pvalue->m.connectPresent) {
      /* NULL */
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RasUsageSpecification                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RasUsageSpecification (OOCTXT* pctxt, H225RasUsageSpecification* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callStartingPointPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode when */

   stat = asn1PE_H225RasUsageSpecification_when (pctxt, &pvalue->when);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callStartingPoint */

   if (pvalue->m.callStartingPointPresent) {
      stat = asn1PE_H225RasUsageSpecification_callStartingPoint (pctxt, &pvalue->callStartingPoint);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode required */

   stat = asn1PE_H225RasUsageInfoTypes (pctxt, &pvalue->required);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RasUsageInformation                                       */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RasUsageInformation (OOCTXT* pctxt, H225RasUsageInformation* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alertingTimePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.connectTimePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.endTimePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardUsageFields */

   stat = asn1PE_H225_SeqOfH225NonStandardParameter (pctxt, pvalue->nonStandardUsageFields);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode alertingTime */

   if (pvalue->m.alertingTimePresent) {
      stat = asn1PE_H235TimeStamp (pctxt, pvalue->alertingTime);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode connectTime */

   if (pvalue->m.connectTimePresent) {
      stat = asn1PE_H235TimeStamp (pctxt, pvalue->connectTime);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode endTime */

   if (pvalue->m.endTimePresent) {
      stat = asn1PE_H235TimeStamp (pctxt, pvalue->endTime);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallTerminationCause                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallTerminationCause (OOCTXT* pctxt, H225CallTerminationCause* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 2);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* releaseCompleteReason */
         case 1:
            stat = asn1PE_H225ReleaseCompleteReason (pctxt, pvalue->u.releaseCompleteReason);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* releaseCompleteCauseIE */
         case 2:
            stat = asn1PE_H225CallTerminationCause_releaseCompleteCauseIE (pctxt, pvalue->u.releaseCompleteCauseIE);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportChannelInfo                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportChannelInfo (OOCTXT* pctxt, H225TransportChannelInfo* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.sendAddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.recvAddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode sendAddress */

   if (pvalue->m.sendAddressPresent) {
      stat = asn1PE_H225TransportAddress (pctxt, &pvalue->sendAddress);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode recvAddress */

   if (pvalue->m.recvAddressPresent) {
      stat = asn1PE_H225TransportAddress (pctxt, &pvalue->recvAddress);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  BandwidthDetails                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225BandwidthDetails (OOCTXT* pctxt, H225BandwidthDetails* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode sender */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->sender);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode multicast */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->multicast);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode bandwidth */

   stat = asn1PE_H225BandWidth (pctxt, pvalue->bandwidth);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode rtcpAddresses */

   stat = asn1PE_H225TransportChannelInfo (pctxt, &pvalue->rtcpAddresses);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallCreditCapability                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallCreditCapability (OOCTXT* pctxt, H225CallCreditCapability* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.canDisplayAmountStringPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.canEnforceDurationLimitPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode canDisplayAmountString */

   if (pvalue->m.canDisplayAmountStringPresent) {
      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->canDisplayAmountString);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode canEnforceDurationLimit */

   if (pvalue->m.canEnforceDurationLimitPresent) {
      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->canEnforceDurationLimit);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RTPSession_associatedSessionIds                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RTPSession_associatedSessionIds (OOCTXT* pctxt, H225RTPSession_associatedSessionIds* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      if ( (pvalue->elem[xx1] >= 1) ) {
         stat = encodeConsUnsigned (pctxt, pvalue->elem[xx1], 1U, 255U);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
      else
         return LOG_ASN1ERR (pctxt, ASN_E_CONSVIO);

   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RTPSession                                                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RTPSession (OOCTXT* pctxt, H225RTPSession* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.multicastPresent ||
   pvalue->m.bandwidthPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode rtpAddress */

   stat = asn1PE_H225TransportChannelInfo (pctxt, &pvalue->rtpAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode rtcpAddress */

   stat = asn1PE_H225TransportChannelInfo (pctxt, &pvalue->rtcpAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode cname */

   stat = encodeConstrainedStringEx (pctxt, pvalue->cname, 0, 8, 7, 7);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode ssrc */

   stat = encodeConsUnsigned (pctxt, pvalue->ssrc, 1U, ASN1UINT_MAX);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode sessionId */

   if ( (pvalue->sessionId >= 1) ) {
      stat = encodeConsUnsigned (pctxt, pvalue->sessionId, 1U, 255U);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }
   else
      return LOG_ASN1ERR (pctxt, ASN_E_CONSVIO);

   /* encode associatedSessionIds */

   stat = asn1PE_H225RTPSession_associatedSessionIds (pctxt, &pvalue->associatedSessionIds);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.multicastPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.bandwidthPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.multicastPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.bandwidthPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225BandWidth (&lctxt, pvalue->bandwidth);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225Endpoint                                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225Endpoint (OOCTXT* pctxt, H225_SeqOfH225Endpoint value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225Endpoint (pctxt, ((H225Endpoint*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225AuthenticationMechanism                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225AuthenticationMechanism (OOCTXT* pctxt, H225_SeqOfH225AuthenticationMechanism value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H235AuthenticationMechanism (pctxt, ((H235AuthenticationMechanism*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GatekeeperRequest_algorithmOIDs                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GatekeeperRequest_algorithmOIDs (OOCTXT* pctxt, H225GatekeeperRequest_algorithmOIDs* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = encodeObjectIdentifier (pctxt, &pvalue->elem[xx1]);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225IntegrityMechanism                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225IntegrityMechanism (OOCTXT* pctxt, H225_SeqOfH225IntegrityMechanism value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225IntegrityMechanism (pctxt, ((H225IntegrityMechanism*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GatekeeperRequest                                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GatekeeperRequest (OOCTXT* pctxt, H225GatekeeperRequest* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.alternateEndpointsPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.authenticationCapabilityPresent ||
   pvalue->m.algorithmOIDsPresent ||
   pvalue->m.integrityPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.supportsAltGKPresent ||
   pvalue->m.featureSetPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatekeeperIdentifierPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callServicesPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.endpointAliasPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode rasAddress */

   stat = asn1PE_H225TransportAddress (pctxt, &pvalue->rasAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode endpointType */

   stat = asn1PE_H225EndpointType (pctxt, &pvalue->endpointType);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode gatekeeperIdentifier */

   if (pvalue->m.gatekeeperIdentifierPresent) {
      stat = asn1PE_H225GatekeeperIdentifier (pctxt, pvalue->gatekeeperIdentifier);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode callServices */

   if (pvalue->m.callServicesPresent) {
      stat = asn1PE_H225QseriesOptions (pctxt, &pvalue->callServices);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode endpointAlias */

   if (pvalue->m.endpointAliasPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->endpointAlias);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 9);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternateEndpointsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.authenticationCapabilityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.algorithmOIDsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportsAltGKPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.alternateEndpointsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225Endpoint (&lctxt, pvalue->alternateEndpoints);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.authenticationCapabilityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AuthenticationMechanism (&lctxt, pvalue->authenticationCapability);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.algorithmOIDsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225GatekeeperRequest_algorithmOIDs (&lctxt, &pvalue->algorithmOIDs);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225IntegrityMechanism (&lctxt, pvalue->integrity);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportsAltGKPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GatekeeperConfirm                                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GatekeeperConfirm (OOCTXT* pctxt, H225GatekeeperConfirm* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.alternateGatekeeperPresent ||
   pvalue->m.authenticationModePresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.algorithmOIDPresent ||
   pvalue->m.integrityPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.featureSetPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatekeeperIdentifierPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode gatekeeperIdentifier */

   if (pvalue->m.gatekeeperIdentifierPresent) {
      stat = asn1PE_H225GatekeeperIdentifier (pctxt, pvalue->gatekeeperIdentifier);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode rasAddress */

   stat = asn1PE_H225TransportAddress (pctxt, &pvalue->rasAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 8);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternateGatekeeperPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.authenticationModePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.algorithmOIDPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.alternateGatekeeperPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AlternateGK (&lctxt, pvalue->alternateGatekeeper);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.authenticationModePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H235AuthenticationMechanism (&lctxt, &pvalue->authenticationMode);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.algorithmOIDPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeObjectIdentifier (&lctxt, &pvalue->algorithmOID);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225IntegrityMechanism (&lctxt, pvalue->integrity);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GatekeeperRejectReason                                    */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GatekeeperRejectReason (OOCTXT* pctxt, H225GatekeeperRejectReason* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 4);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* resourceUnavailable */
         case 1:
            /* NULL */
            break;

         /* terminalExcluded */
         case 2:
            /* NULL */
            break;

         /* invalidRevision */
         case 3:
            /* NULL */
            break;

         /* undefinedReason */
         case 4:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* securityDenial */
         case 5:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* genericDataReason */
         case 6:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* neededFeatureNotSupported */
         case 7:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* securityError */
         case 8:
            stat = asn1PE_H225SecurityErrors (&lctxt, pvalue->u.securityError);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  GatekeeperReject                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225GatekeeperReject (OOCTXT* pctxt, H225GatekeeperReject* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.altGKInfoPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.featureSetPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatekeeperIdentifierPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode gatekeeperIdentifier */

   if (pvalue->m.gatekeeperIdentifierPresent) {
      stat = asn1PE_H225GatekeeperIdentifier (pctxt, pvalue->gatekeeperIdentifier);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode rejectReason */

   stat = asn1PE_H225GatekeeperRejectReason (pctxt, &pvalue->rejectReason);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.altGKInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.altGKInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AltGKInfo (&lctxt, &pvalue->altGKInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225AddressPattern                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225AddressPattern (OOCTXT* pctxt, H225_SeqOfH225AddressPattern value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225AddressPattern (pctxt, ((H225AddressPattern*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225H248PackagesDescriptor                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225H248PackagesDescriptor (OOCTXT* pctxt, H225_SeqOfH225H248PackagesDescriptor* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = asn1PE_H225H248PackagesDescriptor (pctxt, pvalue->elem[xx1]);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RegistrationRequest                                       */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RegistrationRequest (OOCTXT* pctxt, H225RegistrationRequest* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.alternateEndpointsPresent ||
   pvalue->m.timeToLivePresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.keepAlivePresent ||
   pvalue->m.endpointIdentifierPresent ||
   pvalue->m.willSupplyUUIEsPresent ||
   pvalue->m.maintainConnectionPresent ||
   pvalue->m.alternateTransportAddressesPresent ||
   pvalue->m.additiveRegistrationPresent ||
   pvalue->m.terminalAliasPatternPresent ||
   pvalue->m.supportsAltGKPresent ||
   pvalue->m.usageReportingCapabilityPresent ||
   pvalue->m.multipleCallsPresent ||
   pvalue->m.supportedH248PackagesPresent ||
   pvalue->m.callCreditCapabilityPresent ||
   pvalue->m.capacityReportingCapabilityPresent ||
   pvalue->m.capacityPresent ||
   pvalue->m.featureSetPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->m.restartPresent ||
   pvalue->m.supportsACFSequencesPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.terminalAliasPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatekeeperIdentifierPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode discoveryComplete */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->discoveryComplete);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callSignalAddress */

   stat = asn1PE_H225_SeqOfH225TransportAddress (pctxt, pvalue->callSignalAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode rasAddress */

   stat = asn1PE_H225_SeqOfH225TransportAddress (pctxt, pvalue->rasAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode terminalType */

   stat = asn1PE_H225EndpointType (pctxt, &pvalue->terminalType);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode terminalAlias */

   if (pvalue->m.terminalAliasPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->terminalAlias);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode gatekeeperIdentifier */

   if (pvalue->m.gatekeeperIdentifierPresent) {
      stat = asn1PE_H225GatekeeperIdentifier (pctxt, pvalue->gatekeeperIdentifier);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode endpointVendor */

   stat = asn1PE_H225VendorIdentifier (pctxt, &pvalue->endpointVendor);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 22);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternateEndpointsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.timeToLivePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.keepAlivePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.endpointIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.willSupplyUUIEsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.maintainConnectionPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternateTransportAddressesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.additiveRegistrationPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.terminalAliasPatternPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportsAltGKPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.usageReportingCapabilityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.multipleCallsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedH248PackagesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callCreditCapabilityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityReportingCapabilityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.restartPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportsACFSequencesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.alternateEndpointsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225Endpoint (&lctxt, pvalue->alternateEndpoints);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.timeToLivePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225TimeToLive (&lctxt, pvalue->timeToLive);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.keepAlivePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->keepAlive);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.endpointIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225EndpointIdentifier (&lctxt, pvalue->endpointIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.willSupplyUUIEsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->willSupplyUUIEs);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.maintainConnectionPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->maintainConnection);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.alternateTransportAddressesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AlternateTransportAddresses (&lctxt, &pvalue->alternateTransportAddresses);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.additiveRegistrationPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.terminalAliasPatternPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AddressPattern (&lctxt, pvalue->terminalAliasPattern);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportsAltGKPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.usageReportingCapabilityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225RasUsageInfoTypes (&lctxt, &pvalue->usageReportingCapability);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.multipleCallsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->multipleCalls);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedH248PackagesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225H248PackagesDescriptor (&lctxt, &pvalue->supportedH248Packages);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.callCreditCapabilityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallCreditCapability (&lctxt, &pvalue->callCreditCapability);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.capacityReportingCapabilityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CapacityReportingCapability (&lctxt, &pvalue->capacityReportingCapability);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.capacityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallCapacity (&lctxt, &pvalue->capacity);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.restartPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportsACFSequencesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RegistrationConfirm_preGrantedARQ                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RegistrationConfirm_preGrantedARQ (OOCTXT* pctxt, H225RegistrationConfirm_preGrantedARQ* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.irrFrequencyInCallPresent ||
   pvalue->m.totalBandwidthRestrictionPresent ||
   pvalue->m.alternateTransportAddressesPresent ||
   pvalue->m.useSpecifiedTransportPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode makeCall */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->makeCall);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode useGKCallSignalAddressToMakeCall */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->useGKCallSignalAddressToMakeCall);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode answerCall */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->answerCall);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode useGKCallSignalAddressToAnswer */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->useGKCallSignalAddressToAnswer);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.irrFrequencyInCallPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.totalBandwidthRestrictionPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternateTransportAddressesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.useSpecifiedTransportPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.irrFrequencyInCallPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         if ( (pvalue->irrFrequencyInCall >= 1) ) {
            stat = encodeConsUnsigned (&lctxt, pvalue->irrFrequencyInCall, 1U, 65535U);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
         }
         else
            return LOG_ASN1ERR (pctxt, ASN_E_CONSVIO);

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.totalBandwidthRestrictionPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225BandWidth (&lctxt, pvalue->totalBandwidthRestriction);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.alternateTransportAddressesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AlternateTransportAddresses (&lctxt, &pvalue->alternateTransportAddresses);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.useSpecifiedTransportPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225UseSpecifiedTransport (&lctxt, &pvalue->useSpecifiedTransport);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225RasUsageSpecification                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225RasUsageSpecification (OOCTXT* pctxt, H225_SeqOfH225RasUsageSpecification value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225RasUsageSpecification (pctxt, ((H225RasUsageSpecification*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RegistrationConfirm                                       */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RegistrationConfirm (OOCTXT* pctxt, H225RegistrationConfirm* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.alternateGatekeeperPresent ||
   pvalue->m.timeToLivePresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.willRespondToIRRPresent ||
   pvalue->m.preGrantedARQPresent ||
   pvalue->m.maintainConnectionPresent ||
   pvalue->m.serviceControlPresent ||
   pvalue->m.supportsAdditiveRegistrationPresent ||
   pvalue->m.terminalAliasPatternPresent ||
   pvalue->m.supportedPrefixesPresent ||
   pvalue->m.usageSpecPresent ||
   pvalue->m.featureServerAliasPresent ||
   pvalue->m.capacityReportingSpecPresent ||
   pvalue->m.featureSetPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.terminalAliasPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatekeeperIdentifierPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode callSignalAddress */

   stat = asn1PE_H225_SeqOfH225TransportAddress (pctxt, pvalue->callSignalAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode terminalAlias */

   if (pvalue->m.terminalAliasPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->terminalAlias);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode gatekeeperIdentifier */

   if (pvalue->m.gatekeeperIdentifierPresent) {
      stat = asn1PE_H225GatekeeperIdentifier (pctxt, pvalue->gatekeeperIdentifier);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode endpointIdentifier */

   stat = asn1PE_H225EndpointIdentifier (pctxt, pvalue->endpointIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 16);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternateGatekeeperPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.timeToLivePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.willRespondToIRRPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.preGrantedARQPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.maintainConnectionPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.serviceControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportsAdditiveRegistrationPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.terminalAliasPatternPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedPrefixesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.usageSpecPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureServerAliasPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityReportingSpecPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.alternateGatekeeperPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AlternateGK (&lctxt, pvalue->alternateGatekeeper);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.timeToLivePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225TimeToLive (&lctxt, pvalue->timeToLive);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.willRespondToIRRPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->willRespondToIRR);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.preGrantedARQPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225RegistrationConfirm_preGrantedARQ (&lctxt, &pvalue->preGrantedARQ);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.maintainConnectionPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->maintainConnection);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.serviceControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ServiceControlSession (&lctxt, pvalue->serviceControl);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportsAdditiveRegistrationPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.terminalAliasPatternPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AddressPattern (&lctxt, pvalue->terminalAliasPattern);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedPrefixesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedPrefix (&lctxt, pvalue->supportedPrefixes);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.usageSpecPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225RasUsageSpecification (&lctxt, pvalue->usageSpec);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureServerAliasPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AliasAddress (&lctxt, &pvalue->featureServerAlias);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.capacityReportingSpecPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CapacityReportingSpecification (&lctxt, &pvalue->capacityReportingSpec);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RegistrationRejectReason_invalidTerminalAliases           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RegistrationRejectReason_invalidTerminalAliases (OOCTXT* pctxt, H225RegistrationRejectReason_invalidTerminalAliases* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.terminalAliasPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.terminalAliasPatternPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedPrefixesPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode terminalAlias */

   if (pvalue->m.terminalAliasPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->terminalAlias);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode terminalAliasPattern */

   if (pvalue->m.terminalAliasPatternPresent) {
      stat = asn1PE_H225_SeqOfH225AddressPattern (pctxt, pvalue->terminalAliasPattern);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode supportedPrefixes */

   if (pvalue->m.supportedPrefixesPresent) {
      stat = asn1PE_H225_SeqOfH225SupportedPrefix (pctxt, pvalue->supportedPrefixes);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RegistrationRejectReason                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RegistrationRejectReason (OOCTXT* pctxt, H225RegistrationRejectReason* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 8);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* discoveryRequired */
         case 1:
            /* NULL */
            break;

         /* invalidRevision */
         case 2:
            /* NULL */
            break;

         /* invalidCallSignalAddress */
         case 3:
            /* NULL */
            break;

         /* invalidRASAddress */
         case 4:
            /* NULL */
            break;

         /* duplicateAlias */
         case 5:
            stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, *pvalue->u.duplicateAlias);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* invalidTerminalType */
         case 6:
            /* NULL */
            break;

         /* undefinedReason */
         case 7:
            /* NULL */
            break;

         /* transportNotSupported */
         case 8:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 9);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* transportQOSNotSupported */
         case 9:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* resourceUnavailable */
         case 10:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* invalidAlias */
         case 11:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* securityDenial */
         case 12:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* fullRegistrationRequired */
         case 13:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* additiveRegistrationNotSupported */
         case 14:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* invalidTerminalAliases */
         case 15:
            stat = asn1PE_H225RegistrationRejectReason_invalidTerminalAliases (&lctxt, pvalue->u.invalidTerminalAliases);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* genericDataReason */
         case 16:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* neededFeatureNotSupported */
         case 17:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* securityError */
         case 18:
            stat = asn1PE_H225SecurityErrors (&lctxt, pvalue->u.securityError);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RegistrationReject                                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RegistrationReject (OOCTXT* pctxt, H225RegistrationReject* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.altGKInfoPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.featureSetPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatekeeperIdentifierPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode rejectReason */

   stat = asn1PE_H225RegistrationRejectReason (pctxt, &pvalue->rejectReason);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode gatekeeperIdentifier */

   if (pvalue->m.gatekeeperIdentifierPresent) {
      stat = asn1PE_H225GatekeeperIdentifier (pctxt, pvalue->gatekeeperIdentifier);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.altGKInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.altGKInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AltGKInfo (&lctxt, &pvalue->altGKInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  UnregRequestReason                                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225UnregRequestReason (OOCTXT* pctxt, H225UnregRequestReason* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 4);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* reregistrationRequired */
         case 1:
            /* NULL */
            break;

         /* ttlExpired */
         case 2:
            /* NULL */
            break;

         /* securityDenial */
         case 3:
            /* NULL */
            break;

         /* undefinedReason */
         case 4:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* maintenance */
         case 5:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* securityError */
         case 6:
            stat = asn1PE_H225SecurityErrors2 (&lctxt, pvalue->u.securityError);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  UnregistrationRequest                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225UnregistrationRequest (OOCTXT* pctxt, H225UnregistrationRequest* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.alternateEndpointsPresent ||
   pvalue->m.gatekeeperIdentifierPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.reasonPresent ||
   pvalue->m.endpointAliasPatternPresent ||
   pvalue->m.supportedPrefixesPresent ||
   pvalue->m.alternateGatekeeperPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.endpointAliasPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.endpointIdentifierPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callSignalAddress */

   stat = asn1PE_H225_SeqOfH225TransportAddress (pctxt, pvalue->callSignalAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode endpointAlias */

   if (pvalue->m.endpointAliasPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->endpointAlias);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode endpointIdentifier */

   if (pvalue->m.endpointIdentifierPresent) {
      stat = asn1PE_H225EndpointIdentifier (pctxt, pvalue->endpointIdentifier);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 9);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternateEndpointsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatekeeperIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.reasonPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.endpointAliasPatternPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedPrefixesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternateGatekeeperPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.alternateEndpointsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225Endpoint (&lctxt, pvalue->alternateEndpoints);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.gatekeeperIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225GatekeeperIdentifier (&lctxt, pvalue->gatekeeperIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.reasonPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225UnregRequestReason (&lctxt, &pvalue->reason);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.endpointAliasPatternPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AddressPattern (&lctxt, pvalue->endpointAliasPattern);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedPrefixesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedPrefix (&lctxt, pvalue->supportedPrefixes);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.alternateGatekeeperPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AlternateGK (&lctxt, pvalue->alternateGatekeeper);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  UnregistrationConfirm                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225UnregistrationConfirm (OOCTXT* pctxt, H225UnregistrationConfirm* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  UnregRejectReason                                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225UnregRejectReason (OOCTXT* pctxt, H225UnregRejectReason* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 3);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 2);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* notCurrentlyRegistered */
         case 1:
            /* NULL */
            break;

         /* callInProgress */
         case 2:
            /* NULL */
            break;

         /* undefinedReason */
         case 3:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* permissionDenied */
         case 4:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* securityDenial */
         case 5:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* securityError */
         case 6:
            stat = asn1PE_H225SecurityErrors2 (&lctxt, pvalue->u.securityError);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  UnregistrationReject                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225UnregistrationReject (OOCTXT* pctxt, H225UnregistrationReject* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.altGKInfoPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode rejectReason */

   stat = asn1PE_H225UnregRejectReason (pctxt, &pvalue->rejectReason);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.altGKInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.altGKInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AltGKInfo (&lctxt, &pvalue->altGKInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  CallModel                                                 */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225CallModel (OOCTXT* pctxt, H225CallModel* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 2);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* direct */
         case 1:
            /* NULL */
            break;

         /* gatekeeperRouted */
         case 2:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  TransportQOS                                              */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225TransportQOS (OOCTXT* pctxt, H225TransportQOS* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 3);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 2);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* endpointControlled */
         case 1:
            /* NULL */
            break;

         /* gatekeeperControlled */
         case 2:
            /* NULL */
            break;

         /* noControl */
         case 3:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  AdmissionRequest                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225AdmissionRequest (OOCTXT* pctxt, H225AdmissionRequest* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.canMapAliasPresent ||
   pvalue->m.callIdentifierPresent ||
   pvalue->m.srcAlternativesPresent ||
   pvalue->m.destAlternativesPresent ||
   pvalue->m.gatekeeperIdentifierPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.transportQOSPresent ||
   pvalue->m.willSupplyUUIEsPresent ||
   pvalue->m.callLinkagePresent ||
   pvalue->m.gatewayDataRatePresent ||
   pvalue->m.capacityPresent ||
   pvalue->m.circuitInfoPresent ||
   pvalue->m.desiredProtocolsPresent ||
   pvalue->m.desiredTunnelledProtocolPresent ||
   pvalue->m.featureSetPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->m.canMapSrcAliasPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callModelPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destinationInfoPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destCallSignalAddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destExtraCallInfoPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.srcCallSignalAddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callServicesPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callType */

   stat = asn1PE_H225CallType (pctxt, &pvalue->callType);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callModel */

   if (pvalue->m.callModelPresent) {
      stat = asn1PE_H225CallModel (pctxt, &pvalue->callModel);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode endpointIdentifier */

   stat = asn1PE_H225EndpointIdentifier (pctxt, pvalue->endpointIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode destinationInfo */

   if (pvalue->m.destinationInfoPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->destinationInfo);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode destCallSignalAddress */

   if (pvalue->m.destCallSignalAddressPresent) {
      stat = asn1PE_H225TransportAddress (pctxt, &pvalue->destCallSignalAddress);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode destExtraCallInfo */

   if (pvalue->m.destExtraCallInfoPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->destExtraCallInfo);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode srcInfo */

   stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->srcInfo);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode srcCallSignalAddress */

   if (pvalue->m.srcCallSignalAddressPresent) {
      stat = asn1PE_H225TransportAddress (pctxt, &pvalue->srcCallSignalAddress);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode bandWidth */

   stat = asn1PE_H225BandWidth (pctxt, pvalue->bandWidth);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callReferenceValue */

   stat = asn1PE_H225CallReferenceValue (pctxt, pvalue->callReferenceValue);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode callServices */

   if (pvalue->m.callServicesPresent) {
      stat = asn1PE_H225QseriesOptions (pctxt, &pvalue->callServices);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode conferenceID */

   stat = asn1PE_H225ConferenceIdentifier (pctxt, &pvalue->conferenceID);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode activeMC */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->activeMC);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode answerCall */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->answerCall);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 18);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.canMapAliasPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.srcAlternativesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destAlternativesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatekeeperIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.transportQOSPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.willSupplyUUIEsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callLinkagePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatewayDataRatePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.circuitInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.desiredProtocolsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.desiredTunnelledProtocolPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.canMapSrcAliasPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.canMapAliasPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->canMapAlias);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.callIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallIdentifier (&lctxt, &pvalue->callIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.srcAlternativesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225Endpoint (&lctxt, pvalue->srcAlternatives);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.destAlternativesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225Endpoint (&lctxt, pvalue->destAlternatives);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.gatekeeperIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225GatekeeperIdentifier (&lctxt, pvalue->gatekeeperIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.transportQOSPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225TransportQOS (&lctxt, &pvalue->transportQOS);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.willSupplyUUIEsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->willSupplyUUIEs);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.callLinkagePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallLinkage (&lctxt, &pvalue->callLinkage);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.gatewayDataRatePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225DataRate (&lctxt, &pvalue->gatewayDataRate);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.capacityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallCapacity (&lctxt, &pvalue->capacity);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.circuitInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CircuitInfo (&lctxt, &pvalue->circuitInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.desiredProtocolsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedProtocols (&lctxt, pvalue->desiredProtocols);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.desiredTunnelledProtocolPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225TunnelledProtocol (&lctxt, &pvalue->desiredTunnelledProtocol);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.canMapSrcAliasPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->canMapSrcAlias);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  UUIEsRequested                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225UUIEsRequested (OOCTXT* pctxt, H225UUIEsRequested* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.statusPresent ||
   pvalue->m.statusInquiryPresent ||
   pvalue->m.setupAcknowledgePresent ||
   pvalue->m.notifyPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode setup */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->setup);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callProceeding */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->callProceeding);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode connect */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->connect);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode alerting */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->alerting);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode information */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->information);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode releaseComplete */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->releaseComplete);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode facility */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->facility);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode progress */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->progress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode empty */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->empty);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.statusPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.statusInquiryPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.setupAcknowledgePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.notifyPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.statusPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->status);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.statusInquiryPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->statusInquiry);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.setupAcknowledgePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->setupAcknowledge);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.notifyPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->notify);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  AdmissionConfirm_language                                 */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225AdmissionConfirm_language (OOCTXT* pctxt, H225AdmissionConfirm_language* pvalue)
{
   static Asn1SizeCnst element_lsize1 = { 0, 1, 32, 0 };
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = addSizeConstraint (pctxt, &element_lsize1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeConstrainedStringEx (pctxt, pvalue->elem[xx1], 0, 8, 7, 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  AdmissionConfirm                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225AdmissionConfirm (OOCTXT* pctxt, H225AdmissionConfirm* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.destinationInfoPresent ||
   pvalue->m.destExtraCallInfoPresent ||
   pvalue->m.destinationTypePresent ||
   pvalue->m.remoteExtensionAddressPresent ||
   pvalue->m.alternateEndpointsPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.transportQOSPresent ||
   pvalue->m.willRespondToIRRPresent ||
   pvalue->m.uuiesRequestedPresent ||
   pvalue->m.languagePresent ||
   pvalue->m.alternateTransportAddressesPresent ||
   pvalue->m.useSpecifiedTransportPresent ||
   pvalue->m.circuitInfoPresent ||
   pvalue->m.usageSpecPresent ||
   pvalue->m.supportedProtocolsPresent ||
   pvalue->m.serviceControlPresent ||
   pvalue->m.multipleCallsPresent ||
   pvalue->m.featureSetPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->m.modifiedSrcInfoPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.irrFrequencyPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode bandWidth */

   stat = asn1PE_H225BandWidth (pctxt, pvalue->bandWidth);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callModel */

   stat = asn1PE_H225CallModel (pctxt, &pvalue->callModel);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode destCallSignalAddress */

   stat = asn1PE_H225TransportAddress (pctxt, &pvalue->destCallSignalAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode irrFrequency */

   if (pvalue->m.irrFrequencyPresent) {
      if ( (pvalue->irrFrequency >= 1) ) {
         stat = encodeConsUnsigned (pctxt, pvalue->irrFrequency, 1U, 65535U);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
      else
         return LOG_ASN1ERR (pctxt, ASN_E_CONSVIO);

   }

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 21);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destinationInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destExtraCallInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destinationTypePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.remoteExtensionAddressPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternateEndpointsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.transportQOSPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.willRespondToIRRPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.uuiesRequestedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.languagePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternateTransportAddressesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.useSpecifiedTransportPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.circuitInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.usageSpecPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedProtocolsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.serviceControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.multipleCallsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.modifiedSrcInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.destinationInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AliasAddress (&lctxt, pvalue->destinationInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.destExtraCallInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AliasAddress (&lctxt, pvalue->destExtraCallInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.destinationTypePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225EndpointType (&lctxt, &pvalue->destinationType);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.remoteExtensionAddressPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AliasAddress (&lctxt, pvalue->remoteExtensionAddress);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.alternateEndpointsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225Endpoint (&lctxt, pvalue->alternateEndpoints);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.transportQOSPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225TransportQOS (&lctxt, &pvalue->transportQOS);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.willRespondToIRRPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->willRespondToIRR);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.uuiesRequestedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225UUIEsRequested (&lctxt, &pvalue->uuiesRequested);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.languagePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AdmissionConfirm_language (&lctxt, &pvalue->language);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.alternateTransportAddressesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AlternateTransportAddresses (&lctxt, &pvalue->alternateTransportAddresses);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.useSpecifiedTransportPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225UseSpecifiedTransport (&lctxt, &pvalue->useSpecifiedTransport);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.circuitInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CircuitInfo (&lctxt, &pvalue->circuitInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.usageSpecPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225RasUsageSpecification (&lctxt, pvalue->usageSpec);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedProtocolsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedProtocols (&lctxt, pvalue->supportedProtocols);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.serviceControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ServiceControlSession (&lctxt, pvalue->serviceControl);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.multipleCallsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->multipleCalls);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.modifiedSrcInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AliasAddress (&lctxt, pvalue->modifiedSrcInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225PartyNumber                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225PartyNumber (OOCTXT* pctxt, H225_SeqOfH225PartyNumber value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225PartyNumber (pctxt, ((H225PartyNumber*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  AdmissionRejectReason                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225AdmissionRejectReason (OOCTXT* pctxt, H225AdmissionRejectReason* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 8);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* calledPartyNotRegistered */
         case 1:
            /* NULL */
            break;

         /* invalidPermission */
         case 2:
            /* NULL */
            break;

         /* requestDenied */
         case 3:
            /* NULL */
            break;

         /* undefinedReason */
         case 4:
            /* NULL */
            break;

         /* callerNotRegistered */
         case 5:
            /* NULL */
            break;

         /* routeCallToGatekeeper */
         case 6:
            /* NULL */
            break;

         /* invalidEndpointIdentifier */
         case 7:
            /* NULL */
            break;

         /* resourceUnavailable */
         case 8:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 9);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* securityDenial */
         case 9:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* qosControlNotSupported */
         case 10:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* incompleteAddress */
         case 11:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* aliasesInconsistent */
         case 12:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* routeCallToSCN */
         case 13:
            stat = asn1PE_H225_SeqOfH225PartyNumber (&lctxt, *pvalue->u.routeCallToSCN);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* exceedsCallCapacity */
         case 14:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* collectDestination */
         case 15:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* collectPIN */
         case 16:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* genericDataReason */
         case 17:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* neededFeatureNotSupported */
         case 18:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* securityErrors */
         case 19:
            stat = asn1PE_H225SecurityErrors2 (&lctxt, pvalue->u.securityErrors);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* securityDHmismatch */
         case 20:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* noRouteToDestination */
         case 21:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* unallocatedNumber */
         case 22:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  AdmissionReject                                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225AdmissionReject (OOCTXT* pctxt, H225AdmissionReject* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.altGKInfoPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.callSignalAddressPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.serviceControlPresent ||
   pvalue->m.featureSetPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode rejectReason */

   stat = asn1PE_H225AdmissionRejectReason (pctxt, &pvalue->rejectReason);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.altGKInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callSignalAddressPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.serviceControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.altGKInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AltGKInfo (&lctxt, &pvalue->altGKInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.callSignalAddressPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225TransportAddress (&lctxt, pvalue->callSignalAddress);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.serviceControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ServiceControlSession (&lctxt, pvalue->serviceControl);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225BandwidthDetails                                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225BandwidthDetails (OOCTXT* pctxt, H225_SeqOfH225BandwidthDetails value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225BandwidthDetails (pctxt, ((H225BandwidthDetails*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  BandwidthRequest                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225BandwidthRequest (OOCTXT* pctxt, H225BandwidthRequest* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.callIdentifierPresent ||
   pvalue->m.gatekeeperIdentifierPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.answeredCallPresent ||
   pvalue->m.callLinkagePresent ||
   pvalue->m.capacityPresent ||
   pvalue->m.usageInformationPresent ||
   pvalue->m.bandwidthDetailsPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callTypePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode endpointIdentifier */

   stat = asn1PE_H225EndpointIdentifier (pctxt, pvalue->endpointIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode conferenceID */

   stat = asn1PE_H225ConferenceIdentifier (pctxt, &pvalue->conferenceID);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callReferenceValue */

   stat = asn1PE_H225CallReferenceValue (pctxt, pvalue->callReferenceValue);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callType */

   if (pvalue->m.callTypePresent) {
      stat = asn1PE_H225CallType (pctxt, &pvalue->callType);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode bandWidth */

   stat = asn1PE_H225BandWidth (pctxt, pvalue->bandWidth);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 10);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatekeeperIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.answeredCallPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callLinkagePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.usageInformationPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.bandwidthDetailsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.callIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallIdentifier (&lctxt, &pvalue->callIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.gatekeeperIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225GatekeeperIdentifier (&lctxt, pvalue->gatekeeperIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.answeredCallPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->answeredCall);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.callLinkagePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallLinkage (&lctxt, &pvalue->callLinkage);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.capacityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallCapacity (&lctxt, &pvalue->capacity);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.usageInformationPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225RasUsageInformation (&lctxt, &pvalue->usageInformation);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.bandwidthDetailsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225BandwidthDetails (&lctxt, pvalue->bandwidthDetails);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  BandwidthConfirm                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225BandwidthConfirm (OOCTXT* pctxt, H225BandwidthConfirm* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.capacityPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode bandWidth */

   stat = asn1PE_H225BandWidth (pctxt, pvalue->bandWidth);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.capacityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallCapacity (&lctxt, &pvalue->capacity);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  BandRejectReason                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225BandRejectReason (OOCTXT* pctxt, H225BandRejectReason* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 6);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* notBound */
         case 1:
            /* NULL */
            break;

         /* invalidConferenceID */
         case 2:
            /* NULL */
            break;

         /* invalidPermission */
         case 3:
            /* NULL */
            break;

         /* insufficientResources */
         case 4:
            /* NULL */
            break;

         /* invalidRevision */
         case 5:
            /* NULL */
            break;

         /* undefinedReason */
         case 6:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* securityDenial */
         case 7:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* securityError */
         case 8:
            stat = asn1PE_H225SecurityErrors2 (&lctxt, pvalue->u.securityError);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  BandwidthReject                                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225BandwidthReject (OOCTXT* pctxt, H225BandwidthReject* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.altGKInfoPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode rejectReason */

   stat = asn1PE_H225BandRejectReason (pctxt, &pvalue->rejectReason);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode allowedBandWidth */

   stat = asn1PE_H225BandWidth (pctxt, pvalue->allowedBandWidth);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.altGKInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.altGKInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AltGKInfo (&lctxt, &pvalue->altGKInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  DisengageReason                                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225DisengageReason (OOCTXT* pctxt, H225DisengageReason* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 3);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 2);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* forcedDrop */
         case 1:
            /* NULL */
            break;

         /* normalDrop */
         case 2:
            /* NULL */
            break;

         /* undefinedReason */
         case 3:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  DisengageRequest                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225DisengageRequest (OOCTXT* pctxt, H225DisengageRequest* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.callIdentifierPresent ||
   pvalue->m.gatekeeperIdentifierPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.answeredCallPresent ||
   pvalue->m.callLinkagePresent ||
   pvalue->m.capacityPresent ||
   pvalue->m.circuitInfoPresent ||
   pvalue->m.usageInformationPresent ||
   pvalue->m.terminationCausePresent ||
   pvalue->m.serviceControlPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode endpointIdentifier */

   stat = asn1PE_H225EndpointIdentifier (pctxt, pvalue->endpointIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode conferenceID */

   stat = asn1PE_H225ConferenceIdentifier (pctxt, &pvalue->conferenceID);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callReferenceValue */

   stat = asn1PE_H225CallReferenceValue (pctxt, pvalue->callReferenceValue);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode disengageReason */

   stat = asn1PE_H225DisengageReason (pctxt, &pvalue->disengageReason);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 12);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatekeeperIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.answeredCallPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callLinkagePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.circuitInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.usageInformationPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.terminationCausePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.serviceControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.callIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallIdentifier (&lctxt, &pvalue->callIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.gatekeeperIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225GatekeeperIdentifier (&lctxt, pvalue->gatekeeperIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.answeredCallPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->answeredCall);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.callLinkagePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallLinkage (&lctxt, &pvalue->callLinkage);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.capacityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallCapacity (&lctxt, &pvalue->capacity);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.circuitInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CircuitInfo (&lctxt, &pvalue->circuitInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.usageInformationPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225RasUsageInformation (&lctxt, &pvalue->usageInformation);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.terminationCausePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallTerminationCause (&lctxt, &pvalue->terminationCause);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.serviceControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ServiceControlSession (&lctxt, pvalue->serviceControl);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  DisengageConfirm                                          */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225DisengageConfirm (OOCTXT* pctxt, H225DisengageConfirm* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.capacityPresent ||
   pvalue->m.circuitInfoPresent ||
   pvalue->m.usageInformationPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 6);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.circuitInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.usageInformationPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.capacityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallCapacity (&lctxt, &pvalue->capacity);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.circuitInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CircuitInfo (&lctxt, &pvalue->circuitInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.usageInformationPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225RasUsageInformation (&lctxt, &pvalue->usageInformation);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  DisengageRejectReason                                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225DisengageRejectReason (OOCTXT* pctxt, H225DisengageRejectReason* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 2);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* notRegistered */
         case 1:
            /* NULL */
            break;

         /* requestToDropOther */
         case 2:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* securityDenial */
         case 3:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* securityError */
         case 4:
            stat = asn1PE_H225SecurityErrors2 (&lctxt, pvalue->u.securityError);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  DisengageReject                                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225DisengageReject (OOCTXT* pctxt, H225DisengageReject* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.altGKInfoPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode rejectReason */

   stat = asn1PE_H225DisengageRejectReason (pctxt, &pvalue->rejectReason);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.altGKInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.altGKInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AltGKInfo (&lctxt, &pvalue->altGKInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  LocationRequest                                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225LocationRequest (OOCTXT* pctxt, H225LocationRequest* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.sourceInfoPresent ||
   pvalue->m.canMapAliasPresent ||
   pvalue->m.gatekeeperIdentifierPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.desiredProtocolsPresent ||
   pvalue->m.desiredTunnelledProtocolPresent ||
   pvalue->m.featureSetPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->m.hopCountPresent ||
   pvalue->m.circuitInfoPresent ||
   pvalue->m.callIdentifierPresent ||
   pvalue->m.bandWidthPresent ||
   pvalue->m.sourceEndpointInfoPresent ||
   pvalue->m.canMapSrcAliasPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.endpointIdentifierPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode endpointIdentifier */

   if (pvalue->m.endpointIdentifierPresent) {
      stat = asn1PE_H225EndpointIdentifier (pctxt, pvalue->endpointIdentifier);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode destinationInfo */

   stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->destinationInfo);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode replyAddress */

   stat = asn1PE_H225TransportAddress (pctxt, &pvalue->replyAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 15);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.sourceInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.canMapAliasPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.gatekeeperIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.desiredProtocolsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.desiredTunnelledProtocolPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.hopCountPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.circuitInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.bandWidthPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.sourceEndpointInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.canMapSrcAliasPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.sourceInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AliasAddress (&lctxt, pvalue->sourceInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.canMapAliasPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->canMapAlias);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.gatekeeperIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225GatekeeperIdentifier (&lctxt, pvalue->gatekeeperIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.desiredProtocolsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedProtocols (&lctxt, pvalue->desiredProtocols);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.desiredTunnelledProtocolPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225TunnelledProtocol (&lctxt, &pvalue->desiredTunnelledProtocol);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.hopCountPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         if ( (pvalue->hopCount >= 1) ) {
            stat = encodeConsUnsigned (&lctxt, pvalue->hopCount, 1U, 255U);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
         }
         else
            return LOG_ASN1ERR (pctxt, ASN_E_CONSVIO);

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.circuitInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CircuitInfo (&lctxt, &pvalue->circuitInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.callIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallIdentifier (&lctxt, &pvalue->callIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.bandWidthPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225BandWidth (&lctxt, pvalue->bandWidth);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.sourceEndpointInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AliasAddress (&lctxt, pvalue->sourceEndpointInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.canMapSrcAliasPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->canMapSrcAlias);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  LocationConfirm                                           */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225LocationConfirm (OOCTXT* pctxt, H225LocationConfirm* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.destinationInfoPresent ||
   pvalue->m.destExtraCallInfoPresent ||
   pvalue->m.destinationTypePresent ||
   pvalue->m.remoteExtensionAddressPresent ||
   pvalue->m.alternateEndpointsPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.alternateTransportAddressesPresent ||
   pvalue->m.supportedProtocolsPresent ||
   pvalue->m.multipleCallsPresent ||
   pvalue->m.featureSetPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->m.circuitInfoPresent ||
   pvalue->m.serviceControlPresent ||
   pvalue->m.modifiedSrcInfoPresent ||
   pvalue->m.bandWidthPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callSignalAddress */

   stat = asn1PE_H225TransportAddress (pctxt, &pvalue->callSignalAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode rasAddress */

   stat = asn1PE_H225TransportAddress (pctxt, &pvalue->rasAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 16);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destinationInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destExtraCallInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.destinationTypePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.remoteExtensionAddressPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternateEndpointsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.alternateTransportAddressesPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.supportedProtocolsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.multipleCallsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.circuitInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.serviceControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.modifiedSrcInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.bandWidthPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.destinationInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AliasAddress (&lctxt, pvalue->destinationInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.destExtraCallInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AliasAddress (&lctxt, pvalue->destExtraCallInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.destinationTypePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225EndpointType (&lctxt, &pvalue->destinationType);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.remoteExtensionAddressPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AliasAddress (&lctxt, pvalue->remoteExtensionAddress);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.alternateEndpointsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225Endpoint (&lctxt, pvalue->alternateEndpoints);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.alternateTransportAddressesPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AlternateTransportAddresses (&lctxt, &pvalue->alternateTransportAddresses);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.supportedProtocolsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225SupportedProtocols (&lctxt, pvalue->supportedProtocols);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.multipleCallsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->multipleCalls);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.circuitInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CircuitInfo (&lctxt, &pvalue->circuitInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.serviceControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ServiceControlSession (&lctxt, pvalue->serviceControl);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.modifiedSrcInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225AliasAddress (&lctxt, pvalue->modifiedSrcInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.bandWidthPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225BandWidth (&lctxt, pvalue->bandWidth);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  LocationRejectReason                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225LocationRejectReason (OOCTXT* pctxt, H225LocationRejectReason* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 4);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* notRegistered */
         case 1:
            /* NULL */
            break;

         /* invalidPermission */
         case 2:
            /* NULL */
            break;

         /* requestDenied */
         case 3:
            /* NULL */
            break;

         /* undefinedReason */
         case 4:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* securityDenial */
         case 5:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* aliasesInconsistent */
         case 6:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* routeCalltoSCN */
         case 7:
            stat = asn1PE_H225_SeqOfH225PartyNumber (&lctxt, *pvalue->u.routeCalltoSCN);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* resourceUnavailable */
         case 8:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* genericDataReason */
         case 9:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* neededFeatureNotSupported */
         case 10:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* hopCountExceeded */
         case 11:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* incompleteAddress */
         case 12:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* securityError */
         case 13:
            stat = asn1PE_H225SecurityErrors2 (&lctxt, pvalue->u.securityError);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* securityDHmismatch */
         case 14:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* noRouteToDestination */
         case 15:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* unallocatedNumber */
         case 16:
            /* NULL */
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  LocationReject                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225LocationReject (OOCTXT* pctxt, H225LocationReject* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.altGKInfoPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.featureSetPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->m.serviceControlPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode rejectReason */

   stat = asn1PE_H225LocationRejectReason (pctxt, &pvalue->rejectReason);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 6);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.altGKInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.serviceControlPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.altGKInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225AltGKInfo (&lctxt, &pvalue->altGKInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.serviceControlPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ServiceControlSession (&lctxt, pvalue->serviceControl);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  InfoRequest                                               */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225InfoRequest (OOCTXT* pctxt, H225InfoRequest* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.callIdentifierPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.uuiesRequestedPresent ||
   pvalue->m.callLinkagePresent ||
   pvalue->m.usageInfoRequestedPresent ||
   pvalue->m.segmentedResponseSupportedPresent ||
   pvalue->m.nextSegmentRequestedPresent ||
   pvalue->m.capacityInfoRequestedPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.replyAddressPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callReferenceValue */

   stat = asn1PE_H225CallReferenceValue (pctxt, pvalue->callReferenceValue);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode replyAddress */

   if (pvalue->m.replyAddressPresent) {
      stat = asn1PE_H225TransportAddress (pctxt, &pvalue->replyAddress);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 10);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.uuiesRequestedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callLinkagePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.usageInfoRequestedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.segmentedResponseSupportedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nextSegmentRequestedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityInfoRequestedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.callIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallIdentifier (&lctxt, &pvalue->callIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.uuiesRequestedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225UUIEsRequested (&lctxt, &pvalue->uuiesRequested);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.callLinkagePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallLinkage (&lctxt, &pvalue->callLinkage);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.usageInfoRequestedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225RasUsageInfoTypes (&lctxt, &pvalue->usageInfoRequested);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.segmentedResponseSupportedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.nextSegmentRequestedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeConsUnsigned (&lctxt, pvalue->nextSegmentRequested, 0U, 65535U);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.capacityInfoRequestedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         /* NULL */

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225RTPSession                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225RTPSession (OOCTXT* pctxt, H225_SeqOfH225RTPSession value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225RTPSession (pctxt, ((H225RTPSession*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225TransportChannelInfo                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225TransportChannelInfo (OOCTXT* pctxt, H225_SeqOfH225TransportChannelInfo value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225TransportChannelInfo (pctxt, ((H225TransportChannelInfo*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225ConferenceIdentifier                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225ConferenceIdentifier (OOCTXT* pctxt, H225_SeqOfH225ConferenceIdentifier* pvalue)
{
   int stat = ASN_OK;
   ASN1UINT xx1;

   /* encode length determinant */

   stat = encodeLength (pctxt, pvalue->n);
   if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

   /* encode elements */

   for (xx1 = 0; xx1 < pvalue->n; xx1++) {
      stat = asn1PE_H225ConferenceIdentifier (pctxt, &pvalue->elem[xx1]);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  InfoRequestResponse_perCallInfo_element_pdu_element       */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225InfoRequestResponse_perCallInfo_element_pdu_element (OOCTXT* pctxt, H225InfoRequestResponse_perCallInfo_element_pdu_element* pvalue)
{
   int stat = ASN_OK;

   /* encode h323pdu */

   stat = asn1PE_H225H323_UU_PDU (pctxt, &pvalue->h323pdu);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode sent */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->sent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225InfoRequestResponse_perCallInfo_element_pdu_el  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225InfoRequestResponse_perCallInfo_element_pdu_element (OOCTXT* pctxt, H225_SeqOfH225InfoRequestResponse_perCallInfo_element_pdu_element value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225InfoRequestResponse_perCallInfo_element_pdu_element (pctxt, ((H225InfoRequestResponse_perCallInfo_element_pdu_element*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  InfoRequestResponse_perCallInfo_element                   */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225InfoRequestResponse_perCallInfo_element (OOCTXT* pctxt, H225InfoRequestResponse_perCallInfo_element* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.callIdentifierPresent ||
   pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.substituteConfIDsPresent ||
   pvalue->m.pduPresent ||
   pvalue->m.callLinkagePresent ||
   pvalue->m.usageInformationPresent ||
   pvalue->m.circuitInfoPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.originatorPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.audioPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.videoPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.dataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode callReferenceValue */

   stat = asn1PE_H225CallReferenceValue (pctxt, pvalue->callReferenceValue);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode conferenceID */

   stat = asn1PE_H225ConferenceIdentifier (pctxt, &pvalue->conferenceID);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode originator */

   if (pvalue->m.originatorPresent) {
      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->originator);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode audio */

   if (pvalue->m.audioPresent) {
      stat = asn1PE_H225_SeqOfH225RTPSession (pctxt, pvalue->audio);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode video */

   if (pvalue->m.videoPresent) {
      stat = asn1PE_H225_SeqOfH225RTPSession (pctxt, pvalue->video);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode data */

   if (pvalue->m.dataPresent) {
      stat = asn1PE_H225_SeqOfH225TransportChannelInfo (pctxt, pvalue->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode h245 */

   stat = asn1PE_H225TransportChannelInfo (pctxt, &pvalue->h245);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callSignaling */

   stat = asn1PE_H225TransportChannelInfo (pctxt, &pvalue->callSignaling);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callType */

   stat = asn1PE_H225CallType (pctxt, &pvalue->callType);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode bandWidth */

   stat = asn1PE_H225BandWidth (pctxt, pvalue->bandWidth);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callModel */

   stat = asn1PE_H225CallModel (pctxt, &pvalue->callModel);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callIdentifierPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.substituteConfIDsPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.pduPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callLinkagePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.usageInformationPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.circuitInfoPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.callIdentifierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallIdentifier (&lctxt, &pvalue->callIdentifier);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.substituteConfIDsPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ConferenceIdentifier (&lctxt, &pvalue->substituteConfIDs);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.pduPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225InfoRequestResponse_perCallInfo_element_pdu_element (&lctxt, pvalue->pdu);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.callLinkagePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallLinkage (&lctxt, &pvalue->callLinkage);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.usageInformationPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225RasUsageInformation (&lctxt, &pvalue->usageInformation);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.circuitInfoPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CircuitInfo (&lctxt, &pvalue->circuitInfo);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225InfoRequestResponse_perCallInfo_element         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225InfoRequestResponse_perCallInfo_element (OOCTXT* pctxt, H225_SeqOfH225InfoRequestResponse_perCallInfo_element value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225InfoRequestResponse_perCallInfo_element (pctxt, ((H225InfoRequestResponse_perCallInfo_element*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  InfoRequestResponseStatus                                 */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225InfoRequestResponseStatus (OOCTXT* pctxt, H225InfoRequestResponseStatus* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 4);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* complete */
         case 1:
            /* NULL */
            break;

         /* incomplete */
         case 2:
            /* NULL */
            break;

         /* segment */
         case 3:
            stat = encodeConsUnsigned (pctxt, pvalue->u.segment, 0U, 65535U);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

            break;

         /* invalidCall */
         case 4:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 5);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  InfoRequestResponse                                       */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225InfoRequestResponse (OOCTXT* pctxt, H225InfoRequestResponse* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.needResponsePresent ||
   pvalue->m.capacityPresent ||
   pvalue->m.irrStatusPresent ||
   pvalue->m.unsolicitedPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.endpointAliasPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.perCallInfoPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode endpointType */

   stat = asn1PE_H225EndpointType (pctxt, &pvalue->endpointType);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode endpointIdentifier */

   stat = asn1PE_H225EndpointIdentifier (pctxt, pvalue->endpointIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode rasAddress */

   stat = asn1PE_H225TransportAddress (pctxt, &pvalue->rasAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callSignalAddress */

   stat = asn1PE_H225_SeqOfH225TransportAddress (pctxt, pvalue->callSignalAddress);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode endpointAlias */

   if (pvalue->m.endpointAliasPresent) {
      stat = asn1PE_H225_SeqOfH225AliasAddress (pctxt, pvalue->endpointAlias);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode perCallInfo */

   if (pvalue->m.perCallInfoPresent) {
      stat = asn1PE_H225_SeqOfH225InfoRequestResponse_perCallInfo_element (pctxt, pvalue->perCallInfo);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 7);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.needResponsePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.irrStatusPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.unsolicitedPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.needResponsePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->needResponse);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.capacityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallCapacity (&lctxt, &pvalue->capacity);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.irrStatusPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225InfoRequestResponseStatus (&lctxt, &pvalue->irrStatus);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.unsolicitedPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeBit (&lctxt, (ASN1BOOL)pvalue->unsolicited);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  NonStandardMessage                                        */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225NonStandardMessage (OOCTXT* pctxt, H225NonStandardMessage* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.featureSetPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.featureSetPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225FeatureSet (&lctxt, &pvalue->featureSet);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  UnknownMessageResponse                                    */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225UnknownMessageResponse (OOCTXT* pctxt, H225UnknownMessageResponse* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.tokensPresent ||
   pvalue->m.cryptoTokensPresent ||
   pvalue->m.integrityCheckValuePresent ||
   pvalue->m.messageNotUnderstoodPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 3);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.messageNotUnderstoodPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.tokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225ClearToken (&lctxt, pvalue->tokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.cryptoTokensPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225CryptoH323Token (&lctxt, pvalue->cryptoTokens);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.integrityCheckValuePresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225ICV (&lctxt, &pvalue->integrityCheckValue);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.messageNotUnderstoodPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeOctetString (&lctxt, pvalue->messageNotUnderstood.numocts, pvalue->messageNotUnderstood.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RequestInProgress                                         */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RequestInProgress (OOCTXT* pctxt, H225RequestInProgress* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode tokens */

   if (pvalue->m.tokensPresent) {
      stat = asn1PE_H225_SeqOfH225ClearToken (pctxt, pvalue->tokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode cryptoTokens */

   if (pvalue->m.cryptoTokensPresent) {
      stat = asn1PE_H225_SeqOfH225CryptoH323Token (pctxt, pvalue->cryptoTokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode integrityCheckValue */

   if (pvalue->m.integrityCheckValuePresent) {
      stat = asn1PE_H225ICV (pctxt, &pvalue->integrityCheckValue);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode delay */

   if ( (pvalue->delay >= 1) ) {
      stat = encodeConsUnsigned (pctxt, pvalue->delay, 1U, 65535U);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }
   else
      return LOG_ASN1ERR (pctxt, ASN_E_CONSVIO);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ResourcesAvailableIndicate                                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ResourcesAvailableIndicate (OOCTXT* pctxt, H225ResourcesAvailableIndicate* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.capacityPresent ||
   pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode endpointIdentifier */

   stat = asn1PE_H225EndpointIdentifier (pctxt, pvalue->endpointIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocols */

   stat = asn1PE_H225_SeqOfH225SupportedProtocols (pctxt, pvalue->protocols);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode almostOutOfResources */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->almostOutOfResources);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode tokens */

   if (pvalue->m.tokensPresent) {
      stat = asn1PE_H225_SeqOfH225ClearToken (pctxt, pvalue->tokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode cryptoTokens */

   if (pvalue->m.cryptoTokensPresent) {
      stat = asn1PE_H225_SeqOfH225CryptoH323Token (pctxt, pvalue->cryptoTokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode integrityCheckValue */

   if (pvalue->m.integrityCheckValuePresent) {
      stat = asn1PE_H225ICV (pctxt, &pvalue->integrityCheckValue);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count + 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.capacityPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.capacityPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225CallCapacity (&lctxt, &pvalue->capacity);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ResourcesAvailableConfirm                                 */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ResourcesAvailableConfirm (OOCTXT* pctxt, H225ResourcesAvailableConfirm* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->m.genericDataPresent ||
   pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode protocolIdentifier */

   stat = asn1PE_H225ProtocolIdentifier (pctxt, pvalue->protocolIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode tokens */

   if (pvalue->m.tokensPresent) {
      stat = asn1PE_H225_SeqOfH225ClearToken (pctxt, pvalue->tokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode cryptoTokens */

   if (pvalue->m.cryptoTokensPresent) {
      stat = asn1PE_H225_SeqOfH225CryptoH323Token (pctxt, pvalue->cryptoTokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode integrityCheckValue */

   if (pvalue->m.integrityCheckValuePresent) {
      stat = asn1PE_H225ICV (pctxt, &pvalue->integrityCheckValue);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->m.genericDataPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = asn1PE_H225_SeqOfH225GenericData (&lctxt, pvalue->genericData);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) {
            freeContext (&lctxt);
            return LOG_ASN1ERR (pctxt, stat);
         }

         freeContext (&lctxt);
      }

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  InfoRequestAck                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225InfoRequestAck (OOCTXT* pctxt, H225InfoRequestAck* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode tokens */

   if (pvalue->m.tokensPresent) {
      stat = asn1PE_H225_SeqOfH225ClearToken (pctxt, pvalue->tokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode cryptoTokens */

   if (pvalue->m.cryptoTokensPresent) {
      stat = asn1PE_H225_SeqOfH225CryptoH323Token (pctxt, pvalue->cryptoTokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode integrityCheckValue */

   if (pvalue->m.integrityCheckValuePresent) {
      stat = asn1PE_H225ICV (pctxt, &pvalue->integrityCheckValue);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  InfoRequestNakReason                                      */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225InfoRequestNakReason (OOCTXT* pctxt, H225InfoRequestNakReason* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 3);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 2);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* notRegistered */
         case 1:
            /* NULL */
            break;

         /* securityDenial */
         case 2:
            /* NULL */
            break;

         /* undefinedReason */
         case 3:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* securityError */
         case 4:
            stat = asn1PE_H225SecurityErrors2 (&lctxt, pvalue->u.securityError);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  InfoRequestNak                                            */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225InfoRequestNak (OOCTXT* pctxt, H225InfoRequestNak* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.altGKInfoPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode nakReason */

   stat = asn1PE_H225InfoRequestNakReason (pctxt, &pvalue->nakReason);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode altGKInfo */

   if (pvalue->m.altGKInfoPresent) {
      stat = asn1PE_H225AltGKInfo (pctxt, &pvalue->altGKInfo);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode tokens */

   if (pvalue->m.tokensPresent) {
      stat = asn1PE_H225_SeqOfH225ClearToken (pctxt, pvalue->tokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode cryptoTokens */

   if (pvalue->m.cryptoTokensPresent) {
      stat = asn1PE_H225_SeqOfH225CryptoH323Token (pctxt, pvalue->cryptoTokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode integrityCheckValue */

   if (pvalue->m.integrityCheckValuePresent) {
      stat = asn1PE_H225ICV (pctxt, &pvalue->integrityCheckValue);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ServiceControlIndication_callSpecific                     */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ServiceControlIndication_callSpecific (OOCTXT* pctxt, H225ServiceControlIndication_callSpecific* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode callIdentifier */

   stat = asn1PE_H225CallIdentifier (pctxt, &pvalue->callIdentifier);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode conferenceID */

   stat = asn1PE_H225ConferenceIdentifier (pctxt, &pvalue->conferenceID);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode answeredCall */

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->answeredCall);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ServiceControlIndication                                  */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ServiceControlIndication (OOCTXT* pctxt, H225ServiceControlIndication* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.endpointIdentifierPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.callSpecificPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode serviceControl */

   stat = asn1PE_H225_SeqOfH225ServiceControlSession (pctxt, pvalue->serviceControl);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode endpointIdentifier */

   if (pvalue->m.endpointIdentifierPresent) {
      stat = asn1PE_H225EndpointIdentifier (pctxt, pvalue->endpointIdentifier);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode callSpecific */

   if (pvalue->m.callSpecificPresent) {
      stat = asn1PE_H225ServiceControlIndication_callSpecific (pctxt, &pvalue->callSpecific);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode tokens */

   if (pvalue->m.tokensPresent) {
      stat = asn1PE_H225_SeqOfH225ClearToken (pctxt, pvalue->tokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode cryptoTokens */

   if (pvalue->m.cryptoTokensPresent) {
      stat = asn1PE_H225_SeqOfH225CryptoH323Token (pctxt, pvalue->cryptoTokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode integrityCheckValue */

   if (pvalue->m.integrityCheckValuePresent) {
      stat = asn1PE_H225ICV (pctxt, &pvalue->integrityCheckValue);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode featureSet */

   if (pvalue->m.featureSetPresent) {
      stat = asn1PE_H225FeatureSet (pctxt, &pvalue->featureSet);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode genericData */

   if (pvalue->m.genericDataPresent) {
      stat = asn1PE_H225_SeqOfH225GenericData (pctxt, pvalue->genericData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ServiceControlResponse_result                             */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ServiceControlResponse_result (OOCTXT* pctxt, H225ServiceControlResponse_result* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 5);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 4);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* started */
         case 1:
            /* NULL */
            break;

         /* failed */
         case 2:
            /* NULL */
            break;

         /* stopped */
         case 3:
            /* NULL */
            break;

         /* notAvailable */
         case 4:
            /* NULL */
            break;

         /* neededFeatureNotSupported */
         case 5:
            /* NULL */
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 6);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      stat = encodeOpenType (pctxt, pvalue->u.extElem1->numocts, pvalue->u.extElem1->data);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  ServiceControlResponse                                    */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225ServiceControlResponse (OOCTXT* pctxt, H225ServiceControlResponse* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->extElem1.count > 0);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.resultPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.featureSetPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->m.genericDataPresent);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode requestSeqNum */

   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   /* encode result */

   if (pvalue->m.resultPresent) {
      stat = asn1PE_H225ServiceControlResponse_result (pctxt, &pvalue->result);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode nonStandardData */

   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode tokens */

   if (pvalue->m.tokensPresent) {
      stat = asn1PE_H225_SeqOfH225ClearToken (pctxt, pvalue->tokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode cryptoTokens */

   if (pvalue->m.cryptoTokensPresent) {
      stat = asn1PE_H225_SeqOfH225CryptoH323Token (pctxt, pvalue->cryptoTokens);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode integrityCheckValue */

   if (pvalue->m.integrityCheckValuePresent) {
      stat = asn1PE_H225ICV (pctxt, &pvalue->integrityCheckValue);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode featureSet */

   if (pvalue->m.featureSetPresent) {
      stat = asn1PE_H225FeatureSet (pctxt, &pvalue->featureSet);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   /* encode genericData */

   if (pvalue->m.genericDataPresent) {
      stat = asn1PE_H225_SeqOfH225GenericData (pctxt, pvalue->genericData);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
   }

   if (extbit) {

      /* encode extension optional bits length */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->extElem1.count - 1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode optional bits */

      stat = encodeOpenTypeExtBits (pctxt, &pvalue->extElem1);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* encode extension elements */

      if (pvalue->extElem1.count > 0) {
         stat = encodeOpenTypeExt (pctxt, &pvalue->extElem1);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  _SeqOfH225AdmissionConfirm                                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225_SeqOfH225AdmissionConfirm (OOCTXT* pctxt, H225_SeqOfH225AdmissionConfirm value)
{
   int stat = ASN_OK;
   DListNode* pnode;
   ASN1UINT xx1;
   ASN1UINT enclen, fraglen;

   enclen = fraglen = xx1 = 0;
   pnode = value.head;
   for (;;) {
      /* encode length determinant */

      stat = encodeLength (pctxt, (value.count - enclen));
      if (stat < 0) return LOG_ASN1ERR (pctxt, stat);

      fraglen = stat;
      enclen += fraglen;
      /* encode elements */

      for (; xx1 < enclen; xx1++) {
         stat = asn1PE_H225AdmissionConfirm (pctxt, ((H225AdmissionConfirm*)pnode->data));
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
         pnode = pnode->next;
      }
      if ( value.count == enclen && fraglen < 16384) {
         break;
      }
   }

   return (stat);
}

/**************************************************************/
/*                                                            */
/*  RasMessage                                                */
/*                                                            */
/**************************************************************/

EXTERN int asn1PE_H225RasMessage (OOCTXT* pctxt, H225RasMessage* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;

   /* extension bit */

   extbit = (ASN1BOOL)(pvalue->t > 25);

   stat = encodeBit (pctxt, extbit);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

   if (!extbit) {

      /* Encode choice index value */

      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 24);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode root element data value */

      switch (pvalue->t)
      {
         /* gatekeeperRequest */
         case 1:
            stat = asn1PE_H225GatekeeperRequest (pctxt, pvalue->u.gatekeeperRequest);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* gatekeeperConfirm */
         case 2:
            stat = asn1PE_H225GatekeeperConfirm (pctxt, pvalue->u.gatekeeperConfirm);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* gatekeeperReject */
         case 3:
            stat = asn1PE_H225GatekeeperReject (pctxt, pvalue->u.gatekeeperReject);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* registrationRequest */
         case 4:
            stat = asn1PE_H225RegistrationRequest (pctxt, pvalue->u.registrationRequest);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* registrationConfirm */
         case 5:
            stat = asn1PE_H225RegistrationConfirm (pctxt, pvalue->u.registrationConfirm);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* registrationReject */
         case 6:
            stat = asn1PE_H225RegistrationReject (pctxt, pvalue->u.registrationReject);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* unregistrationRequest */
         case 7:
            stat = asn1PE_H225UnregistrationRequest (pctxt, pvalue->u.unregistrationRequest);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* unregistrationConfirm */
         case 8:
            stat = asn1PE_H225UnregistrationConfirm (pctxt, pvalue->u.unregistrationConfirm);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* unregistrationReject */
         case 9:
            stat = asn1PE_H225UnregistrationReject (pctxt, pvalue->u.unregistrationReject);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* admissionRequest */
         case 10:
            stat = asn1PE_H225AdmissionRequest (pctxt, pvalue->u.admissionRequest);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* admissionConfirm */
         case 11:
            stat = asn1PE_H225AdmissionConfirm (pctxt, pvalue->u.admissionConfirm);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* admissionReject */
         case 12:
            stat = asn1PE_H225AdmissionReject (pctxt, pvalue->u.admissionReject);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* bandwidthRequest */
         case 13:
            stat = asn1PE_H225BandwidthRequest (pctxt, pvalue->u.bandwidthRequest);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* bandwidthConfirm */
         case 14:
            stat = asn1PE_H225BandwidthConfirm (pctxt, pvalue->u.bandwidthConfirm);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* bandwidthReject */
         case 15:
            stat = asn1PE_H225BandwidthReject (pctxt, pvalue->u.bandwidthReject);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* disengageRequest */
         case 16:
            stat = asn1PE_H225DisengageRequest (pctxt, pvalue->u.disengageRequest);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* disengageConfirm */
         case 17:
            stat = asn1PE_H225DisengageConfirm (pctxt, pvalue->u.disengageConfirm);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* disengageReject */
         case 18:
            stat = asn1PE_H225DisengageReject (pctxt, pvalue->u.disengageReject);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* locationRequest */
         case 19:
            stat = asn1PE_H225LocationRequest (pctxt, pvalue->u.locationRequest);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* locationConfirm */
         case 20:
            stat = asn1PE_H225LocationConfirm (pctxt, pvalue->u.locationConfirm);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* locationReject */
         case 21:
            stat = asn1PE_H225LocationReject (pctxt, pvalue->u.locationReject);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* infoRequest */
         case 22:
            stat = asn1PE_H225InfoRequest (pctxt, pvalue->u.infoRequest);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* infoRequestResponse */
         case 23:
            stat = asn1PE_H225InfoRequestResponse (pctxt, pvalue->u.infoRequestResponse);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* nonStandardMessage */
         case 24:
            stat = asn1PE_H225NonStandardMessage (pctxt, pvalue->u.nonStandardMessage);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         /* unknownMessageResponse */
         case 25:
            stat = asn1PE_H225UnknownMessageResponse (pctxt, pvalue->u.unknownMessageResponse);
            if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);
            break;

         default:
            return LOG_ASN1ERR (pctxt, ASN_E_INVOPT);
      }
   }
   else {
      /* Encode extension choice index value */

      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 26);
      if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

      /* Encode extension element data value */

      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      switch (pvalue->t)
      {
         /* requestInProgress */
         case 26:
            stat = asn1PE_H225RequestInProgress (&lctxt, pvalue->u.requestInProgress);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* resourcesAvailableIndicate */
         case 27:
            stat = asn1PE_H225ResourcesAvailableIndicate (&lctxt, pvalue->u.resourcesAvailableIndicate);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* resourcesAvailableConfirm */
         case 28:
            stat = asn1PE_H225ResourcesAvailableConfirm (&lctxt, pvalue->u.resourcesAvailableConfirm);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* infoRequestAck */
         case 29:
            stat = asn1PE_H225InfoRequestAck (&lctxt, pvalue->u.infoRequestAck);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* infoRequestNak */
         case 30:
            stat = asn1PE_H225InfoRequestNak (&lctxt, pvalue->u.infoRequestNak);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* serviceControlIndication */
         case 31:
            stat = asn1PE_H225ServiceControlIndication (&lctxt, pvalue->u.serviceControlIndication);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* serviceControlResponse */
         case 32:
            stat = asn1PE_H225ServiceControlResponse (&lctxt, pvalue->u.serviceControlResponse);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         /* admissionConfirmSequence */
         case 33:
            stat = asn1PE_H225_SeqOfH225AdmissionConfirm (&lctxt, *pvalue->u.admissionConfirmSequence);
            if (stat != ASN_OK) {
               freeContext (&lctxt);
               return LOG_ASN1ERR (pctxt, stat);
            }
            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            openType.numocts = pvalue->u.extElem1->numocts;
            openType.data = pvalue->u.extElem1->data;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) {
         freeContext (&lctxt);
         return LOG_ASN1ERR (pctxt, stat);
      }

      freeContext (&lctxt);
   }

   return (stat);
}

