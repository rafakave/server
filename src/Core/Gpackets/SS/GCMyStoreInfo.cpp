//////////////////////////////////////////////////////////////////////////////
// Filename    : GCMyStoreInfo.cpp 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCMyStoreInfo.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
GCMyStoreInfo::~GCMyStoreInfo() 
	throw ()
{
	__BEGIN_TRY 

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCMyStoreInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read(m_OpenUI);
	m_pInfo->read( iStream, false );

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCMyStoreInfo::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write(m_OpenUI);
	m_pInfo->write( oStream, false );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCMyStoreInfo::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCMyStoreInfoHandler::execute( this , pPlayer );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCMyStoreInfo::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCMyStoreInfo(";
	msg << ")";

	return msg.toString();
		
	__END_CATCH
}
