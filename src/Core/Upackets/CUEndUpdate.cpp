//--------------------------------------------------------------------------------
// 
// Filename    : CUEndUpdate.cpp 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "CUEndUpdate.h"


//--------------------------------------------------------------------------------
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void CUEndUpdate::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}


//--------------------------------------------------------------------------------
// �������κ��� ���� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//--------------------------------------------------------------------------------
void CUEndUpdate::read ( Socket * pSocket ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}

	    
//--------------------------------------------------------------------------------
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//--------------------------------------------------------------------------------
void CUEndUpdate::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__END_CATCH
}


//--------------------------------------------------------------------------------
// execute packet's handler
//--------------------------------------------------------------------------------
void CUEndUpdate::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	CUEndUpdateHandler::execute ( this , pPlayer );
		
	__END_CATCH
}


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string CUEndUpdate::toString () const
	throw ()
{
	StringStream msg;

	msg << "CUEndUpdate("
		<< ")";

	return msg.toString();
}