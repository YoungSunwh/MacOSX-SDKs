/*
	File:		DirServicesConst.h

	Contains:	xxx put contents here xxx

	Copyright:	? 1998-2000 by Apple Computer, Inc., all rights reserved.

	NOT_FOR_OPEN_SOURCE <to be reevaluated at a later time>
*/

#ifndef __DirServicesConst_h__
#define	__DirServicesConst_h__	1

//-----------------------------------------------
// Well Known Attribute Type Constants..
// can be used with dsDataNodeAllocate() to create an Attribute Type Node
//	Legend:
//		eDS1xxxxxx  Single Valued Attribute
//		eDSNxxxxxx  Multi-Valued Attribute
//
//	NOTE: Access controls may prevent any particular client from reading/writting
//			various attributes.  In addition some attributes may not be stored at
//			all and could represent "real-time" data generated by the Directory Node
//			plug-in.
//	NOTE #2:	Attributes in the model are available for records & Directory Nodes.
//

// all records
#define		kDSRecordsAll					"dsRecordsAll"
#define		kDSRecordsStandardAll			"dsRecordsStandardAll"
#define		kDSRecordsNativeAll				"dsRecordsNativeAll"

// all attributes
#define		kDSAttributesAll				"dsAttributesAll"
#define		kDSAttributesStandardAll		"dsAttributesStandardAll"
#define		kDSAttributesNativeAll			"dsAttributesNativeAll"

// well known Record types
#define		kDSStdRecordTypePrefix			"dsRecTypeStandard:"
#define		kDSNativeRecordTypePrefix		"dsRecTypeNative:"

#define		kDSStdRecordTypeUsers			"dsRecTypeStandard:Users"
#define		kDSStdRecordTypeUserAliases		"dsRecTypeStandard:UserAliases"
#define		kDSStdRecordTypeGroups			"dsRecTypeStandard:Groups"
#define		kDSStdRecordTypeGroupAliases	"dsRecTypeStandard:GroupAliases"
#define		kDSStdRecordTypeMachines		"dsRecTypeStandard:Machines"
#define		kDSStdRecordTypeAliases			"dsRecTypeStandard:Aliases"
#define		kDSStdRecordTypeHosts			"dsRecTypeStandard:Hosts"
#define		kDSStdRecordTypePrinters		"dsRecTypeStandard:Printers"
#define		kDSStdRecordTypeNetworks		"dsRecTypeStandard:Networks"
#define		kDSStdRecordTypeServices		"dsRecTypeStandard:Services"
#define		kDSStdRecordTypeServer			"dsRecTypeStandard:Server"
#define		kDSStdRecordTypProtocols		"dsRecTypeStandard:Protocols"
#define		kDSStdRecordTypeProtocols		"dsRecTypeStandard:Protocols"
#define		kDSStdRecordTypRPC				"dsRecTypeStandard:RPC"
#define		kDSStdRecordTypeRPC				"dsRecTypeStandard:RPC"
#define		kDSStdRecordTypePrintService	"dsRecTypeStandard:PrintService"
#define		kDSStdRecordTypeConfig			"dsRecTypeStandard:Config"
#define		kDSStdRecordTypeAFPServer		"dsRecTypeStandard:AFPServer"
#define		kDSStdRecordTypeSMBServer		"dsRecTypeStandard:SMBServer"
#define		kDSStdRecordTypeFTPServer		"dsRecTypeStandard:FTPServer"
#define		kDSStdRecordTypeNFS				"dsRecTypeStandard:NFS"
#define		kDSStdRecordTypeWebServer		"dsRecTypeStandard:WebServer"
#define		kDSStdRecordTypeLDAPServer		"dsRecTypeStandard:LDAPServer"
#define		kDSStdRecordTypeQTSServer		"dsRecTypeStandard:QTSServer"
#define		kDSStdRecordTypMounts			"dsRecTypeStandard:Mounts"
#define		kDSStdRecordTypeMounts			"dsRecTypeStandard:Mounts"

#define		kDSStdRecordTypeAFPUserAliases	"dsRecTypeStandard:AFPUserAliases"

#define		kDSStdUserNamesMeta				"dsRecTypeStandard:MetaUserNames"
#define		kDSStdRecordTypeMeta			"dsRecTypeStandard:AppleMetaRecord"

// well know Attribute Types...
#define		kDSStdAttrTypePrefix			"dsAttrTypeStandard:"
#define		kDSNativeAttrTypePrefix			"dsAttrTypeNative:"

#define		kDSAttrNone						"dsNone"

// authentication methods
#define		kDSStdAuthMethodPrefix				"dsAuthMethodStandard:"
#define		kDSNativeAuthMethodPrefix			"dsAuthMethodNative:"

