#pragma once

namespace ad
{
	/**
	 * \brief This function copies a *size* count of bites from address *from* to address *to*
	 * \param from the source address of bytes
	 * \param to the target address
	 * \param size count of bytes to be copied
	 * \see memset(char*, int const, char const)
	 */
	inline void memcpy(char const *from, char *to, int const size)
	{
		for (int i = 0; i < size; ++i)
		{
			to[i] = from[i];
		}
	}

	/**
	 * \brief This function sets the same *byte* by *size* counts into *buf*
	 * \param buf the target memory block
	 * \param size count of bytes to be set
	 * \param byte the value to be set
	 * \see memcpy(char const*, char*, int const)
	 */
	inline void memset(char *buf, int const size, char const byte)
	{
		for (int i = 0; i < size; ++i)
		{
			buf[i] = byte;
		}
	}

	/**
	 * \brief This interface encapsulates the char* structure for manipulations.
	 */
	class ByteBuf
	{
	public:
		/**
		 * \brief The destructor.
		 */
		virtual ~ByteBuf() = default;

		/**
		 * \brief Get the source data.
		 * \return the source data
		 * \see constData()
		 */
		virtual char* data() = 0;

		/**
		 * \brief Get const pointer to the source data.
		 * \return the source data
		 * \see data()
		 */
		virtual char const* constData() const = 0;

		/**
		 * \brief Append bytes at the end of the buffer.
		 * \see remove()
		 */
		virtual void append(char) = 0;

		/**
		 * \brief Remove a byte at the end.
		 * \return the removed byte
		 * \see append()
		 */
		virtual char remove() = 0;

		/**
		 * \brief Get size of the buffer.
		 * \return the size of the buffer
		 */
		virtual int size() const = 0;

		/**
		 * \brief Get byte from the buffer at the specified index.
		 * \param index the index of the byte in the buffer counted from 0
		 * \return the byte
		 * \see data()
		 * \see constData()
		 * \see size()
		 */
		virtual char at(int index) const = 0;

		/**
		 * \brief Implementation for const objects must return the constData.
		 * \return the source data
		 * \see constData()
		 */
		char const* data() const { return constData(); }

	protected:
		/**
		 * \brief Get the buffer's capacity.
		 * \return the buffer's capacity
		 */
		virtual int capacity() const = 0;
	};
}
