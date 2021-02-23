//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddStoreItem.cpp 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCAddStoreItem.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
GCAddStoreItem::~GCAddStoreItem() 
	throw ()
{
	__BEGIN_TRY 

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCAddStoreItem::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	iStream.read(m_OwnerObjectID);
	iStream.read(m_Index);
	m_Item.read(iStream);

	__END_CATCH
}
		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCAddStoreItem::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	oStream.write(m_OwnerObjectID);
	oStream.write(m_Index);
	m_Item.write(oStream);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCAddStoreItem::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAddStoreItemHandler::execute( this , pPlayer );

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCAddStoreItem::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCAddStoreItem(";
	msg << ")";

	return msg.toString();
		
	__END_CATCH
}