#define		kDSStdAuthClearText					"dsAuthMethodStandard:dsAuthClearText"
#define		kDSStdAuthCrypt						"dsAuthMethodStandard:dsAuthCrypt"
#define		kDSStdAuthSetPasswd					"dsAuthMethodStandard:dsAuthSetPasswd"
#define		kDSStdAuthChangePasswd				"dsAuthMethodStandard:dsAuthChangePasswd"
#define		kDSStdAuthSetPasswdAsRoot			"dsAuthMethodStandard:dsAuthSetPasswdAsRoot"
#define		kDSStdAuthAPOP						"dsAuthMethodStandard:dsAuthAPOP"
#define		kDSStdAuth2WayRandom				"dsAuthMethodStandard:dsAuth2WayRandom"
#define		kDSStdAuthNodeNativeClearTextOK		"dsAuthMethodStandard:dsAuthNodeNativeCanUseClearText"
#define		kDSStdAuthNodeNativeNoClearText		"dsAuthMethodStandard:dsAuthNodeNativeCannotUseClearText"
#define		kDSStdAuthSMB_NT_Key				"dsAuthMethodStandard:dsAuthSMBNTKey"
#define		kDSStdAuthSMB_LM_Key				"dsAuthMethodStandard:dsAuthSMBLMKey"

// Users distinguished or real name
#define		kDS1AttrDistinguishedName		"dsAttrTypeStandard:RealName"

// All possible names for a record
#define		kDSNAttrAllNames				"dsAttrTypeStandard:AllNames"

// set password methods
#define		kDSSetPasswdBestOf				"dsSetPasswdBestOf"

//	Single Valued Attribute
#define		kDS1AttrPassword				"dsAttrTypeStandard:Password"
#define		kDS1AttrPasswordPlus			"dsAttrTypeStandard:PasswordPlus"
#define		kDS1AttrAuthenticationHint 		"dsAttrTypeStandard:AuthenticationHint"
#define		kDS1AttrInternetAlias  			"dsAttrTypeStandard:InetAlias"
#define		kDS1AttrNFSHomeDirectory		"dsAttrTypeStandard:NFSHomeDirectory"
#define		kDS1AttrUniqueID				"dsAttrTypeStandard:UniqueID"
#define		kDS1AttrPrimaryGroupID			"dsAttrTypeStandard:PrimaryGroupID"
#define		kDS1AttrMailAttribute			"dsAttrTypeStandard:MailAttribute"
#define		kDS1AttrComment					"dsAttrTypeStandard:Comment"
#define		kDS1AttrRARA					"dsAttrTypeStandard:RARA"
#define		kDS1AttrGeneratedUID			"dsAttrTypeStandard:GeneratedUID"
#define		kDS1AttrAdminStatus				"dsAttrTypeStandard:AdminStatus"
#define		kDS1AttrPwdAgingPolicy			"dsAttrTypeStandard:PwdAgingPolicy"
#define		kDS1AttrUserShell				"dsAttrTypeStandard:UserShell"
#define		kDS1AttrVFSType					"dsAttrTypeStandard:VFSType"
#define		kDS1AttrVFSPassNo				"dsAttrTypeStandard:VFSPassNo"
#define		kDS1AttrVFSDumpFreq				"dsAttrTypeStandard:VFSDumpFreq"
#define		kDS1AttrVFSLinkDir				"dsAttrTypeStandard:VFSLinkDir"
#define		kDS1AttrChange					"dsAttrTypeStandard:Change"
#define		kDS1AttrExpire					"dsAttrTypeStandard:Expire"

#define		kDSNAttrRecordAlias				"dsAttrTypeStandard:RecordAlias"
#define		kDSNAttrGroupMembership			"dsAttrTypeStandard:GroupMembership"
#define		kDSNAttrHomeDirectory			"dsAttrTypeStandard:HomeDirectory"
#define		kDSNAttrEMailAddress			"dsAttrTypeStandard:EMailAddress"
#define		kDSNAttrPhoneNumber				"dsAttrTypeStandard:PhoneNumber"
#define		kDSNAttrProtocols				"dsAttrTypeStandard:Protocols"
#define		kDSNAttrVFSOpts					"dsAttrTypeStandard:VFSOpts"

// Mutivalued meta attribute data
#define		kDSNAttrMetaNodeLocation		"dsAttrTypeStandard:AppleMetaNodeLocation"
#define		kStandardTargetAlias			"dsAttrTypeStandard:AppleMetaAliasTarget"
#define		kStandardSourceAlias			"dsAttrTypeStandard:AppleMetaAliasSource"

#define		kDS1AttrAliasData				"dsAttrTypeStandard:AppleAliasData"

//	Single Valued - checksum/meta data
#define		kDS1AttrDataStamp				"dsAttrTypeStandard:DataStamp"
#define		kDS1AttrTotalSize				"dsAttrTypeStandard:TotalSize"

