#pragma once

namespace ad
{
	class ConnectionParticle;

	class ConnectionPortal
	{
	public:
		/**
		 * \brief The destructor.
		 */
		virtual ~ConnectionPortal() = default;

		virtual void send(ConnectionParticle& request) = 0;
		virtual void receive(ConnectionParticle& request) = 0;
	};
}
