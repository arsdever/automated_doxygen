#pragma once
namespace ad
{
	template <typename bytebuf_t>
	class ConnectionParticle;

	template <typename bytebuf_t>
	class ConnectionPortal
	{
	public:
		/**
		 * @brief The destructor.
		 */
		virtual ~ConnectionPortal() = default;
		virtual void send(ConnectionParticle<bytebuf_t> &request) = 0;
		virtual void receive(ConnectionParticle<bytebuf_t> &request) = 0;
	};
}
