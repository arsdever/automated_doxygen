#pragma once
#include <transferable.h>

namespace ad
{
	class ByteBuf;

	class ConnectionParticle : public Transferable
	{
		virtual ByteBuf const& uri() const = 0;
		virtual ByteBuf const& host() const = 0;
		virtual ByteBuf const& request() const = 0;
		virtual ByteBuf const& response() const = 0;
		virtual void setRequest(ByteBuf const &request) = 0;
		virtual void setResponse(ByteBuf const &response) = 0;
	};
}