//	Single Valued - data of Create, Modify, Backup time in UTC
#define		kDS1AttrTimePackage				"dsAttrTypeStandard:TimePackage"

//  Single Valued - alias attribute, contain pointer to another node/record/attribute
#define		kDS1AttrAlias					"dsAttrTypeStandard:Alias"

//	Single valued - used to get a "auth" credential, to be used to authenticate
//		to other Directory nodes.
#define		kDS1AttrAuthCredential		"dsAttrTypeStandard:AuthCredential"

//	used with directory nodes so that clients can "discover" the
//	API capabilities for this Directory Node.
#define		kDS1AttrCapabilities		"dsAttrTypeStandard:Capabilities"

// can be found using dsGetDirNodeInfo and will return one of
// ReadOnly, ReadWrite, or WriteOnly strings
// note that ReadWrite does not imply fully readable or writable
#define		kDS1AttrReadOnlyNode		"dsAttrTypeStandard:ReadOnlyNode"

//	used with Search Node to  "discover" the search path for this node
#define		kDS1AttrSearchPath			"dsAttrTypeStandard:SearchPath"
#define		kDSNAttrSearchPath			"dsAttrTypeStandard:SearchPath"
//	used with Search Node to "discover" the search policy for this node
#define		kDS1AttrSearchPolicy			"dsAttrTypeStandard:SearchPolicy"
//	used with Search Node to "discover" the possible search paths for this node
#define		kDS1AttrNSPSearchPath			"dsAttrTypeStandard:NSPSearchPath"
#define		kDSNAttrNSPSearchPath			"dsAttrTypeStandard:NSPSearchPath"
#define		kDS1AttrLSPSearchPath			"dsAttrTypeStandard:LSPSearchPath"
#define		kDSNAttrLSPSearchPath			"dsAttrTypeStandard:LSPSearchPath"
#define		kDS1AttrCSPSearchPath			"dsAttrTypeStandard:CSPSearchPath"
#define		kDSNAttrCSPSearchPath			"dsAttrTypeStandard:CSPSearchPath"

//	force the directory service to generate a binary image of the
//	record and all it's attributes.
#define		kDS1AttrRecordImage			"dsAttrTypeStandard:RecordImage"

//	Information (version, signature, about, credits..ect.) about the plug-in that
//	is actually servicing a particular directory node.
#define		kDSNAttrPlugInInfo			"dsAttrTypeStandard:PlugInInfo"

//	Multivalued Attribute, list of names/keys for this record
#define		kDSNAttrRecordName			"dsAttrTypeStandard:RecordName"

//	Multivalued - list of attribute types
#define		kDSNAttrSchema				"dsAttrTypeStandard:Scheama"

//	Single Valued for a Record, Multi-valued for a Directory Node
#define		kDSNAttrRecordType			"dsAttrTypeStandard:RecordType"

#define		kDSNAttrNodePath			"dsAttrTypeStandard:NodePath"

#define		kDSNAttrAuthMethod			"dsAttrTypeStandard:AuthMethod"

#define		kDSNAttrSetPasswdMethod		"dsAttrTypeStandard:SetPasswdMethod"

//	Multivalued - list of group records
#define		kDSNAttrGroup				"dsAttrTypeStandard:Group"

//	Multivalued - list of member records
#define		kDSNAttrMember				"dsAttrTypeStandard:Member"

#define		kDSNAttrURL					"dsAttrTypeStandard:URL"

//	data contained in this attribute type is a fully qualified MIME Type.
#define		kDSNAttrMIME				"dsAttrTypeStandard:MIME"
#define		kDSNAttrHTML				"dsAttrTypeStandard:HTML"

#define		kDSNAttrNBPEntry			"dsAttrTypeStandard:NBPEntry"
#define		kDSNAttrDNSName				"dsAttrTypeStandard:DNSName"
#define		kDSNAttrIPAddress			"dsAttrTypeStandard:IPAddress"

#define		kDSNAttrPGPPublicKey		"dsAttrTypeStandard:PGPPublicKey"
#define		kDSNAttrEMailAddress		"dsAttrTypeStandard:EMailAddress"

#define		kDSNAttrPhoneNumber			"dsAttrTypeStandard:PhoneNumber"
#define		kDSNAttrPostalAddress		"dsAttrTypeStandard:PostalAddress"

// NSL
#define		kDSNAttrURLForNSL			"dsAttrTypeStandard:URLForNSL"

// Print
#define		kDS1AttrPrintServiceInfoXML		"dsAttrTypeStandard:PrintServiceInfoXML"
#define		kDS1AttrPrintServiceInfoText	"dsAttrTypeStandard:PrintServiceInfoText"

#endif
