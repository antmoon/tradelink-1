#include "StdAfx.h"
#include "TLOrder.h"
#include "Util.h"

namespace TradeLinkServer
{

	TLOrder::TLOrder(void)
	{
		symbol = "";
		TIF = "DAY";
		size = 0;
		price = 0;
		stop = 0;
		comment = "";
		date = 0;
		time = 0;
		sec = 0;
		security = "STK";
		currency = "USD";
		account = "";
		exchange = "NYSE";
		localsymbol = "";
	}

	bool TLOrder::isValid()
	{
		return (symbol!="") && (size!=0);
	}

	CString TLOrder::Serialize()
	{
		CString sde = (this->side) ? CString("True") : CString("False");
		CString m;
		// sym,side,size,price,stop,user,exch,acct,sect,curr,lsym,id
		m.Format(_T("%s,%s,%i,%f,%f,%s,%s,%s,%s,%s,%s,%u,%s,%i,%i,%i"),symbol,sde,size,price,stop,comment,exchange,account,security,currency,localsymbol,id,TIF,date,time,sec);
		return m;
	}

	TLOrder::~TLOrder(void)
	{
	}

	TLOrder TLOrder::Deserialize(CString message)
	{
		TLOrder o;
		std::vector<CString> r;
		gsplit(message,_T(","),r);
		o.account = r[oACCT];
		o.comment = r[oUSER];
		o.currency = r[oCURR];
		o.exchange = r[oEXCH];
		o.price = _tstof(r[oPRCE].GetBuffer());
		o.security = r[oSECT];
		CString sde = r[oSIDE];
		o.side = (sde.CompareNoCase(_T("True"))==0);
		o.size = _tstoi(r[oSIZE].GetBuffer());
		o.stop = _tstof(r[oSTOP].GetBuffer());
		o.symbol = r[oSYM];
		o.localsymbol = r[oLSYM];
		o.id = _tstoi(r[oID].GetBuffer());
		o.TIF = r[oTIF];
		o.date = _tstoi(r[oDate].GetBuffer());
		o.time = _tstoi(r[oTime].GetBuffer());
		o.sec = _tstoi(r[oSec].GetBuffer());
		return o;
	}

}

