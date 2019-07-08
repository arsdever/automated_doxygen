#pragma once
#include <transferable.h>

namespace ad
{
	template <typename BYTE_ARRAY_TYPE>
	class ConnectionParticle : public Transferable<BYTE_ARRAY_TYPE>
	{
		virtual BYTE_ARRAY_TYPE const& uri() const = 0;
		virtual BYTE_ARRAY_TYPE const& host() const = 0;
		virtual BYTE_ARRAY_TYPE const& request() const = 0;
		virtual BYTE_ARRAY_TYPE const& response() const = 0;
		virtual void setRequest(BYTE_ARRAY_TYPE const &request) = 0;
		virtual void setResponse(BYTE_ARRAY_TYPE const &response) = 0;
	};
}
