#pragma once
#include <transferable.h>

namespace ad
{
	template <typename bytebuf_t>
	class ConnectionParticle : public Transferable<bytebuf_t>
	{
		virtual bytebuf_t const& uri() const = 0;
		virtual bytebuf_t const& host() const = 0;
		virtual bytebuf_t const& request() const = 0;
		virtual bytebuf_t const& response() const = 0;
		virtual void setRequest(bytebuf_t const &request) = 0;
		virtual void setResponse(bytebuf_t const &response) = 0;
	};
}
