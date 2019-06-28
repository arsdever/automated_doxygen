#pragma once

#include <string>

namespace ad
{
	/**
	 * \brief This interface used to transfer the notifications using the Notify interface.
	 * \see Notify
	 */
	class Notification
	{
	public:
		/**
		 * \brief The destructor.
		 */
		virtual ~Notification() = default;

		/**
		 * \brief This function is used to get the notification body from the notification.
		 * \return the notification body
		 */
		virtual char const* body() = 0;
	};
}
